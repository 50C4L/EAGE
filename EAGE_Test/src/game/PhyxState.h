#ifndef _PHYXSTATE_H
#define _PHYXSTATE_H

#include "../../../src/helper/helper.h"


class PhyxState: public State
{
public:
			~PhyxState();
	
	void	enterFunc();
	void	control();
	void	leaveFunc();

	static PhyxState* getInstance();

protected:
	PhyxState();
	static PhyxState* _instance;

private:
	void	_spwanBox( float mouseX, float mouseY );

	GameObject*	_ground;
	GameObject* _block;
	GameObject* _poorBox;
	bool	_mlFlag;
	bool	_spaceFlag;
	bool	_lcrlFlag;
	bool	_blockFirstFlag;
};	// class PhyxState


#endif