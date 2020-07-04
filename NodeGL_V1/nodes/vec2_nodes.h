#pragma once
#ifndef VEC2_NODES_H
#define VEC2_NODES_H

#include <glm/gtc/type_ptr.hpp>
#include "node_function_interface.h"
#include "../nodes_builder.h"
#include "../utils.h"

class MakeVector2_Func : public NodeFunctions {
public:
    void Initialize() {};
    void Run(std::string called_pin) {};
    void Delete();
    void NoFlowUpdatePinsValues();
    void UpdateNodeUI() {};
    void UpdateNodeInspector() {};
    void SaveNodeData(rapidjson::Writer<rapidjson::StringBuffer>& writer);
    void LoadNodeData(rapidjson::Value& node_obj);
};

std::shared_ptr<Node> MakeVector2Node(std::vector<std::shared_ptr<Node>>& s_Nodes);



class BreakVector2_Func : public NodeFunctions {
public:
    void Initialize() {};
    void Run(std::string called_pin) {};
    void Delete();
    void NoFlowUpdatePinsValues();
    void UpdateNodeUI() {};
    void UpdateNodeInspector() {};
    void SaveNodeData(rapidjson::Writer<rapidjson::StringBuffer>& writer);
    void LoadNodeData(rapidjson::Value& node_obj);
};

std::shared_ptr<Node> BreakVector2Node(std::vector<std::shared_ptr<Node>>& s_Nodes);



class MakeVectorI2_Func : public NodeFunctions {
public:
    void Initialize() {};
    void Run(std::string called_pin) {};
    void Delete();
    void NoFlowUpdatePinsValues();
    void UpdateNodeUI() {};
    void UpdateNodeInspector() {};
    void SaveNodeData(rapidjson::Writer<rapidjson::StringBuffer>& writer);
    void LoadNodeData(rapidjson::Value& node_obj);
};

std::shared_ptr<Node> MakeVectorI2Node(std::vector<std::shared_ptr<Node>>& s_Nodes);



class BreakVectorI2_Func : public NodeFunctions {
public:
    void Initialize() {};
    void Run(std::string called_pin) {};
    void Delete();
    void NoFlowUpdatePinsValues();
    void UpdateNodeUI() {};
    void UpdateNodeInspector() {};
    void SaveNodeData(rapidjson::Writer<rapidjson::StringBuffer>& writer);
    void LoadNodeData(rapidjson::Value& node_obj);
};

std::shared_ptr<Node> BreakVectorI2Node(std::vector<std::shared_ptr<Node>>& s_Nodes);



class Vector2Normalize_Func : public NodeFunctions {
public:
    void Initialize() {};
    void Run(std::string called_pin) {};
    void Delete();
    void NoFlowUpdatePinsValues();
    void UpdateNodeUI() {};
    void UpdateNodeInspector() {};
    void SaveNodeData(rapidjson::Writer<rapidjson::StringBuffer>& writer);
    void LoadNodeData(rapidjson::Value& node_obj);
};

std::shared_ptr<Node> Vector2NormalizeNode(std::vector<std::shared_ptr<Node>>& s_Nodes);



void Vec2NodesSearchSetup(std::vector<SearchNodeObj>& search_nodes_vector);
std::shared_ptr<Node> Vec2NodesLoadSetup(std::vector<std::shared_ptr<Node>>& s_Nodes, std::string node_key);

#endif