#ifndef _TIMER_H
#define _TIMER_H

#include <SFML/System/Clock.hpp>

class Timer
{
public:
	Timer();
	~Timer();

	void		start();

	sf::Time	restart();

	double		getElapsedSec();
	int			getElapsedMilliSec();
	double		getElapsedMircoSec();
	
	bool	isRunning();

private:
	sf::Clock*	_clock;
	bool		_isRunning;

};	// class Timer

#endif