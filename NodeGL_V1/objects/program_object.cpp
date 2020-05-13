#include "program_object.h"

ProgramObject::ProgramObject(std::string object_name, GLuint object_id, GLuint vertex_shader, GLuint fragment_shader)
{
	this->object_name = object_name;
	this->object_id = object_id;
	this->vertex_shader = vertex_shader;
	this->fragment_shader = fragment_shader;
}

ProgramObject::~ProgramObject()
{
	glDeleteProgram(object_id);
}
