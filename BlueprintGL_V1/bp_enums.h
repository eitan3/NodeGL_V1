#pragma once


enum class PinType
{
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