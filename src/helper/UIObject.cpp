#include "../helper/helper.h"

UIObject::UIObject()
{
	_id			= 0;
	_font_id	= 0;
	_rw			= 0;
	this->setPhysx( false );
	this->setDynamic( false );
}

UIObject::~UIObject()
{
}


bool UIObject::isHover()
{
	return _isHover;
}

bool UIObject::isFocused()
{
	return _isFocused;
}

int UIObject::getFontId()
{
	return _font_id;
}

int UIObject::getId()
{
	return _id;
}

void UIObject::setFocus( bool flag )
{
	_isFocused = flag;
}

void UIObject::setId( int id )
{
	_id = id;
}


void UIObject::update( sf::Vector2f mouse )
{
	_isHover = this->isInsertAABB( mouse );
}

void UIObject::changeState()
{
}

void UIObject::setRenderWindowPtr( sf::RenderWindow* ptr )
{
	_rw = ptr;
}

sf::RenderWindow* UIObject::getRenderWindowPtr()
{
	return _rw;
}

