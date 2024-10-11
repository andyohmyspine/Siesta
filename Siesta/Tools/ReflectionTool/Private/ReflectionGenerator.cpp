#include "ReflectionGenerator.h"

TReflectionGenerator::TReflectionGenerator(const DParsedFolderData& FolderData)
	: m_FolderData(FolderData)
{
}

PVector<DTypeReflectionData> TReflectionGenerator::GenerateReflection()
{
	for (const DParsedTypeInfo& Type : m_FolderData.Types)
	{
		// Generate SType for the class
	}
}
