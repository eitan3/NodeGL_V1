#pragma once
#ifndef MATH_NODES_H
#define MATH_NODES_H

#include "node_function_interface.h"
#include "../nodes_builder.h"
#include "../utils.h"

class MathPlusNode_Func : public NodeFunctions {
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

std::shared_ptr<Node> MathPlusNode(std::vector<std::shared_ptr<Node>>& s_Nodes);



class MathMinusNode_Func : public NodeFunctions {
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

std::shared_ptr<Node> MathMinusNode(std::vector<std::shared_ptr<Node>>& s_Nodes);



class MathMultiplyNode_Func : public NodeFunctions {
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

std::shared_ptr<Node> MathMultiplyNode(std::vector<std::shared_ptr<Node>>& s_Nodes);



class MathDivideNode_Func : public NodeFunctions {
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

std::shared_ptr<Node> MathDivideNode(std::vector<std::shared_ptr<Node>>& s_Nodes);


// Binary Operations
class EqualNode_Func : public NodeFunctions {
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

std::shared_ptr<Node> EqualNode(std::vector<std::shared_ptr<Node>>& s_Nodes);



class NotEqualNode_Func : public NodeFunctions {
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

std::shared_ptr<Node> NotEqualNode(std::vector<std::shared_ptr<Node>>& s_Nodes);



class LessNode_Func : public NodeFunctions {
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

std::shared_ptr<Node> LessNode(std::vector<std::shared_ptr<Node>>& s_Nodes);



class LessEqualNode_Func : public NodeFunctions {
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

std::shared_ptr<Node> LessEqualNode(std::vector<std::shared_ptr<Node>>& s_Nodes);



class GreaterNode_Func : public NodeFunctions {
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

std::shared_ptr<Node> GreaterNode(std::vector<std::shared_ptr<Node>>& s_Nodes);



class GreaterEqualNode_Func : public NodeFunctions {
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

std::shared_ptr<Node> GreaterEqualNode(std::vector<std::shared_ptr<Node>>& s_Nodes);



class AndNode_Func : public NodeFunctions {
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

std::shared_ptr<Node> AndNode(std::vector<std::shared_ptr<Node>>& s_Nodes);



class OrNode_Func : public NodeFunctions {
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

std::shared_ptr<Node> OrNode(std::vector<std::shared_ptr<Node>>& s_Nodes);



class NotNode_Func : public NodeFunctions {
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

std::shared_ptr<Node> NotNode(std::vector<std::shared_ptr<Node>>& s_Nodes);



void MathNodesSearchSetup(std::vector<SearchNodeObj>& search_nodes_vector);
std::shared_ptr<Node> MathNodesLoadSetup(std::vector<std::shared_ptr<Node>>& s_Nodes, std::string node_key);

#endif