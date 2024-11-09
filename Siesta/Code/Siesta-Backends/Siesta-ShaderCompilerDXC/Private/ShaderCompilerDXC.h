#pragma once

#include "HAL/RenderCore/ShaderCompiler.h"

#include <Unknwnbase.h>
#include <dxcapi.h>

#include <wrl.h>

using Microsoft::WRL::ComPtr;

class SDXCShaderCompiler : public IShaderCompiler
{
public:
	SDXCShaderCompiler();

	virtual DCompiledData CompileShader(const SShaderCompilerEnvironmentConfiguration& Env, const TString& Path, const TString& EntryPoint, EShaderStage::Type Stage) override;
	virtual void ClearCompiledData(DCompiledData* Data) override;

private:
	ComPtr<IDxcUtils> m_Utils;
	
};