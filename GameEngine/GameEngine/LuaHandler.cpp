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
		String root("../../Assets/Files/LuaFiles/");
		root += s;
		if (!CheckLua(L, luaL_dofile(L, root.toString().c_str())))
			throw 401;
		else
			initialized = true;
	}
}

bool LuaHandler::CheckLua(lua_State* l, int r) {
	if (r != LUA_OK) {
		String e = lua_tostring(L, -1);
		e.Print();
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

void LuaHandler::pushPointer(unsigned long long int i) {
	lua_pushnumber(L, i);
}

void LuaHandler::pushString(String s) {
	lua_pushstring(L, s.toString().c_str());
}

lua_State* LuaHandler::GetState() {
	return L;
}

void LuaHandler::pop(int n) {
	lua_pop(L, n);
}

void LuaHandler::addFunction(String name, int (*f)(lua_State*)) {
	lua_register(L, name.toString().c_str(), f);
}

float LuaHandler::getNumber(int n) {
	return lua_tonumber(L, n);
}

unsigned long long int LuaHandler::getPointer(int n) {
	return lua_tonumber(L, n);
}

std::string LuaHandler::getString(int n) {
	return lua_tostring(L, n);
}

bool LuaHandler::getBoolean(int n) {
	return lua_toboolean(L, n);
}

float LuaHandler::getNumber(lua_State* l, int n) {
	return lua_tonumber(l, n);
}

unsigned long long int LuaHandler::getPointer(lua_State* l, int n) {
	return lua_tonumber(l, n);
}

std::string LuaHandler::getString(lua_State* l, int n) {
	return lua_tostring(l, n);
}
