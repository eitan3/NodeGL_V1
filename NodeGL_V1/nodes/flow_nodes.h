#pragma once
#ifndef FLOW_NODES_H
#define FLOW_NODES_H

#include "node_function_interface.h"
#include "../nodes_builder.h"
#include "../utils.h"

class Sequence_Func : public NodeFunctions {
public:
    void Initialize();
    void Run(std::string called_pin);
    void Delete();
    void NoFlowUpdatePinsValues() {};
    void UpdateNodeUI() {};
    void UpdateNodeInspector();
    void SaveNodeData(rapidjson::Writer<rapidjson::StringBuffer>& writer);
    void LoadNodeData(rapidjson::Value& node_obj);
};

std::shared_ptr<Node> SequenceNode(std::vector<std::shared_ptr<Node>>& s_Nodes);




class Branch_Func : public NodeFunctions {
public:
    void Initialize() {};
    void Run(std::string called_pin);
    void Delete();
    void NoFlowUpdatePinsValues() {};
    void UpdateNodeUI() {};
    void UpdateNodeInspector() {};
    void SaveNodeData(rapidjson::Writer<rapidjson::StringBuffer>& writer);
    void LoadNodeData(rapidjson::Value& node_obj);
};

std::shared_ptr<Node> BranchNode(std::vector<std::shared_ptr<Node>>& s_Nodes);




class WhileLoop_Func : public NodeFunctions {
public:
    void Initialize() {};
    void Run(std::string called_pin);
    void Delete();
    void NoFlowUpdatePinsValues() {};
    void UpdateNodeUI() {};
    void UpdateNodeInspector() {};
    void SaveNodeData(rapidjson::Writer<rapidjson::StringBuffer>& writer);
    void LoadNodeData(rapidjson::Value& node_obj);
};

std::shared_ptr<Node> WhileLoopNode(std::vector<std::shared_ptr<Node>>& s_Nodes);




class ForLoop_Func : public NodeFunctions {
public:
    void Initialize() {};
    void Run(std::string called_pin);
    void Delete();
    void NoFlowUpdatePinsValues() {};
    void UpdateNodeUI() {};
    void UpdateNodeInspector() {};
    void SaveNodeData(rapidjson::Writer<rapidjson::StringBuffer>& writer);
    void LoadNodeData(rapidjson::Value& node_obj);
};

std::shared_ptr<Node> ForLoopNode(std::vector<std::shared_ptr<Node>>& s_Nodes);




class RunEveryXSeconds_Func : public NodeFunctions {
public:
    void Initialize() {};
    void Run(std::string called_pin);
    void Delete();
    void NoFlowUpdatePinsValues() {};
    void UpdateNodeUI() {};
    void UpdateNodeInspector() {};
    void SaveNodeData(rapidjson::Writer<rapidjson::StringBuffer>& writer);
    void LoadNodeData(rapidjson::Value& node_obj);

private:
    float timer;
    float prev_seconds;
};

std::shared_ptr<Node> RunEveryXSecondsNode(std::vector<std::shared_ptr<Node>>& s_Nodes);




void FlowNodesSearchSetup(std::vector<SearchNodeObj>& search_nodes_vector);
std::shared_ptr<Node> FlowNodesLoadSetup(std::vector<std::shared_ptr<Node>>& s_Nodes, std::string node_key);

#endif