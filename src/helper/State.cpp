//#include "State.h"
#include "helper.h"
#include "../manager/StateManager.h"
#include "../graphics/RenderModule.h"
#include "../resource/ResourceModule.h"
#include "../math/PhysicsModule.h"

State::State()
{
	_stateManPtr = 0;
	_rdm = 0;
	_rsm = 0;
	_pxm = 0;
	_rw = 0;
}


State::~State()
{
}

void State::changeState( int id )
{
	_stateManPtr->changeState( id );
}

void State::getManger( StateManager* sm )
{
	if( sm )
		_stateManPtr = sm;
}

void State::loadingScreen()
{
	static GameObject obj;
	static bool isFirst = true;
	if( isFirst )
	{
		obj.setSize( 600.0f, 300.0f, 600.0f, 250.0f, 650.0f, 250.0f, 650.0f, 300.0f );
		isFirst = false;
	}

	obj.render();
}

void State::enter( RenderModule* rdm, ResourceModule* rsm, PhysicsModule* pxm, sf::RenderWindow* rw )
{
	_rdm = rdm;
	_rsm = rsm;
	_pxm = pxm;
	_rw  = rw;
	_rsm->create();
}

void State::loadResource()
{
	this->enterFunc();
	_rdm->create();
}

void State::leave()
{
	_rdm->clear();
	_rsm->clear();
	_pxm->clear();

	this->leaveFunc();

	_rdm = 0;
	_rsm = 0;
	_pxm = 0;
	_rw  = 0;
}

void State::run()
{
	_pxm->update();
	_rdm->render();
}

void State::addFBAObject( FBAnimObject *obj )
{
	_rdm->addFBAnimObject( obj );
	if( obj->isPhysx() )
		_pxm->addObject( obj );
}

void State::addUIObject( UIObject *obj )
{
	_rdm->addUIObject( obj );
}

void State::addObject( GameObject *obj )
{
	_rdm->addObj( obj );
	if( obj->isPhysx() )
		_pxm->addObject( obj );
}
