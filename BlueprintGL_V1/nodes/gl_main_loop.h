#pragma once
#include "node_function_interface.h"
#include "../nodes_builder.h"
#include "../nodes_utils.h"

class GlMainLoop_Func : public NodeFunctions {
public:
    void Initialize();
    void Run();
    void Delete();
};

std::shared_ptr<Node> GlMainLoop(std::vector<std::shared_ptr<Node>>& s_Nodes);