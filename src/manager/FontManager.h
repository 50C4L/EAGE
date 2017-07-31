#ifndef _FONTMANAGER_H
#define _FONTMANAGER_H

#include <string>
#include <map>
#include "../helper/EFont.h"
#include "TaskManager.h"


// FontTask class
class FontTask:public Task
{
public:
	FontTask( char* data, std::size_t size, int id );
	bool run();

private:
	char*		_data;
	std::size_t _size;
	int			_fontId;
};



//-------------------------------------------------------------------------------
// class FontManager
class FontManager
{
public:
						~FontManager();
	static FontManager* getInstance();

	//void				create( int num );
	void				appendFontTask( FontTask* task );
	void				executeTasks();
	void				clear();
	bool				loadFromFile( std::string filename, int id );
	bool				loadFromMemory( char* data, std::size_t size, int id );
	sf::Font*			getFont( int id );

private:
	FontManager();

	static FontManager*				_instance;
	//EFont*							_fontMem;
	//std::map<int,EFont*>			_fontList;
	std::map<int,sf::Font*>			_fontList;
	int								_num;
	int								_index;
	TaskManager*					_fontTaskMan;

	// deallocator
	template <typename T>
	struct Deallocator
	{
		void operator()( const std::pair<int,T> &p )
		{
			if( p )
				delete p.second;
		}
	};

};	// class FontManager

#endif