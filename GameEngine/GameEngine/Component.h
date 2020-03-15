#pragma once
#include "String.h"

class Component
{
public:
	Component();

	bool isActive();
	String getType();

	void Init();
	void Update();
	void Draw();

protected:
	String type;
	bool isActive;
};

