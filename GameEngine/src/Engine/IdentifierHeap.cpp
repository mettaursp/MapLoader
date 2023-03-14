#include "IdentifierHeap.h"

IDHeap::~IDHeap()
{
	Clear();
}

void IDHeap::Write(size_t index, unsigned char bits, unsigned char srcMask)
{
	unsigned char& value = Nodes[index / 4];
	size_t offset = 2 * (index % 4);
	srcMask = (unsigned char)(0xFCFF << (offset - 8)) | srcMask;
	value = (value & srcMask) | bits;
}

void IDHeap::Write(size_t index, unsigned char bits, bool value)
{
	Write(index, value ? bits : 0, (unsigned char)(0x3 ^ bits));
}

unsigned char IDHeap::Read(size_t index) const
{
	unsigned char value = Nodes[index / 4];
	size_t offset = 2 * (index % 4);
	return (value >> offset) & 0x3;
}

unsigned char IDHeap::Read(size_t index, unsigned char mask) const
{
	return (Read(index) & mask) != 0;
}

size_t IDHeap::RequestID()
{
	size_t id = Allocate();

	Write(id, Used, true);

	if (id > 0)
	{
		size_t currentID = (id - 1) / 2;

		while (currentID < Allocated)
		{
			size_t left = 2 * currentID + 1;
			size_t right = 2 * currentID + 2;

			bool childrenUsed = (left >= Allocated || Read(left, ChildrenUsed)) && (right >= Allocated || Read(right, ChildrenUsed));

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
	if (id >= Allocated || !Read(id, Used))
		return;

	Write(id, Used, false);

	if (id == 0)
		return;

	id = (id - 1) / 2;

	while (id >= 0)
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

			if (left < int(Allocated) && (!Read(left, Used) || !Read(left, ChildrenUsed)))
				id = left;
			else if (right < int(Allocated) && (!Read(right, Used) || !Read(right, ChildrenUsed)))
				id = right;
			else
				throw "shts fucked";
		}

		return id;
	}
	else
	{
		size_t capacity = Nodes.size() * 4;
		size_t id = Allocated;

		if (id >= capacity)
		{
			Nodes.push_back(0x3);
		}
		else
		{
			Write(id, Used | ChildrenUsed, true);
		}

		++Allocated;

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
	if (id >= 0 && id < Allocated)
		return Read(id, Used);
	else
		throw "Attempt to access out of bounds ID";
}

void IDHeap::Clear()
{
	Nodes.clear();
	Allocated = 0;
}