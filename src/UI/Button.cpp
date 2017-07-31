#include "../helper/helper.h"
#include <SFML\Window\Mouse.hpp>

Button::Button()
{
	_state = BTN_NORMAL;

	_norUV.leftTop.x		= 0.0f;	_norUV.leftTop.y		= 1.0f;
	_norUV.leftBottom.x		= 0.0f; _norUV.leftBottom.y		= 0.667f;
	_norUV.rightBottom.x	= 1.0f;	_norUV.rightBottom.y	= 0.667f;
	_norUV.rightTop.x		= 1.0f;	_norUV.rightTop.y		= 1.0f;

	_hovUV.leftTop.x		= 0.0f; _hovUV.leftTop.y		= 0.667f;
	_hovUV.leftBottom.x		= 0.0f; _hovUV.leftBottom.y		= 0.334f;
	_hovUV.rightBottom.x	= 1.0f; _hovUV.rightBottom.y	= 0.334f;
	_hovUV.rightTop.x		= 1.0f; _hovUV.rightTop.y		= 0.667f;

	_preUV.leftTop.x		= 0.0f; _preUV.leftTop.y		= 0.334f;
	_preUV.leftBottom.x		= 0.0f; _preUV.leftBottom.y		= 0.001f;
	_preUV.rightBottom.x	= 1.0f;	_preUV.rightBottom.y	= 0.001f;
	_preUV.rightTop.x		= 1.0f; _preUV.rightTop.y		= 0.334f;
}

Button::~Button()
{
}

bool Button::isPress()
{
	if( this )
	{
		if( this->isHover() && sf::Mouse::isButtonPressed( sf::Mouse::Left ) )
			return true;
		return false;
	}
	return false;
}

void Button::_setState( Button_State st )
{
	_state = st;
	switch( _state )
	{
	case BTN_NORMAL:
		{
			this->setUV( _norUV );
			break;
		}
	case BTN_HOVER:
		{
			this->setUV( _hovUV );
			break;
		}
	case BTN_PRESSED:
		{
			this->setUV( _preUV );
			break;
		}
	default:
		break;
	}
}

void Button::changeState()
{
	// State hover
	if( this->isHover() )
		this->_setState( BTN_HOVER );
	if( !this->isHover() )
		this->_setState( BTN_NORMAL );

	// State click
}

Button_State Button::getState()
{
	return _state;
}