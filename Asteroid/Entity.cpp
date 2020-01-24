#include "Entity.h"


Entity::Entity(EntityID& id, sf::Vector2f& pos, sf::Vector2f& dir, sf::Vector2f& velcoity, float& radius, sf::Color& color)
{
	// Check for PLAYER status
	int pointSize = 40;
	if (id == PLAYER)
	{
		pointSize = 3;
		m_Velocity = sf::Vector2f(0, 0);
	}

	// Set Initial Values
	m_EntityID = id;
	m_Position = pos;
	m_Direction = dir;
	m_Velocity = velcoity;
	m_Radius = radius;

	//Set Mass
	float mass = m_Radius * 10.0f;
	SetMass(mass);

	// Static values
	m_ToBeDestroyed = false;

	// Set Sprite
	SetTransform(pos, radius, pointSize, color);
}
Entity::~Entity() {

}

 void Entity::Update(float& deltatime) {
	 // Specific behaviour in inherited class
	printf("%s\n", "Update Base");
	Move(deltatime);
}
void Entity::Update(sf::Vector2i mousePos, std::vector<int> keyboard, float& deltatime) {

}
void Entity::Draw(sf::RenderWindow* window)
{
	window->draw(m_Transform);
}

void Entity::Move(sf::Vector2i mousePos, std::vector<int> keyboard, float& deltatime) {

}

void Entity::Move(float& deltatime)
{
	// SetVelocity
	sf::Vector2f newVelocity = m_Velocity + (m_Acceleration * deltatime);
	SetVelocity(newVelocity);

	// Set New Position
	sf::Vector2f oldPos(m_Position);
	sf::Vector2f newPos(oldPos + m_Velocity);
	SetPosition(newPos);
}

void Entity::SetPosition(sf::Vector2f& position)
{
	m_Position = position;
	m_Transform.setPosition(m_Position);
}
sf::Vector2f Entity::GetPosition()
{
	return m_Position;
}

void Entity::SetTransform(sf::Vector2f &position,float &radius,int &pointSize,sf::Color &color) {
	m_Transform.setRadius(radius);
	m_Transform.setOrigin(m_Transform.getPosition().x + radius, m_Transform.getPosition().y + radius);
	m_Transform.setPosition(position);
	m_Transform.setFillColor(sf::Color::Black);
	m_Transform.setOutlineThickness(4.0f);
	m_Transform.setOutlineColor(color);
	
}
sf::CircleShape Entity::GetTransform() {
	return m_Transform;
}

void Entity::SetDirection(sf::Vector2f& newDir) {
	m_Direction = newDir;
}
sf::Vector2f Entity::GetDirection() {
	return m_Direction;
}

void Entity::SetVelocity(sf::Vector2f& newVel) {
	m_Velocity = newVel;
}
sf::Vector2f Entity::GetVelocity() {
	return m_Velocity;
}

float& Entity::GetRadius()
{
	return m_Radius;
}

void Entity::SetAcceleration(sf::Vector2f& newAcc) {
	m_Acceleration = newAcc;
}
sf::Vector2f Entity::GetAcceleration() {
	return m_Acceleration;
}

void Entity::SetMass(float& mass) {
	m_Mass = mass;
}
float Entity::GetMass() {
	return m_Mass;
}

void Entity::SetEntityID(EntityID& id) {
	m_EntityID = id;
}
EntityID& Entity::GetEntityID() {
	return m_EntityID;
}