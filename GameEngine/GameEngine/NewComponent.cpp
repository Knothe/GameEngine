#include "NewComponent.h"
#include "Singletons/Debug.h"
#include "Singletons/StackAllocator.h"

NewComponent::NewComponent(String file, String i, bool active, GameObject* obj) {
	id = i;
	isActive = active;
	object = obj;
	void* buf = StackAllocator::GetPtr()->alloc(sizeof(LuaHandler));
	lua = new(buf) LuaHandler(file);
}

LuaHandler* NewComponent::GetLua() {
	return lua;
}



void NewComponent::Input(List<int>* keysDown) {
	NodeL<int>* temp = keysDown->first;
	while (temp) {
		if (lua->getGlobal("Input")) {
			lua->pushNumber(temp->value);
			if (lua->callFunction(1, 0)) {

			}
		}
		temp = temp->next;
	}
}

void NewComponent::CollisionEnter(GameObject* other) {
	if (lua->getGlobal("CollisionEnter")) {
		lua->pushPointer((unsigned long long int)object);
		lua->pushPointer((unsigned long long int)other);
		if (lua->callFunction(2, 0)) {

		}
	}
}

void NewComponent::Update() {
	if (lua->getGlobal("Update")) {
		lua->pushPointer((unsigned long long int)object);
		if (lua->callFunction(1, 0)) {

		}
	}
}

void NewComponent::Init() {

}