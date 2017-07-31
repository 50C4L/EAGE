#include "Timer.h"

Timer::Timer()
{
	_clock		= 0;
	_isRunning	= false;
}


Timer::~Timer()
{
}

void Timer::start()
{
	if( !_clock )	_clock = new sf::Clock();
	_isRunning = true;
}

bool Timer::isRunning()
{
	return _isRunning;
}

double Timer::getElapsedSec()
{
	return _clock->getElapsedTime().asSeconds()*1.0;
}

int Timer::getElapsedMilliSec()
{
	return _clock->getElapsedTime().asMilliseconds();
}

double Timer::getElapsedMircoSec()
{
	return _clock->getElapsedTime().asMicroseconds()*1.0;
}

sf::Time Timer::restart()
{
	return _clock->restart();
}