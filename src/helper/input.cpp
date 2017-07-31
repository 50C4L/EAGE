#ifndef _INPUT_H
#define _INPUT_H
#include "helper.h"
#include <SFML\Window\Keyboard.hpp>

bool eage::isKeyPressed( int key )
{
	return sf::Keyboard::isKeyPressed( (sf::Keyboard::Key)key );
}

#endif