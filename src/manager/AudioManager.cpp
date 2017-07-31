#include "AudioManager.h"

// SoundTask Class
SoundTask::SoundTask( const void* data, std::size_t size, int id )
{
	_dataPtr = data;
	_size = size;
	_soundId = id;
}


bool SoundTask::run()
{
	auto itr = AudioManager::getInstance()->_soundList.find( _soundId );

	if( itr == AudioManager::getInstance()->_soundList.end() )
	{
		sf::SoundBuffer* soundBuffer = new sf::SoundBuffer();
		// cannot open file
		if( !soundBuffer->loadFromMemory( _dataPtr, _size ) )
		{
			delete soundBuffer;
			return false;
		}
		else
		{
			// correct iterator's postion and insert new data
			auto res = AudioManager::getInstance()->_soundList.insert( std::pair<int,sf::SoundBuffer*>( _soundId, soundBuffer ) ).first;
			return true;
		}
	}
	else
		return false;
}



//--------------------------------------------------------------------------
// MusicTask class
MusicTask::MusicTask( const void* data, std::size_t size, int id )
{
	_dataPtr = data;
	_size = size;
	_soundId = id;
}


bool MusicTask::run()
{
	auto itr = AudioManager::getInstance()->_musicList.find( _soundId );
	// if music not been loaded
	if( itr == AudioManager::getInstance()->_musicList.end() )
	{
		//sf::Music* music = new sf::Music();
		EMusic* music = new EMusic();
		music->music = new sf::Music();
		if( _dataPtr ) music->data = _dataPtr;

		// cannot open file
		if( !music->music->openFromMemory( _dataPtr, _size ) )
		{
			delete music;
			return false;
		}
		else
		{
			// correct iterator's position and insert new data
			auto res =  AudioManager::getInstance()->_musicList.insert( std::pair<int,EMusic*>( _soundId, music ) ).first;
			return true;
		}
	}
	// this music had been loaded
	else
	{
		return false;
	}
}




//-------------------------------------------------------------------------------
// AudioManager Class

#define DEFAULT_SOUND 0
#define DEFAULT_MUSIC 0

AudioManager* AudioManager::_instance	= 0;

AudioManager* AudioManager::getInstance()
{
	if( !_instance )	_instance = new AudioManager();
	return _instance;
}


AudioManager::AudioManager()
{
	//this->loadSoundFromFile( 0, "data/sounds/button_01.wav" );
	_soundTaskMan = new TaskManager();
	_musicTaskMan = new TaskManager();
}

AudioManager::~AudioManager()
{
	this->clear();
	_soundTaskMan->clear();

	delete _soundTaskMan;
	delete _musicTaskMan;
}


void AudioManager::appendSoundTask( SoundTask* job )
{
	_soundTaskMan->appendTask( job );
}


void AudioManager::appendMusicTask( MusicTask* job )
{
	_musicTaskMan->appendTask( job );
}


void AudioManager::executeTasks()
{
	_soundTaskMan->begin();
	_musicTaskMan->begin();
}


int AudioManager::loadSoundFromFile( int id, std::string filePath )
{
	std::map<int,sf::SoundBuffer*>::iterator itr = _soundList.find( id );
	// if sound not been loaded
	if( itr == _soundList.end() )
	{
		sf::SoundBuffer* soundBuffer = new sf::SoundBuffer();
		// cannot open file
		if( !soundBuffer->loadFromFile( filePath ) )
		{
			delete soundBuffer;
			eage::debug( "Audio Manager: <ERROR> Failed to load audio file [%s]\n", filePath.c_str() );
			return -1;
		}
		else
		{
			// correct iterator's postion and insert new data
			std::map<int,sf::SoundBuffer*>::iterator res =
				_soundList.insert( std::pair<int,sf::SoundBuffer*>( id, soundBuffer ) ).first;
			return res->first;
		}
	}
	else
	{
		return itr->first;
	}
}

int AudioManager::loadSoundFromMemory( const void* data, std::size_t size, int id )
{
	std::map<int,sf::SoundBuffer*>::iterator itr = _soundList.find( id );

	if( itr == _soundList.end() )
	{
		sf::SoundBuffer* soundBuffer = new sf::SoundBuffer();
		// cannot open file
		if( !soundBuffer->loadFromMemory( data, size ) )
		{
			delete soundBuffer;
			return -1;
		}
		else
		{
			// correct iterator's postion and insert new data
			std::map<int,sf::SoundBuffer*>::iterator res =
				_soundList.insert( std::pair<int,sf::SoundBuffer*>( id, soundBuffer ) ).first;
			return res->first;
		}
	}
	else
	{
		return itr->first;
	}
}

int AudioManager::loadMusicFromFile( int id, std::string filePath )
{
	std::map<int,EMusic*>::iterator itr = _musicList.find( id );
	// if music not been loaded
	if( itr == _musicList.end() )
	{
		//sf::Music* music = new sf::Music();
		EMusic* music = new EMusic();
		music->music = new sf::Music();
		// cannot open file
		if( !music->music->openFromFile( filePath ) )
		{
			delete music;
			eage::debug( "Audio Manager: <ERROR> Failed to load audio file [%s]\n", filePath.c_str() );
			return -1;
		}
		else
		{
			// correct iterator's position and insert new data
			std::map<int,EMusic*>::iterator res = 
				_musicList.insert( std::pair<int,EMusic*>( id, music ) ).first;
			return res->first;
		}
	}
	// this music had been loaded
	else
	{
		return itr->first;
	}
}

int AudioManager::loadMusicFromMemory( const void* data, std::size_t size, int id )
{
	std::map<int,EMusic*>::iterator itr = _musicList.find( id );
	// if music not been loaded
	if( itr == _musicList.end() )
	{
		//sf::Music* music = new sf::Music();
		EMusic* music = new EMusic();
		music->music = new sf::Music();
		if( data ) music->data = data;

		// cannot open file
		if( !music->music->openFromMemory( data, size ) )
		{
			delete music;
			//eage::debug( "Audio Manager: <ERROR> Failed to load audio file [%s]\n", filePath.c_str() );
			return -1;
		}
		else
		{
			// correct iterator's position and insert new data
			std::map<int,EMusic*>::iterator res = 
				_musicList.insert( std::pair<int,EMusic*>( id, music ) ).first;
			return res->first;
		}
	}
	// this music had been loaded
	else
	{
		return itr->first;
	}
}

sf::SoundBuffer* AudioManager::getSound( int id )
{
	if( _soundList.find( id ) != _soundList.end() )
		return _soundList[id];
	else
		return _soundList[DEFAULT_SOUND];
}

sf::Music* AudioManager::getMusic( int id )
{
	if( !_musicList.empty() )
	{
		if( _musicList.find( id ) != _musicList.end() )
			return _musicList[id]->music;
		else
			return _musicList[DEFAULT_MUSIC]->music;
	}
	return 0;
}

void AudioManager::clear()
{
	if( !_musicList.empty() )
	{
		std::for_each( _musicList.begin(), _musicList.end(), Deallocator<EMusic*>() );
		_musicList.clear();
	}
	if( !_soundList.empty() )
	{
		std::for_each( _soundList.begin(), _soundList.end(), Deallocator<sf::SoundBuffer*>() );
		_soundList.clear();
	}
	_soundTaskMan->clear();
	_musicTaskMan->clear();
}

