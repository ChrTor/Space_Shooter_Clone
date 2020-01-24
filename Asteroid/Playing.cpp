#include "Playing.h"

#include "SFML/Window.hpp"
#include "SFML/System.hpp"

Playing::Playing(int &difficulty, int &windowsizeX, int &windowsizeY) {
	m_StateName = new std::string("Playing");
	SetCurrentStateID(new StateID(PLAYING));

	m_Window = new sf::RenderWindow(sf::VideoMode(windowsizeX, windowsizeY), "SFML works!", sf::Style::Close | sf::Style::Resize);
	m_Window->setFramerateLimit(60);

	m_World = new World(difficulty, windowsizeX, windowsizeY);
	m_InputManager = new InputManager();

	m_Score = nullptr;
}

Playing::~Playing() {
	delete(m_StateName);
	m_StateName = nullptr;
	delete(m_CurrentState);
	m_CurrentState = nullptr;
	delete(m_Window);
	m_Window = nullptr;
	delete(m_World);
	m_World = nullptr;
	delete(m_InputManager);
	m_InputManager = nullptr;
}


 StateID *Playing::RunState() {
	 // Print name of State
	std::string *name = GetStateName();
	printf("%s\n", name->c_str());
	// Reset Time
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;


	while (m_Window->isOpen())
	{
		sf::Event event;
		while (m_Window->pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				m_Window->close();
				break;
			case sf::Event::Resized:
				printf("New window width: %i\nNew window height: %i", event.size.height, event.size.width);
			}
		}

		sf::Time time = clock.restart();
		float deltaTime = time.asSeconds();


		bool leftClick = m_InputManager->SenseMouseInput();
		std::vector<int> keyBoard = m_InputManager->SenseKeyboardInput();
		sf::Vector2i mousePos = m_InputManager->GetMousePosition(m_Window);

		//m_CollisionManager->Update(m_World->GetEntityList());

		m_World->Update(mousePos, leftClick, keyBoard, deltaTime);

		m_Window->clear();
		m_World->Draw(m_Window);
		m_Window->display();


	}
	return GetCurrentStateID();
}