#include "framebuffer_object.h"

FrameBufferObject::FrameBufferObject(std::string object_name, GLuint object_id)
{
	this->object_name = object_name;
	this->object_id = object_id;
}

FrameBufferObject::~FrameBufferObject()
{
	glDeleteFramebuffers(1, &object_id);
}
