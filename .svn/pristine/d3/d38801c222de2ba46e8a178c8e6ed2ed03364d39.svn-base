#ifndef _ShaderBlockMANAGER_H
#define _ShaderBlockMANAGER_H

#include "../graphics/ShaderBlock.h"
#include "TextureManager.h"
#include "ShaderManager.h"

class ShaderBlockManager
{
	friend class RenderModule;

public:
								~ShaderBlockManager();
	static ShaderBlockManager*	getInstanc();
	int							genLists();
	void						appendObject( GameObject* obj );
	int							classifyObjects();
	void						renderAll();
	void						clearAll();

private:
								ShaderBlockManager();
	void						_runTimeAppend( GameObject* obj );

	static ShaderBlockManager*	_instance;
	int							_listCounts;
	bool						_isFirstClassified;
	ShaderBlock*				_lists;
	TextureManager*				_texManPtr;
	ShaderManager*				_shaManPtr;
	std::list<GameObject*>		_tempList;

};	// class ShaderBlockManager

#endif