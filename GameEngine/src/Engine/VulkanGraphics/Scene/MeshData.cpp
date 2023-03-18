#include "MeshData.h"

namespace Engine
{
	namespace Graphics
	{
		typedef void(*CopyFunction)(const void* source, void* destination);

		template <typename SourceType, typename DestinationType>
		struct SourceDestinationTransferOperation
		{
			static void Copy(const void* source, void* destination)
			{
				*reinterpret_cast<DestinationType*>(destination) = (DestinationType)*reinterpret_cast<const SourceType*>(source);
			}
		};

		template <typename Type>
		struct TypeHolder {};

		template <typename SourceType, typename... DestinationTypes>
		struct SourceTransferOperations
		{
			static inline CopyFunction Operations[sizeof...(DestinationTypes)] = {};

			SourceTransferOperations()
			{
				auto fill = [this]<typename T, T... Indices>(std::integer_sequence<T, Indices...>)
				{
					auto fill = [this]<typename DestinationType>(TypeHolder<DestinationType>, T index)
					{
						Operations[index] = &SourceDestinationTransferOperation<SourceType, DestinationType>::Copy;
					};

					(fill(TypeHolder<DestinationTypes>{}, Indices), ...);
				};

				fill(std::make_index_sequence<sizeof...(DestinationTypes)>{});
			}
		};

		template <typename... Types>
		struct TransferOperationDefinitions
		{
			static inline CopyFunction Operations[sizeof...(Types)][sizeof...(Types)] = {};

			TransferOperationDefinitions()
			{
				auto fill = [this]<typename T, T... Indices>(std::integer_sequence<T, Indices...>)
				{
					auto fill = [this]<typename SourceType>(TypeHolder<SourceType>, T index)
					{
						auto t = SourceTransferOperations<SourceType, Types...>{};

						auto fill = [this, index]<typename U, U... InnerIndices>(std::integer_sequence<U, InnerIndices...>)
						{
							auto fill = [this, index](U innerIndex)
							{
								Operations[index][innerIndex] = SourceTransferOperations<SourceType, Types...>::Operations[innerIndex];
							};

							(fill(InnerIndices), ...);
						};

						fill(std::make_index_sequence<sizeof...(Types)>{});
					};

					(fill(TypeHolder<Types>{}, Indices), ...);
				};

				fill(std::make_index_sequence<sizeof...(Types)>{});
			}
		};

		const auto TransferOperations = TransferOperationDefinitions<float, double, bool, signed char, short, int, long long, unsigned char, unsigned short, unsigned int, unsigned long long>{};

		size_t VertexAttributeFormat::GetElementSize() const
		{
			return GetDataSize(Type);
		}

		size_t VertexAttributeFormat::GetSize() const
		{
			return GetElementSize() * ElementCount;
		}

		void VertexAttributeFormat::Copy(const void* source, void* destination, AttributeDataType destinationType) const
		{
			const char* sourceChar = reinterpret_cast<const char*>(source);
			char* destinationChar = reinterpret_cast<char*>(destination);

			for (size_t i = 0; i < ElementCount; ++i)
				TransferOperations.Operations[Type][destinationType](sourceChar + (i * GetElementSize()), destinationChar + (i * GetDataSize(destinationType)));
		}

		template <typename T>
		void AppendHash(unsigned long long& hash, T value)
		{
			const unsigned int prime = 0x01000193;

			hash ^= (unsigned long long)value;
			hash *= prime;
		}

		void VertexAttributeFormat::GetHash(unsigned long long& hash) const
		{
			size_t addedSize = std::min(sizeof(Type) + sizeof(ElementCount) + sizeof(Binding) + Name.size(), (size_t)0xFF);

			AppendHash(hash, Type);
			AppendHash(hash, ElementCount);
			AppendHash(hash, Binding);
			AppendHash(hash, Binding);

			for (size_t i = 0; i < Name.size(); ++i)
				AppendHash(hash, Name[i]);

			AppendHash(hash, addedSize);
		}

