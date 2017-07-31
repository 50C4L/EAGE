#ifndef _PHYSICSBODY_H
#define _PHYSICSBODY_H

#include <SFML\System.hpp>
#include "AABB.h"
#include "BSphere.h"

struct PhysicsBody
{
	float			mass;
	sf::Vector2f	acceleration;
	sf::Vector2f	uniform;
	sf::Vector2f	currentVelocity;
	sf::Vector2f	accumulation;
	float			currentSpeed;
	float			maxSpeed;
	float			inertia;
	float			radius;
	bool			IsDynamic;
	AABB			aabb;
	BSphere			bsphere;
};

#endif	// _PHYSICSBODY_H