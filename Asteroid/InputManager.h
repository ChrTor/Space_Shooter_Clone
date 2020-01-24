#pragma once
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"

enum InputMouse
{
	M_LEFT, M_RIGHT,
};
enum InputKeyboard 
{
	W, S, A, D,
};




class InputManager
{
public:
	InputManager();
	~InputManager();

	std::vector<int> SenseKeyboardInput();
	bool SenseMouseInput();
	sf::Vector2i GetMousePosition(sf::RenderWindow* window);

private:
	void AddActions();
	void AddKeyboardAction(int id, sf::Keyboard::Key key);
	void AddMouseAction(int id, sf::Mouse::Button button);

	bool IsKeyboardActionTriggered(int id);
	bool IsMouseActionTriggered(int id);
private:
	std::map<int, sf::Keyboard::Key> m_KeyboardAction;

	std::map<int, sf::Mouse::Button> m_MouseAction;
};

