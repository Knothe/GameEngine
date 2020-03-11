#pragma once
#include "NodoS.h"

template<class T>
class Stack
{
private:
	NodoS<T>* first;
	int size;
public:
	Stack();
	~Stack();
	void Push(T val);
	void Pop();
	void Clear();
	int GetSize();
	T Top();
};
/*
Starts the Stack with NULL
*/
template<class T>
Stack<T>::Stack() {
	first = NULL;
	size = 0;
}
/*

*/
template<class T>
Stack<T>::~Stack() {

}
/*
Pushes a value at the top of the Stack
@param val: value to add
*/
template<class T>
void Stack<T>::Push(T val) {
	size++;
	NodoS<T>* n = new NodoS<T>(val);
	n->next = first;
	first = n;
}
/*
Deletes the value at the top of the stack
*/
template<class T>
void Stack<T>::Pop() {
	if (size > 1) {
		first = first->next;
		size--;
	}
	else {
		size = 0;
		first = NULL;
	}
}
/*
Deletes all the stack
*/
template<class T>
void Stack<T>::Clear() {
	size = 0;
	first = NULL;
}
/*
@return the size of the stack
*/
template<class T>
int Stack<T>::GetSize() {
	return size;
}
/*
@return top value of the stack
*/
template<class T>
T Stack<T>::Top() {
	return first->value;
}