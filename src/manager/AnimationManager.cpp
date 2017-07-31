#include "AnimationManager.h"
#include <fstream>
#include <sstream>


// global functons
void eage::pauseAnimation( bool value )
{
	//if( AnimationManager::_instance )
		//AnimationManager::_instance->pause( value );
	AnimationManager::getInstance()->pause( value );
}


// AnimationTask definitions
//------------------------------------------------------------------
AnimationTask::AnimationTask( char* data, int id )
{
	_data = data;
	_animId = id;
}


bool AnimationTask::run()
{
	return AnimationManager::getInstance()->loadFromMemory( _data, _animId );
}



//------------------------------------------------------------------
// AnimationManager definitions
AnimationManager* AnimationManager::_instance = 0;

AnimationManager::AnimationManager()
{
	_isPause	= false;
	_gameSpeed	= 1.0f;
	_animTaskMan = new TaskManager();
}


AnimationManager::~AnimationManager()
{
	delete _animTaskMan;
}



AnimationManager* AnimationManager::getInstance()
{
	if( !_instance )	_instance = new AnimationManager();
	return _instance;
}

void AnimationManager::setSpeed( float value )
{
	_gameSpeed = value;
}


void AnimationManager::appendAnimTask( AnimationTask* task )
{
	_animTaskMan->appendTask( task );
}


void AnimationManager::executeTasks()
{
	_animTaskMan->begin();
}


void AnimationManager::addFBObject( FBAnimObject* obj )
{
	if( obj )
		_objectList.push_back( obj );
	else
		eage::debug( "<ERROR> Animation Manager: Invalid Frame Based Animation Object.\n" );
}

bool AnimationManager::loadFromFile( std::string filepath, int id )
{
	std::map<int,FB_ANIM_SET*>::iterator itr = _animSetList.find( id );
	if( itr == _animSetList.end() )
	{
		std::ifstream	file;
		file.open( filepath );
		if( file.fail() )	return false;

		char			key[256];
		int				count = 0;
		ANIM_INFO		tempInfo;
		FB_ANIM_SET*	animSet;

		animSet		= new FB_ANIM_SET;
		animSet->id = id;

		while( !file.eof() )
		{
			file >> key;
			if( strcmp( key, "@" ) == 0 )
			{
				while(1)
				{
					if( count >= 255 )
					{
						eage::debug( "Animation Manager: Animation limit has been reached, id: %d.\n", id );
						return true;
					}
					file >> key;
					if( strcmp( key, "fStartX" ) == 0 )
						file >> tempInfo.start.x;
					if( strcmp( key, "fStartY" ) == 0 )
						file >> tempInfo.start.y;
					if( strcmp( key, "fHeight" ) == 0 )
						file >> tempInfo.height;
					if( strcmp( key, "fWidth" ) == 0 )
							file >> tempInfo.width;
					if( strcmp( key, "iFrame" ) == 0 )
						file >> tempInfo.frame;
					if( strcmp( key, "dTotalTime" ) == 0 )
						file >> tempInfo.totalTime;
					if( strcmp( key, "$" ) == 0 )
					{
						//tempInfo.offset = 1.0f/(tempInfo.frame*1.0f);
						tempInfo.offset = tempInfo.width;
						animSet->list[count] = tempInfo;
						std::map<int,FB_ANIM_SET*>::iterator res = 
							_animSetList.insert( std::pair<int,FB_ANIM_SET*>( id, animSet ) ).first;
						count++;
						break;
					}
				}
			}
		}

		animSet->size = count;
		eage::debug( "Animation Manager: Animation set [%d] has been loaded, includes %d animations.\n", id, count );
		return true;
	}

	return false;
}

bool AnimationManager::loadFromMemory( char* data, int id )
{
	/*
	std::map<int,char*>::iterator itr = _animationList.find( id );
	if( itr == _animationList.end() )
	{
		if( data )
		{
			std::map<int,char*>::iterator res = _animationList.insert( std::pair<int,char*>( id, data ) ).first;
			return true;
		}
	}
	*/

	std::map<int,FB_ANIM_SET*>::iterator itr = _animSetList.find( id );
	if( itr == _animSetList.end() )
	{
		// handle animation infos inside the data block
		if( data )
		{
			std::stringstream	stream( data );
			char				key[256];
			int					count = 0;
			ANIM_INFO			tempInfo;
			FB_ANIM_SET*		animSet;

			animSet		= new FB_ANIM_SET;
			animSet->id = id;

			while( !stream.eof() )
			{
				stream >> key;
				if( strcmp( key, "@" ) == 0 )
				{
					while(1)
					{
						if( count >= 255 )
						{
							eage::debug( "Animation Manager: Animation limit has been reached, id: %d.\n", id );
							return true;
						}
						stream >> key;
						if( strcmp( key, "fStartX" ) == 0 )
							stream >> tempInfo.start.x;
						if( strcmp( key, "fStartY" ) == 0 )
							stream >> tempInfo.start.y;
						if( strcmp( key, "fHeight" ) == 0 )
							stream >> tempInfo.height;
						if( strcmp( key, "fWidth" ) == 0 )
							stream >> tempInfo.width;
						if( strcmp( key, "iFrame" ) == 0 )
							stream >> tempInfo.frame;
						if( strcmp( key, "dTotalTime" ) == 0 )
							stream >> tempInfo.totalTime;
						if( strcmp( key, "$" ) == 0 )
						{
							//tempInfo.offset = 1.0f/(tempInfo.frame*1.0f);
							tempInfo.offset = tempInfo.width;
							animSet->list[count] = tempInfo;
							std::map<int,FB_ANIM_SET*>::iterator res = 
								_animSetList.insert( std::pair<int,FB_ANIM_SET*>( id, animSet ) ).first;
							count++;
							break;
						}
					}
				}
			}

			animSet->size = count;
			eage::debug( "Animation Manager: Animation set [%d] has been loaded, includes %d animations.\n", id, count );
			return true;
		}
	}

	return false;
}

FB_ANIM_SET* AnimationManager::find( int id )
{
	if( _animSetList.find( id ) != _animSetList.end() )
		return _animSetList[id];
	else
		return 0;
}

void AnimationManager::update( float fps )
{
	if( !_isPause )
	{
		if( !_objectList.empty() )
		{
			std::list<FBAnimObject*>::iterator it = _objectList.begin();
			while( it != _objectList.end() )
			{
				(*it)->update( fps / _gameSpeed );
				++it;
			}
		}
	}
}

void AnimationManager::clear()
{
	_objectList.clear();
	if( !_animSetList.empty() )
	{
		std::for_each( _animSetList.begin(), _animSetList.end(), Deallocator<FB_ANIM_SET*>() );
		_animSetList.clear();
	}

	_animTaskMan->clear();
}

void AnimationManager::pause( bool value )
{
	_isPause = value;
}

