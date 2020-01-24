#pragma once
#define NOMINMAX
#include "StateMachine.h"
#include "Asteroid.h"

// Main loop
int main() {
	// Init Game
	//Game game = {};
	//game.Init();
	StateMachine* machine = new StateMachine();
	while (true)
	{
		machine->RunMachine();

	}


	
	return 0;
}