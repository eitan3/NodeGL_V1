#pragma once
#include "node_function_interface.h"
#include "../nodes_builder.h"
#include "../nodes_utils.h"

class DummyNode_Func : public NodeFunctions {
public:
    void Initialize();
    void Run();
    void Delete();
};

std::shared_ptr<Node> DummyNode(std::vector<std::shared_ptr<Node>>& s_Nodes);



class DummySendFloat_Func : public NodeFunctions {
public:
    void Initialize();
    void Run();
    void Delete();
};

std::shared_ptr<Node> DummySendFloat(std::vector<std::shared_ptr<Node>>& s_Nodes);



class DummyRecvSendFloat_Func : public NodeFunctions {
public:
    void Initialize();
    void Run();
    void Delete();
};

std::shared_ptr<Node> DummyRecvSendFloat(std::vector<std::shared_ptr<Node>>& s_Nodes);



class DummyPrintFloat_Func : public NodeFunctions {
public:
    void Initialize();
    void Run();
    void Delete();
};

std::shared_ptr<Node> DummyPrintFloat(std::vector<std::shared_ptr<Node>>& s_Nodes);