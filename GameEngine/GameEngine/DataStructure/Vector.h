#pragma once
#include <iostream>
using std::cout;
using std::endl;

template <class T>
class Vector
{
public:
	Vector();
	Vector(int s);
	~Vector();
	void PushBack(T val); // PushAt ?
	void PushAt(T val, int n);
	void PushAt(T* val, int n);
	T GetAt(int n);
	T* GetAtPointer(int n);
	int GetSize();
	void ClearVector();
	int GetCurrent();
	void SetNewSize(int n);
	void Print();
	void operator=(Vector<T> other);
private:
	T** array; // Doble apuntador?
	int size;
	int current; // ? 
	void DoubleSize();
};
/*
Creates new array with predetermined size
*/
template <class T>
Vector<T>::Vector() {
	size = 1;
	current = 0;
	array = new T * [1];
	ClearVector();
}
/*
Starts object with indicated size
@param s: size of the array
*/
template <class T>
Vector<T>::Vector(int s) {
	size = s;
	current = 0;
	array = new T * [size];
	ClearVector();
}
/*

*/
template <class T>
Vector<T>::~Vector() {

}
/*
Adds value at the end of the array
@param val: value to push
*/
template <class T>
void Vector<T>::PushBack(T val) {
	if (current == size)
		DoubleSize();

	array[current] = new T(val);
	current++;
}
/*
Adds value at an specified position
@param val: value to add
@param n: position to add
*/
template <class T>
void Vector<T>::PushAt(T val, int n) {
	if (n < size)
		array[n] = new T(val);
}
/*
Adds a pointer to an specified position
@param val: pointer to the value
@param n: position to add
*/
template <class T>
void Vector<T>::PushAt(T* val, int n) {
	if (n < size)
		array[n] = val;
}
/*
Gets value in a position
@param n: position to get
@return value in the position
*/
template <class T>
T Vector<T>::GetAt(int n) {
	if (n >= current)
		//throw(0);
		return NULL;
	else
		return *array[n];
}
/*
Gets the pointer to a value in a position
@param n: position to get
@return pointer to value in the position
*/
template <class T>
T* Vector<T>::GetAtPointer(int n) {
	if (n >= size)
		//throw(0);
		return NULL;
	else
		return array[n];

}
/*
Gets posible size of the array
@return size of the array
*/
template <class T>
int Vector<T>::GetSize() {
	return size;
}
/*
Gets current number of values in the array
@return current number of values
*/
template<class T>
int Vector<T>::GetCurrent() {
	return current;
}
/*
Doubles the size of the array and mantains current values in position
*/
template<class T>
void Vector<T>::DoubleSize() {
	size *= 2;
	T** n = new T * [size];
	for (int i = 0; i < size; i++)
		n[i] = NULL;
	for (int i = 0; i < current; i++)
		n[i] = array[i];
	delete[] array;
	array = n;
}
/*
Clears all values of the vector
*/
template<class T>
void Vector<T>::ClearVector() {
	for (int i = 0; i < size; i++)
		array[i] = NULL;
}
/*
Equals current Vector to another Vector
*/
template<class T>
void Vector<T>::operator=(Vector<T> other) {
	delete[] array;
	size = other.GetSize();
	T** n = new T * [size];
	for (int i = 0; i < size; i++)
		n[i] = other.GetAtPointer(i);
	array = n;
}
/*
Resizes vector and removes all items
@param n: new size of the vector
*/
template<class T>
void Vector<T>::SetNewSize(int n) {
	delete[] array;
	size = n;
	array = new T * [size];
	for (int i = 0; i < size; i++)
		array[i] = NULL;
}
/*
Prints all items in the vector
*/
template<class T>
void Vector<T>::Print() {
	for (int i = 0; i < size; i++) {
		if (array[i])
			cout << *array[i] << endl;
	}
}
