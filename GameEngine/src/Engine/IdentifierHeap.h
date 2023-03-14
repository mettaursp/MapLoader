#pragma once

#include <vector>

class IDHeap
{
public:
	~IDHeap();

	size_t RequestID();
	void Release(size_t id);
	size_t Size() const;
	size_t AllocatedIDs() const;
	bool NodeAllocated(size_t id) const;
	void Clear();
	void ShrinkToAllocated();

	template <typename T>
	size_t Allocate(std::vector<T>& vector, T&& newValue);

	template <typename T>
	size_t Allocate(std::vector<T>& vector, const T& newValue);

private:
	typedef std::vector<unsigned char> NodeHeap;
	const unsigned char Used = 0x1;
	const unsigned char ChildrenUsed = 0x2;

	NodeHeap Nodes;
	size_t Allocated = 0;
	size_t Capacity = 0;

	size_t Allocate();
	void Write(size_t index, unsigned char bits, unsigned char srcMask);
	void Write(size_t index, unsigned char bits, bool value);
	constexpr unsigned char Read(size_t index) const;
	constexpr unsigned char Read(size_t index, unsigned char mask) const;
};

template <typename T>
size_t IDHeap::Allocate(std::vector<T>& vector, T&& newValue)
{
	size_t id = RequestID();

	if (id >= vector.size())
		vector.push_back(newValue);
	else
		vector[id] = newValue;

	return id;
}

template <typename T>
size_t IDHeap::Allocate(std::vector<T>& vector, const T& newValue)
{
	size_t id = RequestID();

	if (id >= vector.size())
		vector.push_back(newValue);
	else
		vector[id] = newValue;

	return id;
}