#ifndef _HELPER_H
#define _HELPER_H

#include "AllHeaders.h"
#include <map>

//#ifdef EAGEFUNCDLL_EXPORTS
#define EAGE_API __declspec(dllexport) 
//#else
//#define EAGE_API __declspec(dllimport)
//#endif



// GLOBAL DEFINITIONS AND ENUMS
/////////////////////////////////////////////////////////////////////////////
#define MAX_NODES_NUMBER	16
#define MAX_NODE_ATTACHMENT_NUMBER	4
#define Pi	3.1415926
#define Epsilon 2.7182818
#define B2D_COORD_SCALE 30.0f
#define MILSPERSEC 1000.0
#define MICSPERSEC 1000000.0
#define RES_4_3_WIDTH	1024
#define RES_4_3_HEIGHT	768
#define RES_16_9_WIDTH	1280
#define RES_16_9_HEIGHT 720

// Data loading modes
enum EAGE_RESOURCE_MODE
{
	EAGE_FROM_FILE = 0,
	EAGE_FROM_MEMORY
};

// Render modes
enum EAGE_RENDER_MODE
{
	EAGE_DIRECT_RENDER = 0,
	EAGE_POST_EFFECT,
	EAGE_WIREFRAME
};

// Button states
enum Button_State
{
	BTN_NORMAL	= 0,
	BTN_HOVER,
	BTN_PRESSED
};	// Button state

enum EAGE_PARTICLE_MODE
{
	EAGE_POINTS = 0,
	EAGE_TRIANGLES
};

// Keys enums
namespace eage{
enum EAGE_KEY
{
	Unknown = -1, ///< Unhandled key
	A = 0,        ///< The A key
	B,            ///< The B key
	C,            ///< The C key
	D,            ///< The D key
	E,            ///< The E key
	F,            ///< The F key
	G,            ///< The G key
	H,            ///< The H key
	I,            ///< The I key
	J,            ///< The J key
	K,            ///< The K key
	L,            ///< The L key
	M,            ///< The M key
	N,            ///< The N key
	O,            ///< The O key
	P,            ///< The P key
	Q,            ///< The Q key
	R,            ///< The R key
	S,            ///< The S key
	T,            ///< The T key
	U,            ///< The U key
	V,            ///< The V key
	W,            ///< The W key
	X,            ///< The X key
	Y,            ///< The Y key
	Z,            ///< The Z key
	Num0,         ///< The 0 key
	Num1,         ///< The 1 key
	Num2,         ///< The 2 key
	Num3,         ///< The 3 key
	Num4,         ///< The 4 key
	Num5,         ///< The 5 key
	Num6,         ///< The 6 key
	Num7,         ///< The 7 key
	Num8,         ///< The 8 key
	Num9,         ///< The 9 key
	Escape,       ///< The Escape key
	LControl,     ///< The left Control key
	LShift,       ///< The left Shift key
	LAlt,         ///< The left Alt key
	LSystem,      ///< The left OS specific key: window (Windows and Linux), apple (MacOS X), ...
	RControl,     ///< The right Control key
	RShift,       ///< The right Shift key
	RAlt,         ///< The right Alt key
	RSystem,      ///< The right OS specific key: window (Windows and Linux), apple (MacOS X), ...
	Menu,         ///< The Menu key
	LBracket,     ///< The [ key
	RBracket,     ///< The ] key
	SemiColon,    ///< The ; key
	Comma,        ///< The , key
	Period,       ///< The . key
	Quote,        ///< The ' key
	Slash,        ///< The / key
	BackSlash,    ///< The \ key
	Tilde,        ///< The ~ key
	Equal,        ///< The = key
	Dash,         ///< The - key
	Space,        ///< The Space key
	Return,       ///< The Return key
	BackSpace,    ///< The Backspace key
	Tab,          ///< The Tabulation key
	PageUp,       ///< The Page up key
	PageDown,     ///< The Page down key
	End,          ///< The End key
	Home,         ///< The Home key
	Insert,       ///< The Insert key
	Delete,       ///< The Delete key
	Add,          ///< The + key
	Subtract,     ///< The - key
	Multiply,     ///< The * key
	Divide,       ///< The / key
	Left,         ///< Left arrow
	Right,        ///< Right arrow
	Up,           ///< Up arrow
	Down,         ///< Down arrow
	Numpad0,      ///< The numpad 0 key
	Numpad1,      ///< The numpad 1 key
	Numpad2,      ///< The numpad 2 key
	Numpad3,      ///< The numpad 3 key
	Numpad4,      ///< The numpad 4 key
	Numpad5,      ///< The numpad 5 key
	Numpad6,      ///< The numpad 6 key
	Numpad7,      ///< The numpad 7 key
	Numpad8,      ///< The numpad 8 key
	Numpad9,      ///< The numpad 9 key
	F1,           ///< The F1 key
	F2,           ///< The F2 key
	F3,           ///< The F3 key
	F4,           ///< The F4 key
	F5,           ///< The F5 key
	F6,           ///< The F6 key
	F7,           ///< The F7 key
	F8,           ///< The F8 key
	F9,           ///< The F9 key
	F10,          ///< The F10 key
	F11,          ///< The F11 key
	F12,          ///< The F12 key
	F13,          ///< The F13 key
	F14,          ///< The F14 key
	F15,          ///< The F15 key
	Pause,        ///< The Pause key
	
