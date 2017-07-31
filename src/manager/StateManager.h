#ifndef _STATEMANAGER_H
#define _STATEMANAGER_H

//#include "../helper/State.h"
#include "../helper/helper.h"
#include <map>
#include <string>

class RenderModule;
class ResourceModule;
class PhysicsModule;

class StateManager
{
public:
	~StateManager();
	static StateManager* getInstance();

	void initialize( RenderModule* rm, ResourceModule* rsm, PhysicsModule* pxm, sf::RenderWindow* rw );
	void changeState( State* newState );
	void changeState( int id );
	void appendState( int id, State* state );
	void run();
	void end();

private:
	StateManager();


	static StateManager*	_instance;
	State*					_currentState;
	RenderModule*			_rm;
	ResourceModule*			_rsm;
	PhysicsModule*			_pxm;
	sf::RenderWindow*		_rw;
	std::map<int,State*>	_stateList;
	bool					_loadingMainState;			
};	// class StateManager		

#endif