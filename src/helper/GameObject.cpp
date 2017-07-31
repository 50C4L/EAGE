//#include "GameObject.h"
#include "../helper/helper.h"
#include "../math/PhysicsModule.h"

#define LT 0
#define LB 1
#define RB 2
#define RT 4
#define VERTEX_COUNT 6

// Friendly functions
bool eage::isCollidedAABB( GameObject* obj1, GameObject* obj2 )
{
	if( obj1->isEnable() && obj2->isEnable() )
		return obj1->_physxBody.aabb.isCollide( obj2->_physxBody.aabb );
	return false;
}

bool eage::isCollidedAABB( GameObject* obj, sf::Vector2f vec )
{
	if( obj->isEnable() )
		return obj->_physxBody.aabb.isCollide( vec );
	return false;
}

bool eage::isCollidedBS( GameObject* obj1, GameObject* obj2 )
{
	if( obj1->isEnable() && obj2->isEnable() )
		return obj1->_physxBody.bsphere.isCollide( obj2->_physxBody.bsphere );
	return false;
}

bool eage::isCollidedBS( GameObject* obj, sf::Vector2f vec )
{
	if( obj->isEnable() )
		return obj->_physxBody.bsphere.isCollide( vec );
	return false;
}

////////////////////////////////////////////////////////////////////////////////////////

GameObject::GameObject()
{
	_texid				= 0;
	_shaid				= 0;
	_renderOffset		= -1;
	_renderList			= -1;
	_shaderBlock		= -1;
	_layer = 0.0f;
	_physxBody.mass			= 1.0f;
	_physxBody.inertia		= 1.0f;
	_physxBody.currentSpeed	= 0.0f;
	_physxBody.maxSpeed		= 1000.0f;
	_physxBody.radius		= 0.0f;
	_physxBody.IsDynamic	= true;
	_isEnable = true;
	_isCaculusPhysx = true;

	_oldAngle = 0.f;
	_bodyDef.fixedRotation = true;
	_fixtureDef.shape = &_shape;
	_fixtureDef.density = 1.0f;
	_fixtureDef.friction = 0.5f;
	_bodyDef.type = b2_dynamicBody;
}

GameObject::~GameObject()
{
	if( _body )
		_body->GetWorld()->DestroyBody( _body );
}


void GameObject::createB2DBody()
{
	_body = PhysicsModule::getInstance()->getWorld()->CreateBody( &_bodyDef );
	_body->SetUserData( this );
	_body->CreateFixture( &_fixtureDef );
}


void GameObject::scaleAABB( float value )
{
	_physxBody.aabb.scale( value );
}

void GameObject::setTexture( int id )
{
	_texid = id;
}

void GameObject::setShader( int id )
{
	_shaid = id;
}

void GameObject::setPhysx( bool flag )
{
	_isCaculusPhysx = flag;
}

bool GameObject::isPhysx()
{
	return _isCaculusPhysx;
}


// This function creates a binding box with the same size for physics simulation
void GameObject::setSize( sf::Vector2f position, sf::Vector2f relCentral )
{
	sf::Vector2f scale = eage::getResolutionScale();
	sf::Vector2f actualPos = sf::Vector2f( position.x * scale.x, position.y * scale.y );
	sf::Vector2f actualCen = sf::Vector2f( relCentral.x * scale.x, relCentral.y * scale.y );
	_CT = actualPos;

	// left top vertex
	Vertex temp;
	temp.pos	= sf::Vector2f( actualPos.x-actualCen.x, actualPos.y+actualCen.y );
	temp.layer	= _layer;
	_LT.pos		= temp;
	_LT.uv.s	= 0.0f; 
	_LT.uv.t	= 1.0f;
	_LT.color.r = 1.0f; 
	_LT.color.g = 1.0f; 
	_LT.color.b = 1.0f; 
	_LT.color.a = 1.0f;

	// left bottom vertex
	temp.pos	= sf::Vector2f( actualPos.x-actualCen.x, actualPos.y-actualCen.y );
	_LB.pos		= temp;
	_LB.uv.s = 0.0f; 
	_LB.uv.t = 0.0f;
	_LB.color.r = 1.0f; 
	_LB.color.g = 1.0f; 
	_LB.color.b = 1.0f; 
	_LB.color.a = 1.0f;

	// right bottom vertex
	temp.pos	= sf::Vector2f( actualPos.x+actualCen.x, actualPos.y-actualCen.y );
	_RB.pos		= temp;
	_RB.uv.s = 1.0f; 
	_RB.uv.t = 0.0f;
	_RB.color.r = 1.0f; 
	_RB.color.g = 1.0f; 
	_RB.color.b = 1.0f; 
	_RB.color.a = 1.0f;

	// right top vertex
	temp.pos	= sf::Vector2f( actualPos.x+actualCen.x, actualPos.y+actualCen.y );
	_RT.pos		= temp;
	_RT.uv.s = 1.0f; 
	_RT.uv.t = 1.0f;
	_RT.color.r = 1.0f; 
	_RT.color.g = 1.0f; 
	_RT.color.b = 1.0f; 
	_RT.color.a = 1.0f;

	// using central point coordinate to create a default binding box
	_bodyDef.position = b2Vec2( actualPos.x/B2D_COORD_SCALE, actualPos.y/B2D_COORD_SCALE );
	_shape.SetAsBox( actualCen.x/B2D_COORD_SCALE, actualCen.y/B2D_COORD_SCALE );
}



