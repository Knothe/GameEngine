#pragma once
#include "NodeT.h"
#include "../Singletons/StackAllocator.h"

template<class U, class T>
class Tree
{
private:
	void insert(U key, NodeT<U, T>* r);
	void checkPrio(NodeT<U, T>* r);
	void reorderInsert(NodeT<U, T>* r);
	void rotateRight(NodeT<U, T>* r);
	void rotateLeft(NodeT<U, T>* r);
	void rotateLeftRight(NodeT<U, T>* r);
	void rotateRightLeft(NodeT<U, T>* r);
	void updateBack(NodeT<U, T>* r);
	void print(NodeT<U, T>* r);
public:
	NodeT<U, T>* root;
	NodeT<U, T>* last;
	Tree();
	~Tree();
	void insert(U key, T val);
	void remove(U key);
	bool find(U key);
	T GetValue(U key);
	void print();
};
/*
Starts tree without values
*/
template<class U, class T>
Tree<U, T>::Tree() {
	root = NULL;
	last = NULL;
}
/**/
template<class U, class T>
Tree<U, T>::~Tree() {

}
/*
Inserts value at the root or starts recursive insert function
@param key: key of the value to insert
@param val: value to insert
*/
template<class U, class T>
void Tree<U, T>::insert(U key, T val) {
	if (find(key))
		return;
	void* buf = StackAllocator::GetPtr()->alloc(sizeof(NodeT<U, T>));
	last = new(buf) NodeT<U, T>(key, val);
	if (root == NULL) 	root = last;
	else {
		insert(key, root);
	}
}
/*
Removes a value from the tree
@param key: value to remove
*/
template<class U, class T>
void Tree<U, T>::remove(U key) {
	NodeT<U, T>* temp = root;
	bool wasFound = false;
	while (!wasFound) {
		if (!temp)	return;
		if (temp->value == key)		wasFound = true;
		else if (temp->value > key)		temp = temp->left;
		else	temp = temp->right;
	}
	if (temp == root) {
		if (temp->left && temp->right) {
			temp = getClosestDown(root);
			temp->right = root->right;
			temp->right->parent = temp;
			temp->left = root->left;
			if (temp->left)	temp->left->parent = temp;
			temp->parent = NULL;
			root = temp;
			checkPrio(root);
		}
		else if (temp->right) {
			root = root->right;
			root->parent = NULL;
		}
		else if (temp->left) {
			root = root->left;
			root->parent = NULL;
		}
		else {
			root = NULL;
			last = NULL;
		}
		temp = root;
	}
	else {

		if (temp->left && temp->right) {
			NodeT<U, T>* prov = getClosestDown(temp);
			prov->right = temp->right;
			temp->right->parent = prov;
			prov->left = temp->left;
			temp->left->parent = prov;
			prov->parent = temp->parent;
			if (temp->parent->right == temp)		temp->parent->right = prov;
			else	temp->parent->left = prov;
			temp = prov;
		}
		else if (temp->right) {
			if (temp->parent->right == temp)		temp->parent->right = temp->right;
			else	temp->parent->left = temp->right;
			temp->right->parent = temp->parent;
			temp = temp->right;
		}
		else if (temp->left) {
			if (temp->parent->right == temp)		temp->parent->right = temp->left;
			else	temp->parent->left = temp->left;
			temp->left->parent = temp->parent;
			temp = temp->left;
		}
		else {
			if (temp->parent->right == temp)		temp->parent->right = NULL;
			else 	temp->parent->left = NULL;
			temp = NULL;
		}
	}
	checkPrio(temp);
}
/*
Searchs a value by key and returns a bool
@param key: key of value to find
*/
template<class U, class T>
bool Tree<U, T>::find(U key) {
	NodeT<U, T>* temp = root;
	while (temp) {
		if (temp->key == key)
			return true;
		else if (temp->key > key)
			temp = temp->left;
		else
			temp = temp->right;
	}
	return false;
}
/*
Searchs a value by key and returns value
@param key: key of value to find
*/
template<class U, class T>
T Tree<U, T>::GetValue(U key) {
	NodeT<U, T>* temp = root;
	while (temp) {
		if (temp->key == key)
			return temp->value;
		else if (temp->key > key)
			temp = temp->left;
		else
			temp = temp->right;
	}
	return NULL;
}
/*
Starts recurse print function
*/
template<class U, class T>
void Tree<U, T>::print() {
	std::cout << "Root: " << root->value << std::endl;
	print(root);
}
/*
Recursive function to find position to insert the new Node
@param key: key of value to save
@param r: root to insert value
*/
template<class U, class T>
void Tree<U, T>::insert(U key, NodeT<U, T>* r) {
	if (r->key > key) {
		if (r->left)	insert(key, r->left);
		else {
			r->left = last;
			last->parent = r;
		}
	}
	else {
		if (r->right) 	insert(key, r->right);
		else {
			r->right = last;
			last->parent = r;
		}
	}
	checkPrio(r);
}
/*
Checks priority of a certain node
@param r: pointer to node to check
*/
template<class U, class T>
void Tree<U, T>::checkPrio(NodeT<U, T>* r) {
	if (!r)
		return;
	if (r->right || r->left) {
		if (!r->right) {
			if (r->left->prio >= 1)
				reorderInsert(r);
			else	r->prio = r->left->prio + 1;
		}
		else if (!r->left) {
			if (r->right->prio >= 1)
				reorderInsert(r);
			else	r->prio = r->right->prio + 1;
		}
		else if (abs(r->right->prio - r->left->prio) >= 2)
			reorderInsert(r);
		else {
			if (r->right->prio > r->left->prio)		r->prio = r->right->prio + 1;
			else	r->prio = r->left->prio + 1;
		}
	}
	else	r->prio = 0;
}
/*
Applies rotations when added new value
@param r: node to check if rotation is needed
*/
template<class U, class T>
void Tree<U, T>::reorderInsert(NodeT<U, T>* r) {
	NodeT<U, T>* temp = r;
	int moves[2];
	for (int i = 0; i < 2; i++) {
		if (!temp->right) {
			moves[i] = -1;
			temp = temp->left;
		}
		else if (!temp->left) {
			moves[i] = 1;
			temp = temp->right;
		}
		else {
			if (temp->right->prio > temp->left->prio) {
				moves[i] = 1;
				temp = temp->right;
			}
			else {
				moves[i] = -1;
				temp = temp->left;
			}
		}
	}

	if (moves[0] == 1) {
		if (moves[1] == 1)
			rotateLeft(r);
		else
			rotateRightLeft(r);
	}
	else {
		if (moves[1] == 1)
			rotateLeftRight(r);
		else
			rotateRight(r);
	}
}
/*
Applies right rotation
@param r: root to rotate
*/
template<class U, class T>
void Tree<U, T>::rotateRight(NodeT<U, T>* r) {
	NodeT<U, T>* temp = r->parent;
	if (temp) {
		if (temp->right == r) {
			temp->right = r->left;
			temp = temp->right;
		}
		else if (temp->left == r) {
			temp->left = r->left;
			temp = temp->left;
		}
		temp->parent = r->parent;
		r->left = temp->right;
		if (temp->right) 	r->left->parent = r;
		temp->right = r;
		r->parent = temp;
	}
	else {
		root = r->left;
		root->parent = NULL;
		r->left = root->right;
		if (r->left)		r->left->parent = r;
		root->right = r;
		r->parent = root;
	}
	checkPrio(r);
}
/*
Applies left rotation
@param r: root to rotate
*/
template<class U, class T>
void Tree<U, T>::rotateLeft(NodeT<U, T>* r) {
	NodeT<U, T>* temp = r->parent;
	if (temp) {
		if (temp->right == r) {
			temp->right = r->right;
			temp = temp->right;
		}
		else if (temp->left == r) {
			temp->left = r->right;
			temp = temp->left;
		}
		temp->parent = r->parent;
		r->right = temp->left;
		if (temp->left) 	r->right->parent = r;
		temp->left = r;
		r->parent = temp;
	}
	else {
		root = r->right;
		root->parent = NULL;
		r->right = root->left;
		if (r->right)		r->right->parent = r;
		root->left = r;
		r->parent = root;
	}
	checkPrio(r);
	checkPrio(r);
}
/*
Applies left-right rotation
@param r: root to rotate
*/
template<class U, class T>
void Tree<U, T>::rotateLeftRight(NodeT<U, T>* r) {
	NodeT<U, T>* temp = r->parent;
	if (temp) {
		if (temp->right == r) {
			temp->right = r->left->right;
			temp->right->parent = temp;
			temp = temp->right;
		}
		else if (temp->left == r) {
			temp->left = r->left->right;
			temp->left->parent = temp;
			temp = temp->left;
		}
		r->parent = temp;
		r->left->right = temp->left;
		if (temp->left)
			r->left->right->parent = r->left;
		temp->left = r->left;
		temp->left->parent = temp;
		r->left = temp->right;
		if (temp->right)
			r->left->parent = r;
		temp->right = r;
		r->parent = temp;
	}
	else {
		root = r->left->right;
		root->parent = NULL;
		r->left->right = root->left;
		if (root->left)
			r->left->right->parent = r->left;
		root->left = r->left;
		root->left->parent = root;
		r->left = root->right;
		if (root->right)
			r->left->parent = r;
		root->right = r;
		r->parent = root;
	}
	temp = r->parent;
	checkPrio(temp->left);
	checkPrio(temp->right);
	checkPrio(temp);
}
/*
Applies left-right rotation
@param r: root to rotate
*/
template<class U, class T>
void Tree<U, T>::rotateRightLeft(NodeT<U, T>* r) {
	NodeT<U, T>* temp = r->parent;
	if (temp) {
		if (temp->right == r) {
			temp->right = r->right->left;
			temp->right->parent = temp;
			temp = temp->right;
		}
		else if (temp->left == r) {
			temp->left = r->right->left;
			temp->left->parent = temp;
			temp = temp->left;
		}
		r->parent = temp;
		r->right->left = temp->right;
		if (temp->right)
			r->right->left->parent = r->right;
		temp->right = r->right;
		temp->right->parent = temp;
		r->right = temp->left;
		if (temp->left)
			r->right->parent = r;
		temp->left = r;
		r->parent = temp;
	}
	else {
		root = r->right->left;
		root->parent = NULL;
		r->right->left = root->right;
		if (root->right)
			r->right->left->parent = r->right;
		root->right = r->right;
		root->right->parent = root;
		r->right = root->left;
		if (root->left)
			r->right->parent = r;
		root->left = r;
		r->parent = root;
	}
	temp = r->parent;
	checkPrio(temp->left);
	checkPrio(temp->right);
	checkPrio(temp);
}
/*
Updates every priority
@param r: pointer to node to update
*/
template<class U, class T>
void Tree<U, T>::updateBack(NodeT<U, T>* r) {
	while (r) {
		checkPrio(r);
		r = r->parent;
	}
}
/*
Recursive function to print all values
*/
template<class U, class T>
void Tree<U, T>::print(NodeT<U, T>* r) {
	if (!r)
		return;
	print(r->left);
	std::cout << r->value << std::endl;
	print(r->right);
}