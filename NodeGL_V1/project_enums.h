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

    VectorI2,
    VectorI3,
    VectorI4,

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