#include "Collider.h"
#include "Singletons/Platform.h"

Collider::Collider(Vec2 s, bool drawing, String t, String i, bool a) : Component(t, i, a) {
	size = s;
	isDrawing = drawing;
	isCircle = false;
}

Collider::Collider(float s, bool drawing, String t, String i, bool a) : Component(t, i, a) {
	size.x = s;
	size.y = 0;
	isDrawing = drawing;
	isCircle = true;
}

void Collider::Init() {

}

void Collider::Update() {

}

bool Collider::IsCircle() {
	return isCircle;
}

Vec2 Collider::GetSize() {
	return size;
}

void Collider::Draw(Vec2 position) {
	if (isDrawing) {
		if (isCircle) {
			Platform::GetPtr()->DrawCircle(position, size.x);
		}
		else {
			Platform::GetPtr()->DrawRect(position, size);
		}
	}
}