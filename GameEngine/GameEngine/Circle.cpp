#include "Circle.h"
#include "Singletons/Platform.h"

Circle::Circle(float r, String t, String i, bool a) : Component(t, i, a) {
	radius = r;
}

void Circle::Init() {

}

void Circle::Update() {

}

void Circle::Draw(Vec2 position) {
	Platform::GetPtr()->DrawCircle(position, radius);

}