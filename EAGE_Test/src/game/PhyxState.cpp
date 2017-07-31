#include "PhyxState.h"

PhyxState* PhyxState::_instance = NULL;


PhyxState* PhyxState::getInstance()
{
	if( !_instance ) _instance = new PhyxState();
	return _instance;
}


PhyxState::PhyxState()
{
	_mlFlag = false;
	_spaceFlag = false;
	_lcrlFlag = false;
	_blockFirstFlag = true;
}


PhyxState::~PhyxState()
{
}


void PhyxState::enterFunc()
{
	eage::loadResourceIndices( "data/scenes/phyxTestScene.res", EAGE_FROM_MEMORY );
	//eage::setPostFXShader( 1 );
	eage::setRenderMode( EAGE_DIRECT_RENDER );

	// creates ground
	_ground = new GameObject();
	_ground->setSize( sf::Vector2f(640.0f, 50.0f), sf::Vector2f(400.0f,30.0f) );
	_ground->setTexture( 2 );
	_ground->setLayer( 0.0f );
	_ground->setShader( 1 );
	_ground->setDynamic( false );
	eage::appendObject( _ground );

	// creates block
	b2BodyDef bodyDef;
	bodyDef.type = b2_kinematicBody;

	_block = new GameObject();
	_block->initialBox2DFixture( bodyDef );
	_block->setSize( sf::Vector2f(640.0f, 480.0f), sf::Vector2f(15.0f,15.0f) );
	_block->setTexture( 2 );
	_block->setLayer( 0.0f );
	_block->setShader( 1 );
	eage::appendObject( _block );

	// creates the poor box :)
	_poorBox = new GameObject();
	_poorBox->setSize( sf::Vector2f(400.0f,400.f), sf::Vector2f(25.0f,25.0f) );
	_poorBox->setTexture( 1 );
	_poorBox->setLayer( 0.0f );
	_poorBox->setShader( 1 );
	_poorBox->setDynamic( true );
	_poorBox->setFixedRotation( false );
	_poorBox->setFriction( 0.f );
	eage::appendObject( _poorBox );


	eage::setGravity( 0.0f, -9.8f );
}


void PhyxState::control()
{
	// kinematicBody test
	if( _blockFirstFlag )
	{
		_block->setLinearVelocity( 20.0f, 0.0f );
		_blockFirstFlag = false;
	}
	if( _block->getCentre().x < 300.0f )
		_block->setLinearVelocity( 20.0f, 0.0f );
	else if( _block->getCentre().x > 900.0f )
		_block->setLinearVelocity( -20.0f, 0.0f );

	if( eage::isKeyPressed( eage::Escape ) )
		changeState( 2 );

	if( sf::Mouse::isButtonPressed( sf::Mouse::Left ) )
	{
		if( !_mlFlag )
		{
			sf::Vector2f pos = eage::getMouseWorldCoord();
			_spwanBox( pos.x, pos.y );
			_mlFlag = true;
		}
	}
	else
		_mlFlag = false;

	if( eage::isKeyPressed( eage::Space ) )
	{
		if( !_spaceFlag )
		{
			_poorBox->setLinearImpulse( 0.f, 2.f );
			_spaceFlag = true;
		}
	}
	else
	{
		_poorBox->setLinearImpulse( 0.f, 0.f );
		_spaceFlag = false;
	}

	if( eage::isKeyPressed( eage::LControl ) )
	{
		if( !_lcrlFlag )
		{
			_poorBox->setLinearVelocity( 0.1f, 0.0f );
			_lcrlFlag = true;
		}
	}
	else
	{
		_lcrlFlag = false;
	}
}


void PhyxState::leaveFunc()
{
}


void PhyxState::_spwanBox( float mouseX, float mouseY )
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.fixedRotation = false;

	GameObject* box = new GameObject();
	box->initialBox2DFixture( bodyDef );
	box->setSize( sf::Vector2f(mouseX,mouseY), sf::Vector2f(25.0f,25.0f) );
	box->setTexture( 1 );
	box->setLayer( 0.0f );
	box->setShader( 1 );
	//box->setDynamic( true );
	//box->setFixedRotation( false );
	eage::appendObject( box );
}