#ifndef _VISIBLEOBJECT_H
#define _VISIBLEOBJECT_H

#include <SFML\System\Vector2.hpp>
#include <SFML\Graphics\Transform.hpp>
#include <string>
#include "../math/PhysicsBody.h"

class PhysicsModule;

struct VO_uvCoordinate
{
	sf::Vector2f leftTop;
	sf::Vector2f leftBottom;
	sf::Vector2f rightBottom;
	sf::Vector2f rightTop;
};

class VisibleObject
{
public:
	VisibleObject();
	virtual ~VisibleObject();

	virtual void			setTexture( int id );
	virtual void			setShader( int id );
	virtual	void			getVertices( sf::Vector2f &lt, sf::Vector2f &lb, sf::Vector2f &rb, sf::Vector2f &rt );
	virtual int				getTexture();
	virtual int				getShader();
	virtual sf::Vector2f	getCentre();
	virtual void			setSize( sf::Vector2f leftTop, sf::Vector2f leftBottom, sf::Vector2f rightBottom, sf::Vector2f rightTop );
	virtual void			setUV( VO_uvCoordinate uvs );
	virtual void			setLayer( float layer );
	virtual void			setTranslate( float x, float y );
	virtual void			setTranslate( sf::Vector2f pos );
	virtual void			setRotate( float angle );
	virtual void			setRotate( float angle, sf::Vector2f point );
	virtual void			setIdentity();
	virtual void			setMass( float value );
	virtual void			setCurrentSpeed( float value );
	virtual void			setMaxSpeed( float value );
	virtual void			setAcceleration( sf::Vector2f );
	virtual void			setUniform( sf::Vector2f );
	virtual void			setInertia( float value );
	virtual void			setRadius( float value );
	virtual void			render();
	virtual bool			isInsertAABB( sf::Vector2f );
	virtual bool			isInsertBSphere( sf::Vector2f );

	friend class PhysicsModule;

private:
	void			_createAABB();
	void			_createBSphere();

	PhysicsBody		_physxBody;
	float			_layer;
	int				_texid;
	int				_shaid;
	sf::Vector2f	_LT, _LB, _RB, _RT, _CT;
	sf::Transform	_transform;
	VO_uvCoordinate	_uv;

};	// class VisibleObject

#endif