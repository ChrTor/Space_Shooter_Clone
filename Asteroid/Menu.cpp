#include "Menu.h"
#include "SFML/Window.hpp"
#include "Playing.h"

Menu::Menu(int &windowSizeX, int &windowSizeY)
{
	m_StateName = new std::string("Menu");

	SetCurrentStateID(new StateID(MENU));

	m_StateChangeTimer = 0.5f;
}

Menu::~Menu()
{
	delete(m_StateName);
	m_StateName = nullptr;
	delete(m_CurrentState);
	m_CurrentState = nullptr;
}

StateID *Menu::RunState() {

	std::string *name = GetStateName();
	printf("%s\n", name->c_str());

	bool left = false;
	bool right = false;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		left = true;
	}

	//if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	//{
	//	left = true;
	//}
	//if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
	//{
	//	right = false;
	//}


	if (left)
	{
		if (m_StateChangeTimer <= 0.0f)
		{
			m_StateChangeTimer = 0.5f;
			left = false;

			return new StateID(PLAYING);
		}
		left = false;
	}
	else if (right)
	{
		if (m_StateChangeTimer <= 0.0f)
		{
			m_StateChangeTimer = 0.5f;
			right = false;
			return new StateID(PLAYING);
		}
		right = false;
	}
	m_StateChangeTimer -= 0.01f;

	return GetCurrentStateID();
}

