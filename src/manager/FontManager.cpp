#include "FontManager.h"
#include <stdio.h>
#include "../helper/helper.h"

#define DEFAULT_FONT 0


// FontTask definitions
FontTask::FontTask( char* data, std::size_t size, int id )
{
	_data = data;
	_size = size;
	_fontId = id;
}


bool FontTask::run()
{
	bool flag = FontManager::getInstance()->loadFromMemory( _data, _size, _fontId );
	if( flag )
	{
		std::string name = std::to_string( _fontId );
		std::shared_ptr<sf::Font> tempFont( FontManager::getInstance()->getFont( _fontId ) );
		eage::getUIDesktop()->GetEngine().GetResourceManager().AddFont( 
			name, 
			tempFont 
			);
	}
	return flag;
}


//------------------------------------------------------------------------------
// FontManager definitions

FontManager* FontManager::_instance = 0;

FontManager::FontManager()
{
	//_fontMem	= 0;
	_num		= 0;
	_index		= 0;

	_fontTaskMan = new TaskManager();
}


FontManager::~FontManager()
{
	this->clear();
}



FontManager* FontManager::getInstance()
{
	if( !_instance ) _instance = new FontManager();
	return _instance;
}


/*
void FontManager::create( int num )
{
	_num = num;
	_fontMem = new EFont[num];
	eage::debug( "Font Manager: %d font instances have been created.\n", _num );
}
*/


void FontManager::appendFontTask( FontTask* task )
{
	_fontTaskMan->appendTask( task );
}


void FontManager::executeTasks()
{
	_fontTaskMan->begin();
}


bool FontManager::loadFromFile( std::string filename, int id )
{
	/*
	if( _index >= _num )	return false;
	if( !_fontMem[_index].loadFromFile( filename ) )	return false;

	_fontList.insert( std::pair<int,EFont*>( id, &_fontMem[_index] ) );
	eage::debug( "Font Manager: Font '%d' has been loaded.\n", id );
	_index++;
	return true;
	*/

	//EFont* font;
	sf::Font* font;
	font = new sf::Font();
	if( !font->loadFromFile( filename ) )	
	{
		delete font;
		return false;
	}

	_fontList.insert( std::pair<int,sf::Font*>( id, font ) );
	return true;
}

bool FontManager::loadFromMemory( char* data, std::size_t size, int id )
{
	if( data )
	{
		//EFont* font;
		sf::Font* font;
		font = new sf::Font();
		if( !font->loadFromMemory( data, size ) )
		{
			delete font;
			return false;
		}

		_fontList.insert( std::pair<int,sf::Font*>( id, font ) );
		return true;
	}
	return false;
}

sf::Font* FontManager::getFont( int id )
{
	if( _fontList.find( id ) != _fontList.end() )
		return _fontList[id];
	else
		return 0;
}

void FontManager::clear()
{
	/*
	if( !_fontList.empty() )
	{
		_fontList.clear();
		eage::debug( "Font Manager: Fonts list is cleared.\n" );
	}
	if( _fontMem )
	{
		//delete _fontMem;
		_index = 0;
		_fontMem = 0;
	}
	*/

	if( !_fontList.empty() )
	{
		//std::for_each( _fontList.begin(), _fontList.end(), Deallocator<sf::Font*>() );
		_fontList.clear();
	}

	_fontTaskMan->clear();
}
