#include "CollisionManager.h"
#include "Entity.h"
#include <map>
#include "Maths.h"
CollisionManager::CollisionManager(int &windowsizeX, int &windowSizeY)
{
	m_WindowSizeX = windowsizeX;
	m_WindowSizeY = windowSizeY;
}

CollisionManager::~CollisionManager()
{
}

void CollisionManager::Update(std::vector<Entity*> entityList) {

	// Collision with objects
	std::map<Entity*, Entity*> collidingEntities = DetectEntityCollision(entityList);
	ResolveCollision(collidingEntities);

	// Collision with map
	std::map<Entity*, MapBounds> MapColList = DetectMapCollision(entityList);
	ResolveMapCollisions(MapColList);
}

void CollisionManager::StoreEntityToBeCreated(Entity* originalBullet, Entity* originalAsteroid) {

	// Dynamic collision
	sf::Vector2f currentPosition = originalBullet->GetTransform().getPosition();
	sf::Vector2f targetPosition = originalAsteroid->GetTransform().getPosition();

	// Distance
	float distance = FDistance(currentPosition, targetPosition);

	// Normal vector
	sf::Vector2f normal(GetNormalizedVector(currentPosition, targetPosition));

	// Tangent
	sf::Vector2f tangentVector(-normal.y, normal.x);

	// Dot Product Tangent
	float dpTan1 = originalBullet->GetVelocity().x * tangentVector.x + originalBullet->GetVelocity().y * tangentVector.y;
	float dpTan2 = originalAsteroid->GetVelocity().x * tangentVector.x + originalAsteroid->GetVelocity().y * tangentVector.y;


	// Dot Product Normal
	float dpNorm1 = originalBullet->GetVelocity().x * normal.x + originalBullet->GetVelocity().y * normal.y;
	float dpNorm2 = originalAsteroid->GetVelocity().x * normal.x + originalAsteroid->GetVelocity().y * normal.y;

	// Conservation of momentum
	float m1 = (dpNorm1 * (originalBullet->GetMass() - originalAsteroid->GetMass()) + 2.0f * originalAsteroid->GetMass() * dpNorm2) / (originalBullet->GetMass() + originalAsteroid->GetMass());
	float m2 = (dpNorm2 * (originalAsteroid->GetMass() - originalBullet->GetMass()) + 2.0f * originalBullet->GetMass() * dpNorm1) / (originalBullet->GetMass() + originalAsteroid->GetMass());

	// With Mass
	sf::Vector2f newVelc((tangentVector.x * dpTan1) + (normal.x * m1),
		(tangentVector.y * dpTan1) + (normal.y * m1));
	sf::Vector2f newVelt((tangentVector.x * dpTan2) + (normal.x * m2),
		(tangentVector.y * dpTan2) + (normal.y * m2));

	// Without Mass
	sf::Vector2f newVelcg(tangentVector.x * dpTan1,
		tangentVector.y * dpTan1);
	sf::Vector2f newVelts(tangentVector.x * dpTan2,
		tangentVector.y * dpTan2);

	// Set Final Velocity
	originalBullet->SetVelocity(newVelc);
	originalAsteroid->SetVelocity(newVelt);


}
std::vector<newEntity> CollisionManager::GetEntitiesToBeCreated() {
	return m_EntitiesToBeCreated;
}

// Entity Collision
std::map<Entity*, Entity*> CollisionManager::DetectEntityCollision(std::vector<Entity*> entityList) {

	std::map<Entity*, Entity*> collidingEntities = {};

	for (auto& object_A : entityList) {
		for (auto& object_B : entityList) {
			if (object_A == object_B)
			{
				continue;
			}


			// Remove Player from collision
			if (object_A->GetEntityID() == PLAYER || object_B->GetEntityID() == PLAYER)
			{
				continue;
			}
			sf::Vector2f posA(object_A->GetPosition());
			sf::Vector2f posB(object_B->GetPosition());

			float distance = fabsf((posA.x - posB.x)*(posA.x - posB.x) + (posA.y - posB.y)*(posA.y - posB.y));

			float combinedRaduis = ((object_A->GetRadius() + object_B->GetRadius()) * (object_A->GetRadius() + object_B->GetRadius()));

			if (distance < combinedRaduis)
			{
				collidingEntities[object_A] = object_B;
			}
		}
	}
	return collidingEntities;
}
	// Resolve
