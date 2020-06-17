#pragma once
#ifndef RESOURCES_NODES_H
#define RESOURCES_NODES_H

#include <ImGuiFileBrowser.h>
#include "node_function_interface.h"
#include "../nodes_builder.h"
#include "../utils.h"
#include "../InstanceConfig.h"
#include "stb/stb_image.h"

class Texture2DResourceNode_Func : public NodeFunctions {
public:
    void Initialize();
    void Run(std::string called_pin) {};
    void Delete();
    void NoFlowUpdatePinsValues();
    void UpdateNodeUI();
    void UpdateNodeInspector();
    void SaveNodeData(rapidjson::Writer<rapidjson::StringBuffer>& writer);
    void LoadNodeData(rapidjson::Value& node_obj);

    std::string filepath;

private:
    void DeleteResource();
    void TextureParamsGui(float paneWidth);
    void ImportTexture();
    void SetUpParams();

    imgui_addons::ImGuiFileBrowser file_dialog;
    bool showImportWindow = false;
    std::string selected_filepath;

    std::string object_prefix;
    char* current_min_param;
    char* current_mag_param;
    char* current_wrap_s;
    char* current_wrap_t;

};

std::shared_ptr<Node> Texture2DResourceNode(std::vector<std::shared_ptr<Node>>& s_Nodes);

void ResourcesNodesSearchSetup(std::vector<SearchNodeObj>& search_nodes_vector);
std::shared_ptr<Node> ResourcesNodesLoadSetup(std::vector<std::shared_ptr<Node>>& s_Nodes, std::string node_key);

#endif