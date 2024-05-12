#pragma once

#include <vector>
#include <string_view>
#include <string>
#include <charconv>

namespace XmlLite
{
	struct XmlNode
	{
		size_t Start = (size_t)-1;
		std::string_view Name;
		size_t Line = (size_t)-1;
	};

	struct XmlAttribute
	{
		std::string_view Name;
		std::string_view Value;

		template <typename T>
		void Read(T& value) const;

		template <typename T>
		void Read(std::vector<T>& value) const;

		template <typename T>
		static void Read(const std::string_view& string, T& value);

		template <typename T>
		T Read() const;
	};

	template <size_t ArraySize>
	struct TaskCompletionStatus
	{
		bool FoundAttribute[ArraySize] = { false };
	};

	struct AttributeTaskBase
	{
		std::string_view Name;

		virtual void Read(const XmlAttribute* attribute) const = 0;
		virtual void Skipped() const = 0;
	};

	template <typename T>
	struct AttributeTask : public AttributeTaskBase
	{
		typedef T Type;

		T& Output;

		AttributeTask(const std::string_view& name, T& output) : Output(output)
		{
			Name = name;
		}

		void Read(const XmlAttribute* attribute) const override
		{
			attribute->Read<T>(Output);
		}

		void Skipped() const override {}
	};

	template <typename T>
	struct AttributeTaskWithDefault : public AttributeTaskBase
	{
		typedef T Type;

		T& Output;
		const T DefaultValue;

		AttributeTaskWithDefault(const std::string_view& name, T& output, const T& defaultValue) : Output(output), DefaultValue(defaultValue)
		{
			Name = name;
		}

		void Read(const XmlAttribute* attribute) const override
		{
			attribute->Read<T>(Output);
		}

		void Skipped() const override
		{
			Output = DefaultValue;
		}
	};

	template <typename T>
	struct AttributeHexTask : public AttributeTaskBase
	{
		typedef T Type;

		T& Output;
		size_t Offset;

		AttributeHexTask(const std::string_view& name, T& output, size_t offset) : Output(output)
		{
			Name = name;
			Offset = offset;
		}

		void Read(const XmlAttribute* attribute) const override
		{
			const std::string_view string = attribute->Value;

			std::from_chars(string.data() + Offset, string.data() + string.size(), Output, 16);
		}

		void Skipped() const override {}
	};

	template <typename T>
	struct AttributeHexTaskWithDefault : public AttributeTaskBase
	{
		typedef T Type;

		T& Output;
		const T DefaultValue;
		size_t Offset;

		AttributeHexTaskWithDefault(const std::string_view& name, T& output, const T& defaultValue, size_t offset) : Output(output), DefaultValue(defaultValue)
		{
			Name = name;
			Offset = offset;
		}

		void Read(const XmlAttribute* attribute) const override
		{
			const std::string_view string = attribute->Value;

			std::from_chars(string.data() + Offset, string.data() + string.size(), Output, 16);
		}

		void Skipped() const override
		{
			Output = DefaultValue;
		}
	};

	template <typename T>
	AttributeTask<T> Attribute(std::string_view name, T& output)
	{
		return AttributeTask<T>(name, output);
	}

	template <typename T>
	AttributeTaskWithDefault<T> Attribute(std::string_view name, T& output, const T defaultValue)
	{
		return AttributeTaskWithDefault<T>(name, output, defaultValue);
	}

	template <typename T>
	AttributeHexTask<T> AttributeHex(const std::string_view& name, T& output, size_t offset)
	{
		return AttributeHexTask<T>(name, output, offset);
	}

	template <typename T>
	AttributeHexTaskWithDefault<T> AttributeHex(const std::string_view& name, T& output, const T defaultValue, size_t offset)
	{
		return AttributeHexTaskWithDefault<T>(name, output, defaultValue, offset);
	}

	class XmlReader
	{
	public:
		struct StackMarker
		{
			size_t Index = (size_t)-1;
			size_t Start = 0;
		};
		
		enum class XmlErrorType
		{
			None,
			ExpectedNodeStart,
			ExpectedNodeEnd,
			ExpectedNodeName,
			ExpectedAttributeEquals,
			ExpectedAttributeValue,
			ExpectedAttributeValueEnd,
			ExpectedHeaderEnd,
			ExpectedClosingNode,
			UnexpectedHeader,
			UnexpectedClosingNode
		};

