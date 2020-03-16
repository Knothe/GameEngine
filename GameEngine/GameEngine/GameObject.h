#pragma once
#include "Component.h"
#include "NewComponent.h"
#include "Vec2.h"
#include "DataStructure/List.h"

class NewComponent;

class GameObject
{
public:
	GameObject(String i, Vec2 pos);
	void AddComponent(Component* c);
	void AddNewComponent(NewComponent* c);
	void CollisionEnter(GameObject* other);
	void Update();
	void Draw();
	void Input(List<int>* keysDown);
	List<Component*>* GetPreComponent();
	Vec2 GetPosition();

private:
	String id;
	Vec2 position;
	List<Component*> premadeComponents;
	List<NewComponent*> newComponents;

	static int lua_MoveObject(lua_State* L);
	static int lua_GetX(lua_State* L);
	static int lua_GetY(lua_State* L);
};

