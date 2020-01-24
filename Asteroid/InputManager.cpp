#include "InputManager.h"
#include <map>
#include <vector>


InputManager::InputManager()
{
	AddActions();
}

InputManager::~InputManager()
{
}

sf::Vector2i InputManager::GetMousePosition(sf::RenderWindow* window) {
	return sf::Mouse::getPosition(*window);
}

std::vector<int> InputManager::SenseKeyboardInput() {
	std::vector<int> input(4);


	if (IsKeyboardActionTriggered(W))
	{
		input[W] = 1;
	}
	else
	{
		input[W] = 0;
	}
	if (IsKeyboardActionTriggered(A))
	{
		input[A] = 1;
	}
	else
	{
		input[A] = 0;
	}
	if (IsKeyboardActionTriggered(S))
	{
		input[S] = 1;
	}
	else
	{
		input[S] = 0;
	}
	if (IsKeyboardActionTriggered(D))
	{
		input[D] = 1;
	}
	else
	{
		input[D] = 0;
	}

	return input;
}

bool InputManager::SenseMouseInput() {
	return IsMouseActionTriggered(M_LEFT);
}

bool InputManager::IsKeyboardActionTriggered(int id) {
	return sf::Keyboard::isKeyPressed(m_KeyboardAction[id]);
}


bool InputManager::IsMouseActionTriggered(int id) {
	return sf::Mouse::isButtonPressed(m_MouseAction[id]);
}


void InputManager::AddActions() {
	AddKeyboardAction(W, sf::Keyboard::W);
	AddKeyboardAction(A, sf::Keyboard::A);
	AddKeyboardAction(S, sf::Keyboard::S);
	AddKeyboardAction(D, sf::Keyboard::D);

	AddMouseAction(M_LEFT, sf::Mouse::Left);
	AddMouseAction(M_RIGHT, sf::Mouse::Right);
}

void InputManager::AddKeyboardAction(int id, sf::Keyboard::Key key) {
	m_KeyboardAction[id] = key;
}
void InputManager::AddMouseAction(int id, sf::Mouse::Button button) {
	m_MouseAction[id] = button;
}