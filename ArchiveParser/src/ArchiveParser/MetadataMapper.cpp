#include "MetadataMapper.h"

#include "ArchiveReader.h"
#include "ParserUtils.h"

#include <algorithm>
#include <iostream>
#include <cassert>

namespace Archive
{

	UUID ParseUUID(const std::string& value, int offset)
	{
		UUID uuid;
		int index = 0;
		int shifts = 0;

		for (size_t i = offset; i < value.size(); ++i)
		{
			if (value[i] == '-')
				continue;

			uuid[index] <<= 4;

			if (value[i] >= '0' && value[i] <= '9')
				uuid[index] += value[i] - '0';
			else if (value[i] >= 'a' && value[i] <= 'f')
				uuid[index] += value[i] - 'a' + 0xA;

			shifts += 4;

			if (shifts == 64)
			{
				shifts = 0;
				++index;
			}
		}

		return uuid;
	}

	unsigned int ParseHexInt(const std::string& value, int offset)
	{
		unsigned int uuid = 0;

		for (size_t i = offset; i < value.size() && i < offset + 8; ++i)
		{
			if (value[i] == '-')
				continue;

			uuid <<= 4;

			if (value[i] >= '0' && value[i] <= '9')
				uuid += value[i] - '0';
			else if (value[i] >= 'a' && value[i] <= 'f')
				uuid += value[i] - 'a' + 0xA;
		}

		return uuid;
	}

	namespace FNV1A32
	{
		const unsigned int OffsetBasis = 0x811c9dc5;
		const unsigned int Prime = 0x01000193;

		unsigned int Hash(const std::string& text)
		{
			const unsigned int offsetBasis = 0x811c9dc5;
			const unsigned int prime = 0x01000193;

			unsigned long long hash = offsetBasis;

			for (size_t i = 0; i < text.size(); ++i)
			{
				hash ^= text[i];
				hash *= prime;
			}

			return (unsigned int)hash;
		}
	}

	namespace Metadata
	{
		std::vector<Tag> Entry::TagTypes = {};
		std::vector<Entry> Entry::Entries = {};
		std::unordered_map<UUID, size_t> Entry::EntryMap = {};

		Entry& Entry::Add()
		{
			Entries.push_back({ Entries.size() });

			return Entries.back();
		}

		void EntryParser::ProcessEntry(const std::string& key, const std::string& type, const std::string& value)
		{
			Entry* entry = nullptr;

			if (strncmp(key.c_str(), "urn:uuid:", 9) == 0)
			{
				UUID id = ParseUUID(key, 9);

				const auto& index = Entry::EntryMap.find(id);

				if (index == Entry::EntryMap.end())
				{
					Entry& newEntry = Entry::Add();

					newEntry.Id = id;

					entry = &newEntry;

					Entry::EntryMap.insert(std::make_pair(id, Entry::Entries.size() - 1));
				}
				else
				{
					entry = &Entry::Entries[index->second];
				}

				if (type == "tag")
				{
					if (LastTagIndex != (size_t)-1 && value == LastTag)
					{
						entry->Tags.push_back(LastTagIndex);

						return;
					}

					size_t tagIndex = (size_t)-1;

					for (size_t i = 0; i < Entry::TagTypes.size() && tagIndex == (size_t)-1; ++i)
						if (value == Entry::TagTypes[i].Name)
							tagIndex = i;

					if (tagIndex == (size_t)-1)
					{
						tagIndex = Entry::TagTypes.size();

						Entry::TagTypes.push_back({ Entry::TagTypes.size(), value });
					}

					LastTagIndex = tagIndex;
					LastTag = value;

					return;
				}

				if (type == "relpath")
				{
					entry->RelativePath = value;

					return;
				}

				if (type == "name")
				{
					entry->Name = value;

					return;
				}

				if (type == "logpath")
				{
					entry->LogPath = value;

					return;
				}

				if (type == "llid")
				{
					entry->LinkId = ParseHexInt(value, 0);

					return;
				}

				if (type == "canonical")
				{
					entry->CanonicalPath = value;

					return;
				}
			}
		}

