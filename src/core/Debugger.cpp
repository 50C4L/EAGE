#include "Debugger.h"
#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <cstdarg>

#define DEBUG_BUFFER_SIZE	256

void eage::debug( const char* format, ... )
{
	char buffer[DEBUG_BUFFER_SIZE];
	char* p = buffer;

	va_list args;
	va_start( args, format );
	vsprintf( p, format, args );
	va_end( args );

	Debugger::getInstance()->debug( buffer );
}

void eage::debugToOSConsole( bool flag )
{
	Debugger::getInstance()->isOutputSysConsole( flag );
}


Debugger* Debugger::_instance = 0;

Debugger::Debugger()
{
	_log.clear();
	_isConsoleReady = false;
	_isO2SystemConsole = false;
	_isHide = true;
}



Debugger::~Debugger()
{
	_log.clear();
}


void Debugger::isOutputSysConsole( bool flag )
{
	_isO2SystemConsole = flag;
}


Debugger* Debugger::getInstance()
{
	if( !_instance )	_instance = new Debugger();
	return _instance;
}



void Debugger::clearLog()
{
	_log.clear();
}



void Debugger::debug( std::string info )
{
	if( _isO2SystemConsole )
		std::cout << info;
	_log += info;
	if( _isConsoleReady )
	{
		_text->SetText( _log.c_str() );
	}
		
}


void Debugger::ouputLogFile( std::string path )
{
	std::ofstream file;

	file.open( path );
	file << _log;
	file.close();
}


void Debugger::initializeConsole( sfg::Desktop* desk )
{
	// create console window
	_window = sfg::Window::Create();
	_window->SetTitle( "Console" );

	// renew text label
	_text = sfg::Label::Create( _log.c_str() );

	// create margin box
	_box = sfg::Box::Create( sfg::Box::Orientation::VERTICAL, 5.0f );

	// create entry
	_entry = sfg::Entry::Create();
	_entry->SetRequisition( sf::Vector2f( 390.0f, 10.0f ) );

	// create console scrollabr viewport
	_console = sfg::ScrolledWindow::Create();
	_console->SetScrollbarPolicy( sfg::ScrolledWindow::HORIZONTAL_ALWAYS | sfg::ScrolledWindow::VERTICAL_AUTOMATIC );
	_console->SetRequisition( sf::Vector2f( 400.0f, 300.0f ) );

	// combine everything
	_console->AddWithViewport( _text );
	_box->Pack( _console );
	_box->Pack( _entry );
	_window->Add( _box );
	desk->Add( _window );

	_isConsoleReady = true;
}


void Debugger::monitor()
{
	if( !_isHide && eage::isKeyPressed( eage::Return ))
	{
		//sf::String command;
		//command = _entry->GetText().getData();
		//if( !command.isEmpty() )
		//{
		//	eage::debug( command.toAnsiString().c_str() );
		//}
	}
}


void Debugger::hideConsole( bool flag )
{
	_window->Show( !flag );
	_isHide = flag;
}