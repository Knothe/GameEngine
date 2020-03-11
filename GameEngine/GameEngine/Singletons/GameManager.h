#pragma once
#include "../DataStructure/Stack.h"
#include "../State.h"

class State;

class GameManager
{
private:
	Stack<State*> statesStack;
	GameManager();
	static GameManager* ptr;
public:
	static GameManager* getPtr();
	void SetState(State* state);
	void GameLoop();
	void ReleaseState();
	~GameManager();
};

