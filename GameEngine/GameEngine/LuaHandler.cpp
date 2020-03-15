#include "LuaHandler.h"

LuaHandler::LuaHandler() {
	L = luaL_newstate();
	luaL_openlibs(L);
	initialized = false;
}

LuaHandler::LuaHandler(String s) {
	L = luaL_newstate();
	luaL_openlibs(L);
	initialized = false;
	initializeLua(s);
}

void LuaHandler::initializeLua(String s) {
	if (!initialized) {
		if (!CheckLua(L, luaL_dofile(L, s.toString().c_str())))
			std::cout << "File not found" << std::endl;
		else
			initialized = true;
	}
}

bool LuaHandler::CheckLua(lua_State* l, int r) {
	if (r != LUA_OK) {
		std::string errormsg = lua_tostring(L, -1);
		std::cout << errormsg << std::endl;
		return false;
	}
	return true;
}

bool LuaHandler::getGlobal(String s) {
	lua_getglobal(L, s.toString().c_str());
	return lua_isfunction(L, -1);
}

bool LuaHandler::callFunction(int args, int result) {
	return CheckLua(L, lua_pcall(L, args, result, 0));
}

void LuaHandler::pushNumber(float f) {
	lua_pushnumber(L, f);
}

void LuaHandler::pushString(String s) {
	lua_pushstring(L, s.toString().c_str());
}

void LuaHandler::registerFunction(String s, int (*f)(lua_State*)) {
	lua_register(L, s.toString().c_str(), f);

}

void LuaHandler::pop(int n) {
	lua_pop(L, n);
}

float LuaHandler::getNumber(int n) {
	return lua_tonumber(L, n);
}

std::string LuaHandler::getString(int n) {
	return lua_tostring(L, n);
}
