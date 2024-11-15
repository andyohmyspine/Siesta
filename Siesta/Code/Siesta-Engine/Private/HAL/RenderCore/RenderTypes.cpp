#include "HAL/RenderCore/RenderTypes.h"

const PArray<DPixelFormatData, PF_MAX> GPixelFormatData = {
	{	
		{ PF_UNKNOWN, 0, 0, 0 },
		{ PF_RGBA8_UNORM, 1, 4, 4 },
		{ PF_RGBA32_FLOAT, 4, 4, 16},
		{ PF_DEPTH_STENCIL, 4, 2, 4}, 
	}
};
S_ASSERT_LAST_PIXEL_FORMAT(PF_DEPTH_STENCIL);