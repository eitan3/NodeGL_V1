#pragma once
#ifndef NODE_FUNCTION_INTERFACE_H
#define NODE_FUNCTION_INTERFACE_H

#include <memory>
#include "../bp_enums.h"

class Node;

class NodeFunctions {
public:
    virtual void Initialize() = 0;
    virtual void Run() = 0;
    virtual void Delete() = 0;
    virtual void NoFlowUpdatePinsValues() = 0;
    virtual void ChangePinType(PinKind kind, int index, PinType type) = 0;

    std::shared_ptr<Node> parent_node;
};

#endif