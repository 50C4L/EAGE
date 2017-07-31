#ifndef _SKELETONSTATE_H
#define _SKELETONSTATE_H

#include "../../../src/helper/helper.h"

class SkeletonState:public State
{
public:
	void enterFunc();
	void control();
	void leaveFunc();

	static SkeletonState* getInstance();

private:
	SkeletonState();
	~SkeletonState();
	static SkeletonState* _instance;

	GameObject		*_part1, *_part2, *_part3;
	SkeletonNode	*_node1, *_node2, *_node3, *_currentNode;
};


#endif