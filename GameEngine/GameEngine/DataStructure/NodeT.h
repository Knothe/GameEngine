#pragma once
#include <iostream>

template<class U, class T>
class NodeT
{
public:
	T value;
	NodeT* right;
	NodeT* left;
	NodeT* parent;
	U key;
	int prio;
	NodeT(U k, T v) : key(k), value(v) {
		right = NULL;
		left = NULL;
		parent = NULL;
		prio = 0;
	}
};