#include "helper.h"

ParticleFX::ParticleFX()
{
	_mode = EAGE_POINTS;
	setPhysx( false );
}

ParticleFX::~ParticleFX()
{
}

void ParticleFX::renderMode( EAGE_PARTICLE_MODE mode )
{
	_mode = mode;
}

void ParticleFX::render()
{
	if( !_particles.empty() && isEnable() )
	{
		glEnableClientState( GL_COLOR_ARRAY );
		//glVertexPointer( 3, GL_FLOAT, 0, &_particles[0].position );
		//glTexCoordPointer( 2, GL_FLOAT, 0, &_particles[0].texcoord );
		glVertexPointer( 3, GL_FLOAT, sizeof(Vertex), &_particles[0].position );
		glTexCoordPointer( 2, GL_FLOAT, sizeof(Texcoord), &_particles[0].texcoord );
		glColorPointer( 4, GL_FLOAT, sizeof(Color), &_particles[0].color );
		switch( _mode )
		{
		case EAGE_POINTS:
			{
				glDrawArrays( GL_POINTS, 0, _particles.size() );
				break;
			}
		case EAGE_TRIANGLES:
			{
				glDrawArrays( GL_TRIANGLES, 0, _particles.size()/3 );
				break;
			}
		default:
			break;
		}
		glDisableClientState( GL_COLOR_ARRAY );
	}
}