#include "PlayState.h"
#include "../graphics/ShaderObject.h"
#include <stdio.h>

#define SPEED 400.0f
#define UNIFORM_TEST_SHADER	1

PlayState* PlayState::_instance = 0;

PlayState* PlayState::getInstance()
{
	if( !_instance )
		_instance = new PlayState();

	return _instance;
}

PlayState::PlayState()
{
	_player = 0;
}

PlayState::~PlayState()
{
}

void PlayState::enterFunc()
{
	this->loadResFile( "data/scenes/test.res" );

	EAGE::loadShaderFromFile( "data/shaders/uniformTest.so", UNIFORM_TEST_SHADER );

	_player = new Player();
	_player->setSize( sf::Vector2f(100.0f,600.0f), sf::Vector2f(100.0f,500.0f), sf::Vector2f(200.0f,500.0f), sf::Vector2f(200.0f,600.0f) );
	_player->setTexture( 4 );
	_player->setLayer( 0.0 );
	_player->addAnimation( "data/objects/animations/test.fba" );

	this->addFBAObject( _player );
	this->setGravity( sf::Vector2f( 0.0f, 0.0f ) );

	this->setRenderMode( EAGE_POST_EFFECT );
	this->setPostFXShader( 1 );

	EAGE::findShader( UNIFORM_TEST_SHADER )->uniform( "status", 1 );
}

void PlayState::leaveFunc()
{
	if( _player )
	{
		delete _player;
		_player = 0;
	}
}

void PlayState::control()
{
	if( sf::Keyboard::isKeyPressed( sf::Keyboard::Right ) && sf::Keyboard::isKeyPressed( sf::Keyboard::Up ) )
	{
		_player->move( sf::Vector2f(1.0,1.0), SPEED );
	}
	else if( sf::Keyboard::isKeyPressed( sf::Keyboard::Right ) )
	{
		_player->move( sf::Vector2f(1.0,0.0), SPEED );
	}
	else if( sf::Keyboard::isKeyPressed( sf::Keyboard::Left ) )
	{
		_player->move( sf::Vector2f(-1.0,0.0), SPEED );
	}
	else if( sf::Keyboard::isKeyPressed( sf::Keyboard::Up ) )
	{
		_player->move( sf::Vector2f(0.0,1.0), SPEED );
	}
	else if( sf::Keyboard::isKeyPressed( sf::Keyboard::Down ) )
	{
		_player->move( sf::Vector2f(0.0,-1.0), SPEED );
	}
	else
	{
		_player->stop();
	}
	_player->playAnimation( 0 );
}
