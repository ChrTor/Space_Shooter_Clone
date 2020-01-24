#include "State.h"
#include <iostream>

 StateID *State::RunState() {
	std::string *name = GetStateName();
	printf("%s\n", name->c_str());
	return m_CurrentState;
}

void State::SetStateName(std::string *name) {
	m_StateName = name;
}

std::string *State::GetStateName() {
	return m_StateName;
}

void State::SetCurrentStateID(StateID *state) {
	if (m_CurrentState != nullptr)
	{
		delete(m_CurrentState);
		m_CurrentState = nullptr;
	}
	m_CurrentState = state;
}

StateID *State::GetCurrentStateID() {
	if (m_CurrentState != nullptr)
	{
		return m_CurrentState;
	}
	else return nullptr;
}