#include "XmlReader.h"

#include <cassert>

#include "ParserUtils.h"

namespace XmlLite
{
	void XmlReader::OpenDocument(const std::string_view& stream)
	{
		Document = stream;
		NodeTree.clear();
		HeaderName = "";
		HeaderAttributes.clear();
		FileHeader = {};
		NextNode = {};
		LastAttribute = {};
		CurrentIndex = 0;
		LineNumber = 1;
		LastLineStart = 0;
		IsReadingNode = false;
		FoundClosingNode = false;
		HasNoChildren = false;
		CurrentNodeSet = false;
		Error = XmlErrorType::None;

		TryReadHeader();
	}

	XmlReader::StackMarker XmlReader::GetStackMarker() const
	{
		if (IsReadingNode)
		{
			return { NodeTree.size(), NextNode.Start };
		}

		return { NodeTree.size(), NodeTree.size() ? NodeTree.back().BranchStart : 0 };
	}

	const XmlNode* XmlReader::GetNextSibling(const StackMarker& marker)
	{
		if (FoundClosingNode) return nullptr;
		
		size_t stackDepth = 0;

		if (marker.Index != (size_t)-1)
		{
			stackDepth = NodeTree.size() - marker.Index - 1;

			if (stackDepth >= NodeTree.size() || marker.Start < NodeTree[marker.Index].BranchStart)
			{
				return nullptr;
			}
		}

		while (CanContinue() && stackDepth < NodeTree.size()) // might need to revisit this loop to double check error handling. didnt care to do it while setting it up
		{
			if (!IsReadingNode)
			{
				if (!ReadNextNode())
				{
					if (FoundClosingNode)
					{
						--stackDepth;

						NodeTree.pop_back();

						continue;
					}

					return nullptr;
				}

				if (!FoundClosingNode && stackDepth == 0)
				{
					return &NextNode;
				}
				else if (FoundClosingNode && stackDepth == 0)
				{
					stackDepth += 0;
				}

				continue;
			}

			if (!TryFindClosingMarker(HasNoChildren))
			{
				TrySetError(XmlErrorType::ExpectedNodeEnd);

				return nullptr;
			}

			if (!HasNoChildren && !FoundClosingNode)
			{
				++stackDepth;

				NodeTree.push_back({ NextNode, NextNode.Start });
			}

			ReadNextNode();
			//if (!ReadNextNode())
			//	return nullptr;

			if (FoundClosingNode)
			{
				if (stackDepth == 0)
					stackDepth += 0;

				--stackDepth;

				NodeTree.pop_back();
			}
			else if (stackDepth == 0)
			{
				return &NextNode;
			}
		}

		if (stackDepth == (size_t)-1 && IsReadingNode && FoundClosingNode)
		{
			FinishCurrentNode();
		}

		return nullptr;
	}

	const XmlNode* XmlReader::GetNextSibling(const std::string_view& name, bool caseSensitive, const StackMarker& marker)
	{
		const XmlNode* node = nullptr;

		for (node = GetNextSibling(marker); node != nullptr && !matches(name, node->Name, !caseSensitive); node = GetNextSibling());

		return node;
	}

	const XmlNode* XmlReader::GetFirstChild()
	{
		if (FoundClosingNode || HasNoChildren) return nullptr;

		bool addToStack = CurrentNodeSet || NodeTree.size() > 0;
		XmlNode newStackNode = NextNode;

		if (!TryFindClosingMarker(HasNoChildren))
		{
			TrySetError(XmlErrorType::ExpectedNodeEnd);

			return nullptr;
		}

		if (HasNoChildren)
		{
			return nullptr;
		}

		if (!ReadNextNode()) return nullptr;

		if (addToStack)
			NodeTree.push_back({ newStackNode, newStackNode.Start });

		if (FoundClosingNode) return nullptr;

		return &NextNode;
	}

