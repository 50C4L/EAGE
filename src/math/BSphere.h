#ifndef _BSphere_H
#define _BSphere_H

#include <SFML\System\Vector2.hpp>

class BSphere
{
public:
	BSphere();
	~BSphere();
	void			create( sf::Vector2f, float );
	bool			isCollide( sf::Vector2f );
	bool			isCollide( BSphere sphere ); 
	sf::Vector2f	getCentre();
	float			getRadius();

private:
	sf::Vector2f	_centre;
	float			_radius;
	float			_radSquare;
};

#endif