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
	PVector<DSourceText> GenerateSources();

private:
	DParsedFolderData m_FolderData;
};