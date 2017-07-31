#ifndef _ENVIRONMENT_H
#define _ENVIRONMENT_H

#include <SFML\System\Vector2.hpp>

class Environment
{
public:
	static Environment* getInstance();
	~Environment();

	void			setGravity( float x, float y );
	void			setWind( float x, float y );
	sf::Vector2f	gravity();
	sf::Vector2f	wind();

private:
	Environment();
	static Environment* _instance;

	sf::Vector2f		_gravity;
	sf::Vector2f		_wind;
};

#endif _ENVIRONMENT_H