#ifndef _PLAYER_H
#define _PLAYER_H

#include "../../../src/helper/helper.h"

class Player:public FBAnimObject
{
public:
	Player();
	~Player();
	void move( sf::Vector2f, float );
	void react();
	void stop();
};	// class Player

#endif