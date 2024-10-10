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
	DParsedFolderData m_FolderData;
};