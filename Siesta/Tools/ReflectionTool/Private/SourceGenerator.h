#pragma once
#include "FolderParser.h"

struct DSourceText
{
	TString FileName;
	TString FileText;
};

class SSourceGenerator
{
public:
	SSourceGenerator(const DParsedFolderData& FolderData);
	PDynArray<DSourceText> GenerateSources();

private:
	DParsedFolderData m_FolderData;
};