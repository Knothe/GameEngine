#pragma once
#include "NodeL.h"
#include "../Singletons/StackAllocator.h"

template <class T>
class List
{
public:
	NodeL<T>* first;
	NodeL<T>* last;
	void Add(List<T>* l);
	int size;
	List();
	~List();
	void clear();
	void push_back(T val);
	T get_at(int index);
	bool find(T val);
	bool pushOrdered(T val);
	void deleteLast();
};
/*
initializes the list
*/
template <class T>
List<T>::List() {
	first = NULL;
	last = NULL;
	size = 0;
}
template <class T>
List<T>::~List() {

}
/*
Adds a value at the end of the list
@param val: value to add
*/
template <class T>
void List<T>::push_back(T val) {
	void* buf = StackAllocator::GetPtr()->alloc(sizeof(NodeL<T>));
	if (!first) {
		first = new(buf) NodeL<T>(val, 0);
		last = first;
	}
	else {
		last->next = new(buf) NodeL<T>(val, size);
		last = last->next;
	}
	size++;
}
/*
@param index: index of the object
@return value in a defined index
*/
template <class T>
T List<T>::get_at(int index) {
	NodeL<T>* it = first;
	while (it != NULL) {
		if (it->index == index)
			return it->value;
		it = it->next;
	}
	return NULL;
}
/*
Clears the List
*/
template<class T>
void List<T>::clear() {
	first = NULL;
	last = NULL;
	size = 0;
}
/*
Asks if an object exists in the list
@param val: value to search
@return true if the value exists
*/
template<class T>
bool List<T>::find(T val) {
	NodeL<T>* it = first;
	while (it != NULL) {
		if (it->value == val)
			return true;
		it = it->next;
	}
	return false;
}
/*
Adds a list to this list
@param l: list to add
*/
template<class T>
void List<T>::Add(List<T>* l) {
	for (int i = 0; i < l->size; i++) {
		push_back(l->get_at(i));
	}
}
/*
Pushes a value at his ordered position
@param val: value to push
@return true if it added to the list
*/
template<class T>
bool List<T>::pushOrdered(T val) {
	void* buf = StackAllocator::GetPtr()->alloc(sizeof(NodeL<T>));
	NodeL<T>* it = first;
	NodeL<T>* temp = new(buf) NodeL<T>(val);
	if (it->value <= val) {
		temp->next = first;
		first = temp;
		deleteLast();
		return true;
	}

	while (it) {
		if (it->next) {
			if (it->value > val&& it->next->value <= val) {
				temp->next = it->next;
				it->next = temp;
				deleteLast();
				return true;
			}
		}
		it = it->next;
	}
	return false;
}
/*
Deletes last item in the list
*/
template<class T>
void List<T>::deleteLast() {
	NodeL<T>* it = first;
	while (it) {
		if (it->next == last) {
			last = it;
			it->next = NULL;
		}
		it = it->next;
	}
}