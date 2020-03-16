#pragma once
#include "Component.h"
#include "Vec2.h"
#include "DataStructure/List.h"

class GameObject
{
public:
	GameObject(String i, Vec2 pos);
	void AddComponent(Component* c);
	void AddNewComponent(Component* c);

	void Update();
	void Draw();

private:
	String id;
	Vec2 position;
	List<Component*> premadeComponents;
	List<Component*> newComponents;
};

