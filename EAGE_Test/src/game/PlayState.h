#ifndef _PLAYSTATE_H
#define _PLAYSTATE_H

#include "../../../src/helper/helper.h"
#include "player.h"
#include <SFGUI\Button.hpp>
#include <SFGUI\Label.hpp>

class PlayState:public State
{
public:
			~PlayState();

	void	enterFunc();
	void	control();
	void	leaveFunc();
	void	onPrevBtn();
	void	onNextBtn();


	static PlayState* getInstance();
	
protected:
	PlayState();
	static PlayState* _instance;

private:
	// test
	Player*				_player;
	GameObject*			_obsticle;
	ParticleFX*			_test;
	Camera*				_camera;
	Layer*				_background;

	sfg::Label::Ptr		_title;
	sfg::Label::Ptr		_message;
	sfg::Button::Ptr	_nextBtn;
	sfg::Button::Ptr	_preBtn;

};	// class PlayState

#endif