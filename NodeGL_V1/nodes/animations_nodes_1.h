#pragma once
#ifndef ANIMATIONS_NODES_1_H
#define ANIMATIONS_NODES_1_H

#define _USE_MATH_DEFINES
#include <random>
#include <math.h>
#include "node_function_interface.h"
#include "../nodes_builder.h"
#include "../utils.h"

class EaseAnimation_Func : public NodeFunctions {
public:
    void Initialize();
    void Run(std::string called_pin);
    void Delete();
    void NoFlowUpdatePinsValues() {};
    void UpdateNodeUI() {};
    void UpdateNodeInspector();
    void SaveNodeData(rapidjson::Writer<rapidjson::StringBuffer>& writer);
    void LoadNodeData(rapidjson::Value& node_obj);

    float min_val;
    float max_val;
    float duration_val;
    bool reverse;
    bool start_random;

    float anim_time;
    bool is_reverse;

    char* current_ease = NULL;
};

std::shared_ptr<Node> EaseAnimationhNode(std::vector<std::shared_ptr<Node>>& s_Nodes);




void AnimNodesSearchSetup(std::vector<SearchNodeObj>& search_nodes_vector);
std::shared_ptr<Node> AnimNodesLoadSetup(std::vector<std::shared_ptr<Node>>& s_Nodes, std::string node_key);
#endif 