	const XmlNode* XmlReader::GetFirstChild(const std::string_view& name, bool caseSensitive)
	{
		const XmlNode* node = GetFirstChild();

		if (node == nullptr) return nullptr;

		if (matches(name, node->Name, !caseSensitive))
			return node;

		return GetNextSibling(name, caseSensitive);
	}

	bool XmlReader::ReadNextNode()
	{
		if (!AdvanceToNextNode())
		{
			if (NodeTree.size() > 0)
				TrySetError(XmlErrorType::ExpectedClosingNode);

			return false;
		}

		FoundClosingNode = Document[CurrentIndex] == '/';

		if (FoundClosingNode)
			++CurrentIndex;

		if (!ReadName(NextNode.Name)) return false;

		if (FoundClosingNode)
		{
			if ((NodeTree.size() == 0 || NextNode.Name != NodeTree.back().Node.Name))
				return TrySetError(XmlErrorType::UnexpectedClosingNode);

			return false;
		}

		CurrentNodeSet = true;

		return true;
	}

	std::string XmlReader::GetFullNodePath() const
	{
		std::stringstream lineNumber;

		lineNumber << "[" << LineNumber << "]: ";

		std::string nodePath = lineNumber.str();
		bool isFirst = true;

		for (const StackItem& node : NodeTree)
		{
			nodePath = nodePath + (isFirst ? std::string(node.Node.Name) : "." + std::string(node.Node.Name));
			isFirst = false;

			std::stringstream lineNumber;

			lineNumber << "[" << node.Node.Line << "]";

			nodePath += lineNumber.str();
		}

		if (IsReadingNode)
		{
			if (!isFirst)
			{
				nodePath += ".";
			}

			if (FoundClosingNode)
			{
				nodePath += "/";
			}

			nodePath += NextNode.Name;

			std::stringstream lineNumber;

			lineNumber << "[" << NextNode.Line << "]";

			nodePath += lineNumber.str();
		}

		return nodePath;
	}

	const XmlAttribute* XmlReader::GetNextAttribute()
	{
		if (!CanContinue() || !IsReadingNode) return nullptr;

		LastAttribute = {};

		bool foundAttribute = false;

		if (!TryReadAttribute(LastAttribute, foundAttribute) || !foundAttribute)
			return nullptr;

		return &LastAttribute;
	}

	const XmlAttribute* XmlReader::GetNextAttribute(const std::string_view& name, bool caseSensitive)
	{
		const XmlAttribute* attribute = nullptr;

		for (attribute = GetNextAttribute(); attribute != nullptr && !matches(name, attribute->Name, !caseSensitive); attribute = GetNextAttribute());

		return attribute;
	}

	void XmlReader::PopNode(size_t count)
	{
		for (size_t i = 0; i < count; ++i)
		{
			while (GetNextSibling());

			if (!FoundClosingNode || !matches(NextNode.Name, NodeTree.back().Node.Name, false))
			{
				TrySetError(XmlErrorType::ExpectedClosingNode);

				return;
			}

			NodeTree.pop_back();

			FinishCurrentNode();
		}
	}

	struct CharacterFlags
	{
		typedef unsigned long long FlagType;

		const size_t FlagCount = 4 * sizeof(FlagType);

		FlagType Flags[256 / sizeof(FlagType)] = {0};

		template <typename... T>
		constexpr CharacterFlags(T... characters)
		{
			const auto setFlag = [this] (char character)
			{
				unsigned char value = (unsigned char)character;

				Flags[value / FlagCount] |= 1ull << (unsigned char)(value % FlagCount);
			};

			(setFlag(characters), ...);
		}

		template <size_t Size>
		constexpr CharacterFlags(const char(&characters)[Size])
		{
			const auto setFlag = [this](char character)
			{
				unsigned char value = (unsigned char)character;

				Flags[value / FlagCount] |= 1ull << (unsigned char)(value % FlagCount);
			};

			for (size_t i = 0; i < Size && characters[i]; ++i)
			{
				setFlag(characters[i]);
			}
		}

