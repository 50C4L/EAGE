#include "helper.h"

Camera::Camera()
{
	_nearClip	= -1.0;
	_farClip	= 1.0;
	_followObj	= 0;
	_zoomAmount	= 1.0f;
	_boundary = new GameObject();
}

Camera::~Camera()
{
}

void Camera::setPosition( sf::Vector2f pos )
{
	_position = pos;
}

void Camera::focus( sf::Vector2f target )
{
	_position.x = target.x;
	_position.y = target.y;
}

void Camera::focusFollowedObject()
{
	if( _followObj )
		_position = _followObj->getCentre();

	//_refreshBoundary();
}

void Camera::releaseFocus()
{
	_followObj = 0;
}

void Camera::follow( GameObject* obj )
{
	_followObj = obj;
}

void Camera::activate( double screenWidth, double screenHeight )
{
	/*
	gluLookAt(	_position.x, _position.y, _position.z,
				_target.x, _target.y, _target.z,
				_upVector.x, _upVector.y, _upVector.z );
	*/
	_screenSize.x = (float)screenWidth;
	_screenSize.y = (float)screenHeight;

	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	//glOrtho( _position.x, _position.x + screenWidth, _position.y, _position.y + screenHeight, -1.0, 1.0 );
	glScalef( _zoomAmount, _zoomAmount, 0.0f );
	glOrtho( _position.x - screenWidth/2.0,		// left
			 _position.x + screenWidth/2.0,		// right
			 _position.y - screenHeight/2.0,	// bottom
			 _position.y + screenHeight/2.0,	// top
			 _nearClip, _farClip );
	//glMatrixMode( GL_MODELVIEW );
	//glLoadIdentity();

	//glLoadIdentity();
}

void Camera::setViewClip(double nearClip, double farClip)
{
	_nearClip = nearClip;
	_farClip  = farClip;
}

void Camera::zoom( float amount )
{
	_zoomAmount *= amount;
	//_refreshBoundary();
}

void Camera::pan( sf::Vector2f vec )
{
	_position.x += vec.x;
	_position.y += vec.y;
	//_refreshBoundary();
}

sf::Vector2f Camera::getPosition()
{
	return _position;
}

GameObject* Camera::getBoundary()
{
	_refreshBoundary();
	return _boundary;
}

void Camera::_refreshBoundary()
{
	_boundary->setSize( sf::Vector2f( _position.x - _screenSize.x/2.0f, _position.y + _screenSize.y/2.0f ),
						sf::Vector2f( _position.x - _screenSize.x/2.0f, _position.y - _screenSize.y/2.0f ),
						sf::Vector2f( _position.x + _screenSize.x/2.0f, _position.y - _screenSize.y/2.0f ),
						sf::Vector2f( _position.x + _screenSize.x/2.0f, _position.y + _screenSize.y/2.0f ) );
}