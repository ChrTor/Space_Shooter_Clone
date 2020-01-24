#pragma once
#include "State.h"
#include "World.h"
#include "CollisionManager.h"
#include "InputManager.h"

class Playing : public State
{
public:
	Playing(int &difficulty, int& windowsizeX, int& windowsizeY);
	~Playing();
	virtual StateID *RunState() override;

private:

	int* m_Score;

	sf::RenderWindow* m_Window;
	World* m_World;
	InputManager* m_InputManager;
};