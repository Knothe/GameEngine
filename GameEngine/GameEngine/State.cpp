#include "State.h"
#include "Singletons/Debug.h"
#include "Collider.h"
#include "Image.h"
#include "Square.h"
#include "Circle.h"

State::State(String s) {
	luaFile = s;
	lua = NULL;
}

void State::Input(List<int>* inputKeys, MouseData* mouseData) {
	NodeL<int>* temp = inputKeys->first;
	while (temp) {
		String s(std::to_string(temp->value));
		Debug::GetPtr()->Log(s);
		temp = temp->next;
	}
}

void State::Update() {
	NodeL<GameObject*>* temp = objectList.first;
	while (temp) {
		temp->value->Update();
		temp = temp->next;
	}
}

void State::Draw() {
	Platform::GetPtr()->RenderClear();
	NodeL<GameObject*>* temp = objectList.first;
	while (temp) {
		temp->value->Draw();
		temp = temp->next;
	}
	Platform::GetPtr()->RenderPresent();
}

void State::Init() {
	try {
		if (lua)
			return;
		lua = new LuaHandler(luaFile);
		lua->addFunction("AddGameObject", lua_AddGameObject);
		lua->addFunction("AddComponent", lua_AddComponent);
		if(lua->getGlobal("SetScene")) {
			lua->pushPointer((unsigned long long int)this);
			if (lua->callFunction(1, 0)) {
				Debug::GetPtr()->Log(L"StartState");
			}
		}
	}
	catch (int i) {
		Debug::GetPtr()->LogFatalError(i);
	}
	catch (...) {

	}
	
}

int State::lua_AddGameObject(lua_State* L) {
	State* s = (State*)LuaHandler::getPointer(L, 1);
	String id(s->lua->getString(2));
	int x = s->lua->getNumber(3);
	int y = s->lua->getNumber(4);

	GameObject* obj = new GameObject(id, Vec2(x, y));
	s->objectList.push_back(obj);
	s->objectMap.Add(id, obj);
	return 0;
}

int State::lua_AddComponent(lua_State* L) {
 	State* s = (State*)LuaHandler::getPointer(L, 1);
	String gameObject(s->lua->getString(2));
	GameObject* g = s->objectMap.Search(gameObject);
	if (!g)
		return 0;
	String type(s->lua->getString(3));
	String name(s->lua->getString(4));
	bool isActive = s->lua->getBoolean(5);

	if (type == String("Collider")) {
		bool isDrawing = s->lua->getBoolean(6);
		bool isCircle = s->lua->getBoolean(7);
		if (isCircle) {
			int r = s->lua->getNumber(8);
			g->AddComponent(new Collider(r, isDrawing, type, name, isActive));
		}
		else {
			int x = s->lua->getNumber(8);
			int y = s->lua->getNumber(9);
			g->AddComponent(new Collider(Vec2(x, y), isDrawing, type, name, isActive));
		}
	}
	else if (type == String("Image")) {
		String file(s->lua->getString(6));
		Image* i = new Image(type, name, isActive);
		g->AddComponent(i);
		i->Load(file);
	}
	else if (type == String("Animation")) {
		String file(s->lua->getString(6));
		Image* i = new Image(type, name, isActive);
		g->AddComponent(i);
		i->Load(file);
	}
	else if (type == String("Circle")) {
		int r = s->lua->getNumber(6);
		g->AddComponent(new Circle(r, type, name, isActive));
	}
	else if (type == String("Square")) {
		int x = s->lua->getNumber(6);
		int y = s->lua->getNumber(7);
		g->AddComponent(new Square(Vec2(x, y), type, name, isActive));
	}
	else if (type == String("New")) {

	}
	return 0;
}

void State::Close() {

}

void State::SetState(bool s) {
	state = s;
}

bool State::GetState() {
	return state;
}