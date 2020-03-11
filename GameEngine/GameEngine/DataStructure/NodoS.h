#pragma once
#include <iostream>

template<class T>
class NodoS
{
public:
	T value;
	NodoS* next;
	NodoS();
	NodoS(T val);
	~NodoS();
};
/*
Starts node with NULL
*/
template<class T>
NodoS<T>::NodoS() {
	next = NULL;
}
/*
Starts node with value
@param val: Value to save
*/
template<class T>
NodoS<T>::NodoS(T val) {
	next = NULL;
	value = val;
}

template<class T>
NodoS<T>::~NodoS() {
}
