#include "ReflectionGenerator.h"

TReflectionGenerator::TReflectionGenerator(const DParsedFolderData& FolderData)
	: m_FolderData(FolderData)
{
}

PVector<DTypeReflectionData> TReflectionGenerator::GenerateReflection()
{
	return {};
}
