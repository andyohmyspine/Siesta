#include "FolderParser.h"
#include "Object.h"

TFolderParser::TFolderParser(const TPath& FolderPath)
	: m_FolderPath(FolderPath)
{
}

DParsedFolderData TFolderParser::GenerateFolderInfo()
{
	DParsedFolderData FolderData{};
	FolderData.FolderPath = m_FolderPath.string();
	

	// Go recursively over every file in project
	for (const auto& Entry : TRecursiveDirectoryIterator(m_FolderPath))
	{
		const TPath& FilePath = Entry.path();
		if (FilePath.extension() != ".h")
		{
			continue;
		}
	}

	return FolderData;
}