		void LoadEntry(ArchiveReader& reader, const ArchivePath& path, std::string& bufferString)
		{
			if (!path.Loaded())
				return;

			bufferString.clear();

			path.Read(bufferString);

			const char* buffer = bufferString.c_str();
			
			std::string key;
			std::string type;
			std::string value;

			EntryParser parser;

			for (size_t i = 1; i < bufferString.size(); ++i)
			{
				size_t j = 0;

				for (j = 0; i + j < bufferString.size() && buffer[i + j] != '>'; ++j);

				key.clear();
				key.append(buffer + i, j);

				i += j + 3;

				for (j = 0; i + j < bufferString.size() && buffer[i + j] != '>'; ++j);

				type.clear();
				type.append(buffer + i + std::min(29ull, j), std::max(0ull, j - 29));

				i += j + 3;

				for (j = 0; i + j < bufferString.size() && buffer[i + j] != '"'; ++j);

				value.clear();
				value.append(buffer + i, j);

				i += j + 2;

				for (i; i < bufferString.size() && (buffer[i] == '\n' || buffer[i] == '\r'); ++i);

				parser.ProcessEntry(key, type, value);
			}
		}

		size_t Entry::GetTag(const std::string& name)
		{
			for (size_t i = 0; i < TagTypes.size(); ++i)
				if (TagTypes[i].Name == name)
					return i;

			return (size_t)-1;
		}

		const Tag* Entry::GetTagData(const std::string& name)
		{
			for (size_t i = 0; i < TagTypes.size(); ++i)
				if (TagTypes[i].Name == name)
					return &TagTypes[i];

			return nullptr;
		}

		void Entry::IndexEntries()
		{
			size_t applicationId = GetTag("application");

			for (Entry& entry : Entry::Entries)
			{
				for (size_t tagIndex : entry.Tags)
				{
					if (tagIndex == applicationId)
						continue;

					Tag& tag = Entry::TagTypes[tagIndex];

					++tag.TotalEntries;

					if (entry.Id != UUID{})
					{
						assert(tag.Ids.find(entry.Id) == tag.Ids.end());

						tag.Ids[entry.Id] = &entry;
					}

					if (entry.LinkId != 0)
					{
						auto& linkIds = tag.LinkIds[entry.LinkId];

						linkIds.push_back(&entry);
						tag.MaxLinkIds = std::max(tag.MaxLinkIds, linkIds.size());
					}

					if (entry.Name != "")
					{
						auto& names = tag.Names[lower(entry.Name)];

						names.push_back(&entry);
						tag.MaxNames = std::max(tag.MaxNames, names.size());
					}

					if (entry.RelativePath != "")
					{
						std::string relativePath = entry.RelativePath.string();
						assert(tag.RelativePaths.find(relativePath) == tag.RelativePaths.end());

						tag.RelativePaths[lower(relativePath)] = &entry;
					}
				}
			}
		}

		void Entry::LoadEntries(ArchiveReader& reader, const fs::path& path)
		{
			std::string buffer;
			LoadEntries(reader, path, buffer);
		}

		void Entry::LoadEntries(ArchiveReader& reader, const fs::path& path, std::string& buffer)
		{
			if (!reader.IsValid()) return;

			ArchivePath webMeta = reader.GetPath(path);

			size_t files = webMeta.ChildFiles();

			for (size_t i = 0; i < files; ++i)
			{
				LoadEntry(reader, webMeta.ChildFile(i), buffer);
			}

			IndexEntries();
		}

