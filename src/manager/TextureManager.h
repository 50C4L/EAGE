#ifndef _TEXTUREMANAGER_H
#define _TEXTUREMANAGER_H

#include <map>
#include <string>
#include "../helper/helper.h"
#include "TaskManager.h"

// TextureTask class
class TextureTask:public Task
{
public:
	TextureTask(  const void* data, std::size_t size, int texid, GLint filter  );
	bool run();

private:
	const void* _data;
	std::size_t _size;
	int			_texId;
	GLint		_filter;
};



//----------------------------------------------------------------------
// class TextureManager
class TextureManager
{
	friend class ShaderBlock;
	typedef std::map<int,GLuint>::iterator _mapIt;
public:
							
							~TextureManager();
	static TextureManager*	getInstance();
	void					appendTexTask( TextureTask* task );
	void					executeTasks();
	bool					loadFromFile( std::string filename, int texid, GLint filter );
	bool					loadFromMemory( const void* data, std::size_t size, int texid, GLint filter );
	bool					unload( int texid );
	void					bind( int texid );
	void					rebuild();
	void					unbind();
	void					clear();
	int						getCount();

protected:
							TextureManager();

private:
	static TextureManager*	_instance;
	std::map<int,GLuint>	_texList;
	TaskManager*			_texTaskMan;

};	// class TextureManager

#endif