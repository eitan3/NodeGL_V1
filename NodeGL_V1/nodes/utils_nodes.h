#pragma once
#ifndef UTILS_NODES_H
#define UTILS_NODES_H

#include "node_function_interface.h"
#include "../nodes_builder.h"
#include "../utils.h"
#include "../objects/shader_object.h"
#include "../objects/program_object.h"
#include "../SpoutSDK/Spout.h"

class PrintString_Func : public NodeFunctions {
public:
    void Initialize();
    void Run();
    void Delete();
    void NoFlowUpdatePinsValues();
    void UpdateNodeUI() {};
    void UpdateNodeInspector() {};
};

std::shared_ptr<Node> PrintString(std::vector<std::shared_ptr<Node>>& s_Nodes);



class ConvertTo_Func : public NodeFunctions {
public:
    void Initialize();
    void Run();
    void Delete();
    void NoFlowUpdatePinsValues();
    void UpdateNodeUI() {};
    void UpdateNodeInspector() {};
};

std::shared_ptr<Node> ConvertTo(std::vector<std::shared_ptr<Node>>& s_Nodes);



class SetPlaceholder_Func : public NodeFunctions {
public:
    void Initialize();
    void Run();
    void Delete();
    void NoFlowUpdatePinsValues();
    void UpdateNodeUI() {};
    void UpdateNodeInspector();

    std::shared_ptr<BasePlaceholder> placeholder;
};

std::shared_ptr<Node> SetPlaceholder(std::vector<std::shared_ptr<Node>>& s_Nodes);



class GetPlaceholder_Func : public NodeFunctions {
public:
    void Initialize();
    void Run();
    void Delete();
    void NoFlowUpdatePinsValues();
    void UpdateNodeUI() {};
    void UpdateNodeInspector();

    std::shared_ptr<BasePlaceholder> placeholder;
    PinType placeholder_type;
};

std::shared_ptr<Node> GetPlaceholder(std::vector<std::shared_ptr<Node>>& s_Nodes);



class SpoutSender_Func : public NodeFunctions {
public:
    void Initialize();
    void Run();
    void Delete();
    void DeleteSpout();
    void NoFlowUpdatePinsValues() {};
    void UpdateNodeUI() {};
    void UpdateNodeInspector() {};

    SpoutSender spoutsender;
    bool bInitialized;
    int width;
    int height;
    std::string spout_name;
};

std::shared_ptr<Node> SpoutSenderNode(std::vector<std::shared_ptr<Node>>& s_Nodes);



class MakeFloat3_Func : public NodeFunctions {
public:
    void Initialize() {};
    void Run() {};
    void Delete();
    void NoFlowUpdatePinsValues();
    void UpdateNodeUI() {};
    void UpdateNodeInspector() {};
};

std::shared_ptr<Node> MakeFloat3Node(std::vector<std::shared_ptr<Node>>& s_Nodes);



class MakeFloat4_Func : public NodeFunctions {
public:
    void Initialize() {};
    void Run() {};
    void Delete();
    void NoFlowUpdatePinsValues();
    void UpdateNodeUI() {};
    void UpdateNodeInspector() {};
};

std::shared_ptr<Node> MakeFloat4Node(std::vector<std::shared_ptr<Node>>& s_Nodes);



class BreakFloat3_Func : public NodeFunctions {
public:
    void Initialize() {};
    void Run() {};
    void Delete();
    void NoFlowUpdatePinsValues();
    void UpdateNodeUI() {};
    void UpdateNodeInspector() {};
};

std::shared_ptr<Node> BreakFloat3Node(std::vector<std::shared_ptr<Node>>& s_Nodes);



class BreakFloat4_Func : public NodeFunctions {
public:
    void Initialize() {};
    void Run() {};
    void Delete();
    void NoFlowUpdatePinsValues();
    void UpdateNodeUI() {};
    void UpdateNodeInspector() {};
};

std::shared_ptr<Node> BreakFloat4Node(std::vector<std::shared_ptr<Node>>& s_Nodes);



void NodesUtilsSearchSetup(std::vector<SearchNodeObj>& search_nodes_vector);

#endif