#ifndef _UIOMANAGER_H
#define _UIOMANAGER_H

#include <map>
#include "../helper/helper.h"

class UIObjectManager
{
public:
	virtual					~UIObjectManager();
	static UIObjectManager*	getInstance();
	int						registerObject( UIObject* );
	void					update( float );
	void					setRenderWindow( sf::RenderWindow* );
	void					render();
	void					clear();

private:
	UIObjectManager();

	static UIObjectManager*		_instance;
	std::map<int,UIObject*>		_objectList;
	int							_count;
	sf::RenderWindow*			_rw;

	struct Deallocator
	{
		void operator()( const std::pair<int,UIObject*> &p )
		{
			delete p.second;
		}
	};
};	// class UIObjectManager

#endif	// _UIOMANAGER_H