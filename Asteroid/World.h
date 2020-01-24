#pragma once
#include "SFML/System.hpp"
#include "Asteroid.h"
#include "Player.h"
#include "Bullet.h"
#include "CollisionManager.h"

class World
{
public:

	int m_ID;

	World(int &difficulty, int &windowSizeX, int &windowSizeY);
	~World();

	void Update(sf::Vector2i mousePos, bool leftClick, std::vector<int> keyBoard, float &deltatime);
	void Draw(sf::RenderWindow *window);

	std::vector<Entity*> GetEntityList();


private:


	void UpdateEntities(sf::Vector2i mousePos, bool leftClick, std::vector<int> keyBoard, float& deltatime);

	void UpdateBullet(float& deltatime);
	
	void UpdateEntityLists();
	void CreateInitialEntities(int &difficulty);
	Entity* CreateEntity(EntityID type, sf::Vector2f& position, sf::Vector2f& direction, sf::Vector2f& velocity, float& radius, sf::Color& color);
	Entity* CreateBullet(sf::Vector2f &playerposition, sf::Vector2i &mousepos);

	float& RandomNumber(float min, float max);
	int& RandomInteger(int min, int max);

	CollisionManager* m_CollissionManager;
	
	std::vector<Entity*> m_EntityList;
	std::vector<Asteroid*> m_AsteroidList;
	std::vector<Bullet*> m_BulletList;

	int m_Difficulty;
	int m_WorldSizeX;
	int m_WorldSizeY;

	Entity *m_Player;
	float m_ShootCD;
};
