#pragma once
#include "Entity.h"

class Bullet : public Entity
{
public:
	Bullet(EntityID& id, sf::Vector2f& pos, sf::Vector2f& dir, sf::Vector2f& velocity, float& radius, sf::Color& color);
	~Bullet();

	void Update(float& deltatime) override;

private:



	void Move(float& deltatime);


	int m_Speed;
};
