#pragma once
#ifndef PROGRAM_OBJECT_H
#define PROGRAM_OBJECT_H

#include "../project_enums.h"
#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <gl/gl3w.h>
#include <GLFW/glfw3.h>
#include "shader_object.h"

struct UniformInfo
{
    std::string name;
    PinType type;

    UniformInfo(std::string name, PinType type)
    {
        this->name = name;
        this->type = type;
    }
};

class ProgramObject
{
public:
    ProgramObject(std::string object_name, GLuint object_id, std::shared_ptr<ShaderObject> vs, std::shared_ptr<ShaderObject> fs);
    ~ProgramObject();

    void FindAttributes();
    void FindUniforms();

    std::string object_name;
    GLuint object_id;
    std::shared_ptr<ShaderObject> vs;
    std::shared_ptr<ShaderObject> fs;
    std::vector< UniformInfo> uniforms_arr;

    int num_textures = 0;
    int current_texture = 0;
};

#endif

