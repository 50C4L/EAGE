#include "UIObjectManager.h"
#include "TextureManager.h"

UIObjectManager* UIObjectManager::_instance = 0;

UIObjectManager::UIObjectManager()
{
	_count	= 0;
	_rw		= 0;
}

UIObjectManager::~UIObjectManager()
{
}

UIObjectManager* UIObjectManager::getInstance()
{
	if( !_instance ) _instance = new UIObjectManager();
	return _instance;
}


int UIObjectManager::registerObject( UIObject* obj )
{
	// if this object registered an id already
	if( obj->getId() != 0 )
	{
		eage::debug( "UIObject Manager: *** UI Object %d already registered. ***\n", obj->getId() );
		return 0;
	}
	// if this is a new object
	_objectList.insert( std::pair< int, UIObject* >( _count+1, obj ) );
	obj->setId( _count+1 );
	obj->setRenderWindowPtr( _rw );
	_count++;
	eage::debug( "UIObject Manager: New UI Object %d registered.\n", obj->getId() );
	return obj->getId();
}

void UIObjectManager::setRenderWindow( sf::RenderWindow* rw )
{
	_rw = rw;
}

void UIObjectManager::update( float aspect )
{
	static int tick = 0;

	if( _count != 0 && tick == 3 )
	{
		sf::Vector2i mousePos = sf::Mouse::getPosition( *_rw );
		std::map< int, UIObject* >::iterator i = _objectList.begin();
		float mouseX, mouseY;
		mouseX = (float)mousePos.x;
		mouseY = (float)_rw->getSize().y - mousePos.y;

		while( i != _objectList.end() )
		{
			i->second->update( sf::Vector2f( mouseX*1.0f, mouseY*1.0f ) );
			i->second->changeState();
			++i;
		}
		tick = 0;
	}

	tick++;
}

void UIObjectManager::render()
{
	TextureManager* texman;
	texman = TextureManager::getInstance();
	if( !_objectList.empty() )
	{
		std::map<int,UIObject*>::iterator itr = _objectList.begin();
		while( itr != _objectList.end() )
		{
			texman->bind( itr->second->getTexture() );
			itr->second->render();
			++itr;
		}
	}
}

void UIObjectManager::clear()
{
	_count = 0;
	if( !_objectList.empty() )
	{
		std::for_each( _objectList.begin(), _objectList.end(), Deallocator() );
		_objectList.clear();
	}
}