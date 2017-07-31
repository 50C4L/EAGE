#ifndef _UIOBJECT_H
#define _UIOBJECT_H

#include <string>
#include "../helper/helper.h"

class UIObject:public VisibleObject
{
public:
			UIObject();
	virtual ~UIObject();

	virtual	void	update( sf::Vector2f );
	virtual void	changeState();
	virtual bool	isClicked();
	virtual bool	isHover();
	virtual bool	isFocused();
	int		getFontId();
	int		getId();
	void	setFocus( bool flag );
	void	setText( std::string text );
	void	setId( int id );

private:
	int			_id;
	int			_font_id;
	bool		_isClicked;
	bool		_isHover;
	bool		_isFocused;
	std::string	_text;

};	// class UIObject

#endif	// _UIOBJECT_H