void GameObject::setSize( float ltx, float lty, float lbx, float lby, float rbx, float rby, float rtx, float rty )
{
	Vertex temp;
	temp.pos.x = ltx;
	temp.pos.y = lty;
	temp.layer = _layer;
	_LT.pos = temp;
	_LT.uv.s = 0.0f; 
	_LT.uv.t = 1.0f;
	_LT.color.r = 1.0f; 
	_LT.color.g = 1.0f; 
	_LT.color.b = 1.0f; 
	_LT.color.a = 1.0f;
	
	temp.pos.x = lbx;
	temp.pos.y = lby;
	_LB.pos = temp;
	_LB.uv.s = 0.0f; 
	_LB.uv.t = 0.0f;
	_LB.color.r = 1.0f; 
	_LB.color.g = 1.0f; 
	_LB.color.b = 1.0f; 
	_LB.color.a = 1.0f;


	temp.pos.x = rbx;
	temp.pos.y = rby;
	_RB.pos = temp;
	_RB.uv.s = 1.0f; 
	_RB.uv.t = 0.0f;
	_RB.color.r = 1.0f; 
	_RB.color.g = 1.0f; 
	_RB.color.b = 1.0f; 
	_RB.color.a = 1.0f;

	temp.pos.x = rtx;
	temp.pos.y = rty;
	_RT.pos = temp;
	_RT.uv.s = 1.0f; 
	_RT.uv.t = 1.0f;
	_RT.color.r = 1.0f; 
	_RT.color.g = 1.0f; 
	_RT.color.b = 1.0f; 
	_RT.color.a = 1.0f;

	_calculateCenter();

	//this->_createAABB();
	//this->_createBSphere();
}

void GameObject::setSize( sf::Vector2f leftTop, sf::Vector2f leftBottom, sf::Vector2f rightBottom, sf::Vector2f rightTop )
{
	Vertex temp;
	temp.pos = leftTop;
	temp.layer = _layer;
	_LT.pos = temp;
	_LT.uv.s = 0.0f; 
	_LT.uv.t = 1.0f;
	_LT.color.r = 1.0f; 
	_LT.color.g = 1.0f; 
	_LT.color.b = 1.0f; 
	_LT.color.a = 1.0f;
	
	temp.pos = leftBottom;
	_LB.pos = temp;
	_LB.uv.s = 0.0f; 
	_LB.uv.t = 0.0f;
	_LB.color.r = 1.0f; 
	_LB.color.g = 1.0f; 
	_LB.color.b = 1.0f; 
	_LB.color.a = 1.0f;

	temp.pos = rightBottom;
	_RB.pos = temp;
	_RB.uv.s = 1.0f; 
	_RB.uv.t = 0.0f;
	_RB.color.r = 1.0f; 
	_RB.color.g = 1.0f; 
	_RB.color.b = 1.0f; 
	_RB.color.a = 1.0f;

	temp.pos = rightTop;
	_RT.pos = temp;
	_RT.uv.s = 1.0f; 
	_RT.uv.t = 1.0f;
	_RT.color.r = 1.0f; 
	_RT.color.g = 1.0f; 
	_RT.color.b = 1.0f; 
	_RT.color.a = 1.0f;

	_calculateCenter();

	// create bounding object
	//this->_createAABB();
	//this->_createBSphere();
}

