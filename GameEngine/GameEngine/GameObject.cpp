#include "GameObject.h"

GameObject::GameObject(String i, Vec2 pos) {
	id = i;
	position = pos;
}

void GameObject::AddComponent(Component* c) {
	premadeComponents.push_back(c);
}

void GameObject::AddNewComponent(Component* c) {

	newComponents.push_back(c);
}

void GameObject::Draw() {
	NodeL<Component*>* temp = premadeComponents.first;
	while (temp) {
		temp->value->Draw(position);
		temp = temp->next;
	}

	temp = newComponents.first;
	while (temp) {
		temp->value->Draw(position);
		temp = temp->next;
	}
}

void GameObject::Update() {
	NodeL<Component*>* temp = premadeComponents.first;
	while (temp) {
		temp->value->Update();
		temp = temp->next;
	}

	temp = newComponents.first;
	while (temp) {
		temp->value->Update();
		temp = temp->next;
	}
}