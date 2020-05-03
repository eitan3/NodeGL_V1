#pragma once
#ifndef PROGRAM_OBJECT_H
#define PROGRAM_OBJECT_H

#include "../bp_enums.h"
#include <string>
#include <vector>
#include <gl/gl3w.h>
#include <GLFW/glfw3.h>

class ProgramObject
{
public:
    ProgramObject(std::string object_name, GLuint object_id, GLuint vertex_shader, GLuint fragment_shader);
    ~ProgramObject();

    std::string object_name;
    GLuint object_id;
    GLuint vertex_shader;
    GLuint fragment_shader;
};

#endif

