#include "SkeletonState.h"

#define SPEED 0.1f

SkeletonState* SkeletonState::_instance = 0;


SkeletonState* SkeletonState::getInstance()
{
	if( !_instance )	_instance = new SkeletonState();
	return _instance;
}


SkeletonState::SkeletonState()
{
	_part1 = 0;
	_part2 = 0;
	_part3 = 0;
	_node1 = 0;
	_node2 = 0;
	_node3 = 0;
	_currentNode = 0;
}



SkeletonState::~SkeletonState()
{
}


void SkeletonState::enterFunc()
{
	eage::loadResourceIndices( "data/scenes/skTest.res", EAGE_FROM_MEMORY );

	// initialize nodes
	_node1 = new SkeletonNode();
	_node1->setId( 0 );
	_node1->setPosition( sf::Vector2f(400.0f, 400.0f) );
	_currentNode = _node1;

	_node2 = new SkeletonNode();
	_node2->setId( 1 );
	_node2->setPosition( sf::Vector2f(460.0f, 400.0f) );

	_node3 = new SkeletonNode();
	_node3->setId( 2 );
	_node3->setPosition( sf::Vector2f(520.0f, 400.0f) );
	_node2->addNode( _node3 );
	_node1->addNode( _node2 );
	

	// initialize mesh
	_part1 = new GameObject();
	_part1->setSize( sf::Vector2f(390.0f,410.f), sf::Vector2f(390.0f,390.0f), sf::Vector2f(470.0f,390.0f), sf::Vector2f(470.0f,410.0f) );
	_part1->setTexture(1);
	_part1->setShader(1);
	_part1->setDynamic(true);
	eage::appendObject( _part1 );
	_node1->attach( _part1 );

	_part2 = new GameObject();
	_part2->setSize( sf::Vector2f(450.0f,410.f), sf::Vector2f(450.0f,390.0f), sf::Vector2f(530.0f,390.0f), sf::Vector2f(530.0f,410.0f) );
	_part2->setTexture(1);
	_part2->setShader(1);
	_part2->setDynamic(true);
	eage::appendObject( _part2 );
	_node2->attach( _part2 );
	

	_part3 = new GameObject();
	_part3->setSize( sf::Vector2f(510.0f,410.f), sf::Vector2f(510.0f,390.0f), sf::Vector2f(590.0f,390.0f), sf::Vector2f(590.0f,410.0f) );
	_part3->setTexture(1);
	_part3->setShader(1);
	_part3->setDynamic(true);
	eage::appendObject( _part3 );
	_node3->attach( _part3 );

	eage::setRenderMode( EAGE_DIRECT_RENDER );
}



void SkeletonState::control()
{
	if( _currentNode->getId() == 0 )
	{
		if( eage::isKeyPressed( eage::W ) )
			_currentNode->translate( sf::Vector2f(0.0f, SPEED) );
		if( eage::isKeyPressed( eage::A ) )
			_currentNode->translate( sf::Vector2f(-SPEED, 0.0f) );
		if( eage::isKeyPressed( eage::S ) )
			_currentNode->translate( sf::Vector2f(0.0f, -SPEED) );
		if( eage::isKeyPressed( eage::D ) )
			_currentNode->translate( sf::Vector2f(SPEED, 0.0f) );
	}
	if( eage::isKeyPressed( eage::Q ) )
		_currentNode->rotate( _currentNode->getPosition(), SPEED );
	if( eage::isKeyPressed( eage::E ) )
		_currentNode->rotate( _currentNode->getPosition(), -SPEED );
	if( eage::isKeyPressed( eage::Num1 ) )
	{
		_currentNode = _node1;
		_part1->setColor( 1.0f, 0.5f, 0.5f, 1.0f );
		_part2->setColor( 1.0f, 1.0f, 1.0f, 1.0f );
		_part3->setColor( 1.0f, 1.0f, 1.0f, 1.0f );
	}
	if( eage::isKeyPressed( eage::Num2 ) )
	{
		_currentNode = _node1->search(1);
		_part2->setColor( 1.0f, 0.5f, 0.5f, 1.0f );
		_part1->setColor( 1.0f, 1.0f, 1.0f, 1.0f );
		_part3->setColor( 1.0f, 1.0f, 1.0f, 1.0f );
	}
	if( eage::isKeyPressed( eage::Num3 ) )
	{
		_currentNode = _node1->search(2);
		_part3->setColor( 1.0f, 0.5f, 0.5f, 1.0f );
		_part2->setColor( 1.0f, 1.0f, 1.0f, 1.0f );
		_part1->setColor( 1.0f, 1.0f, 1.0f, 1.0f );
	}

	if( sf::Mouse::isButtonPressed( sf::Mouse::Button::Left ) )
	{
		sf::Vector2i mPos = sf::Mouse::getPosition();
		GameObject *newObj = new GameObject();
		newObj->setSize( sf::Vector2f( mPos.x, mPos.y ), sf::Vector2f( mPos.x, mPos.y-50.0f ), 
						 sf::Vector2f( mPos.x+50.0f, mPos.y-50.0f ), sf::Vector2f( mPos.x+50.0f, mPos.y ) );
		newObj->setTexture(1);
		newObj->setShader(1);
		newObj->setDynamic(true);
		eage::appendObject( newObj );
	}
}



void SkeletonState::leaveFunc()
{
}
