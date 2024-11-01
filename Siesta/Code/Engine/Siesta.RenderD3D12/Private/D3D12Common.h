#pragma once

#include "CoreAll.h"

#include <directx/d3d12.h>
#include <directx/d3dx12.h>
#include <dxgi1_6.h>

#include <comdef.h>
#include <wrl.h>

inline constexpr uint8 SIESTA_NUM_FRAMES_IN_FLIGHT = 3;
extern uint8 GCurrentFrameInFlight;
extern uint64 GCurrentFrameIndex;

inline constexpr uint8 SIESTA_SWAP_CHAIN_BUFFER_COUNT = 3;

inline void AdvanceFrameInFlight()
{
	GCurrentFrameInFlight = (GCurrentFrameInFlight + 1) % SIESTA_NUM_FRAMES_IN_FLIGHT;
}

inline uint8 GetNextFrameInFlightIndex()
{
	return (GCurrentFrameInFlight + 1) % SIESTA_NUM_FRAMES_IN_FLIGHT;
}

inline uint64 GetNextFrameIndex() 
{
	return GCurrentFrameIndex + 1;
}

inline void ThrowIfFailed(HRESULT Result)
{
	if (FAILED(Result))
	{
		_com_error Error(Result);
#ifndef UNICODE
		Debug::Critical("HRESULT failed with error message: {}", Error.ErrorMessage());
#else
		char* MessageBuffer = new char[1024];
		wcstombs(MessageBuffer, Error.ErrorMessage(), 1024);
		Debug::Critical("HRESULT failed with error message: {}", MessageBuffer);
#endif
	}
}

template<typename T>
using PCom = Microsoft::WRL::ComPtr<T>;