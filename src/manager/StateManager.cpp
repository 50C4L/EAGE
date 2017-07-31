#include "StateManager.h"
#include <stdio.h>

StateManager* StateManager::_instance = 0;

StateManager::StateManager():
	_currentState(0),
	_rm(0),
	_rsm(0),
	_rw(0),
	_loadingMainState(true)
{
}

StateManager::~StateManager()
{
}

StateManager* StateManager::getInstance()
{
	if( !_instance ) _instance = new StateManager;
	return _instance;
}

void StateManager::changeState( State* newState )
{
	eage::debug("State Manager: Changing state ......\n");
	if( _currentState )
		_currentState->leave();
	_currentState = newState;
	_currentState->enter( _rm, _rsm, _pxm, _rw );
}

void StateManager::changeState(  int id  )
{
	if( id == 0 )
	{
		eage::debug( "State Manager: <ERROR> Invalid state has been recevied.\n" );
		return;
	}
	if( _stateList.find( id ) != _stateList.end() )
	{
		if( _currentState )
			_currentState->leave();
		eage::debug( "State Manager: Changes state to %d.\n", id );
		_currentState = _stateList[id];

		_currentState->enter( _rm, _rsm, _pxm, _rw );
		_currentState->loadResource();
	
	}
	else 
	{
		eage::debug( "State Manager: <ERROR> Cann't find state %d.\n", id );
		return;
	}
}

void StateManager::run()
{
	if( _currentState )
	{
		_currentState->control();
		_currentState->run();
	}
	else if( _currentState )
	{
		_currentState->loadingScreen();
	}
}

void StateManager::end()
{
	if( _currentState )
		_currentState->leave();
}

void StateManager::appendState( int id, State* state )
{
	if( id==0 || !state )
	{
		eage::debug( "State Manager: <ERROR> Invalid state.\n" );
		return;
	}
	_stateList.insert( std::pair<int,State*>( id, state ) );
	state->getManger( this );
	eage::debug( "State Manager: State %d has been inserted.\n", id );
}

void StateManager::initialize( RenderModule* rm, ResourceModule* rsm, PhysicsModule* pxm, sf::RenderWindow* rw )
{
	eage::debug( "State Manager: Initializing state manager.\n" );
	_rm = rm;
	_rsm = rsm;
	_pxm = pxm;
	_rw = rw;
}