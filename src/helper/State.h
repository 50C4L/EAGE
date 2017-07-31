#ifndef _STATE_H
#define _STATE_H

#include <SFML\Graphics.hpp>
#include <string>
#include "../helper/helper.h"

class StateManager;
class RenderModule;
class ResourceModule;
class PhysicsModule;
class VisibleObject;
class UIObject;
class FBAnimObject;

class State
{
public:
					State();
	virtual			~State();

	virtual void	enter( RenderModule*, ResourceModule*, PhysicsModule*, sf::RenderWindow* );
	virtual void	enterFunc()					{};
	virtual void	control()					{};
	virtual void	run();
	virtual void	leave();
	virtual void	leaveFunc()					{};
	virtual void	loadResFile( std::string filename );
	virtual void	addFBAObject( FBAnimObject *obj );
	virtual void	addUIObject( UIObject *obj );
	virtual void	addObject( VisibleObject *obj );
	virtual void	setGravity( sf::Vector2f value );
	virtual void	setRenderMode( EAGE_RENDER_MODE mode );
	virtual void	setPostFXShader( int shaderId );

	void			getManger( StateManager* );

protected:
	void			changeState( int id );

private:
	StateManager*		_stateManPtr;
	RenderModule*		_rdm;
	ResourceModule*		_rsm;
	PhysicsModule*		_pxm;
	sf::RenderWindow*	_rw;
};		// class State

#endif