	KeyCount      ///< Keep last -- the total number of keyboard keys
};
}

// MATH BASIC CLASS
/////////////////////////////////////////////////////////////////////////////
// Axis-Alined Bounding Box
class EAGE_API AABB
{
public:
	AABB();
	~AABB();

	void			addVertex( sf::Vector2f );
	void			translate( sf::Vector2f v );
	void			scale( float value );
	bool			judgePoint( sf::Vector2f );
	bool			isCollide( sf::Vector2f );
	bool			isCollide( AABB box );
	sf::Vector2f	getMax();
	sf::Vector2f	getMin();

private:
	sf::Vector2f _max, _min;
	int	flag;
};	// class AABB

// Bounding Sphere
class EAGE_API BSphere
{
public:
	BSphere();
	~BSphere();
	void			create( sf::Vector2f, float );
	bool			isCollide( sf::Vector2f );
	bool			isCollide( BSphere sphere ); 
	sf::Vector2f	getCentre();
	float			getRadius();

private:
	sf::Vector2f	_centre;
	float			_radius;
	float			_radSquare;
};	// class BSphere

// MATH FUNCTIONS AND STRUCTURES
/////////////////////////////////////////////////////////////////////////////
// Structure of physics body
struct PhysicsBody
{
	float			mass;
	sf::Vector2f	acceleration;
	sf::Vector2f	uniform;
	sf::Vector2f	currentVelocity;
	sf::Vector2f	accumulation;
	sf::Vector2f	history;
	float			currentSpeed;
	float			maxSpeed;
	float			inertia;
	float			radius;
	bool			IsDynamic;
	AABB			aabb;
	BSphere			bsphere;
};


// UV Texture coordinates for VisbleObject
struct VO_uvCoordinate
{
	sf::Vector2f leftTop;
	sf::Vector2f leftBottom;
	sf::Vector2f rightBottom;
	sf::Vector2f rightTop;
};


// Vertex structure
struct Vertex
{
	sf::Vector2f pos;
	float		 layer;
};


// Texcoord structure
struct Texcoord
{
	float s;
	float t;
};

// Colour structure
struct Color
{
	float r;
	float g;
	float b;
	float a;
};

// Vertex Attributes
struct VertexAttribute
{
	Vertex		 pos;
	Texcoord	 uv;
	Color		 color;
};

// Animation info for frame based animation
struct ANIM_INFO
{
	sf::Vector2f	start;
	float			height;
	double			totalTime;
	int				frame;
	float			width;
	float			offset;	// *
	

