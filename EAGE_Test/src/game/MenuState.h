#ifndef _MENUSTATE_H
#define _MENUSTATE_H

#include "../../../src/helper/helper.h"
#include <SFGUI\Button.hpp>
#include <SFGUI\Label.hpp>

class MenuState:public State
{
public:
					~MenuState();
	virtual void	enterFunc();
	virtual void	control();
	virtual void	leaveFunc();

	static MenuState* getInstance();

	void ButtonPlayTest();
	void ButtonEndTest();

protected:
	MenuState();
	static MenuState* _instance;

private:
	sfg::Button::Ptr beginBtn;
	sfg::Button::Ptr exitBtn; 
	sfg::Label::Ptr _title;

};	// class MenuState

#endif