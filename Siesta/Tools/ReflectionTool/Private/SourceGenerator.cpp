#include "SourceGenerator.h"

#include <ranges>
#include "ReflectedTypeDatabase.h"

SSourceGenerator::SSourceGenerator(const DParsedFolderData& FolderData)
	: m_FolderData(FolderData)
{

}

static bool HasMetaSpecifier(const TString& Specifier, const auto& Range)
{
	return std::ranges::find_if(Range, [&Specifier](const auto& Elem) { return Elem == Specifier; }) != Range.end();
}

static void GenerateTypeFields(const DParsedTypeInfo& TypeInfo, TStringStream& Stream)
{
	for (const DParsedVariableInfo& Field : TypeInfo.Fields)
	{
		TString TypeName;
		if (Field.TypeParams.empty())
		{
			TypeName = Field.Type;

		}
		else
		{
			TString ParamsString = Field.TypeParams[0];
			for (uint64 Index = 1; Index < Field.TypeParams.size(); ++Index)
			{
				ParamsString += ',';
				ParamsString += Field.TypeParams[Index];
			}

			TypeName = FormatString("{}<{}>", Field.Type, ParamsString);
		}

		bool IsPointer = false;
		if ((Field.DecoratorMask & TD_Pointer) != 0)
		{
			IsPointer = true;
			TypeName += '*';
		}

		Stream << FormatString("\t\t// ----- {} -----\n", Field.Name);
		Stream << FormatString("\t\tclass : public SField_TemplateBase<{}>\n", TypeName);
		Stream << "\t\t{\n";
		{
			/**
			 * Getter
			 */
			if (!IsPointer)
			{

				Stream << FormatString("\t\t\tvirtual const {}& GetValue(const SObject* Object) const override", TypeName);
				Stream << "{";
				{
					Stream << FormatString("return static_cast<const {}*>(Object)->{};", Field.MemberOf, Field.Name);
				}
				Stream << "}\n";
			}
			else
			{
				Stream << FormatString("\t\t\tvirtual {} const& GetValue(const SObject* Object) const override", TypeName);
				Stream << "{";
				{
					Stream << FormatString("return static_cast<const {}*>(Object)->{};", Field.MemberOf, Field.Name);
				}
				Stream << "}\n";
			}

			/**
			 * Setter
			 */
			if (IsPointer)
			{
				Stream << FormatString("\t\t\tvirtual void SetValue(SObject* Object, {} const& Value) override", TypeName);
				Stream << "{";
				{
					Stream << FormatString("static_cast<{}*>(Object)->{} = Value;", Field.MemberOf, Field.Name);
				}
				Stream << "}\n";
			}
			else
			{
				Stream << FormatString("\t\t\tvirtual void SetValue(SObject* Object, const {}& Value) override", TypeName);
				Stream << "{";
				{
					Stream << FormatString("static_cast<{}*>(Object)->{} = Value;", Field.MemberOf, Field.Name);
				}
				Stream << "}\n";
			}

			// Misc functions
			Stream << FormatString("\t\t\tvirtual TStringView GetName() const override", TypeName);
			Stream << "{";
			{
				Stream << FormatString("return \"{}\";", Field.Name);
			}
			Stream << "}\n";

			Stream << FormatString("\t\t\tvirtual TStringView GetTypeName() const override", TypeName);
			Stream << "{";
			{
				Stream << FormatString("return \"{}\";", TypeName);
			}
			Stream << "}\n";
		}
		Stream << "\t\t}";
		Stream << FormatString("{}_Var;\n", Field.Name);
		Stream << FormatString("\t\tAddField(\"{0}\", new decltype({0}_Var)());\n\n", Field.Name);
	}
}

PVector<DSourceText> SSourceGenerator::GenerateSources()
{
	PVector<DSourceText> Output;

	PHashMap<TString, PVector<DParsedTypeInfo>> FileToTypeMap;

	for (const auto& Type : m_FolderData.Types)
	{
		FileToTypeMap[Type.File].push_back(Type);
	}

	for (const TString& FileName : FileToTypeMap | std::views::keys)
	{
		TStringStream SourceStream;
		SourceStream << "// This file was generated by Siesta.ReflectionTool. DO NOT MODIFY - IT'S POINTLESS. It will be regenerated on the next build.\n\n";
		SourceStream << FormatString("#include \"SiestaCore.h\"\n");
		SourceStream << FormatString("#include \"TypeRegistry.h\"\n");

		for (const auto& Type : FileToTypeMap.at(FileName))
		{
			const bool IsAbstract = HasMetaSpecifier("abstract", Type.MetaSpecifiers);
			const bool IsObject = SReflectedTypeDatabase::Get().IsChildOf(Type.Name, "SObject");

			SourceStream << FormatString("SType* {}::GetStaticType()", Type.Name) << "{ static SType* Out = STypeRegistry::GetType(\"" << Type.Name << "\"); return Out; }\n";

			// Create type
			SourceStream << FormatString("class SType_{} : public SType\n", Type.Name);
			SourceStream << "{\n";
			{
				SourceStream << FormatString("public:\n\tSType_{}()", Type.Name);
				// Constructor
				SourceStream << "\t{\n";
				{
					SourceStream << FormatString("\t\tm_Name = \"{}\";\n", Type.Name);
					SourceStream << FormatString("\t\tm_Instantiate = [](const SObjectInfo& ObjectInfo)");

					if (!IsAbstract)
					{
						SourceStream << '{' << " return new " << Type.Name << "(ObjectInfo);" << " };\n";
					}
					else
					{
						SourceStream << '{' << " Debug::Critical(\"Cannot instantiate abstract type.\"); return nullptr; };\n";
					}

					SourceStream << "\n\t\t// ---------- Fields ------------- \n\n";
					GenerateTypeFields(Type, SourceStream);
				}

				// End of the constructor
				SourceStream << "\t}\n";

				if (!Type.Parent.empty())
				{
					SourceStream << "\tvirtual TStringView GetParentName() const override { " << "return "
						<< FormatString("\"{}\";", Type.Parent) << "}\n";

					SourceStream << "\tvirtual SType* GetParentType() const override { " << "return STypeRegistry::Get().GetType(TString(GetParentName())); }\n";
				}
				else
				{
					SourceStream << "\tvirtual TStringView GetParentName() const override { " << "return {}; }\n";
					SourceStream << "\tvirtual SType* GetParentType() const override { " << "return nullptr; }\n";
				}
			}
			SourceStream << "};\n";
			// Type registrar
			SourceStream << FormatString("SIESTA_REGISTER_OBJECT_TYPE({})\n", Type.Name);
		}

		DSourceText SourceText
		{
			.FileName = FileName,
			.FileText = SourceStream.str()
		};
		Output.push_back(SourceText);
	}

	return Output;
}