		bool HasFlag(char character) const
		{
			unsigned char value = (unsigned char)character;

			FlagType flag = 1ull << (value % FlagCount);

			return (Flags[value / FlagCount] & flag) != 0;
		}

		void SetFlag(char character)
		{
			unsigned char value = (unsigned char)character;

			Flags[value / FlagCount] |= 1ull << (unsigned char)(value % FlagCount);
		}
	};

	consteval CharacterFlags GetWhitespaceCharacters()
	{
		return CharacterFlags(' ', '\n', '\r', '\t');
	}

	consteval CharacterFlags GetNewLineCharacters()
	{
		return CharacterFlags('\n', '\r');
	}

	consteval CharacterFlags GetAlphanumericCharacters()
	{
		CharacterFlags flags("_0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");
		//flags.SetFlag('a');
		return flags;
	}

	bool XmlReader::IsWhitespace()
	{
		return IsWhitespace(CurrentIndex);
	}

	bool XmlReader::IsWhitespace(size_t index)
	{
		if (index >= Document.size()) return false;

		return Document[index] == ' ' || Document[index] == '\t' || Document[index] == '\n' || Document[index] == '\r';
		//static const CharacterFlags whitespaceFlags = GetWhitespaceCharacters();
		//
		//return whitespaceFlags.HasFlag(Document[index]);
	}

	bool XmlReader::IsNewLine()
	{
		return IsNewLine(CurrentIndex);
	}

	bool XmlReader::IsNewLine(size_t index)
	{
		if (index >= Document.size()) return false;

		return Document[index] == '\n' || Document[index] == '\r';
		//static const CharacterFlags newLineFlags = GetNewLineCharacters();
		//
		//return newLineFlags.HasFlag(Document[index]);
	}

	bool XmlReader::IsAlphanumeric()
	{
		return IsAlphanumeric(CurrentIndex);
	}

	bool XmlReader::IsAlphanumeric(size_t index)
	{
		if (index >= Document.size()) return false;

		//static const CharacterFlags alphanumericFlags = GetAlphanumericCharacters();
		
		//return alphanumericFlags.HasFlag(Document[index]);

		return ((unsigned char)(Document[index] - 'a') <= ('z' - 'a')) || ((unsigned char)(Document[index] - 'A') <= ('Z' - 'A')) || ((unsigned char)(Document[index] - '0') <= ('9' - '0')) || Document[index] == '_';
	}

	bool XmlReader::SkipWhitespace()
	{
		bool lastWasCarriageReturn = false;

		while (CurrentIndex < Document.size() && IsWhitespace())
		{
			if (IsNewLine())
			{
				if (lastWasCarriageReturn && Document[CurrentIndex] == '\n')
					++LineNumber;

				LastLineStart = CurrentIndex + 1;
			}

			lastWasCarriageReturn = Document[CurrentIndex] == '\r';

			++CurrentIndex;
		}

		return CurrentIndex < Document.size();
	}

	bool XmlReader::CanContinue()
	{
		return CurrentIndex < Document.size() && Error == XmlErrorType::None;
	}

