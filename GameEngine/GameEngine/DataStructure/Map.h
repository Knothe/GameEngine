#pragma once
#include "NodeM.h"

template <class T, class U>
class Map
{
public:
	NodeM<T, U>* first;
	NodeM<T, U>* last;
	int size;
	Map();
	~Map();

	void push(T key, U val);
	U get(T key);
	bool findKey(T key);
};

template <class T, class U>
Map<T, U>::Map() {
	size = 0;
	first = NULL;
}

template <class T, class U>
Map<T, U>::~Map() {

}
/*
@param key: Identificador
@param val: valor ligado al identificador
*/
template <class T, class U>
void Map<T, U>::push(T key, U val) {
	
	if (!first) {
		first = new NodeM<T, U>(key, val);
		last = first;
	}
	else {
		NodeM<T, U>* temp = first;
		while (temp) {
			if (temp->key == key) {
				temp->value = val;
				return;
			}
			temp = temp->next;
		}
		last->next = new NodeM<T, U>(key, val);
		last = last->next;
	}
	size++;
}
/*
@param key: Llave a buscar
@return valor ligado a key
*/
template <class T, class U>
U Map<T, U>::get(T key) {
	NodeM<T, U>* temp = first;
	while (temp) {
		if (temp->key == key)
			return temp->value;
		temp = temp->next;
	}
	return U();
}
/*
@param key: llave a buscar si existe
@return si existe
*/
template <class T, class U>
bool Map<T, U>::findKey(T key) {
	NodeM<T, U>* temp = first;
	while (temp) {
		if (temp->key == key)
			return true;
		temp = temp->next;
	}
	return false;
}

