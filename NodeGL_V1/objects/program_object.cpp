#include "program_object.h"

ProgramObject::ProgramObject(std::string object_name, GLuint object_id, std::shared_ptr<ShaderObject> vs, std::shared_ptr<ShaderObject> fs)
{
	this->object_name = object_name;
	this->object_id = object_id;
	this->vs = vs;
	this->fs = fs;
	FindAttributes();
	FindUniforms();
}

ProgramObject::~ProgramObject()
{
	glDeleteProgram(object_id);
}

void ProgramObject::FindAttributes()
{
	GLint i;
	GLint count;

	GLint size; // size of the variable
	GLenum type; // type of the variable (float, vec3 or mat4, etc)
	
	const GLsizei bufSize = 64; // maximum name length
	GLchar name[bufSize]; // variable name in GLSL
	GLsizei length; // name length

	glGetProgramiv(object_id, GL_ACTIVE_ATTRIBUTES, &count);
	for (i = 0; i < count; i++)
	{
		glGetActiveAttrib(object_id, (GLuint)i, bufSize, &length, &size, &type, name);
		//printf("Attribute #%d Type: %u Name: %s\n", i, type, name);
		//std::cout << (GL_FLOAT_VEC3 == type) << std::endl;
	}

}

void ProgramObject::FindUniforms()
{
	GLint i;
	GLint count;

	GLint size; // size of the variable
	GLenum type; // type of the variable (float, vec3 or mat4, etc)
	
	const GLsizei bufSize = 64; // maximum name length
	GLchar name[bufSize]; // variable name in GLSL
	GLsizei length; // name length

	glGetProgramiv(object_id, GL_ACTIVE_UNIFORMS, &count);
	for (i = 0; i < count; i++)
	{
		glGetActiveUniform(object_id, (GLuint)i, bufSize, &length, &size, &type, name);
		PinType pin_type;
		if (type == GL_BOOL)
		{
			printf("Uniform #%d Type: Bool Name: %s\n", i, name);
			uniforms_arr.push_back(UniformInfo(std::string(name), PinType::Bool));
		}
		else if (type == GL_INT)
		{
			uniforms_arr.push_back(UniformInfo(std::string(name), PinType::Int));
		}
		else if (type == GL_FLOAT)
		{
			uniforms_arr.push_back(UniformInfo(std::string(name), PinType::Float));
		}
		else if (type == GL_INT_VEC2)
		{
			uniforms_arr.push_back(UniformInfo(std::string(name), PinType::VectorI2));
		}
		else if (type == GL_INT_VEC3)
		{
			uniforms_arr.push_back(UniformInfo(std::string(name), PinType::VectorI3));
		}
		else if (type == GL_INT_VEC4)
		{
			uniforms_arr.push_back(UniformInfo(std::string(name), PinType::VectorI4));
		}
		else if (type == GL_FLOAT_VEC2)
		{
			uniforms_arr.push_back(UniformInfo(std::string(name), PinType::Vector2));
		}
		else if (type == GL_FLOAT_VEC3)
		{
			uniforms_arr.push_back(UniformInfo(std::string(name), PinType::Vector3));
		}
		else if (type == GL_FLOAT_VEC4)
		{
			uniforms_arr.push_back(UniformInfo(std::string(name), PinType::Vector4));
		}
		else if (type == GL_FLOAT_MAT4)
		{
			uniforms_arr.push_back(UniformInfo(std::string(name), PinType::Matrix4x4));
		}
		else if (type == GL_SAMPLER_2D)
		{
			uniforms_arr.push_back(UniformInfo(std::string(name), PinType::TextureObject));
			num_textures++;
		}
		else
		{
			printf("Uniform #%d Type: %u Name: %s\n", i, type, name);
		}
	}

}
