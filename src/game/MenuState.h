#ifndef _MENUSTATE_H
#define _MENUSTATE_H

#include "../helper/State.h"
#include "../UI/Button.h"


class MenuState:public State
{
public:
					~MenuState();
	virtual void	enterFunc();
	virtual void	control();
	virtual void	leaveFunc();

	static MenuState* getInstance();

protected:
	MenuState();
	static MenuState* _instance;

private:

	Button	*_test;

};	// class MenuState

#endif