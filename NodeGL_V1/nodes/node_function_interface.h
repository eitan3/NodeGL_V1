#pragma once
#ifndef NODE_FUNCTION_INTERFACE_H
#define NODE_FUNCTION_INTERFACE_H

#include <string>
#include <memory>
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>
#include "../project_enums.h"

class Node;

class NodeFunctions {
public:
    virtual void Initialize() = 0;
    virtual void Run(std::string called_pin) = 0;
    virtual void Delete() = 0;
    virtual void NoFlowUpdatePinsValues() = 0;
    virtual void UpdateNodeUI() = 0;
    virtual void UpdateNodeInspector() = 0;
    virtual void SaveNodeData(rapidjson::Writer<rapidjson::StringBuffer>& writer) = 0;
    virtual void LoadNodeData(rapidjson::Value& node_obj) = 0;

    std::shared_ptr<Node> parent_node;
};

#endif