void CollisionManager::ResolveCollision(std::map<Entity*, Entity*> collidingEntities) {

	if (collidingEntities.size() == 0)
	{
		return;
	}

	std::map<Entity*, Entity*>::iterator it;

	Entity* currentObject = {};
	Entity* targetObject = {};

	for (it = collidingEntities.begin(); it != collidingEntities.end(); it++)
	{
		if (currentObject == it->second)
		{
			continue;
		}
		currentObject = it->first;
		targetObject = it->second;

		if (currentObject->GetEntityID() == PLAYER && targetObject->GetEntityID() == ASTEROID)
		{
			// Kill Player
			//currentObject->m_ToBeDestroyed = true;
			// Split Asteroid

		}
		else if (currentObject->GetEntityID() == ASTEROID && targetObject->GetEntityID() == ASTEROID)
		{
			DisplaceObjects(currentObject, targetObject);
			AlterDirections(currentObject, targetObject);
		}
		else if (currentObject->GetEntityID() == BULLET && targetObject->GetEntityID() == ASTEROID)
		{
			// Kill Bullet
			currentObject->m_ToBeDestroyed = true;

			// Check size of Asteroid
			if (targetObject->GetTransform().getRadius() < 5.0f)
			{
				targetObject->m_ToBeDestroyed = true;
			}
			// Split Asteroid

			StoreEntityToBeCreated(currentObject, targetObject);
		}
		continue;
	}
}
// Static Collision
void CollisionManager::DisplaceObjects(Entity* current, Entity* target) {

	// Get Position
	sf::Vector2f currentPosition = current->GetTransform().getPosition();
	sf::Vector2f targetPosition = target->GetTransform().getPosition();

	// Calculate Distance
	float fDistance = sqrtf((currentPosition.x - targetPosition.x) * (currentPosition.x - targetPosition.x)
		+ (currentPosition.y - targetPosition.y) * (currentPosition.y - targetPosition.y));
	float fOverlap = 0.5f * (fDistance - current->GetTransform().getRadius() - target->GetTransform().getRadius());

	// Displace Current Asteroid
	sf::Vector2f newPosition(currentPosition.x - (fOverlap * (currentPosition.x - targetPosition.x) / fDistance),
		currentPosition.y - (fOverlap * (currentPosition.y - targetPosition.y) / fDistance));
	current->SetPosition(newPosition);

	// Displace Target Asteroid
	sf::Vector2f targetNewPosition(targetPosition.x + (fOverlap * (currentPosition.x - targetPosition.x) / fDistance),
		targetPosition.y + (fOverlap * (currentPosition.y - targetPosition.y) / fDistance));
	target->SetPosition(targetNewPosition);
}
void CollisionManager::AlterDirections(Entity* c, Entity* t) {

	// Dynamic Collission
	sf::Vector2f currentPosition = c->GetPosition();
	sf::Vector2f targetPosition = t->GetPosition();

	// Distance
	float distance = FDistance(currentPosition, targetPosition);

	// Normal vector
	sf::Vector2f normal(GetNormalizedVector(currentPosition, targetPosition));

	// Tangent
	sf::Vector2f tangentVector(-normal.y, normal.x);

	// Dot Product Tangent
	float dpTan1 = c->GetVelocity().x * tangentVector.x + c->GetVelocity().y * tangentVector.y;
	float dpTan2 = t->GetVelocity().x * tangentVector.x + t->GetVelocity().y * tangentVector.y;

	// Dot Product Normal
	float dpNorm1 = c->GetVelocity().x * normal.x + c->GetVelocity().y * normal.y;
	float dpNorm2 = t->GetVelocity().x * normal.x + t->GetVelocity().y * normal.y;

	// Conservation of momentum
	float m1 = (dpNorm1 * (c->GetMass() - t->GetMass()) + 2.0f * t->GetMass() * dpNorm2) / (c->GetMass() + t->GetMass());
	float m2 = (dpNorm2 * (t->GetMass() - c->GetMass()) + 2.0f * c->GetMass() * dpNorm1) / (c->GetMass() + t->GetMass());

	// With Mass
	sf::Vector2f newVelc((tangentVector.x * dpTan1) + (normal.x * m1),
		(tangentVector.y * dpTan1) + (normal.y * m1));
	sf::Vector2f newVelt((tangentVector.x * dpTan2) + (normal.x * m2),
		(tangentVector.y * dpTan2) + (normal.y * m2));
	
	// Without Mass
	sf::Vector2f newVelcg(tangentVector.x * dpTan1, 
		tangentVector.y * dpTan1);
	sf::Vector2f newVelts(tangentVector.x * dpTan2,
		tangentVector.y * dpTan2);

	// Set Final Velocity
	c->SetVelocity(newVelc);
	t->SetVelocity(newVelt);
}



