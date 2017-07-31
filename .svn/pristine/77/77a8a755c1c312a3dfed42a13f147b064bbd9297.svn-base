#include "EFont.h"

EFont::EFont()
{
	_buffer = 0;
	_font = new sf::Font();
}

EFont::~EFont()
{
	if( _font )
	{
		delete _font;
		_font = 0;
	}
	if( _buffer )
	{
		delete _buffer;
		_buffer = 0;
	}
}

bool EFont::loadFromFile( std::string filename )
{
	if( !_font->loadFromFile( filename ) ) return false;
	return true;
}

bool EFont::loadFromMemory( char* data, std::size_t size )
{
	_buffer = data;
	if( !_font->loadFromMemory( _buffer, size ) )	return false;
	return true;
}

sf::Font* EFont::getFont()
{
	return _font;
}