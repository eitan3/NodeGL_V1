#pragma once
#ifndef GL_NODES_1_H
#define GL_NODES_1_H

#include "node_function_interface.h"
#include "../nodes_builder.h"
#include "../utils.h"
#include "../InstanceConfig.h"

#include <gl/gl3w.h>
#include <GLFW/glfw3.h>

class GlMainLoop_Func : public NodeFunctions {
public:
    void Initialize();
    void Run(std::string called_pin);
    void Delete();
    void NoFlowUpdatePinsValues() {};
    void UpdateNodeUI() {};
    void UpdateNodeInspector();
    void SaveNodeData(rapidjson::Writer<rapidjson::StringBuffer>& writer);
    void LoadNodeData(rapidjson::Value& node_obj);

private:
    void SetupFrameBuffer();
    void DeleteFrameBuffer();

private:
    std::string object_prefix;
    int output_width;
    int output_height;

    char* current_min_param;
    char* current_mag_param;
    char* current_wrap_s;
    char* current_wrap_t;

    char* prev_min_param;
    char* prev_mag_param;
    char* prev_wrap_s;
    char* prev_wrap_t;
};

std::shared_ptr<Node> GlMainLoop(std::vector<std::shared_ptr<Node>>& s_Nodes);



class GlClear_Func : public NodeFunctions {
public:
    void Initialize();
    void Run(std::string called_pin);
    void Delete();
    void NoFlowUpdatePinsValues() {};
    void UpdateNodeUI() {};
    void UpdateNodeInspector() {};
    void SaveNodeData(rapidjson::Writer<rapidjson::StringBuffer>& writer);
    void LoadNodeData(rapidjson::Value& node_obj) ;
};

std::shared_ptr<Node> GlClearNode(std::vector<std::shared_ptr<Node>>& s_Nodes);





class GlRenderToTexture_Func : public NodeFunctions {
public:
    void Initialize();
    void Run(std::string called_pin);
    void Delete();
    void NoFlowUpdatePinsValues() {};
    void UpdateNodeUI() {};
    void UpdateNodeInspector();
    void SaveNodeData(rapidjson::Writer<rapidjson::StringBuffer>& writer);
    void LoadNodeData(rapidjson::Value& node_obj);

private:
    void SetupFrameBuffer();
    void DeleteFrameBuffer();

private:
    std::string object_prefix;
    int output_width;
    int output_height;

    char* current_min_param;
    char* current_mag_param;
    char* current_wrap_s;
    char* current_wrap_t;

    char* prev_min_param;
    char* prev_mag_param;
    char* prev_wrap_s;
    char* prev_wrap_t;
};

std::shared_ptr<Node> GlRenderToTexture(std::vector<std::shared_ptr<Node>>& s_Nodes);




void GlNodes1_SearchSetup(std::vector<SearchNodeObj>& search_nodes_vector);
std::shared_ptr<Node> GlNodes1_LoadSetup(std::vector<std::shared_ptr<Node>>& s_Nodes, std::string node_key);

#endif