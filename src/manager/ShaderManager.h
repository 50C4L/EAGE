#ifndef _SHADERMANAGER_H
#define _SHADERMANAGER_H

#include <map>
#include <string>
//#include "../graphics/ShaderObject.h"
#include "../helper/helper.h"
#include "TaskManager.h"

// ShaderTask class
class ShaderTask:public Task
{
public:
	ShaderTask( char* data, int shaderId );
	bool run();

private:
	char*	_data;
	int		_shaderId;	
};



//----------------------------------------------------------------------------------
// ShaderManager class
class ShaderManager
{
	friend class ShaderBlockManager;
	typedef std::map<int,ShaderObject*>::iterator _mapIt;
public:
							~ShaderManager();

	static ShaderManager*	getInstance();
	void					appendShaderTask( ShaderTask* task );
	void					executeTasks();
	bool					loadFromFile( std::string filename, int shaderId );
	bool					loadFromMemory( char* data, int shaderId );
	bool					release( int shaderId );
	bool					rebuild();
	void					bind( int shaderId );
	ShaderObject*			find( int shaderId );
	
	void					disable();
	void					clear();

protected:
					ShaderManager();

private:
	static ShaderManager*	_instance;
	std::map<int,ShaderObject*>	_shaderList;
	int	_currentBindedHandle;
	TaskManager*			_shaderTaskMan;

	template <typename T>
	struct Deallocator
	{
		void operator()( const std::pair<int,T> &p )
		{
			delete p.second;
		}
	};
};	// Class ShaderManager


#endif