		bool Entry::FoundMatch(const Entry* entry, const Tag& tag, const std::string** secondaryTags, size_t tagCount)
		{
			bool found = true;

			for (size_t i = 0; i < tagCount && found; ++i)
			{
				bool matches = false;

				for (size_t i = 0; i < entry->Tags.size() && !matches && tagCount > 0; ++i)
				{
					const Tag& secondaryTag = TagTypes[entry->Tags[i]];

					matches = &secondaryTag == &tag || secondaryTag.Name == *secondaryTags[i];
				}

				found = matches;
			}

			return found;
		}

		void Entry::FindMatches(const std::function<void(const Entry&)>& callback, const Tag& tag, const std::vector<Entry*> matches, const std::string** secondaryTags, size_t tagCount)
		{
			for (const Entry* entry : matches)
			{
				bool found = FoundMatch(entry, tag, secondaryTags, tagCount);

				if (found)
					callback(*entry);
			}
		}

		const Entry* Entry::FindFirstMatch(const Tag& tag, const std::vector<Entry*> matches, const std::string** secondaryTags, size_t tagCount)
		{
			for (const Entry* entry : matches)
			{
				bool found = FoundMatch(entry, tag, secondaryTags, tagCount);

				if (found)
					return entry;
			}

			return nullptr;
		}

		const Entry* Entry::FindFirstEntryByTagWithRelPath(const std::string& path, const std::string& primaryTag)
		{
			const Tag* tag = GetTagData(primaryTag);

			if (tag == nullptr) return nullptr;

			std::string pathLower = lower(path);

			const auto& pathIndex = tag->RelativePaths.find(pathLower);

			if (pathIndex == tag->RelativePaths.end()) return nullptr;

			return pathIndex->second;
		}

		const Entry* Entry::FindFirstEntryByTags(const std::string& name, const std::string& primaryTag, const std::string** secondaryTags, size_t tagCount)
		{
			const Tag* tag = GetTagData(primaryTag);

			if (tag == nullptr) return nullptr;

			std::string nameLower = lower(name);

			const auto& nameIndex = tag->Names.find(nameLower);

			if (nameIndex == tag->Names.end()) return nullptr;

			return FindFirstMatch(*tag, nameIndex->second, secondaryTags, tagCount);
		}

		void Entry::FindEntriesByTags(const std::string& name, const std::string& primaryTag, const std::function<void(const Entry&)>& callback, const std::string** secondaryTags, size_t tagCount)
		{
			const Tag* tag = GetTagData(primaryTag);

			if (tag == nullptr) return;

			std::string nameLower = lower(name);

			const auto& nameIndex = tag->Names.find(nameLower);

			if (nameIndex == tag->Names.end()) return;

			FindMatches(callback, *tag, nameIndex->second, secondaryTags, tagCount);
		}

		const Entry* Entry::FindFirstEntryByTagsWithLink(int linkId, const std::string& primaryTag, const std::string** secondaryTags, size_t tagCount)
		{
			const Tag* tag = GetTagData(primaryTag);

			if (tag == nullptr) return nullptr;

			const auto& linkIndex = tag->LinkIds.find(linkId);

			if (linkIndex == tag->LinkIds.end()) return nullptr;

			return FindFirstMatch(*tag, linkIndex->second, secondaryTags, tagCount);
		}

		void Entry::FindEntriesByTagsWithLink(int linkId, const std::string& primaryTag, const std::function<void(const Entry&)>& callback, const std::string** secondaryTags, size_t tagCount)
		{
			const Tag* tag = GetTagData(primaryTag);

			if (tag == nullptr) return;

			const auto& linkIndex = tag->LinkIds.find(linkId);

			if (linkIndex == tag->LinkIds.end()) return;

			FindMatches(callback, *tag, linkIndex->second, secondaryTags, tagCount);
		}

		template <typename T>
		void Write(std::ostream& out, const T& value)
		{
			out.write(reinterpret_cast<const char*>(&value), sizeof(value));
		}

		template <>
		void Write<std::string>(std::ostream& out, const std::string& value)
		{
			Write(out, (unsigned int)value.size());

			out.write(value.c_str(), value.size());
		}

