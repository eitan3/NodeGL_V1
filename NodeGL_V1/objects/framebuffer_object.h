#pragma once
#ifndef FRAMEBUFFER_OBJECT_H
#define FRAMEBUFFER_OBJECT_H

#include <string>
#include <vector>
#include <gl/gl3w.h>
#include <GLFW/glfw3.h>

class FrameBufferObject
{
public:
    FrameBufferObject(std::string object_name, GLuint object_id);
    ~FrameBufferObject();

    std::string object_name;
    GLuint object_id;
};

#endif

