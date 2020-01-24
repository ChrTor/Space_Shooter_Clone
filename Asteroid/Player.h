#pragma once
#include "Entity.h"


class Player : public Entity
{
public:
	Player(EntityID& id, sf::Vector2f& pos, sf::Vector2f& dir, sf::Vector2f& velocity, float& radius, sf::Color& color);
	~Player();

	void Update(sf::Vector2i mousePos, std::vector<int> keyboard, float& deltatime) override;

	void Move(sf::Vector2i mousePos, std::vector<int> keyboard, float& deltatime);

private:
	int m_Speed;
};


