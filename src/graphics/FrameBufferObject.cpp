#include "FrameBufferObject.h"
#include "../helper/helper.h"

FrameBufferObject::FrameBufferObject( GLint width, GLint height, GLfloat filterMode  )
{
	_width	= width;
	_height	= height;
	_status	= false;

	// create a framebuffer object
	glGenFramebuffersEXT(1, &_fboId);
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, _fboId);

	// create a texture object
	glGenTextures( 1, &_texId );
	glBindTexture( GL_TEXTURE_2D, _texId );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filterMode );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filterMode );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
	//glBindTexture( GL_TEXTURE_2D, 0 );

	// attach the texture to FBO color attachment point
	glFramebufferTexture2DEXT( GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, _texId, 0 );

	// create a renderbuffer object to store depth info
	glGenRenderbuffersEXT( 1, &_rboId );
	glBindFramebuffer( GL_RENDERBUFFER_EXT, _rboId );
	glRenderbufferStorageEXT( GL_RENDERBUFFER_EXT, GL_DEPTH_COMPONENT24, _width, _height );
	glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, _rboId);
	//glBindRenderbuffer( GL_RENDERBUFFER, 0 );	
	

	// check FBO status
	GLenum status = glCheckFramebufferStatusEXT( GL_FRAMEBUFFER_EXT );
	eage::debug( "FBO[%d] status: %d\n", _fboId, status );
	if( status == GL_FRAMEBUFFER_COMPLETE_EXT )
		_status = true;

	// switch to system provided framebuffer
	glBindFramebufferEXT( GL_FRAMEBUFFER_EXT, 0 );
}

FrameBufferObject::~FrameBufferObject()
{
}

GLuint FrameBufferObject::getRTT()
{
	return _texId;
}

bool FrameBufferObject::getStatus()
{
	return _status;
}

void FrameBufferObject::begin()
{
	//glBindFramebuffer(GL_FRAMEBUFFER, _fboId);
	glBindFramebufferEXT( GL_FRAMEBUFFER_EXT, _fboId );
}

void FrameBufferObject::end()
{
	//glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
}