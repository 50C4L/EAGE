#ifndef _AUDIOMANAGER_H
#define _AUDIOMANAGER_H

#include <map>
#include <string>
#include "../helper/helper.h"
#include "TaskManager.h"

//-------------------------------------------------------------------------------
// SoundTask class

class SoundTask:public Task
{
public:
	SoundTask( const void* data, std::size_t size, int id );

	bool run();

private:
	const void* _dataPtr;
	std::size_t _size;
	int			_soundId;
};


//------------------------------------------------------------------------------
// MusicTask class
class MusicTask:public Task
{
public:
	MusicTask( const void* data, std::size_t size, int id );

	bool run();

private:
	const void* _dataPtr;
	std::size_t _size;
	int			_soundId;
};



//------------------------------------------------------------------------------
// EMusic struct
	struct EMusic
	{
		sf::Music*	music;
		const void*	data;

		EMusic()
		{
			music	= 0;
			data	= 0;
		}
		~EMusic()
		{
			if( data )
				delete data;
			if( music )
				delete music;
		}
	};


//------------------------------------------------------------------------------
// AudioManager class

class AudioManager
{
	friend class SoundTask;
	friend class MusicTask;
public:
	~AudioManager();
	static AudioManager* getInstance();

	void			appendSoundTask( SoundTask* job );
	void			appendMusicTask( MusicTask* job );
	void			executeTasks();
	int				loadSoundFromFile( int id, std::string filePath );
	int				loadSoundFromMemory( const void* data, std::size_t size, int id );
	int				loadMusicFromFile( int id, std::string filePath );
	int				loadMusicFromMemory( const void* data, std::size_t size, int id );
	sf::SoundBuffer*getSound( int id );
	sf::Music*		getMusic( int id );
	void			clear();

protected:
	AudioManager();

private:
	// deallocator
	template <typename T>
	struct Deallocator
	{
		void operator()( const std::pair<int,T> &p )
		{
			delete p.second;
		}
	};

	TaskManager*	_soundTaskMan;	
	TaskManager*	_musicTaskMan;
	static AudioManager*			_instance;
	std::map<int,sf::SoundBuffer*>	_soundList;
	std::map<int,EMusic*>			_musicList;
};

#endif