#pragma once
#include "String.h"
#include "Vec2.h"

class Component
{
public:
	Component() {
		active = true;
		type = "";
		id = "";
	}
	Component(String t, String i, bool a) : type(t), id(i), active(a) {

	}

	bool isActive() {
		return active;
	}

	void setActive(bool a) {
		active = a;
	}

	String getType() {
		return type;
	}

	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Draw(Vec2 position) = 0;

protected:
	String type;
	String id;
	bool active;
};

