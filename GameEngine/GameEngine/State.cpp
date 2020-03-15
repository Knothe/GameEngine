#include "State.h"

State::State() {

}

void State::Update() {

}

void State::Draw() {

}

void State::Init() {

}

void State::Close() {

}

void State::Close() {

}
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