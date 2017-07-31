#include "core\System.h"
#include "game\MenuState.h"
#include "game\PlayState.h"

#define STATE_MENU 1
#define STATE_PLAY 2

PlayState* pst;
MenuState* mst;

int main()
{
	System *app;
	app = System::getInstance();
	pst = PlayState::getInstance();
	mst = MenuState::getInstance();

	app->loadCFG( "config.cfg" );

	if( app->initialize() )
	{
		app->appendState( STATE_MENU, mst );
		app->appendState( STATE_PLAY, pst );
		app->setStartState( STATE_MENU );
		app->run();
	}
	app->shutdown();
	delete pst;
	delete mst;

	return 0;
}