#ifndef _LINEEMITTER_H
#define _LINEEMITTER_H

#include "../../../src/helper/helper.h"

class LineEmitter:public ParticleFX
{
public:
	LineEmitter();
	~LineEmitter();

	void initialize();
	void update();

private:
	struct updater
	{
		void operator()( PARTICLE &p )
		{
			//p.position.pos += p.physx.currentVelocity;
		}
	};
};

#endif