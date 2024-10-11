#include "ReflectionGenerator.h"

TReflectionGenerator::TReflectionGenerator(const DParsedFolderData& FolderData)
	: m_FolderData(FolderData)
{
}

PVector<DTypeReflectionData> TReflectionGenerator::GenerateReflection()
{
	GenerateHeaders();
	GenerateSources();

	return m_ReflectionData;
}

static TString GenerateFileIDString(const DParsedTypeInfo& Type)
{
	return fmt::format("_{}_", Type.File);
}

static TString GenerateClassString(const DParsedTypeInfo& Type)
{
	
}

void TReflectionGenerator::GenerateHeaders()
{
	for (const auto& Type : m_FolderData.Types)
	{
		
	}
}

void TReflectionGenerator::GenerateSources()
{

}
