#include "../helper/helper.h"
#include "math.h"

BSphere::BSphere()
{
	_radius = 0.0f;
	_radSquare = 0.0f;
}

BSphere::~BSphere()
{
}

void BSphere::create( sf::Vector2f ct, float rad )
{
	_centre = ct;
	_radius = rad;
	_radSquare = _radius * _radius;
}

sf::Vector2f BSphere::getCentre()
{
	return _centre;
}

float BSphere::getRadius()
{
	return _radius;
}

bool BSphere::isCollide( sf::Vector2f p )
{
	float dist = eage::getDistanceSquare( _centre, p );
	if( _radSquare < dist )
		return false;
	else
		return true;
}

bool BSphere::isCollide( BSphere sphere )
{
	float dist = eage::getDistanceSquare( _centre, sphere.getCentre() );
	float cmp = ( _radius + sphere.getRadius() )*( _radius + sphere.getRadius() );
	if( cmp < dist )
		return false;
	else
		return true;
}