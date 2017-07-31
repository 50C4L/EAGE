#ifndef _AABB_H
#define _AABB_H

#include <SFML\System\Vector2.hpp>

class AABB
{
public:
	AABB();
	~AABB();

	void			addVertex( sf::Vector2f );
	void			translate( sf::Vector2f v );
	bool			judgePoint( sf::Vector2f );
	bool			isCollide( sf::Vector2f );
	bool			isCollide( AABB box );
	sf::Vector2f	getMax();
	sf::Vector2f	getMin();

private:
	sf::Vector2f _max, _min;
	int	flag;
};	// class AABB


#endif _AABB_H	// _AABB_H