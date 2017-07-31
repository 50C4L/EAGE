#include "LineEmitter.h"

LineEmitter::LineEmitter()
{
}

LineEmitter::~LineEmitter()
{
}

void LineEmitter::initialize()
{
	PARTICLE part;
	float x = -40.0f;
	for( int i = 0; i < 10; i++ )
	{
		x += 50.0f;
		part.position.pos.x = x;
		part.position.pos.y = 450.0f;
		part.position.layer = 0.0f;
		part.texcoord.s		= 0.0f;
		part.texcoord.t		= 0.0f;
		part.color.r		= 1.0f;
		part.color.g		= 0.0f;
		part.color.b		= 0.0f;
		part.color.a		= 1.0f;
		//part.physx.currentVelocity.y = (float)eage::randomFloat( (unsigned)eage::randomFloat( 0 ) );
		//part.physx.currentVelocity.x = (float)eage::randomFloat( 0 );
		_particles.push_back( part );
	}
	//_particles[1].physx.currentVelocity.x = 1.0f;
	//_particles[1].physx.currentVelocity.y = 0.0f;
	//_particles[2].physx.currentVelocity.x = 0.0f;
	//_particles[2].physx.currentVelocity.y = 1.0f;

	printf( "%d Particles is created.\n", _particles.size() );
}

void LineEmitter::update()
{
	std::for_each( _particles.begin(), _particles.end(), updater() );
}