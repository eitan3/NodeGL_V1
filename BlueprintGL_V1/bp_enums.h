#pragma once
#ifndef BP_ENUMS_H
#define BP_ENUMS_H


enum class PinType
{
    Unknown,
    Flow,
    Button,
    Bool,
    Int,
    Float,
    String,
    ProgramObject,
    VertexShaderObject,
    FragmentShaderObject,
    TextureObject,
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