#ifndef _EFONT_H
#define _EFONT_H

#include <SFML\Graphics\Font.hpp>
#include <string>

class EFont
{
public:
	EFont();
	~EFont();

	bool		loadFromFile( std::string filename );
	bool		loadFromMemory( char* data, std::size_t size );
	sf::Font*	getFont();

private:
	sf::Font*	_font;
	// _buffer is used while data is loaded from memory
	char*		_buffer;
};

#endif