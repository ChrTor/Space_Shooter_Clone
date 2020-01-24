#pragma once
#include "Entity.h"
class Asteroid : public Entity
{
public:
	Asteroid(EntityID& id, sf::Vector2f& pos, sf::Vector2f& dir, sf::Vector2f& vel, float& radius, sf::Color& color);
	~Asteroid();

	void Update(float &deltatime);


private:

};

