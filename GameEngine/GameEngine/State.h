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

	State();

	void Update();
	void Draw();
	void Init();
	void Close();

	void SetState(bool state);
	bool GetState();
};

