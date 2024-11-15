#pragma once

#include "GPUResourceBase.h"
#include "HAL/RenderCore/RenderTypes.h"

enum class EGPUTextureType
{
	Texture2D,
	Texture2DArray,
	Texture3D,
	TextureCube,
	TextureCubeArray,
};

struct DGPUTextureDesc
{
	TString DebugName;
	EGPUTextureType Type;
	uint32 Width;
	uint32 Height;
	uint32 Depth;
	uint32 ArrayLayers;
	uint32 MipLevels;
	EPixelFormat PixelFormat;
};

struct DGPUTextureWriteData
{
	const void* Data;
	Math::XMUINT3 Offset;
	Math::XMUINT3 Size;
};

class SGPUTextureResource : public SGPUResourceBase
{
public:
	SGPUTextureResource(const DGPUTextureDesc& Desc);

	const DGPUTextureDesc& GetDesc() const { return m_Desc; }

private:
	DGPUTextureDesc m_Desc {};
};