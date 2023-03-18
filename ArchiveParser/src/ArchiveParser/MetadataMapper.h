#pragma once

#include <string>
#include <filesystem>
#include <unordered_map>
#include <functional>

namespace fs = std::filesystem;

/*
* Tag Types:
* <urn:uuid:uuid> <http://emergent.net/aweb/1.0/tag> "value".
* <http://emergent.net/aweb/1.0/std-tags/> <http://emergent.net/aweb/1.0/std-tags/value> "value".
* <urn:uuid:uuid> <http://emergent.net/aweb/1.0/relpath> "relative path".
* <http://emergent.net/aweb/1.0/user-tags/> <http://emergent.net/aweb/1.0/user-tags/value> "value".
* <urn:uuid:uuid> <http://emergent.net/aweb/1.0/name> "value".
* <urn:uuid:uuid> <http://emergent.net/aweb/1.0/logpath> "log path".
* <urn:uuid:uuid> <http://emergent.net/aweb/1.0/llid> "llid value".
* <http://emergent.net/aweb/1.0/user-enums/> <http://emergent.net/aweb/1.0/user-enums/value> "value".
* <urn:uuid:uuid> <http://emergent.net/aweb/1.0/canonical> "canonical path".
* <http://emergent.net/aweb/1.0/ids> <http://emergent.net/aweb/1.0/ids/instance> "urn:uuid:uuid".
* <http://emergent.net/aweb/1.0/file name> <http://emergent.net/aweb/1.0/ckpt/hash> "value".
* 
* <http://emergent.net/aweb/1.0/tag>
* <http://emergent.net/aweb/1.0/std-tags/value>
* <http://emergent.net/aweb/1.0/relpath>
* <http://emergent.net/aweb/1.0/name>
* <http://emergent.net/aweb/1.0/logpath>
* <http://emergent.net/aweb/1.0/llid>
* <http://emergent.net/aweb/1.0/user-enums/value>
* <http://emergent.net/aweb/1.0/canonical>
* <http://emergent.net/aweb/1.0/ids/instance>
* <http://emergent.net/aweb/1.0/ckpt/hash>
*/

namespace Archive
{
	class UUID
	{
	public:
		unsigned long long Values[2] = { 0, 0 };

		UUID() {}

		bool operator==(const UUID& other) const
		{
			return Values[0] == other.Values[0] && Values[1] == other.Values[1];
		}

		template <typename Self>
		auto& operator[](this Self& self, size_t index)
		{
			return self.Values[index];
		}
	};
}

template <>
struct std::hash<Archive::UUID>
{
	size_t operator()(const Archive::UUID& key) const
	{
		size_t value = 17;
		
		for (int i = 0; i < 2; ++i)
			value = value * 31 + hash<unsigned long long>()(key[i]);

		return value;
	}
};


namespace Archive
{
	UUID ParseUUID(const std::string& value, int offset);
	unsigned int ParseHexInt(const std::string& value, int offset);

	namespace FNV1A32
	{
		extern const unsigned int OffsetBasis;
		extern const unsigned int Prime;

		unsigned int Hash(const std::string& text);
	}

	class ArchiveReader;

	namespace Metadata
	{
		struct EntryParser
		{
			void ProcessEntry(const std::string& key, const std::string& type, const std::string& value);

		private:
			size_t LastTagIndex = (size_t)-1;
			std::string LastTag;
		};

		struct Entry;

		struct Tag
		{
			size_t Index = (size_t)-1;
			std::string Name;
			size_t TotalEntries = 0;
			size_t MaxLinkIds = 0;
			size_t MaxNames = 0;

			std::unordered_map<UUID, Entry*> Ids;
			std::unordered_map<unsigned int, std::vector<Entry*>> LinkIds;
			std::unordered_map<std::string, std::vector<Entry*>> Names;
			std::unordered_map<std::string, Entry*> RelativePaths;
		};

		struct Entry
		{
			size_t Index = (size_t)-1;
			UUID Id; // UUID
			unsigned int LinkId = 0; // LLID
			std::string Name;
			fs::path RelativePath;
			fs::path LogPath;
			fs::path CanonicalPath;
			std::vector<size_t> Tags;

			static size_t GetTag(const std::string& name);
			static const Tag* GetTagData(const std::string& name);
			static Entry& Add();
			static void IndexEntries();
			static void LoadEntries(ArchiveReader& reader, const fs::path& path, std::string& buffer);
			static void LoadEntries(ArchiveReader& reader, const fs::path& path);
			static bool LoadCached(const fs::path& path);
			static void Cache(const fs::path& path);

			static bool FoundMatch(const Entry* entry, const Tag& tag, const std::string** secondaryTags, size_t tagCount);
			static void FindMatches(const std::function<void(const Entry&)>& callback, const Tag& tag, const std::vector<Entry*> matches, const std::string** secondaryTags, size_t tagCount);
			static const Entry* FindFirstMatch(const Tag& tag, const std::vector<Entry*> matches, const std::string** secondaryTags, size_t tagCount);

			static const Entry* FindFirstEntryByTagWithRelPath(const std::string& path, const std::string& primaryTag);
			static const Entry* FindFirstEntryByTags(const std::string& name, const std::string& primaryTag, const std::string** secondaryTags = nullptr, size_t tagCount = 0);
			static void FindEntriesByTags(const std::string& name, const std::string& primaryTag, const std::function<void(const Entry&)>& callback, const std::string** secondaryTags = nullptr, size_t tagCount = 0);

			template <typename... T>
			static void FindEntriesByTags(const std::string& name, const std::string& primaryTag, const std::function<void(const Entry&)>& callback, const std::string& secondaryTag0, const T&... secondaryTags)
			{
				const std::string* tags[] = { &secondaryTag0, (&secondaryTags, ...) };
				size_t count = sizeof...(T);

				FindEntriesByTags(name, primaryTag, callback, tags, count);
			}

			template <typename... T>
			static const Entry* FindFirstEntryByTags(const std::string& name, const std::string& primaryTag, const std::string& secondaryTag0, const T&... secondaryTags)
			{
				const std::string* tags[] = { &secondaryTag0, (&secondaryTags, ...) };
				size_t count = sizeof...(T);

				return FindFirstEntryByTags(name, primaryTag, tags, count);
			}

			static const Entry* FindFirstEntryByTagsWithLink(int linkId, const std::string& primaryTag, const std::string** secondaryTags = nullptr, size_t tagCount = 0);
			static void FindEntriesByTagsWithLink(int linkId, const std::string& primaryTag, const std::function<void(const Entry&)>& callback, const std::string** secondaryTags = nullptr, size_t tagCount = 0);

			template <typename... T>
			static void FindEntriesByTagsWithLink(int linkId, const std::string& primaryTag, const std::function<void(const Entry&)>& callback, const std::string& secondaryTag0, const T&... secondaryTags)
			{
				const std::string* tags[] = { &secondaryTag0, (&secondaryTags, ...) };
				size_t count = sizeof...(T);

				FindEntriesByTagsWithLink(linkId, primaryTag, callback, tags, count);
			}

			template <typename... T>
			static const Entry* FindFirstEntryByTagsWithLink(int linkId, const std::string& primaryTag, const std::string& secondaryTag0, const T&... secondaryTags)
			{
				const std::string* tags[] = { &secondaryTag0, (&secondaryTags, ...) };
				size_t count = sizeof...(T);

				return FindFirstEntryByTagsWithLink(linkId, primaryTag, tags, count);
			}

			static std::vector<Tag> TagTypes;
			static std::vector<Entry> Entries;
			static std::unordered_map<UUID, size_t> EntryMap;
		};
	}
}