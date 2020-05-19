#pragma once
#ifndef VEC3_NODES_H
#define VEC3_NODES_H

#include <glm/gtc/type_ptr.hpp>
#include "node_function_interface.h"
#include "../nodes_builder.h"
#include "../utils.h"

class MakeVector3_Func : public NodeFunctions {
public:
    void Initialize() {};
    void Run() {};
    void Delete();
    void NoFlowUpdatePinsValues();
    void UpdateNodeUI() {};
    void UpdateNodeInspector() {};
    void SaveNodeData(rapidjson::Writer<rapidjson::StringBuffer>& writer);
    void LoadNodeData(rapidjson::Value& node_obj);
};

std::shared_ptr<Node> MakeVector3Node(std::vector<std::shared_ptr<Node>>& s_Nodes);



class BreakVector3_Func : public NodeFunctions {
public:
    void Initialize() {};
    void Run() {};
    void Delete();
    void NoFlowUpdatePinsValues();
    void UpdateNodeUI() {};
    void UpdateNodeInspector() {};
    void SaveNodeData(rapidjson::Writer<rapidjson::StringBuffer>& writer);
    void LoadNodeData(rapidjson::Value& node_obj);
};

std::shared_ptr<Node> BreakVector3Node(std::vector<std::shared_ptr<Node>>& s_Nodes);



void Vec3NodesSearchSetup(std::vector<SearchNodeObj>& search_nodes_vector);
std::shared_ptr<Node> Vec3NodesLoadSetup(std::vector<std::shared_ptr<Node>>& s_Nodes, std::string node_key);

#endif