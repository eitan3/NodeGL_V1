#pragma once
#ifndef RENDERBUFFER_OBJECT_H
#define RENDERBUFFER_OBJECT_H

#include <string>
#include <vector>
#include <gl/gl3w.h>
#include <GLFW/glfw3.h>

class RenderBufferObject
{
public:
    RenderBufferObject(std::string object_name, GLuint object_id, int width, int height);
    ~RenderBufferObject();

    std::string object_name;
    GLuint object_id;
    int width;
    int height;
};

#endif
