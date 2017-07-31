#include "ParticleState.h"

ParticleState* ParticleState::_instance = 0;

ParticleState* ParticleState::getInstance()
{
	if( !_instance )	_instance = new ParticleState();
	return _instance;
}

ParticleState::ParticleState()
{
	_lineEmit = 0;
}

ParticleState::~ParticleState()
{
}

void ParticleState::enterFunc()
{
	eage::loadResourceIndices( "data/scenes/particleTest.res", EAGE_FROM_MEMORY );

	_lineEmit = new LineEmitter();
	_lineEmit->setTexture( 0 );
	_lineEmit->setShader( 1 );
	_lineEmit->initialize();
	this->addObject( _lineEmit );

	eage::setPostFXShader( 0 );
}

void ParticleState::control()
{
	_lineEmit->update();
}

void ParticleState::leaveFunc()
{
}