	void operator=( ANIM_INFO info )
	{
		start		= info.start;
		offset		= info.offset;
		totalTime	= info.totalTime;
		width		= info.width;
		frame		= info.frame;
		height		= info.height;
	};
};

// Animations set for frame based animation
struct FB_ANIM_SET
{
	int				id;
	int				size;
	std::string		name;
	ANIM_INFO		list[256];
};

// Particle basic structure
struct PARTICLE
{
	Vertex		position;
	Texcoord	texcoord;
	Color		color;
	//PhysicsBody physx;
};

// GLOBAL FUNCTIONS
/*** These functions can only be called after the engine was initialized ***/
/////////////////////////////////////////////////////////////////////////////
class ShaderObject;
class GameObject;
class FBAnimObject;
class UIObject;
class Camera;
namespace eage
{
	EAGE_API void				loadShaderFromFile( std::string filename, int shaderId );
	EAGE_API ShaderObject*		findShader( int shaderId );
	EAGE_API bool				isKeyPressed( int key );
	EAGE_API bool				isCollidedAABB( GameObject* obj1, GameObject* obj2 );
	EAGE_API bool				isCollidedAABB( GameObject* obj, sf::Vector2f vec );
	EAGE_API bool				isCollidedBS( GameObject* obj1, GameObject* obj2 );
	EAGE_API bool				isCollidedBS( GameObject* obj, sf::Vector2f vec );
	EAGE_API Camera*			getMainCamera();
	EAGE_API void				playSound( int id );
	EAGE_API void				playMusic( int id );
	EAGE_API void				stopAllSound();
	EAGE_API void				stopMusic();
	EAGE_API void				pauseAudio();
	EAGE_API void				pauseAnimation( bool value );
	EAGE_API void				pausePhysics( bool value );
	EAGE_API void				setGameSpeed( float value );
	EAGE_API void				setAudioSpeed( float value );
	EAGE_API void				setGravity( float x, float y );
	EAGE_API void				setRenderMode( EAGE_RENDER_MODE mode );
	EAGE_API void				setPostFXShader( int id );
	EAGE_API void				debugToOSConsole( bool flag );
	EAGE_API bool				loadResourceIndices( std::string filename, EAGE_RESOURCE_MODE mode );
	EAGE_API void				exit();
	EAGE_API float				getDistanceSquare( sf::Vector2f ptA, sf::Vector2f ptB );
	EAGE_API double				randomFloat( unsigned shift );
	EAGE_API float				getAngle( sf::Vector2f v1, sf::Vector2f v2 );
	EAGE_API float				getRotationalAngle( sf::Vector2f v1, sf::Vector2f v2 );
	EAGE_API sf::Vector2f		getResolutionScale();
	EAGE_API sf::Vector2f		normalize( sf::Vector2f v );
	EAGE_API sf::Vector2f		getMouseWorldCoord();
	EAGE_API int				getElapsedMilliSec();
	EAGE_API void				alphaBlend( bool flag );
	EAGE_API void				appendFBAObject( FBAnimObject* obj );
	EAGE_API void				appendObject( GameObject* obj );
	EAGE_API void				appendUIObject( UIObject* obj );
	EAGE_API void				updateVertex( int shaderBlock, int renderList, int renderOffset, VertexAttribute vert );
	EAGE_API void				updateVertex( int shaderBlock, int renderList, int renderOffset, Texcoord uv );
	EAGE_API void				updateVertex( int shaderBlock, int renderList, int renderOffset, Color color );
	EAGE_API void				resumeAudio();
	EAGE_API void				debug( const char* format, ... );
	EAGE_API void				drawLine( sf::Vector2f begin, sf::Vector2f end, float r, float g, float b, float a );
	EAGE_API sf::Event			getEvent();

	// Box2D
	EAGE_API void				appendContactListener( b2ContactListener* ptr );

