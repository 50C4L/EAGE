#ifndef _FBANIMOBJECT_H
#define _FBANIMOBJECT_H

#include <map>
#include <string>
#include "../helper/helper.h"

struct ANIM_INFO
{
	sf::Vector2f	start;
	float			height;
	double			totalTime;
	int				frame;
	//double			spf;	// *second per frame
	float			offset;	// *
	

	void operator=( ANIM_INFO info )
	{
		start		= info.start;
		offset		= info.offset;
		totalTime	= info.totalTime;
		//spf			= info.spf;
		frame		= info.frame;
		height		= info.height;
	};
};

class FBAnimObject:public VisibleObject
{
public:
			FBAnimObject();
	virtual ~FBAnimObject();

	virtual void update( float fps );

	int		addAnimation( int, ANIM_INFO );
	int		addAnimation( std::string );
	void	playAnimation( int );
	bool	isPlaying();

private:
	std::map<int,ANIM_INFO> _animList;
	ANIM_INFO				_currentAnim;
	int						_currentID;
	VO_uvCoordinate			_currentUV;
	int						_frameCount;
	int						_keyFrameCount;
	bool					_isPlaying;
	int						_animCount;

};	// class FBAnimObject

#endif	// _FBANIMOBJECT_H