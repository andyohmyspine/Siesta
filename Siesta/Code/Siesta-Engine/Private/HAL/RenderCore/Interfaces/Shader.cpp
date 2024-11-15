#include "HAL/RenderCore/Interfaces/SiestaShader.h"

void Detail::SetShaderByteCode(SShader* Shader, PUniquePtr<SCPUBlob>&& ByteCode)
{
	Shader->m_ByteCode = std::move(ByteCode);
}

SShader::SShader(const TString& Path, const TString& EntryPoint, EShaderStage::Type Stage)
	: m_Path(Path)
	, m_EntryPoint(EntryPoint)
	, m_Stage(Stage)
{
}