		void VertexAttributeFormat::GetHash(unsigned long long& hash, const std::vector<VertexAttributeFormat>& attributes)
		{
			size_t maxBinding = 0;

			for (size_t i = 0; i < attributes.size(); ++i)
				maxBinding = std::max(maxBinding, attributes[i].Binding);

			for (size_t binding = 0; binding < maxBinding + 1; ++binding)
				for (size_t i = 0; i < attributes.size(); ++i)
					if (attributes[i].Binding == binding)
						attributes[i].GetHash(hash);
		}

		size_t MeshFormat::GetVertexSize(size_t binding) const
		{
			if (binding > VertexSizes.size()) return 0;

			return VertexSizes[binding];
		}

		void MeshFormat::Push(const VertexAttributeFormat& attribute)
		{
			size_t offset = 0;// Attributes.size() > 0 ? Attributes.back().Offset + Attributes.back().GetSize() : 0;

			for (size_t i = 0; i < Attributes.size(); ++i)
				if (Attributes[i].Binding == attribute.Binding)
					offset += Attributes[i].GetSize();

			IndexMap[attribute.Name] = Attributes.size();
			Attributes.push_back(attribute);
			Attributes.back().Offset = offset;
			Attributes.back().Index = Attributes.size() - 1;

			while (VertexSizes.size() <= attribute.Binding)
				VertexSizes.push_back(0);

			VertexSizes[attribute.Binding] += attribute.GetSize();
		}

		struct stringpeak { float a[25] = {}; };

		void MeshFormat::Copy(const void* const * source, void** destination, const std::shared_ptr<MeshFormat>& destinationFormat, size_t vertices, size_t offsetCount) const
		{
			std::vector<int> mappings(Attributes.size());

			if (false) {
				stringpeak peak;
				peak.a[0] = 0;
			}

			for (size_t i = 0; i < mappings.size(); ++i)
			{
				auto index = destinationFormat->IndexMap.find(Attributes[i].Name);

				if (index != destinationFormat->IndexMap.end())
					mappings[i] = (int)index->second;
				else
					mappings[i] = -1;
			}

			for (size_t i = 0; i < vertices; ++i)
			{
				for (size_t j = 0; j < mappings.size(); ++j)
				{
					if (mappings[j] != -1)
					{
						const VertexAttributeFormat& sourceAttribute = Attributes[j];
						const VertexAttributeFormat& destinationAttribute = destinationFormat->Attributes[mappings[j]];

						const char* sourceChar = reinterpret_cast<const char*>(source[sourceAttribute.Binding]);
						char* destinationChar = reinterpret_cast<char*>(destination[destinationAttribute.Binding]);

						size_t sourceVertexSize = VertexSizes[sourceAttribute.Binding];
						size_t destinationVertexSize = destinationFormat->VertexSizes[destinationAttribute.Binding];

						sourceAttribute.Copy(
							sourceChar + (i * sourceVertexSize + sourceAttribute.Offset),
							destinationChar + ((i + offsetCount) * destinationVertexSize + destinationAttribute.Offset),
							destinationAttribute.Type
						);
					}
				}
			}
		}

		void MeshFormat::WriteAttribute(const void* const * source, void* destination, size_t attribute, size_t element) const
		{
			char* destinationChar = reinterpret_cast<char*>(destination);

			Attributes[attribute].Copy(
				source[Attributes[attribute].Binding],
				destinationChar + Attributes[attribute].Offset,
				Attributes[attribute].Type
			);
		}

		void MeshFormat::WriteAttribute(const void* const* source, void* destination, const std::string& attribute, size_t element) const
		{
			auto index = IndexMap.find(attribute);

			if (index != IndexMap.end())
				WriteAttribute(source, destination, index->second, element);
		}

		std::shared_ptr<MeshFormat> MeshFormat::GetCachedFormat(unsigned int hash)
		{
			auto entry = Cache.find(hash);

			if (entry != Cache.end())
				return entry->second;

			return nullptr;
		}

