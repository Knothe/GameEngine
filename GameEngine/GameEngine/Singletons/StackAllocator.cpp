#include "StackAllocator.h"

StackAllocator* StackAllocator::ptr;

StackAllocator* StackAllocator::GetPtr() {
	if (!ptr)
		ptr = new StackAllocator(1024 * 1024 * 512);
	return ptr;
}


StackAllocator::StackAllocator(size_t size)
{
	static_assert(sizeof(size_t) >= sizeof(void*), "the size of uint must be greater than or equal to the size of a pointer");
	maxSize = size;
	start = malloc(size);
	if (start == NULL)
	{
		printf("Error al asignar memoria");
	}
	first = (size_t)start;
	marker = first;
	prev = marker;
}

void* StackAllocator::alloc(size_t size)
{
	if (first + maxSize >= prev + size)
	{
		prev = marker;
		marker = marker + size;
		return (void*)prev;
	}
	else return NULL;
}

StackAllocator::Marker StackAllocator::getMarker()
{
	return marker;
}

void StackAllocator::clear()
{
	marker = (size_t)start;
}