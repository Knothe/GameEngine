#pragma once
#include "LuaHandler.h"
#include "String.h"
#include "GameObject.h"
#include "DataStructure/List.h"

class GameObject;

class NewComponent
{
public:
	NewComponent(String file, String i, bool active, GameObject* obj);

	LuaHandler* GetLua();

	void Input(List<int>* keysDown);
	void CollisionEnter(GameObject* other);
	void Update();
	void Init();


private:
	String id;
	LuaHandler* lua;
	GameObject* object;
	bool isActive;
};

