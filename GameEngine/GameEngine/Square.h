#pragma once
#include "Component.h"

class Square : public Component
{
public:
	Square(Vec2 s, String t, String i, bool a);

	void Init();
	void Update();
	void Draw(Vec2 position);

private:
	Vec2 size;
};

