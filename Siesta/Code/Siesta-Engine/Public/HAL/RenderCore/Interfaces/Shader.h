#pragma once

#include "Core.h"
#include "HAL/RenderCore/RenderTypes.h"
#include "HAL/RenderCore/CPUBlob.h"

class SShader;
namespace Detail
{
	void SetShaderByteCode(SShader* Shader, PUniquePtr<SCPUBlob>&& ByteCode);
}

class SShader : public SIntrusiveRefCounted
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
