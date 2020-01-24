#pragma once
#include "State.h"



class StateMachine
{
public:
	StateMachine();
	~StateMachine();

	void RunMachine();

	State* SetState(StateID *newState);

private:
	State *m_PreviousState;
	State *m_CurrentState;

	std::vector<State*> m_StateList;
	std::map<State*, StateID*> m_StateMap;


	// Somewhere else
	int m_WindowSizeX;
	int m_WindowSizeY;
	int m_Difficulty;
};