#pragma once

// DXGI_FORMAT coded.
enum EPixelFormat : uint8
{
	PF_UNKNOWN = 0,
	PF_RGBA8_UNORM = 1,
	PF_RGBA32_FLOAT = 2,
	PF_DEPTH_STENCIL = 3,
	PF_MAX,
};
#define S_ASSERT_LAST_PIXEL_FORMAT(Name) static_assert(PF_MAX - 1 == Name, "Should probably check in other places where mappings are created.")

struct DPixelFormatData
{	
	EPixelFormat Format;
	uint32 ComponentSizeBytes;
	uint32 ComponentCount;
	uint32 FormatSizeBytes;
};

extern const PArray<DPixelFormatData, PF_MAX> GPixelFormatData;

namespace EShaderStage
{
	enum Type : uint8
	{
		None = 0,
		VertexShader = 1 << 0,
		PixelShader = 1 << 1,
		ComputeShader = 1 << 2,
	};
	using Mask = uint8;
} // namespace EShaderStage
