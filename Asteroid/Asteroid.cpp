#include "Asteroid.h"
#include "SFML/Graphics.hpp"

#include <math.h>
#define PI 3.14159265359

Asteroid::Asteroid(EntityID& id, sf::Vector2f& pos, sf::Vector2f& dir, sf::Vector2f& velocity, float& radius, sf::Color& color) 
	: Entity(id, pos, dir, velocity, radius, color){
}

Asteroid::~Asteroid() {

}

void Asteroid::Update(float &deltaTime) {
	Move(deltaTime);
}

