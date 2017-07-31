#ifndef _DEBUGGER_H
#define _DEBUGGER_H

#include "../helper/helper.h"
#include <SFGUI\Box.hpp>
#include <SFGUI\ScrolledWindow.hpp>
#include <SFGUI\Window.hpp>
#include <SFGUI\Label.hpp>
#include <SFGUI\Entry.hpp>
#include <string>

class Debugger
{
	friend void eage::debug( const char* format, ... );

public:
	static Debugger* getInstance();
	~Debugger();

	void initializeConsole( sfg::Desktop* desk );
	void clearLog();
	void debug( std::string info );
	void ouputLogFile( std::string path );
	void hideConsole( bool flag );
	void isOutputSysConsole( bool flag );
	void monitor();

private:
	Debugger();

	std::string					_log;
	sfg::Box::Ptr				_box;
	sfg::ScrolledWindow::Ptr	_console;
	sfg::Window::Ptr			_window;
	sfg::Label::Ptr				_text;
	sfg::Entry::Ptr				_entry;
	bool						_isConsoleReady;
	bool						_isO2SystemConsole;
	bool						_isHide;

	static Debugger*			_instance;
};

#endif