#pragma once

#include <vector>
#include <memory>
#include <string>
#include <map>
#include <functional>
#include <stdexcept>

#include <Engine/Objects/Object.h>
#include <Engine/VulkanGraphics/Core/BufferFormat.h>

namespace Engine
{
	namespace Graphics
	{
		struct VertexAttributeFormat
		{
			typedef AttributeDataTypeEnum::AttributeDataType AttributeDataType;

			AttributeDataType Type = AttributeDataType::Float32;
			size_t ElementCount = 1;
			std::string Name;
			size_t Binding = 0;
			size_t Offset = 0;
			size_t Index = 0;

			size_t GetElementSize() const;
			size_t GetSize() const;

			void Copy(const void* source, void* destination, AttributeDataType destinationType) const;
			void GetHash(unsigned long long& hash) const;

			static void GetHash(unsigned long long& hash, const std::vector<VertexAttributeFormat>& attributes);
		};

		class MeshFormat : public Object
		{
		public:
			size_t GetVertexSize(size_t binding) const;
			size_t GetBindingCount() const { return VertexSizes.size(); }

			void Push(const VertexAttributeFormat& attribute);
			void Copy(const void* const* source, void** destination, const std::shared_ptr<MeshFormat>& destinationFormat, size_t vertices, size_t offsetCount = 0) const;
			void WriteAttribute(const void* const * source, void* destination, size_t attribute, size_t element) const;
			void WriteAttribute(const void* const * source, void* destination, const std::string& attribute, size_t element) const;
			unsigned int GetHash() const;
			int GetCachedIndex() const { return CachedIndex; }

			const std::vector<VertexAttributeFormat>& GetAttributes() const { return Attributes; }
			const VertexAttributeFormat* GetAttribute(const std::string& name) const;
			size_t GetAttributeIndex(const std::string& name) const;

			template <typename T>
			T& GetAttribute(void* const* source, size_t vertex, size_t attributeIndex) const;

			template <typename T>
			const T& GetAttribute(const void* const* source, size_t vertex, size_t attributeIndex) const;

			template <typename T>
			void ForEach(const void* const* source, size_t attributeIndex, size_t vertices, const std::function<void(const T&)>& callback) const;

			static std::shared_ptr<MeshFormat> GetFormat(const std::vector<VertexAttributeFormat>& attributes);
			static std::shared_ptr<MeshFormat> GetCachedFormat(unsigned int hash);
			static std::shared_ptr<MeshFormat> GetCachedFormat(int index);
			static void CacheFormat(unsigned int& hashString, const std::shared_ptr<MeshFormat>& format);
			static void CacheFormat(const std::shared_ptr<MeshFormat>& format);

		private:
			typedef std::map<unsigned int, std::shared_ptr<MeshFormat>> MeshFormatMap;
			typedef std::vector<std::shared_ptr<MeshFormat>> MeshFormatVector;

			std::vector<VertexAttributeFormat> Attributes;
			std::map<std::string, size_t> IndexMap;

			static inline MeshFormatMap Cache = MeshFormatMap();
			static inline MeshFormatVector CacheVector = MeshFormatVector();
			static inline int CachedFormats = 0;

			size_t Bindings = 0;
			std::vector<size_t> VertexSizes;
			int CachedIndex = -1;
		};

		class MeshData : public Object
		{
		public:
			void SetFormat(const std::shared_ptr<MeshFormat>& format);
			const std::shared_ptr<MeshFormat>& GetFormat() const { return Format; }

			size_t GetTotalSize(size_t binding) const;
			size_t GetBindingCount() const;
			size_t GetVertices() const { return Vertices; }
			size_t GetTriangleVertices() const { return Indices.size(); }
			const void* const* GetData() const { return DataPointers.data(); }
			void** GetData() { return DataPointers.data(); }
			void* GetIndexData() { return Indices.data(); }
			const void* GetIndexData() const { return Indices.data(); }

