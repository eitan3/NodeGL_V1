#pragma once
#include <memory>

struct Node;

class NodeFunctions {
public:
    virtual void Initialize() = 0;
    virtual void Run() = 0;
    virtual void Delete() = 0;
};