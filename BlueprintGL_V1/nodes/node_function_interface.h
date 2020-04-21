#pragma once
#include <memory>

class Node;

class NodeFunctions {
public:
    virtual void Initialize() = 0;
    virtual void Run() = 0;
    virtual void Delete() = 0;

    std::shared_ptr<Node> parent_node;
};