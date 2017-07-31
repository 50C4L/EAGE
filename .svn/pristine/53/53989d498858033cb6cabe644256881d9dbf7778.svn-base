#include "../helper/helper.h"
#include "../manager/FontManager.h"

Label::Label()
{
	_fontID		= 0;
	_size		= 20;
	_color		= sf::Color::White;
	_isChanged	= true;
}

Label::~Label()
{
}

void Label::render()
{
	if( _isChanged )
	{
		//sf::Font* font;
		//font = FontManager::getInstance()->getFont( _fontID );

		_text.setCharacterSize( _size );
		_text.setFont( *FontManager::getInstance()->getFont( _fontID ) );
		_text.setColor( _color );
		_text.setPosition( _position );

		_isChanged = false;
	}

	this->getRenderWindowPtr()->pushGLStates();
	this->getRenderWindowPtr()->draw( _text );
	this->getRenderWindowPtr()->popGLStates();
}

void Label::setPosition( float x, float y )
{
	_position.x = x;
	_position.y = y;
	_isChanged = true;
}

void Label::setText( std::string text )
{
	_text.setString( text );
}

void Label::setFontSize( unsigned int size )
{
	_size = size;
	_isChanged = true;
}

void Label::setFontColor( float r, float g, float b, float a )
{
	_color = sf::Color( int(r*255.0f), int(g*255.0f), int(b*255.0f), int(a*255.0f) );
	_isChanged = true;
}

void Label::setFont( int id )
{
	_fontID = id;
	_isChanged = true;
}