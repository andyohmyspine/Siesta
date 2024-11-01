#include "D3D12RenderDevice.h"
#include <cstdlib>
#include "D3D12SwapChain.h"
#include "Resources/D3D12BufferResource.h"
#include "D3D12RenderAPI.h"

SD3D12RenderDevice::SD3D12RenderDevice()
{
#if !defined(NDEBUG) || defined(SIESTA_ENABLE_GPU_VALIDATION)
	PCom<ID3D12Debug> DebugInterface;
	ThrowIfFailed(D3D12GetDebugInterface(IID_PPV_ARGS(&DebugInterface)));
	if (DebugInterface)
	{
		DebugInterface->EnableDebugLayer();
	}

	UINT DXGIFlags = DXGI_CREATE_FACTORY_DEBUG;
#else
	UINT DXGIFlags = 0;
#endif

	// Create DXGI factory
	ThrowIfFailed(CreateDXGIFactory2(DXGIFlags, IID_PPV_ARGS(&m_Factory)));

	// Pick adapter
	ThrowIfFailed(m_Factory->EnumAdapterByGpuPreference(0, DXGI_GPU_PREFERENCE_HIGH_PERFORMANCE, IID_PPV_ARGS(&m_Adapter)));

	// Create device
	ThrowIfFailed(D3D12CreateDevice(m_Adapter.Get(), D3D_FEATURE_LEVEL_12_0, IID_PPV_ARGS(&m_Device)));

	DXGI_ADAPTER_DESC AdapterDesc;
	ThrowIfFailed(m_Adapter->GetDesc(&AdapterDesc));
	char DeviceNameBuffer[ARRAYSIZE(AdapterDesc.Description)] = {};
	wcstombs(DeviceNameBuffer, AdapterDesc.Description, ARRAYSIZE(DeviceNameBuffer));

	m_DeviceName = DeviceNameBuffer;
	Debug::Info("D3D12 Device created from {}", m_DeviceName);

	// Create the command queue and fence
	D3D12_COMMAND_QUEUE_DESC DirectQueueDesc = {};
	DirectQueueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
	ThrowIfFailed(m_Device->CreateCommandQueue(&DirectQueueDesc, IID_PPV_ARGS(&m_DirectCommandQueue)));

	// Create main fence
	ThrowIfFailed(m_Device->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&m_Fence)));

	InitCommandBlock();

	ThrowIfFailed(m_GraphicsCommandList->Close());

	// Create resource allocator
	m_ResourceAllocator = MakeShared<SD3D12ResourceAllocator>(m_Device.Get(), m_Adapter.Get());
}

SD3D12RenderDevice::~SD3D12RenderDevice()
{
	ClearPendingTransfers();
	FlushCommandQueue();
}

void SD3D12RenderDevice::FlushCommandQueue()
{
	if (HANDLE EventHandle = CreateEventEx(nullptr, nullptr, 0, EVENT_ALL_ACCESS))
	{
		m_FenceValue++;

		ThrowIfFailed(m_DirectCommandQueue->Signal(m_Fence.Get(), m_FenceValue));
		ThrowIfFailed(m_Fence->SetEventOnCompletion(m_FenceValue, EventHandle));
		WaitForSingleObject(EventHandle, INFINITE);

		CloseHandle(EventHandle);
	}
}

void SD3D12RenderDevice::SubmitWork_Simple()
{
	FlushPendingTransfers();

	ID3D12CommandList* CmdLists[] = { m_GraphicsCommandList.Get() };
	m_DirectCommandQueue->ExecuteCommandLists(_countof(CmdLists), CmdLists);
}

PSharedPtr<SSwapChain> SD3D12RenderDevice::CreateSwapChain(const IPlatformWindow* PlatformWindow)
{
	return MakeShared<SD3D12SwapChain>(this, PlatformWindow);
}

ID3D12CommandAllocator* SD3D12RenderDevice::GetComandAllocatorForCurrentFrameInFlight() const
{
	return m_FrameCommandAllocators.at(GCurrentFrameInFlight).Get();
}

ID3D12GraphicsCommandList* SD3D12RenderDevice::GetGraphicsCommandList() const
{
	return m_GraphicsCommandList.Get();
}

