#pragma once
#include <cstdlib>
#include <iostream>

class StackAllocator
{
public:
	static StackAllocator* GetPtr();
	typedef size_t Marker;
	void* alloc(size_t size);
	Marker getMarker();
	void clear();

private:
	StackAllocator();
	static StackAllocator* ptr;
	Marker maxSize;
	void* start;
	Marker marker;
	Marker prev;
	Marker first;
};

