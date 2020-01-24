#pragma once
#include "State.h"
#include "SFML/Graphics.hpp"

class Menu : public State
{
public:
	Menu(int &indowSizeX, int &windowSizeY);
	~Menu();

	virtual StateID *RunState() override;

private:



};
