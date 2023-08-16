#pragma once

#include <fstream>

#include "OutputSchema.h"

namespace OutputSchema
{
	void addProjectNode(tinyxml2::XMLElement* root, const char* nodeType, const std::string& fileName, const char* filterContents);

	class ModuleWriter
	{
	public:
		struct StackContext
		{
			bool IsNamespace = false;
			bool CurrentlyPrivate = false;
		};

		struct StackHandle
		{
			~StackHandle();

			void Bind(ModuleWriter& writer);

		private:
			size_t StackDepth = (size_t)-1;
			ModuleWriter* Writer = nullptr;
		};

		std::ofstream& Out;

		ModuleWriter(std::ofstream& out) : Out(out) {}
		~ModuleWriter();

		void PushNamespace(const std::string_view& name);
		void PushNamespace(StackHandle& handle, const std::string_view& name);
		void PushStruct(const std::string_view& name);
		void PushStruct(StackHandle& handle, const std::string_view& name);
		void PushEnum(const std::string_view& name);
		void PushEnum(StackHandle& handle, const std::string_view& name);
		void PushCollection(const std::string_view& name);
		void PushCollection(StackHandle& handle, const std::string_view& name);
		void PushLine();
		void PushMember(const SchemaClass& type);
		void PushMember(const std::string& type, const std::string_view& name, const std::string_view& value);
		void PushEnumValue(const std::string& name, const std::string_view& value, bool isLast);
		void PopStack();

		size_t GetStackDepth() const { return Stack.size(); }
		const auto& GetStack() const { return Stack; }

		std::string_view Indent() const { return { Indentation.data(), Indentation.size() }; }

	private:
		std::vector<StackContext> Stack;
		std::vector<char> Indentation;
	};

	void generateModuleNamespace(ModuleWriter& module, const std::string& currentNamespace);

	void generateClassDefinitions(const SchemaClass& schemaClass, ModuleWriter& module, const std::string& currentNamespace);

	void generateClassDeclarations(const SchemaClass& schemaClass, ModuleWriter& module, const std::string& currentNamespace, const std::string& classPath);

	void generateCollectionDefinitions(const SchemaCollection& schemaCollection, ModuleWriter& module, const std::string& currentNamespace);

	void generateCollectionDeclarations(const SchemaCollection& schemaCollection, ModuleWriter& module, const std::string& currentNamespace, const std::string& classPath);

	void generateClasses(const SchemaClass& schemaClass, tinyxml2::XMLElement* vcxprojRoot, tinyxml2::XMLElement* filtersRoot, const std::string& currentNamespace);

	void generateCollection(const SchemaCollection& schemaCollection, tinyxml2::XMLElement* vcxprojRoot, tinyxml2::XMLElement* filtersRoot, const std::string& currentNamespace);

	void generateItemsInNamespace(const SchemaNamespace& schemaNamespace, tinyxml2::XMLElement* vcxprojRoot, tinyxml2::XMLElement* filtersRoot, const std::string& currentNamespace = "Global");

	void generateGameData();
}