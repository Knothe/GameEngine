#pragma once
#include "Singletons/Platform.h"
#include "Singletons/GameManager.h"
#include "LuaHandler.h"
#include "GameObject.h"

class Platform;
class StateManager;

class State
{
private:
	bool state = true;
	String luaFile;
	LuaHandler* lua;
	List<GameObject*> objectList;
	HashTable<GameObject*> objectMap;

	static int lua_AddGameObject(lua_State* L);
	static int lua_AddComponent(lua_State* L);
public:

	State(String s);

	void Input(List<int>* inputKeys, MouseData* mouseData);
	void Update();
	void Draw();
	void Init();
	void Close();

	void SetState(bool state);
	bool GetState();
};

