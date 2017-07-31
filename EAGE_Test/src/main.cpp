#include "../../src/EAGE.h"
#include "game/MenuState.h"
#include "game/PlayState.h"
#include "game/ParticleState.h"
#include "game/SkeletonState.h"
#include "game/PhyxState.h"

#define STATE_MENU 1
#define STATE_PLAY 2
#define STATE_PART 3
#define STATE_SKEN 4
#define STATE_PHYX 5

PlayState* pst;
MenuState* mst;
ParticleState* partst;
SkeletonState *skt;
PhyxState* phyxst;

int main()
{
	EAGE* app;
	app = engineCreate();
	eage::debug( "Engine version: %s\n", app->getVersion().c_str() );
	pst = PlayState::getInstance();
	mst = MenuState::getInstance();
	partst = ParticleState::getInstance();
	skt = SkeletonState::getInstance();
	phyxst = PhyxState::getInstance();

	app->setDesignResolution( 1280, 720 );
	app->loadCFG( "config.cfg" );

	if( app->initialize() )
	{
		app->appendState( STATE_MENU, mst );
		app->appendState( STATE_PLAY, pst );
		app->appendState( STATE_PART, partst );
		app->appendState( STATE_SKEN, skt );
		app->appendState( STATE_PHYX, phyxst );
		app->setStartState( STATE_PLAY );
		app->run();
	}
	app->shutdown();

	return 0;
}