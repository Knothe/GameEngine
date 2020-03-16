#include "Square.h"
#include "Singletons/Platform.h"

Square::Square(Vec2 s, String t, String i, bool a) : Component(t, i, a) {
	size = s;
}

void Square::Init() {

}

void Square::Update() {

}

void Square::Draw(Vec2 position) {
	Platform::GetPtr()->DrawRect(position, size);

}