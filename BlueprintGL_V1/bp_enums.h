#pragma once
#ifndef BP_ENUMS_H
#define BP_ENUMS_H


enum class PinType
{
    Unknown,
    Flow,
    Bool,
    Int,
    Float,
    String,
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
    Tree,
    Comment
};

#endif