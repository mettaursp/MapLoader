#include "IdentifierHeap.h"

IDHeap::~IDHeap()
{
	Clear();
}

constexpr unsigned short rshift(unsigned short value, int offset)
{
	return offset > 0 ? value << offset : value >> -offset;
}

void IDHeap::Write(size_t index, unsigned char bits, unsigned char srcMask)
{
	unsigned char& value = Nodes[index / 4];
	size_t offset = 2 * (index % 4);
	srcMask = (unsigned char)rshift(0xFCFF, ((int)offset - 8)) | (srcMask << offset);
	value = ((unsigned short)value & ((unsigned short)srcMask)) | (bits << offset);
}

void IDHeap::Write(size_t index, unsigned char bits, bool value)
{
	Write(index, value ? bits : 0, (unsigned char)(0x3 ^ bits));
}

constexpr unsigned char IDHeap::Read(size_t index) const
{
	unsigned char value = Nodes[index / 4];
	size_t offset = 2 * (index % 4);
	return (value >> offset) & 0x3;
}

constexpr unsigned char IDHeap::Read(size_t index, unsigned char mask) const
{
	return (Read(index) & mask) != 0;
}

size_t IDHeap::RequestID()
{
	size_t id = Allocate();

	++Allocated;

	Write(id, Used, true);

	if (id > 0)
	{
		size_t currentID = (id - 1) / 2;

		while (currentID < Capacity)
		{
			size_t left = 2 * currentID + 1;
			size_t right = 2 * currentID + 2;

			bool childrenUsed = (left >= Capacity || Read(left, ChildrenUsed)) && (right >= Capacity || Read(right, ChildrenUsed));

			Write(currentID, ChildrenUsed, childrenUsed);

			if (currentID == 0)
				currentID = -1;
			else
				currentID = (currentID - 1) / 2;
		}
	}

	return id;
}
void IDHeap::Release(size_t id)
{
	if (id >= Capacity || !Read(id, Used))
		return;

	--Allocated;

	Write(id, Used, false);

	if (id == 0)
		return;

	id = (id - 1) / 2;

	while (id < Capacity)
	{
		Write(id, ChildrenUsed, false);

		if (id == 0)
			id = -1;
		else
			id = (id - 1) / 2;
	}
}

size_t IDHeap::Allocate()
{
	if (Nodes.size() > 0 && !Read(0, Used))
		return 0;

	if (Nodes.size() > 0 && !Read(0, ChildrenUsed))
	{
		size_t id = 0;

		while (Read(id, Used))
		{
			size_t left = 2 * id + 1;
			size_t right = 2 * id + 2;

			if (left < int(Capacity) && (!Read(left, Used) || !Read(left, ChildrenUsed)))
				id = left;
			else if (right < int(Capacity) && (!Read(right, Used) || !Read(right, ChildrenUsed)))
				id = right;
			else
				throw "shts fucked";
		}

		return id;
	}
	else
	{
		size_t capacity = Nodes.size() * 4;
		size_t id = Capacity;

		if (id >= capacity)
		{
			Nodes.push_back(0x3);
		}
		else
		{
			Write(id, Used | ChildrenUsed, true);
		}

		++Capacity;

		return id;
	}
}

size_t IDHeap::Size() const
{
	return Nodes.size() * 4;
}

size_t IDHeap::AllocatedIDs() const
{
	return Allocated;
}

bool IDHeap::NodeAllocated(size_t id) const
{
	if (id >= 0 && id < Capacity)
		return Read(id, Used);
	else
		throw "Attempt to access out of bounds ID";
}

void IDHeap::Clear()
{
	Nodes.clear();
	Allocated = 0;
	Capacity = 0;
}

void IDHeap::ShrinkToAllocated()
{
	Nodes.resize((Capacity / 4) + std::max(1ull, Capacity % 4));
	std::memset(Nodes.data(), 0xFF, Nodes.size());
}