#pragma once

#include "ShaderCompiler.h"

#include <Unknwnbase.h>
#include <dxcapi.h>

#include <wrl.h>

using Microsoft::WRL::ComPtr;

class SDXCShaderCompiler : public IShaderCompiler
{
public:
	SDXCShaderCompiler();

	virtual DCompiledData CompileShader(const TString& Path, const TString& EntryPoint, ECompilerShaderStage::Type Stage) override;
	virtual void ClearCompiledData(DCompiledData* Data) override;

private:
	ComPtr<IDxcUtils> m_Utils;
	
};