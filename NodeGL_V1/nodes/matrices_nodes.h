#pragma once
#ifndef MATRICES_NODES_H
#define MATRICES_NODES_H

#include "node_function_interface.h"
#include "../nodes_builder.h"
#include "../utils.h"
#include "../InstanceConfig.h"

#include <gl/gl3w.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>


class Mat4IdentityNode_Func : public NodeFunctions {
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

std::shared_ptr<Node> Mat4IdentityNode(std::vector<std::shared_ptr<Node>>& s_Nodes);




class Mat4TranslateNode_Func : public NodeFunctions {
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

std::shared_ptr<Node> Mat4TranslateNode(std::vector<std::shared_ptr<Node>>& s_Nodes);




class Mat4RotateNode_Func : public NodeFunctions {
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

std::shared_ptr<Node> Mat4RotateNode(std::vector<std::shared_ptr<Node>>& s_Nodes);




class Mat4ScaleNode_Func : public NodeFunctions {
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

std::shared_ptr<Node> Mat4ScaleNode(std::vector<std::shared_ptr<Node>>& s_Nodes);




class OrthoProjNode_Func : public NodeFunctions {
public:
    void Initialize() {};
    void Run() {};
    void Delete();
    void NoFlowUpdatePinsValues();
    void UpdateNodeUI() {};
    void UpdateNodeInspector() {};
    void SaveNodeData(rapidjson::Writer<rapidjson::StringBuffer>& writer);
    void LoadNodeData(rapidjson::Value& node_obj);

    float p_left;
    float p_right;
    float p_bottom;
    float p_top;
    float p_zNear;
    float p_zFar;
};

std::shared_ptr<Node> OrthoProjNode(std::vector<std::shared_ptr<Node>>& s_Nodes);




class PerspectiveProjNode_Func : public NodeFunctions {
public:
    void Initialize() {};
    void Run() {};
    void Delete();
    void NoFlowUpdatePinsValues();
    void UpdateNodeUI() {};
    void UpdateNodeInspector() {};
    void SaveNodeData(rapidjson::Writer<rapidjson::StringBuffer>& writer);
    void LoadNodeData(rapidjson::Value& node_obj);

    float p_fovy;
    float p_width;
    float p_height;
    float p_zNear;
    float p_zFar;
};

std::shared_ptr<Node> PerspectiveProjNode(std::vector<std::shared_ptr<Node>>& s_Nodes);




class LookAtNode_Func : public NodeFunctions {
public:
    void Initialize() {};
    void Run() {};
    void Delete();
    void NoFlowUpdatePinsValues();
    void UpdateNodeUI() {};
    void UpdateNodeInspector() {};
    void SaveNodeData(rapidjson::Writer<rapidjson::StringBuffer>& writer);
    void LoadNodeData(rapidjson::Value& node_obj);

    glm::vec3 p_position;
    float p_yaw;
    float p_pitch;
    bool first_run = true;
};

std::shared_ptr<Node> LookAtNode(std::vector<std::shared_ptr<Node>>& s_Nodes);




void MatricesNodes_SearchSetup(std::vector<SearchNodeObj>& search_nodes_vector);
std::shared_ptr<Node> MatricesNodes_LoadSetup(std::vector<std::shared_ptr<Node>>& s_Nodes, std::string node_key);

#endif