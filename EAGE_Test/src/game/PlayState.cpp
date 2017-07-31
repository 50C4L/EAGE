#include "PlayState.h"
#include <stdio.h>
#include "../../../src/helper/OpenGL.h"

#define SPEED 10.5f

enum
{
	DEFAULT_SHADER	= 0,
	UNIFORM_TEST_SHADER,
	TEXTURE_DISCARD_SHADER,
	GREY_PFX_SHADER,
	BASIC_TEXTURE
};

PlayState* PlayState::_instance = 0;

PlayState* PlayState::getInstance()
{
	if( !_instance )
		_instance = new PlayState();

	return _instance;
}

PlayState::PlayState()
{
	_player		= 0;
	_obsticle	= 0;
	_camera		= 0;
	_background = 0;
}

PlayState::~PlayState()
{
}

void PlayState::enterFunc()
{
	sf::Vector2f screenScale = eage::getResolutionScale();

	eage::alphaBlend( true );
	eage::loadResourceIndices( "data/scenes/animationTest_scene.res", EAGE_FROM_MEMORY );

	// player initialization
	_player = new Player();
	//_player->setSize( sf::Vector2f(100.0f,600.0f), sf::Vector2f(100.0f,500.0f), sf::Vector2f(200.0f,500.0f), sf::Vector2f(200.0f,600.0f) );
	_player->setSize( sf::Vector2f( 100.0f, 400.0f ), sf::Vector2f(50.0f, 50.0f) );
	_player->setTexture( 4 );
	_player->setLayer( 0.0f );
	_player->setShader( BASIC_TEXTURE );
	_player->addAnimationSet( 1 );
	//_player->createB2DBody();

	// static object initialization
	_obsticle = new GameObject();
	_obsticle->setSize( sf::Vector2f( 600.0f, 550.0f ), sf::Vector2f(75.0f, 75.0f) );
	_obsticle->setTexture( 2 );
	_obsticle->setLayer( 0.0f );
	_obsticle->setShader( BASIC_TEXTURE );
	_obsticle->setDynamic( false );
	//_obsticle->createB2DBody();

	// Layer initialization
	//_background = new Layer( -0.5f );
	//std::vector<int> texIdlist;
	//for( int i = 0; i < 100000; ++i )
	//{
	//	texIdlist.push_back( 7 );
	//}
	//_background->initialize( 100.0f, 100, 1000, sf::Vector2f(), 0, &texIdlist );

	// SFGUI
	_title = sfg::Label::Create( "Massive rendering and FBA Test" );
	_title->SetPosition( sf::Vector2f(50.0f*screenScale.x, 50.0f*screenScale.y) );
	_title->SetId( "title" );

	_message = sfg::Label::Create( "Mouse vector: 0.0f, 0.0f" );
	_message->SetPosition( sf::Vector2f( 50.0f*screenScale.x, 200.0f*screenScale.y ) );
	_message->SetId( "message" );

	_nextBtn = sfg::Button::Create( "Next Scene" );
	_nextBtn->SetPosition( sf::Vector2f( 1100.0f*screenScale.x, 680.0f*screenScale.y ) );
	_nextBtn->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind( &PlayState::onNextBtn, this ));

	_preBtn = sfg::Button::Create( "Previous Scene" );
	_preBtn->SetPosition( sf::Vector2f( 1100.0f*screenScale.x, 650.0f*screenScale.y ) );
	_preBtn->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind( &PlayState::onPrevBtn, this ));

	eage::appendUIWidget( _title );
	eage::appendUIWidget( _message );
	eage::appendUIWidget( _nextBtn );
	eage::appendUIWidget( _preBtn );
	eage::appendObject( _obsticle );
	eage::appendFBAObject( _player );

	//this->setRenderMode( EAGE_DIRECT_RENDER );
	//this->setRenderMode( EAGE_WIREFRAME );
	eage::setRenderMode( EAGE_DIRECT_RENDER );
	eage::setPostFXShader( GREY_PFX_SHADER );

	//eage::findShader( UNIFORM_TEST_SHADER )->uniform( "status", 0 );

	eage::getUIDesktop()->SetProperty( "#title", "Color", sf::Color::Yellow );
	eage::getUIDesktop()->SetProperty( "#title", "FontName", "1" );
	eage::getUIDesktop()->SetProperty( "#title", "FontSize", 25.0f );

	_camera = eage::getMainCamera();
}

void PlayState::leaveFunc()
{
	eage::stopAllSound();
	eage::stopMusic();

	eage::removeUIWidget( _message );
	eage::removeUIWidget( _title );
	eage::removeUIWidget( _nextBtn );
	eage::removeUIWidget( _preBtn );
}

void PlayState::control()
{
	// player control
	if( eage::isKeyPressed( eage::D ) )
	{
		_player->move( sf::Vector2f(1.0,0.0), SPEED );
	}
	else if( eage::isKeyPressed( eage::A ) )
	{
		_player->move( sf::Vector2f(-1.0,0.0), SPEED );
	}
	else if( eage::isKeyPressed( eage::W ) )
	{
		_player->move( sf::Vector2f(0.0,1.0), SPEED );
	}
	else if( eage::isKeyPressed( eage::S ) )
	{
		_player->move( sf::Vector2f(0.0,-1.0), SPEED );
	}
	else
	{
		_player->stop();
	}

	// camera focus control
	if( eage::isKeyPressed( eage::Num1 ) )
	{
		_camera->follow( _player );
	}
	if( eage::isKeyPressed( eage::Num2 ) )
	{
		_camera->releaseFocus();
	}
	if( eage::isKeyPressed( eage::Add ) )
	{
		_camera->zoom( 1.05f );
	}
	if( eage::isKeyPressed( eage::Subtract ) )
	{
		_camera->zoom( 0.95f );
	}

	// music control
	if( eage::isKeyPressed( eage::Space) )
	{
		eage::playMusic( 0 );
	}

	// game speed control
	if( eage::isKeyPressed( eage::Num3) )
	{
		eage::setGameSpeed( 0.5f );
		eage::setAudioSpeed( 0.5f );
	}
	if( eage::isKeyPressed( eage::Num4 ) )
	{
		eage::setGameSpeed( 1.0f );
		eage::setAudioSpeed( 1.0f );
	}

	// pause/unpause control
	if( eage::isKeyPressed( eage::Escape ) )
	{
		static bool flag = false;
		flag = !flag;
		eage::pauseAnimation( flag );
		eage::pausePhysics( flag );

		if( !flag ) eage::resumeAudio();
		if( flag )	eage::pauseAudio();
	}

	_player->playAnimation( 0 );	

	//if( eage::isCollidedAABB( _player, _obsticle ) )
	//{
	//	eage::playSound( 1 );
	//	_player->react();
	//}


	// mouse vector

	/*sf::Vector2f mv = eage::getMouseWorldCoord() - _player->getCentre();
	static sf::Vector2f uv = sf::Vector2f( 0.0f, 1.0f );
	char str[256];
	float angle = eage::getAngle( uv, mv );
	sprintf_s( str, "Mouse Vector: %.2f, %.2f\nRotation Angle: %.2f", mv.x, mv.y, angle );

	_player->setRotate( -angle, _player->getCentre() );*/

	//_message->SetText( str );
}


void PlayState::onPrevBtn()
{
	_title->Show(false);
	_nextBtn->Show(false);
	_preBtn->Show(false);

	changeState( 1 );
}


void PlayState::onNextBtn()
{
	_title->Show(false);
	_nextBtn->Show(false);
	_preBtn->Show(false);

	changeState( 5 );
}