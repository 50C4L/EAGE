#ifndef _BUTTON_H
#define _BUTTON_H

#include "../helper/helper.h"

enum Button_State
{
	BTN_NORMAL	= 0,
	BTN_HOVER,
	BTN_PRESSED
};	// Button state

class Button:public UIObject
{
public:
			Button();
	virtual ~Button();

	bool			isPress();
	void			changeState();
	Button_State	getState();

private:
	void			_setState( Button_State );

	Button_State	_state;

	VO_uvCoordinate _norUV;
	VO_uvCoordinate _hovUV;
	VO_uvCoordinate _preUV;
};	// class Button


#endif	// _BUTTON_H