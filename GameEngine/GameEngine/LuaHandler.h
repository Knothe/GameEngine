#pragma once
extern"C" {
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

	void initializeLua(String s);

	bool getGlobal(String s);
	bool callFunction(int args, int result);

	void pushNumber(float f);
	void pushString(String s);

	void registerFunction(String s, int (*f)(lua_State*));
	void pop(int n);

	float getNumber(int n);
	std::string getString(int n);

private:
	bool CheckLua(lua_State* l, int r);

	lua_State* L;
	bool initialized;

};

