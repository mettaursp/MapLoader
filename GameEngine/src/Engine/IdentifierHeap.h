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

	template <typename T>
	size_t Allocate(std::vector<T>& vector, T&& newValue);

private:
	typedef std::vector<unsigned char> NodeHeap;
	const unsigned char Used = 0x1;
	const unsigned char ChildrenUsed = 0x2;

	NodeHeap Nodes;
	size_t Allocated = 0;

	size_t Allocate();
	void Write(size_t index, unsigned char bits, unsigned char srcMask);
	void Write(size_t index, unsigned char bits, bool value);
	unsigned char Read(size_t index) const;
	unsigned char Read(size_t index, unsigned char mask) const;
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