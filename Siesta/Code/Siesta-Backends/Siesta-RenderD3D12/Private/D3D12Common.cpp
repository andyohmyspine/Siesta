#include "D3D12Common.h"

PArray<DXGI_FORMAT, PF_MAX> GDxgiFormatMapping;
void InitializeFormatMapping()
{
	GDxgiFormatMapping[PF_UNKNOWN] = DXGI_FORMAT_UNKNOWN;
	GDxgiFormatMapping[PF_RGBA8_UNORM] = DXGI_FORMAT_R8G8B8A8_UNORM;
	GDxgiFormatMapping[PF_RGBA32_FLOAT] = DXGI_FORMAT_R32G32B32A32_FLOAT;
	GDxgiFormatMapping[PF_DEPTH_STENCIL] = DXGI_FORMAT_D24_UNORM_S8_UINT;
}
S_ASSERT_LAST_PIXEL_FORMAT(PF_DEPTH_STENCIL);