void GameObject::setUV( VO_uvCoordinate uvs )
{
	//_uv = uvs;
	Texcoord temp;
	temp.s = uvs.leftTop.x; temp.t = uvs.leftTop.y;
	_LT.uv = temp;

	temp.s = uvs.leftBottom.x; temp.t = uvs.leftBottom.y;
	_LB.uv = temp;

	temp.s = uvs.rightBottom.x; temp.t = uvs.rightBottom.y;
	_RB.uv = temp;

	temp.s = uvs.rightTop.x; temp.t = uvs.rightTop.y;
	_RT.uv = temp;
}

void GameObject::updateUV(  VO_uvCoordinate uvs  )
{
	Texcoord temp;
	temp.s = uvs.leftTop.x; temp.t = uvs.leftTop.y;
	_LT.uv = temp;
	
	temp.s = uvs.leftBottom.x; temp.t = uvs.leftBottom.y;
	_LB.uv = temp;
	
	temp.s = uvs.rightBottom.x; temp.t = uvs.rightBottom.y;
	_RB.uv = temp;
	
	temp.s = uvs.rightTop.x; temp.t = uvs.rightTop.y;
	_RT.uv = temp;

	eage::updateVertex( _shaderBlock, _renderList, _renderOffset,	_LT.uv );
	eage::updateVertex( _shaderBlock, _renderList, _renderOffset+5, _LT.uv );
	eage::updateVertex( _shaderBlock, _renderList, _renderOffset+1, _LB.uv );
	eage::updateVertex( _shaderBlock, _renderList, _renderOffset+2, _RB.uv );
	eage::updateVertex( _shaderBlock, _renderList, _renderOffset+3, _RB.uv );
	eage::updateVertex( _shaderBlock, _renderList, _renderOffset+4, _RT.uv );
}

void GameObject::setLayer( float layer )
{
	_LT.pos.layer = layer;
	_LB.pos.layer = layer;
	_RB.pos.layer = layer;
	_RT.pos.layer = layer;
	_layer = layer;
}

void GameObject::setEnable( bool flag )
{
	_isEnable = flag;
}

void GameObject::setTranslate( float x, float y )
{
	_transform.translate( x, y );
	_LT.pos.pos = _transform * _LT.pos.pos;
	_LB.pos.pos = _transform * _LB.pos.pos;
	_RB.pos.pos = _transform * _RB.pos.pos;
	_RT.pos.pos = _transform * _RT.pos.pos;
	_CT = _transform * _CT;

	//_physxBody.aabb.translate( sf::Vector2f(x,y) );
	//_calculateCenter();
	//_createBSphere();
	this->setIdentity();

	if( _renderOffset != -1 )
		_updateVert();
}

void GameObject::setTranslate( sf::Vector2f newPosition )
{
	sf::Vector2f value = newPosition - _CT;
	_transform.translate( value );
	_LT.pos.pos = _transform * _LT.pos.pos;
	_LB.pos.pos = _transform * _LB.pos.pos;
	_RB.pos.pos = _transform * _RB.pos.pos;
	_RT.pos.pos = _transform * _RT.pos.pos;
	_CT = _transform * _CT;

	/*_physxBody.aabb.translate( pos );
	_calculateCenter();
	_createBSphere();*/
	this->setIdentity();

	if( _renderOffset != -1 )
		_updateVert();
}

void GameObject::setRotate( float angle )
{
	_transform.rotate( angle );
	_LT.pos.pos = _transform * _LT.pos.pos;
	_LB.pos.pos = _transform * _LB.pos.pos;
	_RB.pos.pos = _transform * _RB.pos.pos;
	_RT.pos.pos = _transform * _RT.pos.pos;

	/*_calculateCenter();
	_createAABB();
	_createBSphere();*/

	this->setIdentity();
	if( _renderOffset != -1 )
		_updateVert();
}