	// SFGUI
	EAGE_API void				appendUIWidget( std::shared_ptr<sfg::Widget> widget );
	EAGE_API void				removeUIWidget( std::shared_ptr<sfg::Widget> widget );
	EAGE_API sfg::Desktop*		getUIDesktop();
}


// STATE ABSTRACT CLASS
/////////////////////////////////////////////////////////////////////////////
class StateManager;
class RenderModule;
class ResourceModule;
class PhysicsModule;
class GameObject;
class UIObject;
class FBAnimObject;

class EAGE_API State
{
	friend class StateManager;
public:
					State();
	virtual			~State();

			 void	enter( RenderModule*, ResourceModule*, PhysicsModule*, sf::RenderWindow* );
			 void	loadResource();
	virtual  void	enterFunc()					{};
	virtual  void	control()					{};
	virtual  void	loadingScreen();
			 void	run();
			 void	leave();
	virtual  void	leaveFunc()					{};
	virtual  void	addFBAObject( FBAnimObject *obj );
	virtual  void	addUIObject( UIObject *obj );
	virtual  void	addObject( GameObject *obj );

			 void	getManger( StateManager* );

protected:
			 void	changeState( int id );

private:
	StateManager*		_stateManPtr;
	RenderModule*		_rdm;
	ResourceModule*		_rsm;
	PhysicsModule*		_pxm;
	sf::RenderWindow*	_rw;
};		// class State


// Skeleton Nodes Class
class EAGE_API	SkeletonNode
{
public:
	SkeletonNode();
	~SkeletonNode();

	sf::Vector2f	getPosition();
	void			setPosition( sf::Vector2f pos );
	void			setParent( SkeletonNode* par );
	void			clear();
	void			attach( GameObject* obj );
	void			translate( sf::Vector2f direction );
	void			rotate( sf::Vector2f center, float angle );
	void			rotate( sf::Transform trans );
	void			rotateArroundParent( float angle );
	SkeletonNode*	search( int id );
	SkeletonNode*	addNode( int id, sf::Vector2f pos );
	bool			addNode( SkeletonNode* node );
	int				getId();
	void			setId( int id );


private:
	sf::Vector2f				_position;
	std::vector<SkeletonNode*>	_childList;
	SkeletonNode				*_parent;
	int							_childCount, _attCount;
	int							_id;
	std::vector<GameObject*>	_attachment;
};




// GameObject CLASS
/////////////////////////////////////////////////////////////////////////////////
class PhysicsModule;

class EAGE_API GameObject
{
	friend	bool		 eage::isCollidedAABB( GameObject* obj1, GameObject* obj2 );
	friend	bool		 eage::isCollidedAABB( GameObject* obj, sf::Vector2f vec );
	friend	bool		 eage::isCollidedBS( GameObject* obj1, GameObject* obj2 );
	friend	bool		 eage::isCollidedBS( GameObject* obj, sf::Vector2f vec );
	friend  class		 ShaderBlockManager;
	friend  class		 PhysicsModule;
	friend  class		 ShaderBlock;
	friend  class        RenderList;

public:
						 GameObject();
	virtual				 ~GameObject();

						 // creates Box2D body, must be called after defining b2BodyDef, 
						 // b2PolygonShape and b2FixtureDef
			void		 createB2DBody();

			void		 setTexture( int id );
			void		 setShader( int id );
			void		 setEnable( bool flag );
			void		 setPhysx( bool flag );
			bool		 isPhysx();
			bool		 isDynamic();
			bool		 isEnable();
			int			 getTexture();
			int			 getShader();
			float		 getLayer() const;
			sf::Vector2f getCentre();
			sf::Vector2f getHistory();
			void		 setSize( sf::Vector2f leftTop, sf::Vector2f leftBottom, sf::Vector2f rightBottom, sf::Vector2f rightTop );
			void		 setSize( float ltx, float lty, float lbx, float lby, float rbx, float rby, float rtx, float rty );
			
