#pragma once
#include "FolderParser.h"

struct DHeaderText
{
	TString HeaderName;
	TString HeaderText;
};

class SHeaderGenerator
{
public:
	SHeaderGenerator(const DParsedFolderData& FolderData);

	PVector<DHeaderText> GenerateHeaders() const;

private:
	const DParsedFolderData& m_FolderData;
};