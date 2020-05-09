#pragma once
#ifndef FLOW_NODES_H
#define FLOW_NODES_H

#include "node_function_interface.h"
#include "../nodes_builder.h"
#include "../utils.h"

class Sequence_Func : public NodeFunctions {
public:
    void Initialize();
    void Run();
    void Delete();
    void NoFlowUpdatePinsValues() {};
    void UpdateNodeUI() {};
    void UpdateNodeInspector();
};

std::shared_ptr<Node> SequenceNode(std::vector<std::shared_ptr<Node>>& s_Nodes);




class Branch_Func : public NodeFunctions {
public:
    void Initialize() {};
    void Run();
    void Delete();
    void NoFlowUpdatePinsValues() {};
    void UpdateNodeUI() {};
    void UpdateNodeInspector() {};
};

std::shared_ptr<Node> BranchNode(std::vector<std::shared_ptr<Node>>& s_Nodes);




class WhileLoop_Func : public NodeFunctions {
public:
    void Initialize() {};
    void Run();
    void Delete();
    void NoFlowUpdatePinsValues() {};
    void UpdateNodeUI() {};
    void UpdateNodeInspector() {};
};

std::shared_ptr<Node> WhileLoopNode(std::vector<std::shared_ptr<Node>>& s_Nodes);




class ForLoop_Func : public NodeFunctions {
public:
    void Initialize() {};
    void Run();
    void Delete();
    void NoFlowUpdatePinsValues() {};
    void UpdateNodeUI() {};
    void UpdateNodeInspector() {};
};

std::shared_ptr<Node> ForLoopNode(std::vector<std::shared_ptr<Node>>& s_Nodes);




void FlowNodesSearchSetup(std::vector<SearchNodeObj>& search_nodes_vector);

#endif