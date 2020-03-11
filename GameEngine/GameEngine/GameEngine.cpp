//#include "String.h"
//
//extern "C"
//{
//#include "../ExternalLibs/Lua535/include/lua.h"
//#include "../ExternalLibs/Lua535/include/lauxlib.h"
//#include "../ExternalLibs/Lua535/include/lualib.h"
//}
//
//#ifdef _WIN32
//#pragma comment(lib, "../ExternalLibs/Lua535/liblua53.a")
//#endif
//
//int main() {
//    std::string cmd = "a = 7 + 11";
//
//    lua_State* L = luaL_newstate();
//    luaL_openlibs(L);
//
//    int r = luaL_dostring(L, cmd.c_str());
//
//    if (r == LUA_OK) {
//        lua_getglobal(L, "a");
//        if (lua_isnumber(L, -1)) {
//            float a_in_cpp = (float)lua_tonumber(L, -1);
//            std::cout << "a_in_cpp = " << a_in_cpp << std::endl;
//        }
//    }
//    else {
//        std::string errormsg = lua_tostring(L, -1);
//        std::cout << errormsg << std::endl;
//    }
//    system("pause");
//    lua_close(L);
//    return 0;
//}

#include "Singletons/Platform.h"

int main() {
	
	Platform* p = Platform::GetPtr();
	while (true) {
		p->RenderClear();
		p->DrawRect(0, 0, 500, 200);
		p->DrawCircle(Vec2(200, 200), 100);
		p->RenderPresent();
	}
	return 0;
}