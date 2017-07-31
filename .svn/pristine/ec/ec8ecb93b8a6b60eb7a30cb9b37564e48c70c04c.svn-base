#ifndef _RENDERLIST_H
#define _RENDERLIST_H

#include <list>
#include "../helper/helper.h"

class RenderList
{
	friend class RenderModule;

public:
	RenderList();
	~RenderList();

	void setId( int id );
	void push( GameObject* obj );
	void render();
	void clear();
	void sort();
	int  getId();

private:
	bool _lessLayer( VertexAttribute* obj1, VertexAttribute* obj2 );

	int									_texId; // texture id from THE ENGINE, NOT OPENGL
	//std::list<GameObject*>				_staticList;
	std::list<GameObject*>				_dynamicList;
	//std::vector<VertexAttribute>		_staticVert;
	std::vector<VertexAttribute>		_dynamicVert;

	struct DynamicRenderer
	{
		void operator()( GameObject* p )
		{
			p->render();
		}
	};

	struct Deallocator
	{
		void operator()( GameObject* p )
		{
			if( p )
			{
				delete p;
				p = 0;
			}
		}
	};

	struct LessLayer
	{
		bool operator()( VertexAttribute obj1, VertexAttribute obj2 )
		{
			return obj1.pos.layer < obj2.pos.layer;
		}
	};
};

#endif