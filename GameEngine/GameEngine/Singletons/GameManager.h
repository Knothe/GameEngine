#pragma once
#include "../DataStructure/Stack.h"
#include "../DataStructure/HashTable.h"
#include "../State.h"
#include "../LuaHandler.h"

class State;

class GameManager
{
private:
	GameManager();
	static int lua_AddState(lua_State* L);
	static int lua_FirstState(lua_State* L);
	static int lua_AddFile(lua_State* L);

	Stack<State*> statesStack;
	HashTable<State*> stateTable;

	static GameManager* ptr;
	List<int> keysDown;
	MouseData mouseData;

	LuaHandler* luaHandler;

public:
	static GameManager* getPtr();
	void Init();
	void SetState(String id);
	void AddState(String id, String file);
	void GameLoop();
	void ReleaseState();
	~GameManager();
};

