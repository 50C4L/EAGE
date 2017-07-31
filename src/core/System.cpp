#include "System.h"
#include <fstream>
#include <stdio.h>
#include <time.h>

void eage::exit()
{
	System::_instance->_isRunning = false;
}

int eage::getElapsedMilliSec()
{
	if( System::getInstance()->_timer )
		return System::getInstance()->_timer->getElapsedMilliSec();
	else
		return 0;
}

//void eage::appendUIWidget(std::shared_ptr<sfg::Widget> widget)
//{
//	System::getInstance()->appendSFGUIWidget( widget );
//}

//void eage::removeUIWidget( std::shared_ptr<sfg::Widget> widget )
//{
//	System::getInstance()->_desk->Remove( widget );
//}
//
//sfg::Desktop* eage::getUIDesktop()
//{
//	return System::getInstance()->_desk;
//}

sf::Vector2f eage::getMouseWorldCoord()
{
	// get mouse window coordinate
	sf::Vector2i wndCroodi = sf::Mouse::getPosition( *System::getInstance()->_window );
	sf::Vector2f wndCoord = sf::Vector2f( (float)wndCroodi.x, (float)wndCroodi.y );
	wndCoord.y = (float)System::getInstance()->_window->getSize().y - wndCoord.y;

	sf::Vector2f offset = eage::getMainCamera()->getBoundary()->getVertexAttrit( 1 ).pos.pos;

	return (wndCoord+offset);
}

sf::Event eage::getEvent()
{
	return *System::getInstance()->_event;
}


//void eage::removeAllUIWidget()
//{
//	System::getInstance()->_desk->RemoveAll();
//}

////////////////////////////////////////////////////////////////////////////////////////////////

System* System::_instance = 0;

EAGE* engineCreate()
{
	return (EAGE*)System::getInstance();
}

System::System()
{
	// default settings
	_cfgPath				= "config.cfg";
	_params.isFullScreen	= false;
	_params.isVSync			= true;
	_params.windowSize		= sf::Vector2i( RES_16_9_WIDTH, RES_16_9_HEIGHT );
	strcpy_s( _params.windowTitle, "EAGE Window" );
	_window					= NULL;
	_event					= NULL;
	_isSplash				= false;
	_isRunning				= true;
	_splashLength			= 2.0f;
	_designWidth			= RES_16_9_WIDTH;
	_designHeight			= RES_16_9_HEIGHT;

	// managers and modules
	_texman					= NULL;
	_stateman				= NULL;
	_renderModule			= NULL;
	_resourceModule			= NULL;
	_physicsModule			= NULL;

	// debug info
	_frameInterval			= 0;
	_debugger				= 0;
	_consoleFlag			= false;

	// states
	_startState				= 0;
}

System::~System()
{
	_debugger->ouputLogFile("Log.txt");
}

System* System::getInstance()
{
	if( !_instance )	_instance = new System();
	return _instance;
}


std::string System::getVersion()
{
	static const char* comDate = __DATE__;
	static const char* comTime = __TIME__;

	char sMonth[5];
	int month, day, year, hour, min, sec;
	std::tm tStruct = {0};
	static const char monthNames[] = "JanFebMarAprMayJunJulAugSepOctNovDec";
	sscanf( comDate, "%s %d %d", sMonth, &day, &year );
	sscanf( comTime, "%d:%d:%d", &hour, &min, &sec );
	month = ( strstr( monthNames, sMonth ) - monthNames )/3;

	tStruct.tm_mon = month;
	tStruct.tm_mday = day;
	tStruct.tm_year = year - 1900;
	tStruct.tm_isdst = -1;
	tStruct.tm_hour = hour;
	tStruct.tm_min = min;
	tStruct.tm_sec = sec;

	std::stringstream buffer;
	buffer << std::put_time( &tStruct, "1.%d%m%Y%H%M%S" );
	std::string version = buffer.str();
	return version;
}


void System::loadCFG( std::string path )
{
	if( !path.empty() )
		_cfgPath = path;
}

//void System::appendSFGUIWidget( std::shared_ptr<sfg::Widget> widget )
//{
//	if( _desk )
//		_desk->Add( widget );
//}

int System::appendState( int id, State* state )
{
	if( _stateman && state )
	{
		_stateman->appendState( id, state );
		return id;
	}
	return 0;
}

void System::setStartState( int id )
{
	if( id != 0 )
		_startState = id;
}

void System::setSplashLength( float length )
{
	_splashLength = length;
}


void System::setDesignResolution( int width, int height )
{
	_designWidth = width;
	_designHeight = height;
}


void System::enableSplashScreen( bool value )
{
	_isSplash = value;
}

bool System::initialize()
{
	// get debugger
	_debugger = Debugger::getInstance();

	// load cfg file
	eage::debug( "CORE: Initializing...\n" );
	eage::debug( "CORE: Preparing to read cfg file...\n" );
	if( !this->_readCFG() ) eage::debug( "CORE: Failed to open cfg file, genera4ting one with default parameters.\n" );
	_window = new  sf::RenderWindow;
	if( !_params.isFullScreen)	_window->create( sf::VideoMode( _params.windowSize.x, _params.windowSize.y ), _params.windowTitle );
	else						_window->create( sf::VideoMode( _params.windowSize.x, _params.windowSize.y ), _params.windowTitle, sf::Style::Fullscreen );
	if( _params.isVSync )		_window->setVerticalSyncEnabled( true );

	// init OGL
	eage::debug( "CORE: Initializing OpenGL states...\n" );
	if( !this->_initGL() ) return false;

	// init timer
	eage::debug( "CORE: Main timer instanced.\n" );
	_timer = new Timer();

	// init modules
	eage::debug( "CORE: Preparing to initialize modules...\n" );
	_resourceModule = ResourceModule::getInstance();
	_resourceModule->initialize();
	_physicsModule = PhysicsModule::getInstance();
	_physicsModule->initialize( 1/60.0f, 8, 3 );
	_renderModule = RenderModule::getInstance();
	_renderModule->initialize( _resourceModule->getTexMan() );
	_renderModule->setDesignResolution( _designWidth, _designHeight );

	_stateman = StateManager::getInstance();
	_stateman->initialize( _renderModule, _resourceModule, _physicsModule, _window );

	_resourceModule->setSFGUI( eage::getUIDesktop() );

	_debugger->initializeConsole( eage::getUIDesktop() );
	_debugger->hideConsole( true );

	return true;
}