void SD3D12RenderDevice::SyncFrameInFlight()
{
	m_FrameFenceValues[GCurrentFrameInFlight] = ++m_FenceValue;
	ThrowIfFailed(m_DirectCommandQueue->Signal(m_Fence.Get(), m_FenceValue));
}

SGPUBufferResource* SD3D12RenderDevice::CreateBufferResource(const DGPUBufferDesc& Desc)
{
	return new SD3D12BufferResource(Desc);
}

void SD3D12RenderDevice::AddPendingBufferTransfer(DPendingBufferTransfer NewTransfer)
{
	if (!NewTransfer.DstResource)
	{
		return;
	}

	DGPUBufferDesc StagingDesc = NewTransfer.DstResource->GetDesc();
	StagingDesc.Mutability = EGPUBufferMutability::Staging;
	StagingDesc.DebugName = "TransferBuffer";

	NewTransfer.InternalSrcResource = (SD3D12BufferResource*)CreateBufferResource(StagingDesc);
	NewTransfer.DstResource->AddRef();

	m_PendingBufferTransfers[GetNextFrameInFlightIndex()].push_back(NewTransfer);
}

void SD3D12RenderDevice::ClearPendingTransfers()
{
	for (PDynArray<DPendingBufferTransfer>& Transfers : m_PendingBufferTransfers)
	{
		for (DPendingBufferTransfer& Transfer : Transfers)
		{
			Transfer.DstResource->Release();
			Transfer.InternalSrcResource->Release();
		}

		Transfers.clear();
	}
}

void SD3D12RenderDevice::InitCommandBlock()
{
	// Create command allocators
	for (uint8 Index = 0; Index < SIESTA_NUM_FRAMES_IN_FLIGHT; ++Index)
	{
		ThrowIfFailed(m_Device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&m_FrameCommandAllocators[Index])));
	}

	// Create the command list
	ThrowIfFailed(m_Device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, m_FrameCommandAllocators.at(0).Get(), nullptr, IID_PPV_ARGS(&m_GraphicsCommandList)));
}

void SD3D12RenderDevice::FlushPendingTransfers()
{
	static PDynArray<D3D12_RESOURCE_BARRIER> TransferBarriers;

	// Transition all transfer dests
	for (auto& Transfer : m_PendingBufferTransfers[GCurrentFrameInFlight])
	{
		// Transfer selected buffer to copy dest
		TransferBarriers.push_back(
			CD3DX12_RESOURCE_BARRIER::Transition(Transfer.DstResource->GetResource(), Transfer.InitialState, D3D12_RESOURCE_STATE_COPY_DEST));

		// Transfer staging buffer to copy source
		TransferBarriers.push_back(
			CD3DX12_RESOURCE_BARRIER::Transition(Transfer.InternalSrcResource->GetResource(), D3D12_RESOURCE_STATE_GENERIC_READ, D3D12_RESOURCE_STATE_COPY_SOURCE));
	}

	if (!TransferBarriers.empty())
	{
		m_GraphicsCommandList->ResourceBarrier((UINT)TransferBarriers.size(), TransferBarriers.data());
		TransferBarriers.clear();
	}

	for (const auto& Transfer : m_PendingBufferTransfers[GCurrentFrameInFlight])
	{
		m_GraphicsCommandList->CopyBufferRegion(
			Transfer.DstResource->GetResource(),
			0,
			Transfer.InternalSrcResource->GetResource(),
			0,
			Transfer.DstResource->GetDesc().ByteSize);

		TransferBarriers.push_back(
			CD3DX12_RESOURCE_BARRIER::Transition(Transfer.DstResource->GetResource(), D3D12_RESOURCE_STATE_COPY_DEST, Transfer.FinalState));
	}

	if (!TransferBarriers.empty())
	{
		m_GraphicsCommandList->ResourceBarrier((UINT)TransferBarriers.size(), TransferBarriers.data());
		TransferBarriers.clear();
	}

	// TODO: Need a way to notify buffer, that it was completed.
}

void EnqueueBufferTransfer(DPendingBufferTransfer Transfer)
{
	if (SD3D12RenderAPI* API = SRenderAPI::GetOrLoad<SD3D12RenderAPI>())
	{
		if (SD3D12RenderDevice* Device = (SD3D12RenderDevice*)API->GetDevice())
		{
			Device->AddPendingBufferTransfer(Transfer);
		}
	}
}
