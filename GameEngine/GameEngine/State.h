#pragma once
#include "Singletons/Platform.h"
#include "Singletons/GameManager.h"

class Platform;
class StateManager;

class State
{
protected:
	bool state = true;
public:
	virtual void Input() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void Init() = 0;
	virtual void Close() = 0;

	void SetState(bool state);
	bool GetState();
};

