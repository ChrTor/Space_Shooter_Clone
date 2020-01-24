#pragma once
#include "SFML/Graphics.hpp"

enum EntityID
{
	ASTEROID,
	PLAYER,
	BULLET,

};


class Entity
{
public:

	int m_Id;

	Entity(EntityID& id, sf::Vector2f& pos, sf::Vector2f& dir, sf::Vector2f& velocity, float& radius, sf::Color& color);
	~Entity();

	virtual void Update(float& deltatime);
	virtual void Update(sf::Vector2i mousePos, std::vector<int> keyboard, float& deltatime);
	void Draw(sf::RenderWindow* window);

	virtual void Move(sf::Vector2i mousePos, std::vector<int> keyboard, float& deltatime);
	void Move(float& deltatime);

	void SetPosition(sf::Vector2f& position);
	sf::Vector2f GetPosition();

	void SetTransform(sf::Vector2f& position, float& radius, int& pointSize, sf::Color &color);
	sf::CircleShape GetTransform();

	void SetDirection(sf::Vector2f &newDir);
	sf::Vector2f GetDirection();

	void SetVelocity(sf::Vector2f& newVel);
	sf::Vector2f GetVelocity();

	float& GetRadius();

	void SetAcceleration(sf::Vector2f& newAcc);
	sf::Vector2f GetAcceleration();

	void SetMass(float& mass);
	float GetMass();

	void SetEntityID(EntityID& id);
	EntityID& GetEntityID();

	bool m_ToBeDestroyed;
private:
	EntityID m_EntityID;


	sf::CircleShape m_Transform;
	sf::Vector2f m_Position;
	sf::Vector2f m_Direction;
	sf::Vector2f m_Velocity;
	sf::Vector2f m_Acceleration;

	float m_Radius;
	float m_Mass;
};
