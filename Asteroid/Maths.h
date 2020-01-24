#pragma once
#include "Maths.h"

static	 sf::Vector2f GetNormalizedVector(sf::Vector2f& posA, sf::Vector2f& posB) {
	float distance = sqrtf((posA.x - posB.x) * (posA.x - posB.x) + (posA.y - posB.y) * (posA.y - posB.y));
	return sf::Vector2f((posB.x - posA.x) / distance, (posB.y - posA.y) / distance);
}

static sf::Vector2f CastIntToFloat(sf::Vector2i vector) {
	sf::Vector2f rVector = sf::Vector2f((float)vector.x, (float)vector.y);
	return rVector;
}

static float FDistance(sf::Vector2f objectA, sf::Vector2f objectB) {
	return sqrtf((objectA.x - objectB.x) * (objectA.x - objectB.x)
		+ (objectA.y - objectB.y) * (objectA.y - objectB.y));
}