		void OpenDocument(const std::string_view& stream);

		const std::string_view& GetHeaderName() const { return HeaderName; }
		const std::vector<XmlAttribute>& GetHeaderAttributes() const { return HeaderAttributes; }
		XmlErrorType GetError() const { return Error; }
		bool HasError() const { return Error != XmlErrorType::None; }
		std::string GetErrorMessage() const;

		StackMarker GetStackMarker() const;
		const XmlNode* GetNextSibling(const StackMarker& marker = {});
		const XmlNode* GetNextSibling(const std::string_view& name, bool caseSensitive = true, const StackMarker& marker = {});
		const XmlNode* GetFirstChild();
		const XmlNode* GetFirstChild(const std::string_view& name, bool caseSensitive = true);
		const XmlAttribute* GetNextAttribute();
		const XmlAttribute* GetNextAttribute(const std::string_view& name, bool caseSensitive = true);
		void PopNode(size_t count = 1);
		std::string GetFullNodePath() const;

		size_t GetLineNumber() const { return LineNumber; }

		template <typename T>
		bool ReadAttribute(const std::string_view& name, T& value);

		template <typename T>
		bool ReadAttribute(const std::string_view& name, T& value, const T& defaultValue);

		template <typename T>
		T ReadAttributeValue(const std::string_view& name, const T& defaultValue);

		template <typename T>
		bool ReadAttributeHex(const std::string_view& name, T& value, size_t offset);

		template <typename T>
		bool ReadAttributeHex(const std::string_view& name, T& value, const T& defaultValue, size_t offset);

		template <typename T>
		T ReadAttributeValueHex(const std::string_view& name, const T& defaultValue, size_t offset);

		template <typename... TaskType>
		typename TaskCompletionStatus<sizeof...(TaskType)> ReadAttributes(const TaskType&... tasks);

	private:
		struct StackItem
		{
			XmlNode Node;
			size_t BranchStart = 0;
		};

		std::string_view Document;
		std::vector<StackItem> NodeTree;
		std::string_view HeaderName;
		std::vector<XmlAttribute> HeaderAttributes;
		XmlNode FileHeader;
		XmlNode NextNode;
		XmlAttribute LastAttribute;
		size_t CurrentIndex = 0;
		size_t LineNumber = 1;
		size_t LastLineStart = 0;
		bool IsReadingNode = false;
		bool FoundClosingNode = false;
		bool HasNoChildren = false;
		bool CurrentNodeSet = false;
		XmlErrorType Error = XmlErrorType::None;
		
		bool IsWhitespace();
		bool IsWhitespace(size_t index);
		bool IsNewLine();
		bool IsNewLine(size_t index);
		bool IsAlphanumeric();
		bool IsAlphanumeric(size_t index);
		bool SkipWhitespace();
		bool CanContinue();
		bool TryReadHeader();
		bool ReadName(std::string_view& name);
		bool ReadValue(std::string_view& name);
		bool TrySetError(XmlErrorType error); // Only sets if an error wasnt set before to prevent double setting
		bool TryReadAttribute(XmlAttribute& attribute, bool& foundAttribute);
		bool FinishCurrentNode();
		bool AdvanceToNextNode(bool allowHeader = false);
		bool TryFindClosingMarker(bool& foundMarker);
		bool ReadNextNode();
	};

	template <typename T>
	T XmlAttribute::Read() const
	{
		T value = {};
		
		Read(value);

		return value;
	}

	template <typename T>
	void XmlAttribute::Read(const std::string_view& string, T& value)
	{
		std::from_chars(string.data(), string.data() + string.size(), value);
	}

	template <typename T>
	void XmlAttribute::Read(T& value) const
	{
		Read<T>(Value, value);
	}

	template <>
	void XmlAttribute::Read<int>(const std::string_view& string, int& value);
	
	template <>
	void XmlAttribute::Read<unsigned int>(const std::string_view& string, unsigned int& value);
	
	template <>
	void XmlAttribute::Read<short>(const std::string_view& string, short& value);
	
	template <>
	void XmlAttribute::Read<unsigned short>(const std::string_view& string, unsigned short& value);
	
	template <>
	void XmlAttribute::Read<unsigned char>(const std::string_view& string, unsigned char& value);
	
	template <>
	void XmlAttribute::Read<signed char>(const std::string_view& string, signed char& value);

	template <>
	void XmlAttribute::Read<bool>(const std::string_view& string, bool& value);

