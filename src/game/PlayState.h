#ifndef _PLAYSTATE_H
#define _PLAYSTATE_H

#include "../helper/State.h"
#include "player.h"

class PlayState:public State
{
public:
					~PlayState();

	virtual void	enterFunc();
	virtual void	control();
	virtual void	leaveFunc();

	static PlayState* getInstance();
	
protected:
	PlayState();
	static PlayState* _instance;

private:
	// test
	Player*				_player;

};	// class PlayState

#endif