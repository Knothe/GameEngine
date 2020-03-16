#include "GameManager.h"
#include "AssetManager.h"
#include "StackAllocator.h"
#include "Debug.h"
#include <functional>

GameManager* GameManager::ptr;
/*
Starts the gameManager
*/
GameManager::GameManager() {
	try {
		luaHandler = new LuaHandler("GameManager.lua");
		luaHandler->addFunction("AddState", lua_AddState);
		luaHandler->addFunction("FirstState", lua_FirstState);
		luaHandler->addFunction("AddFile", lua_AddFile);
	}
	catch (int i) {
		Debug::GetPtr()->LogFatalError(i);
	}
}
/*
@return pointer to this object
*/
GameManager* GameManager::getPtr() {
	if (!ptr) {
		void* buf = StackAllocator::GetPtr()->alloc(sizeof(GameManager));
		ptr = new(buf) GameManager();

	}
	return ptr;
}

void GameManager::Init() {
	if (luaHandler->getGlobal("Start")) {
		luaHandler->pushPointer((unsigned long long int)ptr);
		if (luaHandler->callFunction(1, 0)) {
			Debug::GetPtr()->Log(L"Start initialized");
		}
		luaHandler->pop(1);
	}
}

/*
Allows to add new state from Lua
*/
int GameManager::lua_AddState(lua_State* L) {
	GameManager* g = (GameManager*)LuaHandler::getPointer(L, 1);
	String id(g->luaHandler->getString(2));
	String luaFile(g->luaHandler->getString(3));
	g->AddState(id, luaFile);
	return 0;
}

int GameManager::lua_FirstState(lua_State* L) {
	GameManager* g = (GameManager*)LuaHandler::getPointer(L, 1);
	String id(g->luaHandler->getString(2));
	g->SetState(id);
	return 0;
}

int GameManager::lua_AddFile(lua_State* L) {
	GameManager* g = (GameManager*)LuaHandler::getPointer(L, 1);
	String assetType(g->luaHandler->getString(2));
	String fileName(g->luaHandler->getString(3));
	String id(g->luaHandler->getString(4));

	if (assetType == String("Texture")) {
		int frames = g->luaHandler->getNumber(5);
		AssetManager::getPtr()->AddTexture(fileName, id, frames);
	}
	else if (assetType == String("Music")) {
		AssetManager::getPtr()->AddMusic(fileName, id);
	}
	else if (assetType == String("SFX")) {
		AssetManager::getPtr()->AddSfx(fileName, id);
	}
	else if (assetType == String("Font")) {
		int size = g->luaHandler->getNumber(5);
		AssetManager::getPtr()->AddFont(fileName, id, size);
	}

	return 0;
}

void GameManager::AddState(String id, String file) {
	void* buf = StackAllocator::GetPtr()->alloc(sizeof(State));
	State* s = new (buf)State(file);
	stateTable.Add(id, s);
}

/*
Adds a new state to the stack
@param state: new State to add
*/
void GameManager::SetState(String id) {
	State* s = stateTable.Search(id);
	s->Init();
	if (s)
		statesStack.Push(s);
	else
		Debug::GetPtr()->LogFatalError(402);
}
/*
Executes the game loop while there are things in the stack
*/
void GameManager::GameLoop() {
	while(true) {
		try {
			if (statesStack.GetSize() <= 0)
				throw 0;
			Platform::GetPtr()->NextFrame();
			auto estado = statesStack.Top();
			Platform::GetPtr()->CheckEvent(&keysDown, &mouseData);
			estado->Input(&keysDown, &mouseData);
			estado->Update();
			estado->Draw();
			if (!estado->GetState())
				ReleaseState();
		}
		catch (int e) {

			break;
		}
		catch (std::exception e) {
			std::string s = "Unahndled Exception: ";
			s += e.what();
			Debug::GetPtr()->LogError(s);
		}
	}
}
/*
Takes a State out of the stack
*/
void GameManager::ReleaseState() {
	State* s = statesStack.Top();
	s->Close();
	statesStack.Pop();
}

GameManager::~GameManager() {

}