void System::run()
{
	eage::debug( "CORE: Main timer starts.\n" );
	_timer->start();
	eage::debug( "CORE: Begining to loop...\n" );

	double frameStart = 0;

	_event = new sf::Event();

	_renderModule->reshape( _window );
	_renderModule->genScaleRatio();
	_stateman->changeState( _startState );

	// loop them to hell
	while( _isRunning )
	{
		frameStart = _timer->getElapsedMircoSec();

		while( _window->pollEvent( *_event ) )
		{
			eage::getUIDesktop()->HandleEvent(*_event);

			if( _event->type == sf::Event::Closed )		_isRunning = false;
			if( _event->type == sf::Event::Resized )		_renderModule->reshape( _window );
		}

		if( _event->type == sf::Event::LostFocus )	
		{
			eage::pauseAudio();
			continue;
		}

		if( eage::isKeyPressed( eage::Tilde ) )
		{
			static bool flag = false;
			if( !_consoleFlag )
			{
				flag = !flag;
				_debugger->hideConsole( flag );
				_consoleFlag = true;
			}	
		}
		if( !eage::isKeyPressed( eage::Tilde ) )
			_consoleFlag = false;

		_debugger->monitor();

		_renderModule->clearBuffers();
		// state running zone
		//if( _isSplash )
			//_isSplash = _renderModule->renderSplash( (float)_frameInterval, _splashLength );
		//else
			_stateman->run();
		_window->display();

		_frameInterval = _timer->getElapsedMircoSec() - frameStart;
		_renderModule->gether( _frameInterval );
		_physicsModule->activate();
	}

	_stateman->end();

	delete _event;
	delete _window;
	delete _timer;
}


void System::shutdown()
{
	_renderModule->shutdown();
	_resourceModule->shutdown();
	_physicsModule->shutdown();

	_debugger->ouputLogFile("Log.txt");
	this->_writeCFG();
}

void System::setCoreParams( CoreParams param )
{
	_params = param;
	this->_writeCFG();
}

bool System::_initGL()
{
	glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
	glClearDepth( 1.0f );
	glEnable( GL_DEPTH_TEST );
	glDepthFunc( GL_LEQUAL );
	glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );

	GLenum err = glewInit();
	if( GLEW_OK != err )
	{
		eage::debug( "CORE: Failed to initialize GLEW\n" );
		return false;
	}
	eage::debug( "CORE: GLEW initialized, version %s\n", glewGetString(GLEW_VERSION) );

	glEnableClientState( GL_VERTEX_ARRAY );
	glEnableClientState( GL_TEXTURE_COORD_ARRAY );
	glEnableClientState( GL_COLOR_ARRAY );
	glEnable( GL_TEXTURE_2D );

	return true;
}


bool System::_readCFG()
{
	std::ifstream file;
	file.open( _cfgPath );
	if( file.fail() )
	{
		this->_writeCFG();
		return false;
	}

	char key[32];

	while( !file.eof() )
	{
		file >> key;
		// core config
		if( strcmp( key,"[CORE]" ) == 0 )
		{
			char param[32];
			file >> param;

			while( strcmp( param,"$" )!= 0 )
			{
				if( strcmp( param,"sTitle" ) == 0 )
				{
					file.get();
					file.getline( _params.windowTitle, sizeof( _params.windowTitle ) );
				}
				if( strcmp( param,"iWidth" ) == 0 )			file >> _params.windowSize.x;
				if( strcmp( param,"iHeight" ) == 0 )		file >> _params.windowSize.y;
				if( strcmp( param,"bFullScreen" ) == 0 )	file >> _params.isFullScreen;
				if( strcmp( param,"bVSync" ) == 0 )			file >> _params.isVSync;
				file >> param;
			}
			continue;
		}
	}

	return true;
}

bool System::_writeCFG()
{
	std::ofstream file;

	file.open( _cfgPath );
	if( file.fail() )		return false;

	// output descriptions
	file << "# MAIN CONFIG FILE FOR EAGE\n"
		 << "# Don not miss the '$' symbol after each module.\n"
		 << "#\n"
		 << "# Header References:\n"
		 << "# b - bool value\n"
		 << "# i - integer value\n"
		 << "# f - float value\n"
		 << "# s - string value\n\n";

	// output core params
	file << "[CORE]\n"
		 << "sTitle "		<< _params.windowTitle		<< std::endl
		 << "iWidth "		<< _params.windowSize.x		<< std::endl
		 << "iHeight "		<< _params.windowSize.y		<< std::endl
		 << "bFullScreen "	<< _params.isFullScreen		<< std::endl
		 << "bVSync "		<< _params.isVSync			<< std::endl
		 << "$" << std::endl;

	return true;
}
