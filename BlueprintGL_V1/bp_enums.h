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
    Delegate,
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