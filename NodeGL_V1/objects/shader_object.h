#pragma once
#ifndef SHADER_OBJECT_H
#define SHADER_OBJECT_H

#include "../project_enums.h"
#include <string>
#include <vector>
#include <gl/gl3w.h>
#include <GLFW/glfw3.h>

class ShaderObject
{
public:
    ShaderObject(std::string object_name, GLuint object_id, std::string shader_code, PinType type);
    ~ShaderObject();

    std::string object_name;
    GLuint object_id;
    std::string shader_code;
    PinType type;
};

#endif
