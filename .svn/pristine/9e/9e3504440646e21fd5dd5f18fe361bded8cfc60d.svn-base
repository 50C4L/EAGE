//#include "math.h"
//#include "../helper/helper.h"
#include "../helper/helper.h"
//#include <Windows.h>
#include <math.h>
#include <cstdlib>

/*
// FPS calculation
int Frames		= 0;
int UpdateTime	= 1000;
int LastTime	= 0;
double FPS		= 0.0;


// runs every frame
double eage::getFPS()
{
	Frames++;

	if( (int)GetTickCount() - LastTime > UpdateTime )
	{
		FPS = ((double)Frames/(double)(GetTickCount()-LastTime))*1000.0;
		LastTime = GetTickCount();
		Frames = 0;
	}
	return FPS;
}*/

//////////////////////////////////////////////////////////////////
float eage::getDistanceSquare( sf::Vector2f ptA, sf::Vector2f ptB )
{
	sf::Vector2f factor = ptA - ptB;
	float dist = factor.x*factor.x + factor.y*factor.y;
	return dist;
}


// calculate the angles from v1 to v2
float eage::getAngle( sf::Vector2f v1, sf::Vector2f v2 )
{
	//const float nyPi = (float)acos(-1.0);
	//float dot, angle;

	//// normalize
	//v1 = normalize(v1);
	//v2 = normalize(v2);
	//// dot product
	//dot = v1.x*v2.x + v1.y*v2.y;

	//if( fabs(dot-1.0) <= Epsilon )
	//	angle = 0.0f;
	//else if( fabs(dot+1.0) >= Epsilon )
	//	angle = nyPi;
	//else 
	//	angle = acos(dot);
	//
	//return angle;

	float angleV1, angleV2;
	angleV1 = std::atan2( v1.x, v1.y );
	angleV2 = std::atan2( v2.x, v2.y );

	return angleV2 - angleV1;

	/*sf::Vector2f dv;
	dv = v2 - v1;

	return atan2( dv.x, dv.y );*/
}


float eage::getRotationalAngle( sf::Vector2f v1, sf::Vector2f v2 )
{
	const float nyPi = (float)acos(-1.0);
	float dot, angle, degree;

	// normalize
	v1 = normalize(v1);
	v2 = normalize(v2);
	// dot product
	dot = v1.x*v2.x + v1.y*v2.y;

	if( fabs(dot-1.0) <= Epsilon )
		angle = 0.0f;
	else if( fabs(dot+1.0) >= Epsilon )
		angle = nyPi;
	else 
	{
		float cross;
		angle = acos(dot);
		// cross product
		cross = v1.x*v2.y - v2.x*v1.y;
		// v2 is clockwise from v1 with respect to the origin (0.0)
		if (cross < 0 )
			angle = 2 * nyPi - angle;
	}
	degree = angle *  180.0f / nyPi;
	return degree;
}



double eage::randomFloat( unsigned shift )
{
	srand((unsigned)eage::getElapsedMilliSec+shift);
	return rand()%3-1+(rand()%1000)/10000.0;
}



sf::Vector2f eage::normalize( sf::Vector2f v )
{
	float length = sqrt( v.x*v.x + v.y*v.y );

	return sf::Vector2f( v.x/length, v.y/length );
}