		template <>
		void Write<std::wstring>(std::ostream& out, const std::wstring& value)
		{
			Write(out, (unsigned int)value.size());

			for (size_t i = 0; i < value.size(); ++i)
				Write(out, (char)value[i]);
		}

		template <>
		void Write<fs::path>(std::ostream& out, const fs::path& value)
		{
			Write(out, value.native());
		}

		template <typename T>
		void Read(std::istream& in, T& value)
		{
			in.read(reinterpret_cast<char*>(&value), sizeof(value));
		}

		template <>
		void Read<std::string>(std::istream& in, std::string& value)
		{
			unsigned int size;

			Read(in, size);

			value.resize(size);

			in.read(&value[0], size);
		}

		template <>
		void Read<std::wstring>(std::istream& in, std::wstring& value)
		{
			unsigned int size;

			Read(in, size);

			value.resize(size);

			for (size_t i = 0; i < value.size(); ++i)
			{
				char character;
				Read(in, character);
				value[i] = character;
			}
		}

		template <>
		void Read<fs::path>(std::istream& in, fs::path& value)
		{
			std::string valueString;
			Read(in, valueString);
			value = valueString;
		}

		void Read(std::istream& in, fs::path& value, std::string& valueString)
		{
			valueString.clear();
			Read(in, valueString);
			value = valueString;
		}

		void Entry::Cache(const fs::path& path)
		{
			fs::path parentPath = path.parent_path();

			if (!fs::is_directory(parentPath))
				fs::create_directories(parentPath);

			std::ofstream cache(path, std::ios::binary);

			Write(cache, (unsigned char)TagTypes.size());

			for (size_t i = 0; i < TagTypes.size(); ++i)
				Write(cache, TagTypes[i].Name);

			Write(cache, (unsigned int)Entries.size());

			for (size_t i = 0; i < Entries.size(); ++i)
			{
				Entry& entry = Entries[i];

				Write(cache, entry.Id[0]);
				Write(cache, entry.Id[1]);
				Write(cache, entry.LinkId);
				Write(cache, entry.Name);
				Write(cache, entry.RelativePath);
				Write(cache, entry.LogPath);
				Write(cache, entry.CanonicalPath);

				Write(cache, (unsigned char)entry.Tags.size());

				for (size_t i = 0; i < entry.Tags.size(); ++i)
				{
					Write(cache, (unsigned char)entry.Tags[i]);
				}
			}
		}

		bool Entry::LoadCached(const fs::path& path)
		{
			if (!fs::is_regular_file(path))
				return false;

			std::ifstream cache(path, std::ios::binary);

			std::string pathBuffer;

			unsigned char tagCount;

			Read(cache, tagCount);

			TagTypes.resize(tagCount);

			for (size_t i = 0; i < TagTypes.size(); ++i)
			{
				TagTypes[i].Index = i;
				Read(cache, TagTypes[i].Name);
			}

			unsigned int entryCount;
			Read(cache, entryCount);

			Entries.resize(entryCount);

			for (size_t i = 0; i < Entries.size(); ++i)
			{
				Entry& entry = Entries[i];

				entry.Index = i;
				Read(cache, entry.Id[0]);
				Read(cache, entry.Id[1]);
				Read(cache, entry.LinkId);
				Read(cache, entry.Name);
				Read(cache, entry.RelativePath, pathBuffer);
				Read(cache, entry.LogPath, pathBuffer);
				Read(cache, entry.CanonicalPath, pathBuffer);

				unsigned char tagCount;
				Read(cache, tagCount);
				entry.Tags.resize(tagCount);

				for (size_t i = 0; i < entry.Tags.size(); ++i)
				{
					unsigned char tag;
					Read(cache, tag);
					entry.Tags[i] = tag;
				}
			}

			IndexEntries();

			return true;
		}
	}
}