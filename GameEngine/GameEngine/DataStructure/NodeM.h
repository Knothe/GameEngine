#pragma once
#include <iostream>

template<class T, class U>
class NodeM {
public:
	T value;
	U key;
	NodeM* next;
	NodeM(U k, T v) : key(k), value(v) {
		next = NULL;
	}
};