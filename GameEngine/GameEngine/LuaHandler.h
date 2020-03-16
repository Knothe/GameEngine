#pragma once

extern "C" {
#include "../ExternalLibs/Lua535/include/lua.h"
#include "../ExternalLibs/Lua535/include/lauxlib.h"
#include "../ExternalLibs/Lua535/include/lualib.h"
}

#ifdef _WIN32
#pragma comment(lib, "../ExternalLibs/Lua535/liblua53.a")
#endif

#include "String.h"

class LuaHandler
{
public:

	LuaHandler();
	LuaHandler(String s);

	lua_State* GetState();

	void initializeLua(String s);

	bool getGlobal(String s);
	bool callFunction(int args, int result);

	void pushNumber(float f);
	void pushString(String s);
	void pushPointer(unsigned long long int i);

	void pop(int n);

	void addFunction(String name, int (*f)(lua_State*));

	unsigned long long int getPointer(int n);
	float getNumber(int n);
	std::string getString(int n);
	bool getBoolean(int n);

	static unsigned long long int getPointer(lua_State* l, int n);
	static float getNumber(lua_State* l, int n);
	static std::string getString(lua_State* l, int n);

	static void pushNumber(lua_State* l, float f);
	

private:
	bool CheckLua(lua_State* l, int r);

	lua_State* L;
	bool initialized;

};

