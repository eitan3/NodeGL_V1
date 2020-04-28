#pragma once
#ifndef MATH_NODES_H
#define MATH_NODES_H

#include "node_function_interface.h"
#include "../nodes_builder.h"
#include "../utils.h"

class MathPlusNode_Func : public NodeFunctions {
public:
    void Initialize();
    void Run();
    void Delete();
    void NoFlowUpdatePinsValues();
    void ChangePinType(PinKind kind, int index, PinType type);
};

std::shared_ptr<Node> MathPlusNode(std::vector<std::shared_ptr<Node>>& s_Nodes);



class MathMinusNode_Func : public NodeFunctions {
public:
    void Initialize();
    void Run();
    void Delete();
    void NoFlowUpdatePinsValues();
    void ChangePinType(PinKind kind, int index, PinType type);
};

std::shared_ptr<Node> MathMinusNode(std::vector<std::shared_ptr<Node>>& s_Nodes);



class MathMultiplyNode_Func : public NodeFunctions {
public:
    void Initialize();
    void Run();
    void Delete();
    void NoFlowUpdatePinsValues();
    void ChangePinType(PinKind kind, int index, PinType type);
};

std::shared_ptr<Node> MathMultiplyNode(std::vector<std::shared_ptr<Node>>& s_Nodes);



class MathSubtractNode_Func : public NodeFunctions {
public:
    void Initialize();
    void Run();
    void Delete();
    void NoFlowUpdatePinsValues();
    void ChangePinType(PinKind kind, int index, PinType type);
};

std::shared_ptr<Node> MathSubtractNode(std::vector<std::shared_ptr<Node>>& s_Nodes);



void MathNodesSearchSetup(std::vector<SearchNodeObj>& search_nodes_vector);

#endif