#pragma once
#ifndef PROJECT_ENUMS_H
#define PROJECT_ENUMS_H


enum class PinType
{
    Unknown,
    Flow,
    String,

    Bool,
    Int,
    Float,

    Vector2,
    Vector3,
    Vector4,
    Matrix4x4,

    ProgramObject,
    VertexShaderObject,
    FragmentShaderObject,
    TextureObject,
    MeshObject,
};

enum class PinKind
{
    Output,
    Input
};

enum class NodeType
{
    Blueprint,
    Simple,
    Comment
};

#endif