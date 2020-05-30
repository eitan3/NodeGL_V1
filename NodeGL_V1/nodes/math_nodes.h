#pragma once
#ifndef MATH_NODES_H
#define MATH_NODES_H

#include "node_function_interface.h"
#include "../nodes_builder.h"
#include "../utils.h"
#include <math.h>

class MathPlusNode_Func : public NodeFunctions {
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

std::shared_ptr<Node> MathPlusNode(std::vector<std::shared_ptr<Node>>& s_Nodes);



class MathMinusNode_Func : public NodeFunctions {
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

std::shared_ptr<Node> MathMinusNode(std::vector<std::shared_ptr<Node>>& s_Nodes);



class MathMultiplyNode_Func : public NodeFunctions {
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

std::shared_ptr<Node> MathMultiplyNode(std::vector<std::shared_ptr<Node>>& s_Nodes);



class MathDivideNode_Func : public NodeFunctions {
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

std::shared_ptr<Node> MathDivideNode(std::vector<std::shared_ptr<Node>>& s_Nodes);



class MathSinNode_Func : public NodeFunctions {
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

std::shared_ptr<Node> MathSinNode(std::vector<std::shared_ptr<Node>>& s_Nodes);



class MathCosNode_Func : public NodeFunctions {
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

std::shared_ptr<Node> MathCosNode(std::vector<std::shared_ptr<Node>>& s_Nodes);



class MathToDegreesNode_Func : public NodeFunctions {
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

std::shared_ptr<Node> MathToDegreesNode(std::vector<std::shared_ptr<Node>>& s_Nodes);



class MathToRadiansNode_Func : public NodeFunctions {
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

std::shared_ptr<Node> MathToRadiansNode(std::vector<std::shared_ptr<Node>>& s_Nodes);



void MathNodesSearchSetup(std::vector<SearchNodeObj>& search_nodes_vector);
std::shared_ptr<Node> MathNodesLoadSetup(std::vector<std::shared_ptr<Node>>& s_Nodes, std::string node_key);

#endif