	bool XmlReader::TryReadHeader()
	{
		if (!CanContinue()) return false;

		const std::string_view byteOrderMarks[] = {
			"\xef\xbb\xbf",
			"\xfe\xff",
			"\xff\xff",
			{ "\x00\x00\xfe\xff", 4 },
			"\xff\xfe\x00\x00",
			"\x2b\x2f\x76",
			"\xf7\x64\x4c",
			"\xdd\x73\x66\x73",
			"\x0e\xfe\xff",
			"\xfb\xee\x28",
			"\x84\x31\x95\x33"
		};

		for (const std::string_view& byteOrderMark : byteOrderMarks)
		{
			if (Document.size() < byteOrderMark.size()) continue;

			if (strncmp(Document.data(), byteOrderMark.data(), byteOrderMark.size()) != 0) continue;

			CurrentIndex += byteOrderMark.size();

			break;
		}

		if (!AdvanceToNextNode(true)) return false;

		IsReadingNode = true;

		if (Document[CurrentIndex] != '?')
		{
			CurrentIndex = 0;
			IsReadingNode = false;

			return CanContinue();
		}

		++CurrentIndex;

		if (!ReadName(HeaderName)) return false;

		bool readingAttributes = true;
		XmlAttribute attribute;

		while (TryReadAttribute(attribute, readingAttributes) && readingAttributes)
		{
			HeaderAttributes.push_back(attribute);
			attribute = {};
		}

		if (!SkipWhitespace() || Document[CurrentIndex] != '?')
			return TrySetError(XmlErrorType::ExpectedHeaderEnd);

		++CurrentIndex;

		if (!SkipWhitespace() || Document[CurrentIndex] != '>')
			return TrySetError(XmlErrorType::ExpectedNodeEnd);

		++CurrentIndex;

		IsReadingNode = false;

		return CanContinue();
	}

	bool XmlReader::ReadName(std::string_view& name)
	{
		if (!CanContinue()) return false;

		if (!SkipWhitespace()) return false;

		if (!IsAlphanumeric()) return false;

		size_t nameStart = CurrentIndex;

		while (IsAlphanumeric())
			++CurrentIndex;

		name = { Document.data() + nameStart, CurrentIndex - nameStart };

		return CanContinue();
	}

	bool XmlReader::TrySetError(XmlErrorType error)
	{
		if (Error == XmlErrorType::None)
			Error = error;

		return false;
	}

	bool XmlReader::TryReadAttribute(XmlAttribute& attribute, bool& foundAttribute)
	{
		assert(IsReadingNode);

		foundAttribute = false;

		if (!CanContinue()) return false;
		if (!SkipWhitespace()) return false;

		if (!ReadName(attribute.Name))
			return CanContinue();

		if (!SkipWhitespace()) return false;

		if (Document[CurrentIndex] != '=')
			return TrySetError(XmlErrorType::ExpectedAttributeEquals);

		++CurrentIndex;

		if (!ReadValue(attribute.Value))
			return TrySetError(XmlErrorType::ExpectedAttributeValue);

		foundAttribute = true;

		return CanContinue();
	}

	bool XmlReader::ReadValue(std::string_view& name)
	{
		if (!SkipWhitespace()) return false;

		if (Document[CurrentIndex] != '"')
			return TrySetError(XmlErrorType::ExpectedAttributeValue);

		++CurrentIndex;

		size_t valueStart = CurrentIndex;
		bool isEscaped = false;

		while (CurrentIndex < Document.size() && (Document[CurrentIndex] != '"' || isEscaped))
		{
			isEscaped = Document[CurrentIndex] == '\\';

			++CurrentIndex;
		}

		if (!CanContinue())
			return TrySetError(XmlErrorType::ExpectedAttributeValueEnd);

		name = { Document.data() + valueStart, CurrentIndex - valueStart };

		++CurrentIndex;

		return CanContinue();
	}

	bool XmlReader::FinishCurrentNode()
	{
		if (!CanContinue()) return false;
		if (!IsReadingNode) return CanContinue();

		while (CurrentIndex < Document.size() && Document[CurrentIndex] != '>')
			++CurrentIndex; // Can potentially skip errors with node formatting, but faster to parse. Should work if the rest of the document is valid

		if (!CanContinue()) return false;

		if (Document[CurrentIndex] != '>')
			return TrySetError(XmlErrorType::ExpectedNodeEnd);

		++CurrentIndex;

		IsReadingNode = false;
		FoundClosingNode = false;
		CurrentNodeSet = false;
		HasNoChildren = false;

		return CanContinue();
	}

	bool XmlReader::TryFindClosingMarker(bool& foundMarker)
	{
		if (!CanContinue()) return false;
		if (!IsReadingNode) return true;

		while (CurrentIndex < Document.size() && Document[CurrentIndex] != '>' && Document[CurrentIndex] != '/')
			++CurrentIndex; // Can potentially skip errors with node formatting, but faster to parse. Should work if the rest of the document is valid

		if (!CanContinue()) return false;

		foundMarker = Document[CurrentIndex] == '/';

		return true;
	}

