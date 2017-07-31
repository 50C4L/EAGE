#include "ShaderBlockManager.h"
#include "../helper/helper.h"
#include "TextureManager.h"
#include "ShaderManager.h"
#include <stdio.h>

ShaderBlockManager* ShaderBlockManager::_instance = 0;

ShaderBlockManager::ShaderBlockManager()
{
	_listCounts = 0;
	_lists		= 0;
	_texManPtr	= 0;
	_shaManPtr  = 0;
	_isFirstClassified = false;
}

ShaderBlockManager::~ShaderBlockManager()
{
}

ShaderBlockManager* ShaderBlockManager::getInstanc()
{
	if( !_instance ) _instance = new ShaderBlockManager();
	return _instance;
}

int ShaderBlockManager::genLists()
{
	_texManPtr = TextureManager::getInstance();
	_shaManPtr = ShaderManager::getInstance();;
	_listCounts = _shaManPtr->_shaderList.size();
	_lists = new ShaderBlock[ _listCounts ];
	eage::debug( "ShaderBlock Manager: Preparing to generate %d shader block.\n", _listCounts );

	ShaderManager::_mapIt it = _shaManPtr->_shaderList.begin();

	for( int i = 0; i < _listCounts; i ++ )
	{
		if( it == _shaManPtr->_shaderList.end() )
			break;
		_lists[i].setID( it->first );
		_lists[i].genRenderList();
		++it;
	}

	_isFirstClassified = false;
	return _listCounts;
}

void ShaderBlockManager::appendObject( GameObject* obj )
{
	// push object to temporary list in initial phase
	if( !_isFirstClassified )
	{
		_tempList.push_back( obj );
	}
	else 
		this->_runTimeAppend( obj );
}

int ShaderBlockManager::classifyObjects()
{
	if( _tempList.empty() )
		return 0;

	int num = 0;
	std::list<GameObject*>::iterator it = _tempList.begin();

	while( it != _tempList.end() )
	{
		int id;
		id = (*it)->getShader();
		// if there is suitable render list for this object
		for( int i = 0; i < _listCounts; ++i )
		{
			if( _lists[i].getID() == (*it)->getShader() )
			{
				_lists[i].push( (*it) );
				(*it)->_shaderBlock = i;
				break;
			}
			// if there is no suitable render list for this object, put it in the default render list
			else if( i == (_listCounts - 1) )
			{
				eage::debug( "ShaderBlock Manager: Can't find suitable list [%d] for current obj\n", id );
				_lists[0].push(*it);
				break;
			}
		}		
		
		++it;
		++num;
	}

	for( int i =0; i < _listCounts; ++i )
	{
		_lists[i].sort();
	}

	_tempList.clear();
	_isFirstClassified = true;
	return num;
}

void ShaderBlockManager::renderAll()
{
	int i = 0;
	while( i < _listCounts )
	{
		_shaManPtr->bind( _lists[i].getID() );
		_lists[i].render();  
		i++;
	}
	_shaManPtr->disable();
	//_texManPtr->unbind();
}


void ShaderBlockManager::clearAll()
{
	_isFirstClassified = false;

	int i = 0;
	while( i < _listCounts )
	{
		_lists[i].clear();
		i++;
	}
	//delete _lists;
	_lists = 0;
	_listCounts = 0;
}


void ShaderBlockManager::_runTimeAppend( GameObject* obj )
{
	int id;
	id = obj->getShader();
	// if there is suitable render list for this object
	for( int i = 0; i < _listCounts; ++i )
	{
		if( _lists[i].getID() == obj->getShader() )
		{
			_lists[i].push( obj );
			obj->_shaderBlock = i;
			break;
		}
		// if there is no suitable render list for this object, put it in the default render list
		else if( i == (_listCounts - 1) )
		{
			eage::debug( "ShaderBlock Manager: Can't find suitable list [%d] for current obj\n", id );
			_lists[0].push( obj );
			break;
		}
	}		
}