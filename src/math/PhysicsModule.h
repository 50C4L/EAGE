#ifndef _PHYSICSMODULE_H
#define _PHYSICSMODULE_H

// multi-progress physics engine

#include <SFML\System.hpp>
#include <Box2D\Box2D.h>
#include <list>
#include "../helper/helper.h"
#include "Environment.h"


class PhysicsModule
{
public:
	static PhysicsModule*	getInstance();
	virtual ~PhysicsModule();

	bool initialize( float frequency, int vecIteration, int posIteration );
	void activate();
	void shutdown();

	void setSpeed( float value );
	void setGravity( sf::Vector2f value );
	void setFPS( float value );
	b2World* getWorld();
	void addObject( GameObject* obj );
	void pause( bool value );
	void clear();
	void update();

protected:
	PhysicsModule();

private:
	static PhysicsModule*		_instance;
	std::list<GameObject*>	_objectList;

	sf::Vector2f	_gravity;
	float			_currentFPS;
	bool			_isPause;
	Environment*	_env;
	float			_gameSpeed;

	// Box2D properties
	float32			_frequency;
	int32			_velocityIteration;
	int32			_positionIteration;
	b2World			*_world;
};


#endif