			// This function creates a binding box with the same size for physics simulation
			void		 setSize( sf::Vector2f position, sf::Vector2f relCentral );
			void		 setUV( VO_uvCoordinate uvs );
			void		 setLayer( float layer );
			void		 setTranslate( float x, float y );
			void		 setTranslate( sf::Vector2f newPosition );
			void		 setRotate( float angle );
			void		 setRotate( float angle, sf::Vector2f point );
			void		 setRotate( sf::Transform trans );
			void		 setRotation( float angle, sf::Vector2f point );
			void		 setIdentity();
			void		 setMass( float value );
			void		 setColor( float r, float g, float b, float a );

			// functions for old physics module
			void		 setCurrentSpeed( float value );
			void		 setMaxSpeed( float value );
			void		 setAcceleration( sf::Vector2f );
			void		 setUniform( sf::Vector2f );
			void		 setInertia( float value );
			void		 setRadius( float value );
			void		 setDynamic( bool value );
			void		 scaleAABB( float value ); 

			// functions for physics module with Box2D embbed
			void		 initialBox2DFixture( b2BodyDef bodyDef );
			void		 setLinearVelocity( float x, float y );
			void		 setLinearImpulse( float x, float y );
			void		 setTransform( float x, float y );
			void		 setForce( float x, float y );
			void		 setFixedRotation( bool flag );
			void		 setFriction( float friction );
			void		 setDensity( float density );
			void		 setGravityScale( float scale );

	virtual void		 render();
			bool		 isInsertAABB( sf::Vector2f );
			bool		 isInsertBSphere( sf::Vector2f );
			void		 updateUV( VO_uvCoordinate uvs );
			VertexAttribute	getVertexAttrit( int flag );

	// compare Z value
	bool operator < ( const GameObject &obj );

protected:
	void			_createAABB();
	void			_createBSphere();
	void			_calculateCenter();
	void			_updateVert();

	float			_layer;
	sf::Vector2f	_CT;
	VertexAttribute	_LT, _LB, _RB, _RT;
	VO_uvCoordinate	_uv;
	

	bool			_isEnable;
	bool			_isCaculusPhysx;
	int				_texid;
	int				_shaid;
	PhysicsBody		_physxBody;

	// Box2D attribute
	b2BodyDef		_bodyDef;
	b2Body			*_body;
	b2PolygonShape	_shape;
	b2FixtureDef	_fixtureDef;
	float			_oldAngle;

private:
	sf::Transform	_transform;
	int				_shaderBlock;
	int				_renderList;
	int				_renderOffset;

};	// class GameObject


// PARTICLE FX ABSTRACT ClASS
class EAGE_API ParticleFX:public GameObject
{
public:
	ParticleFX();
	~ParticleFX();

	void			render();
	void			renderMode( EAGE_PARTICLE_MODE mode );
	virtual void	initialize() = 0;
	virtual void	update() = 0;

protected:
	std::vector<PARTICLE> _particles;

private:
	EAGE_PARTICLE_MODE _mode;
};

// FRAME BASED ANIMATION OBJECT ABSTRACT CLASS
/////////////////////////////////////////////////////////////////////////////////
class EAGE_API FBAnimObject:public GameObject
{
public:
				 FBAnimObject();
	virtual		 ~FBAnimObject();

	virtual void update( float fps );

	int			 addAnimation( int, ANIM_INFO );
	int			 addAnimation( std::string );
	int			 getAnimCount();
	void		 addAnimationSet( int id );
	void		 playAnimation( int );
	void		 enableLoop( bool flag );
	bool		 isPlaying();
	bool		 isOnLastFrame();

private:
	std::map<int,ANIM_INFO> _animList;
	ANIM_INFO				_currentAnim;
	int						_currentID;
	VO_uvCoordinate			_currentUV;
	int						_frameCount;
	int						_keyFrameCount;
	bool					_isPlaying;
	bool					_isLoop;
	bool					_isLastFrame;
	int						_animCount;

};	// class FBAnimObject


// SHADER OBJECT CLASS
/////////////////////////////////////////////////////////////////////////////////
class EAGE_API ShaderObject
{
public:
					ShaderObject();
					~ShaderObject();