void GameObject::setRotate( float angle, sf::Vector2f point )
{

	_transform.rotate( angle, point );
	_LT.pos.pos = _transform * _LT.pos.pos;
	_LB.pos.pos = _transform * _LB.pos.pos;
	_RB.pos.pos = _transform * _RB.pos.pos;
	_RT.pos.pos = _transform * _RT.pos.pos;
	_CT = _transform * _CT;

	/*_calculateCenter();
	_createAABB();
	_createBSphere();*/
	this->setIdentity();

	if( _renderOffset != -1 )
		_updateVert();
}


void GameObject::setRotation( float angle, sf::Vector2f point )
{

	float currentAngle = _oldAngle-angle;
	if( abs(currentAngle) < 0.0001f )
		currentAngle = 0.0f;

	_transform.rotate( currentAngle, point );
	_LT.pos.pos = _transform * _LT.pos.pos;
	_LB.pos.pos = _transform * _LB.pos.pos;
	_RB.pos.pos = _transform * _RB.pos.pos;
	_RT.pos.pos = _transform * _RT.pos.pos;
	_CT = _transform * _CT;

	/*_calculateCenter();
	_createAABB();
	_createBSphere();*/
	this->setIdentity();

	_oldAngle = angle;

	if( _renderOffset != -1 )
		_updateVert();
}


void GameObject::setRotate( sf::Transform trans )
{
	if( !_physxBody.IsDynamic )
		return;

	_LT.pos.pos = trans * _LT.pos.pos;
	_LB.pos.pos = trans * _LB.pos.pos;
	_RB.pos.pos = trans * _RB.pos.pos;
	_RT.pos.pos = trans * _RT.pos.pos;

	_calculateCenter();
	_createAABB();
	_createBSphere();
	if( _renderOffset != -1 )
		_updateVert();
}


void GameObject::setColor( float r, float g, float b, float a )
{
	Color temp = {r,g,b,a};
	_LT.color = temp;
	_LB.color = temp;
	_RB.color = temp;
	_RT.color = temp;

	if( _renderOffset != -1 )
		_updateVert();
}

void GameObject::setIdentity()
{
	_transform = sf::Transform::Identity;
}

void GameObject::render()
{
	std::vector<VertexAttribute> _vert;
	_vert.push_back( _LT );
	_vert.push_back( _LB );
	_vert.push_back( _RB );
	_vert.push_back( _RB );
	_vert.push_back( _RT );
	_vert.push_back( _LT );

	glVertexPointer( 3, GL_FLOAT, sizeof(VertexAttribute), &_vert[0].pos );
	glTexCoordPointer( 2, GL_FLOAT, sizeof(VertexAttribute), &_vert[0].uv );
	glColorPointer( 4, GL_FLOAT, sizeof(VertexAttribute), &_vert[0].color );
	glDrawArrays( GL_TRIANGLES, 0, 6 );

	_vert.clear();
}

int GameObject::getTexture()
{
	return _texid;
}

int GameObject::getShader()
{
	return _shaid;
}

bool GameObject::isEnable()
{
	return _isEnable;
}

bool GameObject::isDynamic()
{
	return _physxBody.IsDynamic;
}

//void GameObject::getVertices( sf::Vector2f &lt, sf::Vector2f &lb, sf::Vector2f &rb, sf::Vector2f &rt )
//{
//	lt = _vertices[LT].pos; lb = _vertices[LB].pos; rb = _vertices[RB].pos; rt = _vertices[RT].pos;
//}

sf::Vector2f GameObject::getCentre()
{
	return _CT;
}

sf::Vector2f GameObject::getHistory()
{
	return _physxBody.history;
}

void GameObject::setMass( float value )
{
	_physxBody.mass = value;
}

void GameObject::setAcceleration( sf::Vector2f vector )
{
	_physxBody.acceleration = vector;
}

void GameObject::setUniform( sf::Vector2f vector )
{
	_physxBody.uniform = vector;
}

void GameObject::setInertia( float value )
{
	_physxBody.inertia = value;
}

void GameObject::setRadius( float value )
{
	_physxBody.radius = value;
}

void GameObject::setCurrentSpeed( float value )
{
	_physxBody.currentSpeed = value;
}

