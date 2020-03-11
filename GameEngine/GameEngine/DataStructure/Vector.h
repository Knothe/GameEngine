#pragma once
#include <iostream>
#include "../MessageException.h"
#include "List.h"

template<class T>
class Vector
{
private:
	T* arr;
	int size;
	int capacity;
	void CopyNewVector(int newSize);

public:
	Vector();
	Vector(int size);
	T GetAt(unsigned int index);
	T GetLast();
	void PushBack(T val);
	void Clear();
	void TightVector();
	int GetSize();
	void Print();
	bool hasValue(T val);
	void PushAt(int pos, T val);
	void operator=(List<T>* l);
	void operator+(Vector<T>* v);
	void order();
};
/*
Stats class with capacity = 0 and size = 0
*/
template<class T>
Vector<T>::Vector() {
	size = 0;
	capacity = 1;
	arr = new T[capacity];
}
/*
Starts with a set size and capacity
@param size: starting size of the vector
*/
template<class T>
Vector<T>::Vector(int size) {
	this->size = size;
	capacity = size;
	arr = new T[capacity];
	for (int i = 0; i < size; i++) {
		arr[i] = NULL;
	}
}
/*
Return value in a position inside the bounds of the size
@param index: position in the vector
@return value
*/
template<class T>
T Vector<T>::GetAt(unsigned int index) {
	if (index < size)
		return arr[index];
}
/*
Increments the size of the vector and adds a value at the end
@param val: value to add
*/
template<class T>
void Vector<T>::PushBack(T val) {
	if (size >= capacity)
		CopyNewVector(capacity * 2);

	arr[size] = val;
	size++;
}
/*
Clears the vector and defines the capacity = 0
*/
template<class T>
void Vector<T>::Clear() {
	size = 0;
	capacity = 1;
	delete arr;
	arr = new T[capacity];
}
/*
Sets the capacity equal to the size of the vector
*/
template <class T>
void Vector<T>::TightVector() {
	if (capacity > size)
		CopyNewVector(size);

}
/*
Sets new size for the vector
If the new size is bigger the data stays
If the new size is smaller the data is deleted
*/
template <class T>
void Vector<T>::CopyNewVector(int newSize) {
	T* newArr = new T[newSize];
	if (newSize >= size) {
		for (int i = 0; i < size; i++) {
			newArr[i] = arr[i];
		}
	}
	capacity = newSize;
	arr = newArr;
}
/*
Returns vector size
*/
template<class T>
int Vector<T>::GetSize() {
	return size;
}
/*
TODO: Remember to delete later
*/
template<class T>
void Vector<T>::Print() {
	for (int i = 0; i < size; i++) {
		std::cout << arr[i] << std::endl;
	}
	std::cout << "Size: " << size << std::endl;
	std::cout << "Capacity: " << capacity << std::endl;
}
/*
Searchs for a specific value
@param val: value to search
@return true if exists, false if not
*/
template<class T>
bool Vector<T>::hasValue(T val) {
	for (int i = 0; i < size; i++) {
		if (arr[i] == val)
			return true;
	}
	return false;
}
/*
Adds a value at a certain position
@param pos: position to push
@param val: value to add
*/
template<class T>
void  Vector<T>::PushAt(int pos, T val) {
	if (pos < size) {
		arr[pos] = val;
	}
}
/*
Equals this vector to a list
@param l: list to equal
*/
template<class T>
void  Vector<T>::operator=(List<T>* l) {
	size = l->size;
	capacity = size;
	T* newArr = new T[size];
	for (int i = 0; i < size; i++) {
		newArr[i] = l->get_at(i);
	}
	arr = newArr;
}
/*
Pushes another vector at the back of this one
@param v: vector to push
*/
template<class T>
void Vector<T>::operator+(Vector<T>* v) {
	for (int i = 0; i < v->size; i++)
		PushBack(v->GetAt(i));
}
/*
Orders the vector
*/
template<class T>
void Vector<T>::order() {
	int biggest;
	T temp;
	for (int i = 0; i < size; i++) {
		biggest = i;
		for (int j = i; j < size; j++) {
			if (*arr[biggest] < *arr[j])
				biggest = j;
		}
		temp = arr[i];
		arr[i] = arr[biggest];
		arr[biggest] = temp;
	}
}
/*
@return last object in the vector
*/
template<class T>
T Vector<T>::GetLast() {
	if (size > 0)
		return  arr[size - 1];
	return NULL;
}
