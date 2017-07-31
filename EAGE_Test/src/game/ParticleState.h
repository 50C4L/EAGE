#ifndef _PARTICLESTATE_H
#define _PARTICLESTATE_H

#include "../../../src/helper/helper.h"
#include "LineEmitter.h"

class ParticleState:public State
{
public:
	~ParticleState();

	void enterFunc();
	void control();
	void leaveFunc();

	static ParticleState* getInstance();

private:
	ParticleState();
	static ParticleState* _instance;

	LineEmitter*	_lineEmit;
};

#endif