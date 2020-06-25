#pragma once
#ifndef ARRAYS_NODES_H
#define ARRAYS_NODES_H

#include "node_function_interface.h"
#include "../nodes_builder.h"
#include "../utils.h"



class GetArrayNode_Func : public NodeFunctions {
public:
    void Initialize();
    void Run(std::string called_pin) {};
    void Delete();
    void NoFlowUpdatePinsValues();
    void UpdateNodeUI() {};
    void UpdateNodeInspector();
    void SaveNodeData(rapidjson::Writer<rapidjson::StringBuffer>& writer);
    void LoadNodeData(rapidjson::Value& node_obj);

    std::shared_ptr<BaseArray> arrayPH;
    PinType arrayPH_type;
};

std::shared_ptr<Node> GetArrayNode(std::vector<std::shared_ptr<Node>>& s_Nodes);



class GetArraySizeNode_Func : public NodeFunctions {
public:
    void Initialize() {};
    void Run(std::string called_pin) {};
    void Delete();
    void NoFlowUpdatePinsValues();
    void UpdateNodeUI() {};
    void UpdateNodeInspector() {};
    void SaveNodeData(rapidjson::Writer<rapidjson::StringBuffer>& writer) {};
    void LoadNodeData(rapidjson::Value& node_obj) {};

};

std::shared_ptr<Node> GetArraySizeNode(std::vector<std::shared_ptr<Node>>& s_Nodes);



class ArrayInsertNode_Func : public NodeFunctions {
public:
    void Initialize() {};
    void Run(std::string called_pin);
    void Delete();
    void NoFlowUpdatePinsValues() {};
    void UpdateNodeUI();
    void UpdateNodeInspector() {};
    void SaveNodeData(rapidjson::Writer<rapidjson::StringBuffer>& writer) {};
    void LoadNodeData(rapidjson::Value& node_obj) {};
};

std::shared_ptr<Node> ArrayInsertNode(std::vector<std::shared_ptr<Node>>& s_Nodes);



class ArrayInsertDefaultNode_Func : public NodeFunctions {
public:
    void Initialize() {};
    void Run(std::string called_pin);
    void Delete();
    void NoFlowUpdatePinsValues() {};
    void UpdateNodeUI();
    void UpdateNodeInspector() {};
    void SaveNodeData(rapidjson::Writer<rapidjson::StringBuffer>& writer) {};
    void LoadNodeData(rapidjson::Value& node_obj) {};
};

std::shared_ptr<Node> ArrayInsertDefaultNode(std::vector<std::shared_ptr<Node>>& s_Nodes);



class ArrayClearValuesNode_Func : public NodeFunctions {
public:
    void Initialize() {};
    void Run(std::string called_pin);
    void Delete();
    void NoFlowUpdatePinsValues() {};
    void UpdateNodeUI() {};
    void UpdateNodeInspector() {};
    void SaveNodeData(rapidjson::Writer<rapidjson::StringBuffer>& writer) {};
    void LoadNodeData(rapidjson::Value& node_obj) {};
};

std::shared_ptr<Node> ArrayClearValuesNode(std::vector<std::shared_ptr<Node>>& s_Nodes);



class ArrayClearDefaultValuesNode_Func : public NodeFunctions {
public:
    void Initialize() {};
    void Run(std::string called_pin);
    void Delete();
    void NoFlowUpdatePinsValues() {};
    void UpdateNodeUI() {};
    void UpdateNodeInspector() {};
    void SaveNodeData(rapidjson::Writer<rapidjson::StringBuffer>& writer) {};
    void LoadNodeData(rapidjson::Value& node_obj) {};
};

std::shared_ptr<Node> ArrayClearDefaultValuesNode(std::vector<std::shared_ptr<Node>>& s_Nodes);



class ArrayClearToDefaultValuesNode_Func : public NodeFunctions {
public:
    void Initialize() {};
    void Run(std::string called_pin);
    void Delete();
    void NoFlowUpdatePinsValues() {};
    void UpdateNodeUI() {};
    void UpdateNodeInspector() {};
    void SaveNodeData(rapidjson::Writer<rapidjson::StringBuffer>& writer) {};
    void LoadNodeData(rapidjson::Value& node_obj) {};
};

std::shared_ptr<Node> ArrayClearToDefaultValuesNode(std::vector<std::shared_ptr<Node>>& s_Nodes);



void ArraysNodesSearchSetup(std::vector<SearchNodeObj>& search_nodes_vector);
std::shared_ptr<Node> ArraysNodesLoadSetup(std::vector<std::shared_ptr<Node>>& s_Nodes, std::string node_key);



#endif