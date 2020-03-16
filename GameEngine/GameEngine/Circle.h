#pragma once
#include "Component.h"

class Circle : public Component
{
public:
	Circle(float r, String t, String i, bool a);

	void Init();
	void Update();
	void Draw(Vec2 position);

private:
	float radius;
};

