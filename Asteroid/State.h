#pragma once
#include "SFML/Graphics.hpp"

enum StateID
{
	MENU,
	PLAYING,
	SCOREBOARD,
	EXIT,
};

enum Status
{
	RUNNING,
	FAIL,
	SUCCESS,
};

class State
{
public:

	virtual StateID *RunState();

	void SetStateName(std::string *name);
	std::string *GetStateName();

	void SetCurrentStateID(StateID *state);
	StateID* GetCurrentStateID();

	std::string *m_StateName;
	float m_StateChangeTimer;

	StateID* m_CurrentState;

private:


};
