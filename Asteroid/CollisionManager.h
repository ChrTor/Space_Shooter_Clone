#pragma once
#include "Entity.h"
#include "Maths.h"

enum MapBounds
{
	TOP,
	BOT,
	LEFT,
	RIGHT,
};

struct newEntity
{
	sf::Vector2f position;
	sf::Vector2f velocity;
	float radius;
	sf::Color color;
};


class CollisionManager
{
public:
	CollisionManager(int& windowsizeX, int& windowSizeY);
	~CollisionManager();

	void Update(std::vector<Entity*> entities);

	void StoreEntityToBeCreated(Entity* originalBullet, Entity* originalAsteroid);
	std::vector<newEntity> GetEntitiesToBeCreated();
private:

	int m_WindowSizeX, m_WindowSizeY;
	std::vector<newEntity> m_EntitiesToBeCreated;


	std::map<Entity*, Entity*> DetectEntityCollision(std::vector<Entity*> entities);
	void ResolveCollision(std::map<Entity*, Entity*> collidingEntities);
	void DisplaceObjects(Entity* current, Entity* target);
	void AlterDirections(Entity* current, Entity* target);

	std::map<Entity*, MapBounds> DetectMapCollision(std::vector<Entity*> entities);
	void ResolveMapCollisions(std::map<Entity*, MapBounds> collidingEntities);
	void SolveAsteroid(Entity* asteroid, MapBounds& bound);
	void SolvePlayer(Entity* player, MapBounds& bound);
	void SolveBullet(Entity* bullet, MapBounds& bound);
};

