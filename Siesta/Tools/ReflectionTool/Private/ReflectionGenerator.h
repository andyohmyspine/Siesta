#pragma once

#include "FolderParser.h"

struct DTypeReflectionData
{

};

class TReflectionGenerator
{
public:
	TReflectionGenerator(const DParsedFolderData& FolderData);

	PVector<DTypeReflectionData> GenerateReflection();

private:
	void GenerateHeaders();
	void GenerateSources();

	DParsedFolderData m_FolderData;
	PVector<DTypeReflectionData> m_ReflectionData;
};