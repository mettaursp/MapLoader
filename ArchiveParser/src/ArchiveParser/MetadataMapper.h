#pragma once

#include <string>
#include <filesystem>
#include <unordered_map>

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
			static Entry& Add();
			static void IndexEntries();
			static void LoadEntries(ArchiveReader& reader, const fs::path& path);
			static bool LoadCached(const fs::path& path);
			static void Cache(const fs::path& path);

			static std::vector<Tag> TagTypes;
			static std::vector<Entry> Entries;
			static std::unordered_map<UUID, size_t> EntryMap;
		};
	}
}