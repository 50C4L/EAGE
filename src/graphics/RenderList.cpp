#include "RenderList.h"
#include "../manager/TextureManager.h"

RenderList::RenderList()
{
	_texId = -1;
}

RenderList::~RenderList()
{
}

void RenderList::setId( int id )
{
	_texId = id;
}

void RenderList::push( GameObject* obj )
{
	//if( obj->isDynamic() )
	{
		_dynamicList.push_back( obj );
		_dynamicVert.push_back( obj->_LT );
		_dynamicVert.push_back( obj->_LB );
		_dynamicVert.push_back( obj->_RB );
		_dynamicVert.push_back( obj->_RB );
		_dynamicVert.push_back( obj->_RT );
		_dynamicVert.push_back( obj->_LT );

		obj->_renderOffset = _dynamicVert.size() - 6;
	}
	//else
	//{
	//	_staticList.push_back( obj );
	//	_staticVert.push_back( obj->_LT );
	//	_staticVert.push_back( obj->_LB );
	//	_staticVert.push_back( obj->_RB );
	//	_staticVert.push_back( obj->_RB );
	//	_staticVert.push_back( obj->_RT );
	//	_staticVert.push_back( obj->_LT );
	//}
}

void RenderList::render()
{
	TextureManager::getInstance()->bind(_texId);
	//if (!_staticList.empty())
	//{
	//	glVertexPointer(3, GL_FLOAT, sizeof(VertexAttribute), &_staticVert[0].pos);
	//	glTexCoordPointer(2, GL_FLOAT, sizeof(VertexAttribute), &_staticVert[0].uv);
	//	glColorPointer( 4, GL_FLOAT, sizeof(VertexAttribute), &_staticVert[0].color );
	//	glDrawArrays(GL_TRIANGLES, 0, _staticVert.size());
	//}
	if (!_dynamicList.empty())
	{
		glVertexPointer(3, GL_FLOAT, sizeof(VertexAttribute), &_dynamicVert[0].pos);
		glTexCoordPointer(2, GL_FLOAT, sizeof(VertexAttribute), &_dynamicVert[0].uv);
		glColorPointer( 4, GL_FLOAT, sizeof(VertexAttribute), &_dynamicVert[0].color );
		glDrawArrays(GL_TRIANGLES, 0, _dynamicVert.size());
	}
	TextureManager::getInstance()->unbind();
}

void RenderList::clear()
{
	_texId = -1;
	//std::for_each( _staticList.begin(), _staticList.end(), Deallocator() );
	std::for_each( _dynamicList.begin(), _dynamicList.end(), Deallocator() );
	//_staticList.clear();
	_dynamicList.clear();
}

void RenderList::sort()
{
	//std::stable_sort( _staticVert.begin(), _staticVert.end(), LessLayer() );
}

int RenderList::getId()
{
	return _texId;
}

bool RenderList::_lessLayer( VertexAttribute* obj1, VertexAttribute* obj2 )
{
	return obj1->pos.layer < obj2->pos.layer;
}