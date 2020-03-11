#include "State.h"
/*
Changes the value of the state
@param s: new value of state
*/
void State::SetState(bool s) {
	state = s;
}
/*
@return value of state
*/
bool State::GetState() {
	return state;
}