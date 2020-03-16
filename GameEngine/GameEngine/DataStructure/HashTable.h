#pragma once
#include <iostream>
#include "Vector.h"
#include "../String.h"

using std::wcout;
using std::endl;

template<class T>
struct Object {
	Object(String id, T val) : identifier(id), obj(val) {}
	String identifier;
	T obj;
};

template<class T>
class HashTable
{
public:
	HashTable();
	HashTable(int size);
	~HashTable();
	void Add(String id, T val);
	T Search(String id);
	void PrintAll();
	void Delete(int id);
private:
	Vector<Vector<Object<T>>>* vector;
	int size;
	int capacity;
	void AddVectors(int cap);
	int CalculateFirst(int size, String id);
	int CalculateSecond(int size, String id);
	void IncrementVector(Vector<Object<T>>* v1, Object<T>* add);
};
/*
Inicializamos nuestra tabla con valores predeterminados
*/
template<class T>
HashTable<T>::HashTable() {
	vector = new Vector<Vector<Object<T>>>(10);
	AddVectors(3);
	size = 0;
	capacity = 30;
}
/*
Constructor with a set capacity
@param cap: starting capacity
*/
template<class T>
HashTable<T>::HashTable(int cap) {
	int c = (cap / 2) + 1;
	vector = new Vector<Vector<Object<T>>>(c);
	AddVectors(3);
	capacity = c + (c * 3);
	size = 0;
}
/*

*/
template<class T>
HashTable<T>::~HashTable() {

}
/*
Initialices vectors to each position
@param size: size of the vector
*/
template<class T>
void HashTable<T>::AddVectors(int size) {
	for (int i = 0; i < vector->GetSize(); i++)
		vector->PushAt(new Vector<Object<T>>(size), i);
}
/*
Executes first HashAlgorithm
@param size: size of the vector
@param id: key of the object
@return value from key
*/
template<class T>
int HashTable<T>::CalculateFirst(int size, String id) {
	int c = 0;
	int i = 0;
	for (wchar_t w : id.Get()) {
		i += w;
	}
	while (i != 0) {
		c += i % 10;
		i = i / 10;
	}
	return c % size;
}
/*
Executes second HashAlgorithm
@param size: size of the vector
@param id: key of the object
@return value from key
*/
template<class T>
int HashTable<T>::CalculateSecond(int size, String id) {
	int i = 0;
	for (wchar_t w : id.Get()) {
		i += w;
	}
	int c = (i * i) - (i / 2);
	return c % size;
}
/*
Algorith to add new item
@param id: item key
@param val: value to save
*/
template<class T>
void HashTable<T>::Add(String id, T val) {
	int pos = CalculateFirst(vector->GetSize(), id);
	Vector<Object<T>>* v = vector->GetAtPointer(pos);
	pos = CalculateSecond(v->GetSize(), id);
	Object<T>* o = v->GetAtPointer(pos);
	if (o) {
		if (o->identifier != id) {
			IncrementVector(v, new Object<T>(id, val));
		}
	}
	else {
		v->PushAt(new Object<T>(id, val), pos);
	}
}
/*
Searchs item in the hashTable
@param id: item key
@return value in the position found
*/
template<class T>
T  HashTable<T>::Search(String id) {
	int pos = CalculateFirst(vector->GetSize(), id);
	Vector<Object<T>>* v = vector->GetAtPointer(pos);
	pos = CalculateSecond(v->GetSize(), id);
	Object<T>* o = v->GetAtPointer(pos);
	if (o)
		return o->obj;
	else
		return NULL;
}
/*
Prints all the hashTable in orders
*/
template<class T>
void HashTable<T>::PrintAll() {
	Vector<Object<T>>* v;
	Object<T>* o;
	for (int i = 0; i < vector->GetSize(); i++) {
		v = vector->GetAtPointer(i);
		for (int j = 0; j < v->GetSize(); j++) {
			o = v->GetAtPointer(j);
			if (o)
				wcout << o->obj;
			else
				wcout << L"-";
			wcout << "\t";
		}
		wcout << endl;
	}
	wcout << "____________________________________________________________________" << endl << endl;
}
/*
Deletes an item in the table
@param id: key to delete
*/
template<class T>
void HashTable<T>::Delete(int id) {
	int pos = CalculateFirst(vector->GetSize(), id);
	Vector<Object<T>>* v = vector->GetAtPointer(pos);
	pos = CalculateSecond(v->GetSize(), id);
	if (v->GetAtPointer(pos)->identifier == id)
		v->PushAt(NULL, pos);

}
/*
Increments Vector size and reacomodates every data
@param v1: pointer to vector to resize
@param add: objecto to add to de table
*/
template<class T>
void HashTable<T>::IncrementVector(Vector<Object<T>>* v1, Object<T>* add) {
	Vector<Object<T>> v2;
	v2 = (*v1);
	Object<T>* obj;
	v1->SetNewSize(v1->GetSize() * 2);
	int pos;
	for (int i = 0; i < v2.GetSize(); i++) {
		obj = v2.GetAtPointer(i);
		if (obj) {
			pos = CalculateSecond(v1->GetSize(), obj->identifier);
			v1->PushAt(obj, pos);
		}
	}
	pos = CalculateSecond(v1->GetSize(), add->identifier);
	v1->PushAt(add, pos);
}