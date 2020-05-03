#include "shader_object.h"

ShaderObject::ShaderObject(std::string object_name, GLuint object_id, std::string shader_code, PinType type)
{
	this->object_name = object_name;
	this->object_id = object_id;
	this->shader_code = shader_code;
	this->type = type;
}

ShaderObject::~ShaderObject()
{
	glDeleteShader(object_id);
}
