#pragma once
#include "node_function_interface.h"
#include "../nodes_builder.h"

class DummyNode_Func : public NodeFunctions {
public:
    void Initialize();
    void Run();
    void Delete();

    std::shared_ptr<Node> parent_node;
};

std::shared_ptr<Node> DummyNode(std::vector<std::shared_ptr<Node>>& s_Nodes);