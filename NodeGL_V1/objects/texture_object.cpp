#include "texture_object.h"

TextureObject::TextureObject(std::string object_name, GLuint object_id, int width, int height)
{
	this->object_name = object_name;
	this->object_id = object_id;
	this->width = width;
	this->height = height;
}

TextureObject::~TextureObject()
{
	glDeleteTextures(1, &object_id);
}
