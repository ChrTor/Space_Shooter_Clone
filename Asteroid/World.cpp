#include "World.h"
#include "Maths.h"
#include <cstdlib>
#include <time.h>
#include <random>
#include <iostream>
#include <vector>

World::World(int &difficulty, int &windowSizeX, int &windowSizeY)
{
	m_Difficulty = difficulty;
	m_WorldSizeX = windowSizeX;
	m_WorldSizeY = windowSizeY;
	m_EntityList = {};

	m_CollissionManager = new CollisionManager(m_WorldSizeX, m_WorldSizeY);
	CreateInitialEntities(m_Difficulty);
}

World::~World()
{
	m_CollissionManager = nullptr;
	delete(m_CollissionManager);
}


void World::Update(sf::Vector2i mousePos, bool leftClick, std::vector<int> keyBoard, float &deltatime) {
	
	UpdateEntities(mousePos, leftClick, keyBoard, deltatime);

	UpdateBullet(deltatime);

	m_CollissionManager->Update(m_EntityList);

	UpdateEntityLists();

}

void World::Draw(sf::RenderWindow* window)
{
	for (auto* ent : m_EntityList) {
		ent->Draw(window);
	}
}

// Update 

void World::UpdateEntities(sf::Vector2i mousePos, bool leftClick, std::vector<int> keyBoard, float& deltatime) {
	for (auto* ent : m_EntityList) {
		if (ent->GetEntityID() == PLAYER)
		{
			// Check Shoot
			m_ShootCD -= deltatime;
			bool isShooting = m_ShootCD <= 0.0f && leftClick;
			if (isShooting)
			{
				sf::Vector2f pos = m_Player->GetTransform().getPosition();
				CreateBullet(pos, mousePos);
				m_ShootCD = 0.5f;
			}

			// Modified Update
			ent->Update(mousePos, keyBoard, deltatime);
			ent->Move(mousePos, keyBoard, deltatime);
		}
		else
		{
			ent->Update(deltatime);
		}
	}
}

void World::UpdateBullet(float& deltatime) {

	int bulletSize = m_BulletList.size();
	for (int i = 0; i < bulletSize; i++)
	{
		Bullet* ent = m_BulletList[i];
		ent->Update(deltatime);
	}
}

void World::UpdateEntityLists() {

	// Entity List
	std::vector<Entity*> newList = {};
	int e_Size = m_EntityList.size();
	for (int i = 0; i < e_Size; i++)
	{
		Entity* ent = m_EntityList[i];
		if (!ent->m_ToBeDestroyed)
		{
			newList.push_back(ent);
		}
		else
		{
			ent->~Entity();
		}
	}
	m_EntityList.clear();
	m_EntityList = newList;
}

std::vector<Entity*> World::GetEntityList() {
	return m_EntityList;
}

// Create
void World::CreateInitialEntities(int& difficulty) {
	// Asteroids
	for (int i = 0; i < 10; i++)
	{

		// Rand Direction
		sf::Vector2f direction(RandomNumber(1.0f, -1.0f), RandomNumber(1.0f, -1.0f));
		// Rand Radius
		float radius = RandomNumber(50, 10);
		// Rand Position
		sf::Vector2f newPosition = sf::Vector2f(RandomNumber(m_WorldSizeX - radius , 0.0f), RandomNumber(m_WorldSizeY - radius, 0.0f));
		// Rand Velocity
		sf::Vector2f velocity(RandomNumber(5.0f, -5.0f), RandomNumber(5.0f, -5.0f));
		// Rand Color
		sf::Color col = sf::Color(RandomInteger(0, 255), RandomInteger(0, 255), 255);
		col = sf::Color::Red;

		
		Entity* newAsteroid = CreateEntity(ASTEROID, newPosition, direction, velocity, radius, col);
		 m_EntityList.push_back(newAsteroid);
	}		
	// Ship

	sf::Vector2f newPosition = sf::Vector2f(m_WorldSizeX / 2, m_WorldSizeY / 2);
	sf::Vector2f direction(RandomNumber(1.0f, -1.0f), RandomNumber(1.0f, -1.0f));

	float radius = 25.0f;
	sf::Color col = sf::Color(rand() % 256, rand() % 256, rand() % 256, 255);
	col = sf::Color::Blue;
	sf::Vector2f velocity(0.0f, 0.0f);
	m_Player = CreateEntity(PLAYER, newPosition, direction, velocity, radius, col);
	m_EntityList.push_back(m_Player);
	
}

Entity* World::CreateEntity(EntityID type, sf::Vector2f& position, sf::Vector2f& direction, sf::Vector2f& velocity, float& radius, sf::Color& color) {

	Entity* newEntity;
	int pointSize = 40;

	if (type == ASTEROID)
	{
		newEntity = new Asteroid(type, position, direction, velocity, radius, color);
	}
	else if (type == PLAYER)
	{
		newEntity = new Player(type, position, direction, velocity, radius, color);
		pointSize = 3;
	}
	else
	{
		newEntity = new Bullet(type, position, direction, velocity, radius, color);
	}
	newEntity->m_Id = m_ID;
	m_ID += 1;
	return newEntity;
}

Entity* World::CreateBullet(sf::Vector2f &playerposition, sf::Vector2i &mousepos) {


	// Get direction Vector
	sf::Vector2f originPosition(playerposition);
	sf::Vector2f mousePosition = CastIntToFloat(mousepos);
	sf::Vector2f normalizeVector = GetNormalizedVector(playerposition, mousePosition);
	sf::Vector2f dir(.0f, .0f);
	float radius = 2.5f;
	sf::Color color = sf::Color::White;

	Entity* newBullet = CreateEntity(BULLET, playerposition, dir, normalizeVector, radius, color);


	return newBullet;
}


// Random Number Generator
float& World::RandomNumber(float max, float min)
{
	std::random_device generator;
	generator.entropy();
	std::uniform_real_distribution<float> distribution(min, max);
	float numb = distribution(generator);
	return numb;
}

int& World::RandomInteger(int min, int max)
{
	std::random_device generator;
	generator.entropy();
	std::uniform_int_distribution<int> distribution(min, max);
	int numb = distribution(generator);
	return numb;
}
