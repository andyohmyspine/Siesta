#include "SiestaCore.h"
#include "SiestaFilesystem.h"

#include "FolderParser.h"

#include <iostream>
#include <sstream>
#include <future>
#include <format>
#include "ReflectionGenerator.h"

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

int32 main(int32 ArgCount, char* const* ArgValues)
{
	PVector<TString> ProjectPaths = SplitFilePaths(SIESTA_REFLECTION_FOLDERS);

	TAsyncExecutor Executor{};
	TAsyncGraph Graph{};

	// Generate folder info
	DProtectedList<DParsedFolderData> ParsedFolderDatas;
	DProtectedList<DTypeReflectionData> GeneratedReflectionDatas;

	{
		// Walk through all paths and read folder files
		for (const TString& ProjectPath : ProjectPaths)
		{
			// Read folder info
			auto ReadFolderTask = Graph.emplace(
				[CopiedPath = ProjectPath, &ParsedFolderDatas]
				{
					std::cout << std::format("Generating folder info for folder: {}\n", CopiedPath);
					TFolderParser Parser(CopiedPath);
					ParsedFolderDatas.PushBack((Parser.GenerateFolderInfo()));
				});

			// Generate reflection for folder
			auto GenerateReflectionTask = Graph.emplace(
				[&ParsedFolderDatas, ProjectPath, &GeneratedReflectionDatas]
				{
					std::cout << std::format("Generating reflection info for folder: {}\n", ProjectPath);

					TReflectionGenerator Generator(*ParsedFolderDatas.FindByPredicate([&ProjectPath](const auto& Value) { return Value.FolderPath == ProjectPath; }));
					PVector<DTypeReflectionData> ReflectionData = Generator.GenerateReflection();
					for (DTypeReflectionData& Data : ReflectionData)
					{
						GeneratedReflectionDatas.PushBack(Data);
					}
				});

			GenerateReflectionTask.succeed(ReadFolderTask);
		}
	}

	Executor.run(Graph);
	Executor.wait_for_all();

	return 0;
}