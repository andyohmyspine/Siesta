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
}

SD3D12RenderDevice::~SD3D12RenderDevice()
{
}
