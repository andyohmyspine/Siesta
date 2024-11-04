#pragma once

#include "CoreAll.h"
#include "CPUBlob.h"
#include "Siesta.RenderCoreAPI.h"

class SShader;
namespace Detail
{
	SIESTA_RENDERCORE_API void SetShaderByteCode(SShader* Shader, PUniquePtr<SCPUBlob>&& ByteCode);
}

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

class SIESTA_RENDERCORE_API SShader : public SIntrusiveRefCounted
{
public:
	SShader(const TString& Path, const TString& EntryPoint, EShaderStage::Type Stage);

protected:
	PUniquePtr<SCPUBlob> m_ByteCode;
	TString m_Path;
	TString m_EntryPoint;
	EShaderStage::Type m_Stage;

	friend void Detail::SetShaderByteCode(SShader*, PUniquePtr<SCPUBlob>&&);
};