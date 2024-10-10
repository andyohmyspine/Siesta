#include "FolderParser.h"
#include "Object.h"

#include <fstream>

TFolderParser::TFolderParser(const TPath& FolderPath)
	: m_FolderPath(FolderPath)
{
}

DParsedFolderData TFolderParser::GenerateFolderInfo()
{
	m_OutData.FolderPath = m_FolderPath.string();

	// Go recursively over every file in project
	for (const auto& Entry : TRecursiveDirectoryIterator(m_FolderPath))
	{
		const TPath& FilePath = Entry.path();
		if (FilePath.extension() != ".h")
		{
			continue;
		}

		// Found a header file

		// 1. Read file to buffer
		std::ifstream File(FilePath);
		TStringStream FileSS;
		FileSS << File.rdbuf();
		TString FileContents = FileSS.str();

		// 2. Scan file for classes and structs
		ReadFileTypes(FileContents);	

		// 3. See if a class contains expose_class macro
		// 4. Add it to the reflection database
	}

	return m_OutData;
}

void TFolderParser::ReadFileTypes(const TString& FileContents)
{
	
}