			void PushVertices(size_t count = 1, bool pushIndices = false);
			void PushIndices(size_t count = 1);
			void PushIndices(const std::vector<int>& indices);
			void PushIndex(size_t location, int index);
			void ResetData();

			template <typename T>
			T& GetAttribute(size_t vertex, size_t attributeIndex);

			template <typename T>
			const T& GetAttribute(size_t vertex, size_t attributeIndex) const;

			template <typename T>
			void ForEach(size_t attributeIndex, const std::function<void(const T&)>& callback) const;

			//const std::vector<unsigned char>& GetVertexBuffer() const { return Data; }
			const std::vector<int>& GetIndexBuffer() const { return Indices; }

		private:
			std::shared_ptr<MeshFormat> Format;

			size_t Vertices = 0;
			std::vector<std::vector<unsigned char>> Data;
			std::vector<void*> DataPointers;
			std::vector<int> Indices;
		};

		template <typename T>
		T& MeshFormat::GetAttribute(void* const* source, size_t vertex, size_t attributeIndex) const
		{
			if (attributeIndex > Attributes.size())
				throw std::out_of_range("attribute out of bounds");

			const VertexAttributeFormat& attribute = Attributes[attributeIndex];

			if (sizeof(T) != attribute.GetSize())
				throw std::invalid_argument("template parameter size does not match attribute size");

			size_t vertexSize = VertexSizes[attribute.Binding];

			char* buffer = reinterpret_cast<char*>(source[attribute.Binding]);
			char* data = buffer + (vertex * vertexSize + attribute.Offset);

			return *reinterpret_cast<T*>(data);
		}

		template <typename T>
		const T& MeshFormat::GetAttribute(const void* const* source, size_t vertex, size_t attributeIndex) const
		{
			if (attributeIndex > Attributes.size())
				throw std::out_of_range("attribute out of bounds");

			const VertexAttributeFormat& attribute = Attributes[attributeIndex];

			if (sizeof(T) != attribute.GetSize())
				throw std::invalid_argument("template parameter size does not match attribute size");

			size_t vertexSize = VertexSizes[attribute.Binding];

			const char* buffer = reinterpret_cast<const char*>(source[attribute.Binding]);
			const char* data = buffer + (vertex * vertexSize + attribute.Offset);

			return *reinterpret_cast<const T*>(data);
		}

		template <typename T>
		T& MeshData::GetAttribute(size_t vertex, size_t attributeIndex)
		{
			if (vertex > Vertices)
				throw std::out_of_range("vertex out of bounds");

			return Format->GetAttribute<T>(DataPointers.data(), vertex, attributeIndex);
		}

		template <typename T>
		const T& MeshData::GetAttribute(size_t vertex, size_t attributeIndex) const
		{
			if (vertex > Vertices)
				throw std::out_of_range("vertex out of bounds");

			return Format->GetAttribute<T>(DataPointers.data(), vertex, attributeIndex);
		}

		template <typename T>
		void MeshFormat::ForEach(const void* const* source, size_t attributeIndex, size_t vertices, const std::function<void(const T&)>& callback) const
		{
			if (attributeIndex >= Attributes.size())
				return;

			const VertexAttributeFormat& attribute = Attributes[attributeIndex];

			if (sizeof(T) != attribute.GetSize())
				return;

			for (size_t i = 0; i < vertices; ++i)
			{
				size_t vertexSize = VertexSizes[attribute.Binding];

				const char* buffer = reinterpret_cast<const char*>(source[attribute.Binding]);
				const char* data = buffer + (i * vertexSize + attribute.Offset);

				callback(*reinterpret_cast<const T*>(data));
			}
		}

		template <typename T>
		void MeshData::ForEach(size_t attributeIndex, const std::function<void(const T&)>& callback) const
		{
			if (Format == nullptr)
				return;

			Format->ForEach(DataPointers.data(), attributeIndex, Vertices, callback);
		}
	}
}