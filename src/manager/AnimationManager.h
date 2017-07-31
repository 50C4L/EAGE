#ifndef _ANIMATIONMANAGER_H
#define _ANIMATIONMANAGER_H

#include <list>
#include "../helper/helper.h"
#include "TaskManager.h"

// AnimationTask class
class AnimationTask:public Task
{
public:
	AnimationTask( char* data, int id );
	bool run();

private:
	char*		_data;
	int			_animId;
};




//--------------------------------------------------------------------------------
// AnimationManager class
class AnimationManager
{
public:
	virtual						~AnimationManager();
	static AnimationManager*	getInstance();

	void			addFBObject( FBAnimObject* );
	void			appendAnimTask( AnimationTask* task );
	void			executeTasks();
	bool			loadFromMemory( char* data, int id );
	bool			loadFromFile( std::string filepath, int id );
	FB_ANIM_SET*	find( int id );
	void			update( float );
	void			clear();
	void			pause( bool value );
	void			setSpeed( float value );

private:
	AnimationManager();

	static AnimationManager*	_instance;
	std::list<FBAnimObject*>	_objectList;
	//std::map<int,char*>			_animationList;
	std::map<int,FB_ANIM_SET*>	_animSetList;
	TaskManager*				_animTaskMan;


	// deallocator
	template <typename T>
	struct Deallocator
	{
		void operator()( const std::pair<int,T> &p )
		{
			delete p.second;
		}
	};

	bool	_isPause;
	float	_gameSpeed;
};	// class AnimationManager

#endif	// ANIMATIONMANAGER_H