// Map Collision
std::map<Entity*, MapBounds> CollisionManager::DetectMapCollision(std::vector<Entity*> entities) {

	std::map<Entity*, MapBounds> colList = {};

	for (auto& Object : entities) {

		sf::CircleShape transform = Object->GetTransform();
		sf::Vector2f currentPosition(transform.getPosition());
		float radius = transform.getRadius();

		if (currentPosition.x - radius < 0.0f)
		{
			colList[Object] = LEFT;
		}
		else if (currentPosition.y - radius < 0.0f)
		{
			colList[Object] = TOP;
		}
		else if (currentPosition.x + radius > m_WindowSizeX)
		{
			colList[Object] = RIGHT;
		}
		else if (currentPosition.y + radius > m_WindowSizeY)
		{
			colList[Object] = BOT;
		}
	}
	return colList;
}
void CollisionManager::ResolveMapCollisions(std::map<Entity*, MapBounds> collidingEntities) {
	if (collidingEntities.size() == 0)
	{
		return;
	}
	std::map<Entity*, MapBounds>::iterator it;

	for (it = collidingEntities.begin(); it != collidingEntities.end(); it++)
	{
		Entity* ent = it->first;
		MapBounds bounds = it->second;
		EntityID id = ent->GetEntityID();
		sf::Vector2f oldDir = it->first->GetDirection();

		if (id == ASTEROID)
		{
			SolveAsteroid(ent, bounds);
		}
		else if (id == PLAYER)
		{
			SolvePlayer(ent, bounds);
		}
		else if (id == BULLET)
		{
			SolveBullet(ent, bounds);
		}
	}
}
	// Solve Individual Entities
void CollisionManager::SolveAsteroid(Entity* asteroid, MapBounds &bound) {

	sf::Vector2f currentPosition = asteroid->GetPosition();
	sf::Vector2f currentVelocity = asteroid->GetVelocity();
	float radius = asteroid->GetRadius();

	if (bound == TOP || bound == BOT)
	{
		currentVelocity.y = currentVelocity.y * -1;

		if (bound == TOP)
		{
			float offset = (currentPosition.y - radius);
			asteroid->GetTransform().setPosition(currentPosition.x, currentPosition.y - offset);
		}
		else
		{
			float offset = (currentPosition.y + radius) - m_WindowSizeY;
			asteroid->GetTransform().setPosition(currentPosition.x, currentPosition.y - offset);
		}
	}
	else
	{
		currentVelocity.x = currentVelocity.x * -1;
		if (bound == LEFT)
		{
			float offset = (currentPosition.x - radius);
			asteroid->GetTransform().setPosition(currentPosition.x - offset, currentPosition.y);
		}
		else
		{
			float offset = (currentPosition.x + radius) - m_WindowSizeX;
			asteroid->GetTransform().setPosition(currentPosition.x - offset, currentPosition.y);
		}
	}
	asteroid->SetVelocity(currentVelocity);
}
void CollisionManager::SolvePlayer(Entity* player, MapBounds& bound) {
	sf::Vector2f position = player->GetTransform().getPosition();
	if (bound == TOP)
	{
		player->GetTransform().setPosition(position.x, (float)m_WindowSizeY - 25.0f);
	}
	if (bound == BOT)
	{
		player->GetTransform().setPosition(position.x, 25.0f);
	}
	if (bound == LEFT)
	{
		player->GetTransform().setPosition((float)m_WindowSizeX - 25.0f, position.y);
	}
	if (bound == RIGHT)
	{
		player->GetTransform().setPosition(25.0f, position.y);
	}
}
void CollisionManager::SolveBullet(Entity* bullet, MapBounds& bound) {
	bullet->m_ToBeDestroyed = true;
}