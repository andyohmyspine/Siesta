#include "SiestaCore.h"
#include "SiestaFilesystem.h"

#include "FolderParser.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <future>
#include <format>
#include <chrono>
#include "ReflectedTypeDatabase.h"
#include "HeaderGenerator.h"
#include "SourceGenerator.h"

inline static PVector<TString> SplitFilePaths(const TString& String)
{
	PVector<TString> Output;

	TStringStream SS(String);

	TString Token;
	const char Delimiter = '|';
	while (std::getline(SS, Token, Delimiter))
	{
		Output.push_back(std::move(Token));
	}

	return Output;
}

static void WriteStringToFile(const TString& FilePath, const TString& Text)
{
	std::ofstream File(FilePath);
	if (!File.is_open())
	{
		Debug::Critical("Failed to open file {} for writing.", FilePath);
	}
	File << Text << '\n';
	File.flush();
}

int32 main(int32 ArgCount, char* const* ArgValues)
{
	Debug::Trace(" ----------------------------------------------------------\n");
	Debug::Trace(" -- Starting reflection generation for Siesta workspace. --\n");
	Debug::Trace(" ----------------------------------------------------------\n");

	const auto BeginTimePoint = std::chrono::high_resolution_clock::now();

	PVector<TString> ProjectPaths = SplitFilePaths(SIESTA_REFLECTION_FOLDERS);

	TAsyncExecutor Executor{};
	TAsyncGraph Graph{};

	// Generate folder info with reflection data
	DProtectedList<DParsedFolderData> ParsedFolderDatas;
	{
		// Walk through all paths and read folder files
		for (const TString& ProjectPath : ProjectPaths)
		{
			// Read folder info
			Graph.emplace(
				[CopiedPath = ProjectPath, &ParsedFolderDatas]
				{
					Debug::Trace(" - Generating folder info for folder: {}", CopiedPath);
					SFolderParser Parser(CopiedPath);
					ParsedFolderDatas.PushBack((Parser.GenerateFolderInfo()));
				});
		}
	}

	Executor.run(Graph);
	Executor.wait_for_all();
	Graph.clear();

	// Collect all types
	if (!std::filesystem::exists(SIESTA_REFLECTION_OUTPUT))
	{
		std::filesystem::create_directory(SIESTA_REFLECTION_OUTPUT);
	}

	for (const DParsedFolderData& FolderData : ParsedFolderDatas)
	{
		if (FolderData.ContainsReflection)
		{
			Graph.emplace(
				[&]
				{
					SHeaderGenerator HeaderGenerator(FolderData);
					PVector<DHeaderText> Headers = HeaderGenerator.GenerateHeaders();

					for (const DHeaderText& Header : Headers)
					{
						WriteStringToFile(FormatString("{}/{}.gen.h", SIESTA_REFLECTION_OUTPUT, Header.HeaderName), Header.HeaderText);
					}
				});

			Graph.emplace(
				[&]
				{
					SSourceGenerator SourceGenerator(FolderData);
					PVector<DSourceText> Sources = SourceGenerator.GenerateSources();

					for (const DSourceText& Source : Sources)
					{
						WriteStringToFile(FormatString("{}/{}.gen.cpp", SIESTA_REFLECTION_OUTPUT, Source.FileName), Source.FileText);
					}
				});
		}
	}

	Executor.run(Graph);
	Executor.wait_for_all();

	const auto EndTimePoint = std::chrono::high_resolution_clock::now();
	const auto TimeDifference = EndTimePoint - BeginTimePoint;
	const auto Milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(TimeDifference);

	Debug::Trace(" - Reflection generation took {} seconds\n", (double)Milliseconds.count() * 0.001);

	return 0;
}