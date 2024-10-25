#include "D3D12RenderDevice.h"
#include <cstdlib>

SD3D12RenderDevice::SD3D12RenderDevice()
{
	// Create DXGI factory
	ThrowIfFailed(CreateDXGIFactory2(0, IID_PPV_ARGS(&m_Factory)));

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
}

SD3D12RenderDevice::~SD3D12RenderDevice()
{
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
	ID3D12CommandList* CmdLists[] = {m_GraphicsCommandList.Get()};
	m_DirectCommandQueue->ExecuteCommandLists(_countof(CmdLists), CmdLists);
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
