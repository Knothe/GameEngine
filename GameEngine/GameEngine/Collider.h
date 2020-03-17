#pragma once
#include "Component.h"
#include "Vec2.h"

class Collider : public Component
{
public:
	Collider(Vec2 s, bool drawing, String t, String i, bool a);
	Collider(float s, bool drawing, String t, String i, bool a);

	void Init();
	void Update();
	void Draw(Vec2 position);
	bool IsCircle();
	Vec2 GetSize();

private:
	Vec2 size;
	bool isDrawing;
	bool isCircle;
};

