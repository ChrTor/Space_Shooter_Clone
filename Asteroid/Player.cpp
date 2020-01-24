#include "Player.h"
#include <vector>



Player::Player(EntityID& id, sf::Vector2f& pos, sf::Vector2f& dir, sf::Vector2f& velocity, float& radius, sf::Color& color)
	: Entity(id, pos, dir, velocity, radius, color) {

	m_Speed = 120;
}

Player::~Player()
{
}


void Player::Update(sf::Vector2i mousePos, std::vector<int> keyboard, float& deltatime) {
	Move(mousePos, keyboard, deltatime);
}

void Player::Move(sf::Vector2i mousePos, std::vector<int> keyboard, float& deltatime) {

	sf::Vector2f newAcceleration((float)(keyboard[3] - keyboard[2]) * 10.0f, (float)(keyboard[1] - keyboard[0]) * 10.0f);
	sf::Vector2f newVelocity = GetVelocity() + GetAcceleration();
	SetAcceleration(newAcceleration);
	SetVelocity(newVelocity);

	sf::Vector2i newMousePos = mousePos;
	sf::Vector2f oldPos(GetTransform().getPosition());

	float angle = atan2f(oldPos.y - newMousePos.y, oldPos.x - newMousePos.x) * 180 / 3.14f;

	// SetVelocity
	sf::Vector2f direction((float)(keyboard[3] - keyboard[2]), (float)(keyboard[1] - keyboard[0]));

	// Set New Position
	GetTransform().setRotation(angle + 30.0f);
	GetTransform().setPosition(oldPos += (newVelocity * deltatime));
}