#include "GameObject.h"

GameObject::GameObject(String i, Vec2 pos) {
	id = i;
	position = pos;
}

void GameObject::AddComponent(Component* c) {
	premadeComponents.push_back(c);
}

void GameObject::AddNewComponent(NewComponent* c) {
	c->GetLua()->addFunction("Translate", lua_MoveObject);
	c->GetLua()->addFunction("GetX", lua_GetX);
	c->GetLua()->addFunction("GetY", lua_GetY);
	newComponents.push_back(c);
}

void GameObject::Input(List<int>* keysDown) {
	NodeL<NewComponent*>* t = newComponents.first;
	while (t) {
		t->value->Input(keysDown);
		t = t->next;
	}
}

void GameObject::Draw() {
	NodeL<Component*>* temp = premadeComponents.first;
	while (temp) {
		temp->value->Draw(position);
		temp = temp->next;
	}
}

void GameObject::CollisionEnter(GameObject* other) {
	NodeL<NewComponent*>* t = newComponents.first;
	while (t) {
		t->value->CollisionEnter(other);
		t = t->next;
	}
}

List<Component*>* GameObject::GetPreComponent() {
	return &premadeComponents;
}

Vec2 GameObject::GetPosition() {
	return position;
}

void GameObject::Update() {
	NodeL<Component*>* temp = premadeComponents.first;
	while (temp) {
		temp->value->Update();
		temp = temp->next;
	}
	NodeL<NewComponent*>* t = newComponents.first;
	while (t) {
		t->value->Update();
		t = t->next;
	}
}

int GameObject::lua_MoveObject(lua_State* L) {
	GameObject* obj = (GameObject*)LuaHandler::getPointer(L, 1);
	int x = LuaHandler::getNumber(L, 2);
	int y = LuaHandler::getNumber(L, 3);
	Vec2 add(x, y);
 	obj->position = obj->position + add;
	return 0;
}

int GameObject::lua_GetX(lua_State* L) {
	GameObject* obj = (GameObject*)LuaHandler::getPointer(L, 1);
	LuaHandler::pushNumber(L, obj->position.x);
	return 1;
}

int GameObject::lua_GetY(lua_State* L) {
	GameObject* obj = (GameObject*)LuaHandler::getPointer(L, 1);
	LuaHandler::pushNumber(L, obj->position.y);
	return 1;
}