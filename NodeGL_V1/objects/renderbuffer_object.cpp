#include "renderbuffer_object.h"

RenderBufferObject::RenderBufferObject(std::string object_name, GLuint object_id, int width, int height)
{
	this->object_name = object_name;
	this->object_id = object_id;
	this->width = width;
	this->height = height;
}

RenderBufferObject::~RenderBufferObject()
{
	glDeleteRenderbuffers(1, &object_id);
}
