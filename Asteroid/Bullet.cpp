#include "Bullet.h"




Bullet::Bullet(EntityID& id, sf::Vector2f& pos, sf::Vector2f& dir, sf::Vector2f& velocity, float& radius, sf::Color& color)
	: Entity(id, pos, dir, velocity, radius, color) {
		
	m_Speed = 550;
}

Bullet::~Bullet()
{
	
}
void Bullet::Update(float& deltatime) {
	Move(deltatime);
}

void Bullet::Move(float& deltatime) {

	sf::Vector2f oldPos(GetTransform().getPosition());

	// Set New Position
	sf::Vector2f direction = GetDirection();
	GetTransform().setPosition(oldPos += direction * (m_Speed * deltatime));
}