	template <>
	void XmlAttribute::Read<long long>(const std::string_view& string, long long& value);
	
	template <>
	void XmlAttribute::Read<unsigned long long>(const std::string_view& string, unsigned long long& value);
	
	template <>
	void XmlAttribute::Read<float>(const std::string_view& string, float& value);
	
	template <>
	void XmlAttribute::Read<double>(const std::string_view& string, double& value);

	template <>
	void XmlAttribute::Read<std::string>(const std::string_view& string, std::string& value);

	template <>
	void XmlAttribute::Read<std::string_view>(const std::string_view& string, std::string_view& value);

	template <typename T>
	void XmlAttribute::Read(std::vector<T>& vector) const
	{
		if (Value.size() == 0)
			return;

		int i = 0;

		while (Value[i])
		{
			vector.push_back(Read<T>(std::string_view(Value.data() + i, Value.size() - i)));

			while (Value[i] && Value[i] >= '0' && Value[i] <= '9')
				++i;

			while (Value[i] && (Value[i] < '0' || Value[i] > '9'))
				++i;
		}
	}

	template <typename T>
	bool XmlReader::ReadAttribute(const std::string_view& name, T& value)
	{
		const XmlAttribute* attribute = GetNextAttribute(name);

		if (attribute == nullptr) return false;

		value = attribute->Read<T>();

		return true;
	}

	template <typename T>
	bool XmlReader::ReadAttribute(const std::string_view& name, T& value, const T& defaultValue)
	{
		const XmlAttribute* attribute = GetNextAttribute(name);

		value = defaultValue;

		if (attribute == nullptr) return false;

		value = attribute->Read<T>();

		return true;
	}

	template <typename T>
	T XmlReader::ReadAttributeValue(const std::string_view& name, const T& defaultValue)
	{
		T value = {};

		if (!ReadAttribute<T>(name, value))
			value = defaultValue;

		return value;
	}

	template <typename T>
	bool XmlReader::ReadAttributeHex(const std::string_view& name, T& value, size_t offset)
	{
		const XmlAttribute* attribute = GetNextAttribute(name);

		if (attribute == nullptr) return false;

		const std::string_view string = attribute->Value;

		std::from_chars(string.data() + offset, string.data() + string.size(), value, 16);

		return true;
	}

	template <typename T>
	bool XmlReader::ReadAttributeHex(const std::string_view& name, T& value, const T& defaultValue, size_t offset)
	{
		const XmlAttribute* attribute = GetNextAttribute(name);

		value = defaultValue;

		if (attribute == nullptr) return false;

		const std::string_view string = attribute->Value;

		std::from_chars(string.data() + offset, string.data() + string.size(), value, 16);

		return true;
	}

	template <typename T>
	T XmlReader::ReadAttributeValueHex(const std::string_view& name, const T& defaultValue, size_t offset)
	{
		T value = {};

		if (!ReadAttributeHex<T>(name, value, offset))
			value = defaultValue;

		return value;
	}

	template <typename... TaskType>
	typename TaskCompletionStatus<sizeof...(TaskType)> XmlReader::ReadAttributes(const TaskType&... tasks)
	{
		const size_t taskCount = sizeof...(TaskType);

		TaskCompletionStatus<taskCount> statuses;

		const AttributeTaskBase* taskArray[taskCount] = { nullptr };
		size_t newTaskIndex = 0;
		
		const auto addTask = [&taskArray, &newTaskIndex](const auto& task)
		{
			taskArray[newTaskIndex] = &task;
			++newTaskIndex;
		};

		(addTask(tasks), ...);

		size_t startIndex = 0;

		for (const XmlAttribute* attribute = GetNextAttribute(); attribute != nullptr && startIndex < taskCount; attribute = GetNextAttribute())
		{
			size_t foundIndex = startIndex;

			for (foundIndex; foundIndex < taskCount; ++foundIndex)
			{
				if (!matches(attribute->Name, taskArray[foundIndex]->Name, false)) continue;

				taskArray[foundIndex]->Read(attribute);
				statuses.FoundAttribute[foundIndex] = true;

				break;
			}
			
			if (foundIndex >= taskCount) continue;

			for (size_t i = startIndex; i < foundIndex; ++i)
			{
				taskArray[i]->Skipped();
			}

			startIndex = foundIndex + 1;
		}

		return statuses;
	}
}