#include "MenuState.h"
#include <stdio.h>

bool btn1_hover = false;
bool btn2_hover = false;

MenuState* MenuState::_instance = NULL;

MenuState* MenuState::getInstance()
{
	if( !_instance )
		_instance = new MenuState();

	return _instance;
}

MenuState::MenuState()
{
}

MenuState::~MenuState()
{
}

void MenuState::enterFunc()
{
	//this->loadResFile( "data/scenes/uiTest_scene.res" );
	eage::loadResourceIndices( "data/scenes/uiTest_scene.res", EAGE_FROM_FILE );

	/*_test = new Button();
	_test->setSize( sf::Vector2f(600.0f,400.0f), sf::Vector2f(600.0f,350.0f), sf::Vector2f(700.0f,350.0f), sf::Vector2f(700.0f,400.0f) );
	_test->setTexture( 5 );
	_test->setLayer( 0.5 );

	_btn_exit = new Button();
	_btn_exit->setSize( sf::Vector2f(600.0f,300.0f), sf::Vector2f(600.0f,250.0f), sf::Vector2f(700.0f,250.0f), sf::Vector2f(700.0f,300.0f) );
	_btn_exit->setTexture( 6 );
	_btn_exit->setLayer( 0.5 );

	_title = new Label();
	_title->setFontSize( 20 );
	_title->setFont( 2 );
	_title->setFontColor( 0.0f, 1.0f, 0.0f, 1.0f );
	_title->setText( "UI Objects Test" );
	_title->setPosition( 10.0f, 20.0f );

	this->addUIObject( _title );
	this->addUIObject( _test );
	this->addUIObject( _btn_exit );*/

	_title = sfg::Label::Create( "SFGUI Test" );
	_title->SetPosition( sf::Vector2f(50.0f, 50.0f) );
	_title->SetId( "title" );

	beginBtn = sfg::Button::Create("Begin Test");
	beginBtn->SetPosition(sf::Vector2f(600.0f, 400.0f));

	exitBtn = sfg::Button::Create("Exit Test");
	exitBtn->SetPosition( sf::Vector2f( 600.0f, 450.0f ) );

	beginBtn->GetSignal( sfg::Widget::OnLeftClick ).Connect( std::bind( &MenuState::ButtonPlayTest, this ) );
	exitBtn->GetSignal( sfg::Widget::OnLeftClick ).Connect( std::bind( &MenuState::ButtonEndTest, this ) );

	eage::appendUIWidget( _title );
	eage::appendUIWidget( beginBtn );
	eage::appendUIWidget( exitBtn );
	
	eage::getUIDesktop()->SetProperty( "#title", "Color", sf::Color::Yellow );
	eage::getUIDesktop()->SetProperty( "#title", "FontName", "1" );
	eage::getUIDesktop()->SetProperty( "#title", "FontSize", 25.0f );

	//eage::setRenderMode( EAGE_POST_EFFECT );
}

void MenuState::leaveFunc()
{
	eage::removeUIWidget(beginBtn);
	eage::removeUIWidget(exitBtn);
	eage::removeUIWidget( _title );
}

void MenuState::control()
{
	if( eage::isKeyPressed( eage::Escape ) )
		eage::exit();
}

void MenuState::ButtonPlayTest()
{
	beginBtn->Show( false );
	exitBtn->Show( false );
	_title->Show( false );
	
	changeState( 2 );
}

void MenuState::ButtonEndTest()
{
	eage::exit();
}