	bool XmlReader::AdvanceToNextNode(bool allowHeader)
	{
		if (!CanContinue()) return false;

		if (!FinishCurrentNode()) return false;
		if (!SkipWhitespace()) return false;

		if (Document[CurrentIndex] != '<')
			return TrySetError(XmlErrorType::ExpectedNodeStart);

		NextNode.Start = CurrentIndex;
		NextNode.Line = LineNumber;

		++CurrentIndex;
		IsReadingNode = true;

		while (SkipWhitespace() && Document[CurrentIndex] == '!')
		{
			if (!FinishCurrentNode() || CurrentIndex < 3) return false;

			while (Document[CurrentIndex - 3] != '-' && Document[CurrentIndex - 2] != '-')
			{
				IsReadingNode = true;

				if (!FinishCurrentNode() || CurrentIndex < 3) return false;
			}

			if (!SkipWhitespace()) return false;

			if (Document[CurrentIndex] != '<')
				return TrySetError(XmlErrorType::ExpectedNodeStart);

			NextNode.Start = CurrentIndex;
			NextNode.Line = LineNumber;

			++CurrentIndex;
			IsReadingNode = true;
		}

		if (CanContinue() && Document[CurrentIndex] == '?' && !allowHeader)
			return TrySetError(XmlErrorType::UnexpectedHeader);

		return CanContinue();
	}

	template <>
	void XmlAttribute::Read<int>(const std::string_view& string, int& value)
	{
		std::from_chars(string.data(), string.data() + string.size(), value);
	}
	
	template <>
	void XmlAttribute::Read<unsigned int>(const std::string_view& string, unsigned int& value)
	{
		std::from_chars(string.data(), string.data() + string.size(), value);
	}
	
	template <>
	void XmlAttribute::Read<short>(const std::string_view& string, short& value)
	{
		std::from_chars(string.data(), string.data() + string.size(), value);
	}
	
	template <>
	void XmlAttribute::Read<unsigned short>(const std::string_view& string, unsigned short& value)
	{
		std::from_chars(string.data(), string.data() + string.size(), value);
	}
	
	template <>
	void XmlAttribute::Read<unsigned char>(const std::string_view& string, unsigned char& value)
	{
		std::from_chars(string.data(), string.data() + string.size(), value);
	}
	
	template <>
	void XmlAttribute::Read<signed char>(const std::string_view& string, signed char& value)
	{
		std::from_chars(string.data(), string.data() + string.size(), value);
	}

	template <>
	void XmlAttribute::Read<bool>(const std::string_view& string, bool& value)
	{
		int boolValue = 0;

		std::from_chars(string.data(), string.data() + string.size(), boolValue);

		value = boolValue != 0;
	}

	template <>
	void XmlAttribute::Read<long long>(const std::string_view& string, long long& value)
	{
		std::from_chars(string.data(), string.data() + string.size(), value);
	}
	
	template <>
	void XmlAttribute::Read<unsigned long long>(const std::string_view& string, unsigned long long& value)
	{
		std::from_chars(string.data(), string.data() + string.size(), value);
	}
	
	template <>
	void XmlAttribute::Read<float>(const std::string_view& string, float& value)
	{
		std::from_chars(string.data(), string.data() + string.size(), value);
	}
	
	template <>
	void XmlAttribute::Read<double>(const std::string_view& string, double& value)
	{
		std::from_chars(string.data(), string.data() + string.size(), value);
	}

	template <>
	void XmlAttribute::Read<std::string>(const std::string_view& string, std::string& value)
	{
		value = string;
	}

	template <>
	void XmlAttribute::Read<std::string_view>(const std::string_view& string, std::string_view& value)
	{
		value = string;
	}
}