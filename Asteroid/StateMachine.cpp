#include "StateMachine.h"
#include "Playing.h"
#include "Menu.h"
#include <vector>
#include <map>
#define WINDOWSIZEX 1920
#define WINDOWSIZEY 1080

StateMachine::StateMachine() {
	m_CurrentState = nullptr;
	m_PreviousState = nullptr;

	m_Difficulty = 1;
	m_WindowSizeX = 1240;
	m_WindowSizeY = 720;

	m_CurrentState = new Menu(m_WindowSizeX, m_WindowSizeY);
}

StateMachine::~StateMachine() {
	delete(m_PreviousState);
	m_PreviousState = nullptr;
	delete(m_CurrentState);
	m_CurrentState = nullptr;
	for (auto &S : m_StateList) {
		delete(S);
		S = nullptr;
	}
	m_StateList.clear();
}

// Public

void StateMachine::RunMachine() {

	StateID* result = m_CurrentState->RunState();

	if (result != m_CurrentState->GetCurrentStateID())
	{
		m_CurrentState = SetState(result);
		if (m_CurrentState == nullptr)
		{
			return;
		}
	}
}

State* StateMachine::SetState(StateID *newState) {
	m_PreviousState = m_CurrentState;
	delete(m_CurrentState);

	if (*newState == MENU)
	{
		return new Menu(m_WindowSizeX, m_WindowSizeY);

	}
	else if (*newState == PLAYING)
	{
		return new Playing(m_Difficulty, m_WindowSizeX, m_WindowSizeY);

	}
	else
	{
		return nullptr;
	}
}