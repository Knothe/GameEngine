#pragma once
#include  <iostream>

template<class T>
class NodeL
{
public:
	T value;
	NodeL* next;
	int index;
	NodeL(T v) : value(v) {
		next = NULL;
		index = 0;
	}
	NodeL(T v, int n) : value(v), index(n) {
		next = NULL;
	}
};

