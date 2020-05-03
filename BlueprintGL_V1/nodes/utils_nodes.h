#pragma once
#ifndef UTILS_NODES_H
#define UTILS_NODES_H

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
    void PressButton(PinKind, int index) {};
    void UpdateUI() {};
};

std::shared_ptr<Node> PrintString(std::vector<std::shared_ptr<Node>>& s_Nodes);



class ConvertTo_Func : public NodeFunctions {
public:
    void Initialize();
    void Run();
    void Delete();
    void NoFlowUpdatePinsValues();
    void ChangePinType(PinKind kind, int index, PinType type);
    void PressButton(PinKind, int index) {};
    void UpdateUI() {};
};

std::shared_ptr<Node> ConvertTo(std::vector<std::shared_ptr<Node>>& s_Nodes);



class SetPlaceholder_Func : public NodeFunctions {
public:
    void Initialize();
    void Run();
    void Delete();
    void NoFlowUpdatePinsValues();
    void ChangePinType(PinKind kind, int index, PinType type);
    void PressButton(PinKind, int index) {};
    void UpdateUI() {};

    std::shared_ptr<BasePlaceholder> placeholder;
};

std::shared_ptr<Node> SetPlaceholder(std::vector<std::shared_ptr<Node>>& s_Nodes);



class GetPlaceholder_Func : public NodeFunctions {
public:
    void Initialize();
    void Run();
    void Delete();
    void NoFlowUpdatePinsValues();
    void ChangePinType(PinKind kind, int index, PinType type);
    void PressButton(PinKind, int index) {};
    void UpdateUI() {};

    std::shared_ptr<BasePlaceholder> placeholder;
    PinType placeholder_type;
};

std::shared_ptr<Node> GetPlaceholder(std::vector<std::shared_ptr<Node>>& s_Nodes);



void NodesUtilsSearchSetup(std::vector<SearchNodeObj>& search_nodes_vector);

#endif