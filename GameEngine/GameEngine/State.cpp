#include "State.h"
#include "Singletons/Debug.h"
#include "Image.h"
#include "Square.h"
#include "Circle.h"
#include "NewComponent.h"
#include "Singletons/StackAllocator.h"
#include "Singletons/AudioManager.h"

State::State(String s) {
	luaFile = s;
	lua = NULL;
}

void State::Input(List<int>* inputKeys, MouseData* mouseData) {
	NodeL<GameObject*>* temp = objectList.first;
	while (temp) {
		temp->value->Input(inputKeys);
		temp = temp->next;
	}
}

void State::Update() {
	NodeL<GameObject*>* temp = objectList.first;
	while (temp) {
		temp->value->Update();
		temp = temp->next;
	}
	NodeL<GameObject*>* t;
	temp = objectList.first;
	if (!temp) return;

	while (temp->next) {
		t = temp->next;
		while (t) {
			CheckCollision(temp->value, t->value);
			t = t->next;
		}
		temp = temp->next;
	}
}

void State::CheckCollision(GameObject* obj1, GameObject* obj2) {
	NodeL<Component*>* temp1 = obj1->GetPreComponent()->first;
	NodeL<Component*>* temp2 = obj2->GetPreComponent()->first;
	if (!temp2) return;
	while (temp1) {
		if (temp1->value->getType() == "Collider") {
			while (temp2) {
				if (temp2->value->getType() == "Collider") {
					if (CheckCollision(obj1->GetPosition(), (Collider*)temp1->value, obj2->GetPosition(), (Collider*)temp2->value)) {
						obj1->CollisionEnter(obj2);
						obj2->CollisionEnter(obj1);
					}
				}
				temp2 = temp2->next;
			}
		}
		temp1 = temp1->next;
	}
}

bool State::CheckCollision(Vec2 pos1, Collider* col1, Vec2 pos2, Collider* col2) {
	if (col1->IsCircle() == col2->IsCircle()) {
		if (col1->IsCircle()) {
			Vec2 dist = pos1 - pos2;
			if (dist.size <= col1->GetSize().x + col2->GetSize().x) {
				return true;
			}
		}
		else {
			Vec2 p1x, p1y, p2x, p2y;
			p1x.x = pos1.x - (col1->GetSize().x / 2);
			p1x.y = pos1.x + (col1->GetSize().x / 2);

			p1y.x = pos1.y - (col1->GetSize().y / 2);
			p1y.y = pos1.y + (col1->GetSize().y / 2);


			p2x.x = pos2.x - (col2->GetSize().x / 2);
			p2x.y = pos2.x + (col2->GetSize().x / 2);

			p2y.x = pos2.y - (col2->GetSize().y / 2);
			p2y.y = pos2.y + (col2->GetSize().y / 2);

			if ((p1x.x >= p2x.x && p1x.x <= p2x.y) || (p1x.y >= p2x.x && p1x.y <= p2x.y)) {
				if ((p1y.x >= p2y.x && p1y.x <= p2y.y) || (p1y.y >= p2y.x && p1y.y <= p2y.y)) {
					return true;
				}
			}

		}
	}
	return false;
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
		lua->addFunction("StartMusic", lua_StartMusic);
		if(lua->getGlobal("SetScene")) {
			lua->pushPointer((unsigned long long int)this);
			if (lua->callFunction(1, 0)) {
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
	void* buf = StackAllocator::GetPtr()->alloc(sizeof(GameObject));
	GameObject* obj = new(buf) GameObject(id, Vec2(x, y));
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
			void* buf = StackAllocator::GetPtr()->alloc(sizeof(Collider));
			g->AddComponent(new(buf) Collider(r, isDrawing, type, name, isActive));
		}
		else {
			int x = s->lua->getNumber(8);
			int y = s->lua->getNumber(9);
			void* buf = StackAllocator::GetPtr()->alloc(sizeof(Collider));
			g->AddComponent(new(buf) Collider(Vec2(x, y), isDrawing, type, name, isActive));
		}
	}
	else if (type == String("Image")) {
		String file(s->lua->getString(6));
		void* buf = StackAllocator::GetPtr()->alloc(sizeof(Image));
		Image* i = new(buf) Image(type, name, isActive);
		g->AddComponent(i);
		i->Load(file);
	}
	else if (type == String("Animation")) {
		String file(s->lua->getString(6));
		void* buf = StackAllocator::GetPtr()->alloc(sizeof(Image));
		Image* i = new(buf) Image(type, name, isActive);
		g->AddComponent(i);
		i->Load(file);
	}
	else if (type == String("Circle")) {
		int r = s->lua->getNumber(6);
		void* buf = StackAllocator::GetPtr()->alloc(sizeof(Circle));
		g->AddComponent(new(buf) Circle(r, type, name, isActive));
	}
	else if (type == String("Square")) {
		int x = s->lua->getNumber(6);
		int y = s->lua->getNumber(7);
		void* buf = StackAllocator::GetPtr()->alloc(sizeof(Square));
		g->AddComponent(new(buf) Square(Vec2(x, y), type, name, isActive));
	}
	else if (type == String("New")) {
		String file(s->lua->getString(6));
		void* buf = StackAllocator::GetPtr()->alloc(sizeof(NewComponent));
		NewComponent* n = new(buf) NewComponent(file, name, isActive, g);
		g->AddNewComponent(n);
	}
	return 0;
}

int State::lua_StartMusic(lua_State* L) {
	String s(LuaHandler::getString(L, 1));
	AudioManager::getPtr()->PlayMusic(s);
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