		std::shared_ptr<MeshFormat> MeshFormat::GetCachedFormat(int index)
		{
			if (index < 0 || index >= CacheVector.size())
				return nullptr;

			return CacheVector[index];
		}

		void MeshFormat::CacheFormat(unsigned int& hash, const std::shared_ptr<MeshFormat>& format)
		{
			Cache[hash] = format;
			CacheVector.push_back(format);

			format->CachedIndex = CachedFormats;
			++CachedFormats;
		}

		void MeshFormat::CacheFormat(const std::shared_ptr<MeshFormat>& format)
		{
			unsigned int hash = format->GetHash();

			if (GetCachedFormat(hash) == nullptr)
				CacheFormat(hash, format);
		}

		unsigned int MeshFormat::GetHash() const
		{
			const unsigned int offsetBasis = 0x811c9dc5;

			unsigned long long hash = offsetBasis;

			VertexAttributeFormat::GetHash(hash, Attributes);

			return (unsigned int)hash;
		}

		const VertexAttributeFormat* MeshFormat::GetAttribute(const std::string& name) const
		{
			for (size_t i = 0; i < Attributes.size(); ++i)
				if (Attributes[i].Name == name)
					return &Attributes[i];

			return nullptr;
		}

		size_t MeshFormat::GetAttributeIndex(const std::string& name) const
		{
			for (size_t i = 0; i < Attributes.size(); ++i)
				if (Attributes[i].Name == name)
					return i;

			return -1;
		}

		std::shared_ptr<MeshFormat> MeshFormat::GetFormat(const std::vector<VertexAttributeFormat>& attributes)
		{
			unsigned long long hashLong;

			VertexAttributeFormat::GetHash(hashLong, attributes);

			unsigned int hash = (unsigned int)hashLong;

			std::shared_ptr<MeshFormat> meshFormat = GetCachedFormat(hash);

			if (meshFormat == nullptr)
			{
				meshFormat = Engine::Create<MeshFormat>();

				for (size_t i = 0; i < attributes.size(); ++i)
					meshFormat->Push(attributes[i]);

				CacheFormat(hash, meshFormat);
			}

			return meshFormat;
		}

		void MeshData::SetFormat(const std::shared_ptr<MeshFormat>& format)
		{
			Format = format;

			while (Data.size() < Format->GetBindingCount())
				Data.push_back(std::vector<unsigned char>());

			DataPointers.resize(Data.size());

			for (size_t i = 0; i < DataPointers.size(); ++i)
				DataPointers[i] = Data[i].data();
		}

		size_t MeshData::GetTotalSize(size_t binding) const
		{
			if (Format == nullptr) return 0;

			return Format->GetVertexSize(binding) * Vertices;
		}

		size_t MeshData::GetBindingCount() const
		{
			if (Format == nullptr) return 0;

			return Format->GetBindingCount();
		}

		void MeshData::PushVertices(size_t count, bool pushIndices)
		{
			if (Format == nullptr) return;

			for (size_t binding = 0; binding < Data.size(); ++binding)
			{
				size_t newSize = Data[binding].size() + count * Format->GetVertexSize(binding);

				Data[binding].resize(newSize);
				DataPointers[binding] = Data[binding].data();
			}

			if (pushIndices)
			{
				size_t indexCount = Indices.size();
				size_t newIndexCount = indexCount + count;

				Indices.resize(newIndexCount);

				for (size_t i = 0; i < count; ++i)
					Indices[indexCount + i] = (int)(Vertices + i);
			}

			Vertices += count;
		}

		void MeshData::PushIndices(size_t count)
		{
			Indices.resize(Indices.size() + count);
		}

		void MeshData::PushIndex(size_t location, int index)
		{
			Indices[location] = index;
		}

		void MeshData::PushIndices(const std::vector<int>& indices)
		{
			Indices = indices;
		}

		void MeshData::ResetData()
		{
			for (size_t binding = 0; binding < Data.size(); ++binding)
			{
				Data[binding].clear();
				DataPointers[binding] = nullptr;
			}

			Indices.clear();

			Vertices = 0;
		}
	}
}