void GameObject::setMaxSpeed( float value )
{
	_physxBody.maxSpeed = value;
}

void GameObject::setDynamic( bool value )
{
	//_physxBody.IsDynamic = value;
	if( value )		
		_bodyDef.type = b2_dynamicBody;
	else
		_bodyDef.type = b2_staticBody;
}


// Functions for Box2D
/* use customized b2FixtureDef to initialize body
** @param	bodyDef pass instance of customized b2BodyDef
*/
void GameObject::initialBox2DFixture(b2BodyDef bodyDef )
{
	_bodyDef	= bodyDef;
}


void GameObject::setLinearVelocity( float x, float y )
{
	b2Vec2 value = _body->GetLinearVelocity();

	value.x = x;
	value.y = y;
	_body->SetLinearVelocity( value );
}


void GameObject::setLinearImpulse( float x, float y )
{
	if( _body )
	{
		b2Vec2 dir = b2Vec2( x, y );
		b2Vec2 pos = _body->GetWorldCenter();
		_body->ApplyLinearImpulse( dir, pos );
	}
}


void GameObject::setTransform( float x, float y )
{
	b2Vec2 dir = b2Vec2( x/B2D_COORD_SCALE, y/B2D_COORD_SCALE );
	_body->SetTransform( dir, 0.f ); 
}


void GameObject::setForce( float x, float y )
{
	b2Vec2 dir = b2Vec2( x, y );
	b2Vec2 pos = _body->GetWorldCenter();
	_body->ApplyForce( dir, pos );
}


void GameObject::setFixedRotation( bool flag )
{
	//_body->SetFixedRotation( flag );
	_bodyDef.fixedRotation = flag;
}


void GameObject::setFriction( float friction )
{
	_fixtureDef.friction = friction;
}


void GameObject::setDensity( float density )
{
	_fixtureDef.density = density;
}


void GameObject::setGravityScale( float scale )
{
	_body->SetGravityScale( scale );
}


VertexAttribute GameObject::getVertexAttrit( int flag )
{
	switch( flag )
	{
	case 0:
		return _LT;
		break;
	case 1:
		return _LB;
		break;
	case 2:
		return _RB;
		break;
	case 3:
		return _RT;
		break;
	default:
		return VertexAttribute();
		break;
	}
}



// OLD SHITS
//-------------------------------------------------------------------------
void GameObject::_createAABB()
{
	//sf::Vector2f lt,lb,rb,rt;
	//this->getVertices( lt, lb, rb, rt );
	
	_physxBody.aabb.addVertex( _LT.pos.pos );
	_physxBody.aabb.addVertex( _LB.pos.pos );
	_physxBody.aabb.addVertex( _RB.pos.pos );
	_physxBody.aabb.addVertex( _RT.pos.pos );
}

void GameObject::_createBSphere()
{
	_physxBody.bsphere.create( _CT, _physxBody.radius );
}

void GameObject::_calculateCenter()
{
	//_CT = (_vertices[RT].pos - _vertices[LB].pos)/2.0f + _vertices[LB].pos;
	_CT = (_RT.pos.pos - _LB.pos.pos)/2.0f + _LB.pos.pos;
}

bool GameObject::isInsertAABB( sf::Vector2f p )
{
	if( _physxBody.aabb.isCollide( p ) )
		return true;
	else 
		return false;
}

bool GameObject::isInsertBSphere( sf::Vector2f p )
{
	if( _physxBody.bsphere.isCollide( p ) )
		return true;
	else
		return false;
}

float GameObject::getLayer() const
{
	return _layer;
}

bool GameObject::operator<( const GameObject &obj )
{
	return _layer < obj.getLayer();
}

void GameObject::_updateVert()
{
	eage::updateVertex( _shaderBlock, _renderList, _renderOffset,	_LT );
	eage::updateVertex( _shaderBlock, _renderList, _renderOffset+5, _LT );
	eage::updateVertex( _shaderBlock, _renderList, _renderOffset+1, _LB );
	eage::updateVertex( _shaderBlock, _renderList, _renderOffset+2, _RB );
	eage::updateVertex( _shaderBlock, _renderList, _renderOffset+3, _RB );
	eage::updateVertex( _shaderBlock, _renderList, _renderOffset+4, _RT );
}