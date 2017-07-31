#include "Environment.h"

Environment* Environment::_instance = 0;

Environment* Environment::getInstance()
{
	if( !_instance )	_instance = new Environment();
	return _instance;
}

Environment::Environment()
{
}

Environment::~Environment()
{
}


void Environment::setGravity( float x, float y )
{
	_gravity.x = x;
	_gravity.y = y;
}


void Environment::setWind( float x, float y )
{
	_wind.x = x;
	_wind.y = y;
}


sf::Vector2f Environment::gravity()
{
	return _gravity;
}


sf::Vector2f Environment::wind()
{
	return _wind;
}