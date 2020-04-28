#pragma once
#ifndef TEXTUREOBJECT_H
#define TEXTUREOBJECT_H

#include <string>
#include <vector>
#include <gl/gl3w.h>
#include <GLFW/glfw3.h>

class TextureObject
{
public:
    TextureObject(std::string object_name, GLuint object_id, int width, int height);
    ~TextureObject();

    std::string object_name;
    GLuint object_id;
    int width;
    int height;
};

#endif