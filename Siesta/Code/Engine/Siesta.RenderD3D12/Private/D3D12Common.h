#pragma once

#include "SiestaCore.h"

#include <directx/d3d12.h>
#include <directx/d3dx12.h>
#include <dxgi1_6.h>

#include <comdef.h>
#include <wrl.h>

inline void ThrowIfFailed(HRESULT Result)
{
	if (FAILED(Result))
	{
		_com_error Error(Result);
		Debug::Critical("HRESULT failed with error message: {}", Result);
	}
}

template<typename T>
using PCom = Microsoft::WRL::ComPtr<T>;