	bool			loadShader( std::string filename );
	bool			loadShaderFromMemory( char* shaderContent );
	void			activate();
	void			destroy();
	unsigned int	getProgramId();

	// uniform functions
	// ints
	void 			uniform( const char* name, int v0 );
	void 			uniform( const char* name, sf::Vector2i v );
	void 			uniform( const char* name, sf::Vector3i v );
	void 			uniform( const char* name, int count, int* v );

	// floats
	void			uniform( const char* name, float v0 );
	void			uniform( const char* name, sf::Vector2f v );
	void			uniform( const char* name, sf::Vector3f v );
	void			uniform( const char* name, int count, float* v );

private:
	void _printInfoLog( unsigned int obj );

	unsigned int	_vert, _frag, _prog;
	bool			_vertCom, _fragCom, _progCom;
};



// USER INTERFACE OBJECTS
///////////////////////////////////////////////////////////////////////////////
class EAGE_API UIObject:public GameObject
{
public:
				 UIObject();
				 ~UIObject();

	virtual	void		update( sf::Vector2f );
	virtual void		changeState();
	virtual bool		isHover();
	virtual bool		isFocused();
	int					getFontId();
	int					getId();
	void				setFocus( bool flag );
	void				setId( int id );
	void				setRenderWindowPtr( sf::RenderWindow* ptr );
	sf::RenderWindow*	getRenderWindowPtr();

private:
	sf::RenderWindow*	_rw;
	int			_id;
	int			_font_id;
	bool		_isClicked;
	bool		_isHover;
	bool		_isFocused;

};	// class UIObject

// UI Button Class
class EAGE_API Button:public UIObject
{
public:
				 Button();
				 ~Button();

	bool		 isPress();
	void		 changeState();
	Button_State getState();

private:
	void			_setState( Button_State );

	Button_State	_state;

	VO_uvCoordinate _norUV;
	VO_uvCoordinate _hovUV;
	VO_uvCoordinate _preUV;
};	// class Button


// UI Text label class
class EAGE_API Label:public UIObject
{
public:
				Label();
				~Label();

	void		render();
	void		setFontSize( unsigned int size );
	void		setFontColor( float r, float g, float b, float a );
	void		setPosition( float x, float y );
	void		setFont( int id );
	void		setText( std::string text );

private:
	int				_fontID;
	unsigned int	_size;
	sf::Color		_color;
	sf::Text		_text;
	bool			_isChanged;
	sf::Vector2f	_position;
};



// CAMERA CLASS
///////////////////////////////////////////////////////////////////////////////////
class EAGE_API Camera
{
public:
	Camera();
	~Camera();

	void			setPosition( sf::Vector2f pos );
	void			focus( sf::Vector2f target );
	void			focusFollowedObject();
	void			follow( GameObject* obj );
	void			releaseFocus();
	void			setViewClip( double nearClip, double farClip );
	void			zoom( float amount );
	void			pan( sf::Vector2f vec );
	void			activate( double screenWidth, double screenHeight );
	GameObject*		getBoundary();
	sf::Vector2f	getPosition();

private:
	void			_refreshBoundary();

	sf::Vector2f	_position, _screenSize;
	double			_nearClip, _farClip;
	GameObject*		_followObj;
	GameObject*		_boundary;
	float			_zoomAmount;

};	// class Camera


// LAYER CLASS
/////////////////////////////////////////////////////////////////////////////////////
class EAGE_API Layer
{
public:
	Layer( float value );
	~Layer();

	bool initialize( float tileSize, unsigned int herTileNum, 
					 unsigned int verTileNum, sf::Vector2f startCoord, 
					 int shaderID, const std::vector<int> *texIdList );

private:
	float			_value;
	float			_tileSize;
	float			_totalWidth, _totalHeight;
	unsigned int	_herTileNum, _verTileNum;
	std::vector<GameObject*>	_tileList;
};


#endif