#ifndef _EAGE_H
#define _EAGE_H

#include "helper\helper.h"

struct CoreParams
{
	sf::Vector2i	windowSize;
	char			windowTitle[256];
	bool			isFullScreen;
	bool			isVSync;
};

class  EAGE
{
public:
	bool		virtual	initialize()						= 0;
	void		virtual	run()								= 0;
	void		virtual	setCoreParams( CoreParams param )	= 0;
	void		virtual	setStartState( int )				= 0;
	void		virtual setDesignResolution( int width, int height ) = 0;
	void		virtual	shutdown()							= 0;
	void		virtual	loadCFG( std::string path )			= 0;
	void		virtual enableSplashScreen( bool value )	= 0;
	void		virtual setSplashLength( float length )		= 0;
	int			virtual	appendState( int, State* )			= 0;
	std::string	virtual	getVersion()						= 0;
};	// virtual class for entry

EAGE_API EAGE* engineCreate();

#endif _EAGE_H