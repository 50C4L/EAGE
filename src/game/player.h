#ifndef _PLAYER_H
#define _PLAYER_H

#include "../helper/FBAnimObject.h"

class Player:public FBAnimObject
{
public:
	Player();
	~Player();
	void move( sf::Vector2f, float );
	void stop();
};	// class Player

#endif