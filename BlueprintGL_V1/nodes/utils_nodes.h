#pragma once
#include "node_function_interface.h"
#include "../nodes_builder.h"
#include "../utils.h"

class PrintString_Func : public NodeFunctions {
public:
    void Initialize();
    void Run();
    void Delete();
    void NoFlowUpdatePinsValues();
    void ChangePinType(PinKind kind, int index, PinType type);
};

std::shared_ptr<Node> PrintString(std::vector<std::shared_ptr<Node>>& s_Nodes);



class ConvertTo_Func : public NodeFunctions {
public:
    void Initialize();
    void Run();
    void Delete();
    void NoFlowUpdatePinsValues();
    void ChangePinType(PinKind kind, int index, PinType type);
};

std::shared_ptr<Node> ConvertTo(std::vector<std::shared_ptr<Node>>& s_Nodes);



void NodesUtilsSearchSetup(std::vector<SearchNodeObj>& search_nodes_vector);