#pragma once
#ifndef SHADERS_NODES_H
#define SHADERS_NODES_H

#include <ImGuiFileBrowser.h>
#include <TextEditor.h>
#include <fstream>
#include <iostream>
#include <glm/gtc/type_ptr.hpp>
#include "node_function_interface.h"
#include "../nodes_builder.h"
#include "../utils.h"
#include "../objects/shader_object.h"
#include "../InstanceConfig.h"

class CreateSahder_Func : public NodeFunctions {
public:
    void Initialize();
    void Run(std::string called_pin) {};
    void Delete();
    void DeleteShader();
    void NoFlowUpdatePinsValues() {};
    void UpdateNodeUI();
    void UpdateNodeInspector();
    void SaveNodeData(rapidjson::Writer<rapidjson::StringBuffer>& writer);
    void LoadNodeData(rapidjson::Value& node_obj);

    void CompileShader();
    void ShowShaderEditorWindow(bool* show = nullptr);
    void ShowFileBrowserWindow(bool* show = nullptr);

    std::string object_prefix;
    imgui_addons::ImGuiFileBrowser file_dialog;
    TextEditor editor;
    bool showShaderEditorWindow;
    bool showFileBrowserWindow;
    const char* current_shader_type = NULL;
    bool is_compiled;

    std::shared_ptr<ShaderObject> shader_obj;
};

std::shared_ptr<Node> CreateSahder(std::vector<std::shared_ptr<Node>>& s_Nodes);



class CreateProgram_Func : public NodeFunctions {
public:
    void Initialize();
    void Run(std::string called_pin) {};
    void Delete();
    void DeleteProgram();
    void NoFlowUpdatePinsValues();
    void UpdateNodeUI();
    void UpdateNodeInspector() {};
    void SaveNodeData(rapidjson::Writer<rapidjson::StringBuffer>& writer);
    void LoadNodeData(rapidjson::Value& node_obj);

    void CreateProgram(std::shared_ptr<ShaderObject> vertex_shader, std::shared_ptr<ShaderObject> fragment_shader);

    std::string object_prefix;
    std::shared_ptr<ProgramObject> program_obj;
};

std::shared_ptr<Node> CreateProgram(std::vector<std::shared_ptr<Node>>& s_Nodes);



class BindProgram_Func : public NodeFunctions {
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

std::shared_ptr<Node> BindProgramNode(std::vector<std::shared_ptr<Node>>& s_Nodes);



class BindProgramWithUniforms_Func : public NodeFunctions {
public:
    void Initialize() {};
    void Run(std::string called_pin);
    void Delete();
    void NoFlowUpdatePinsValues() {};
    void UpdateNodeUI();
    void UpdateNodeInspector() {};
    void SaveNodeData(rapidjson::Writer<rapidjson::StringBuffer>& writer);
    void LoadNodeData(rapidjson::Value& node_obj);

private:
    void ProgramChanged();
    void DeletePins();

    GLuint prev_program;
    bool continue_loading = false;
    std::map<std::string, std::shared_ptr<BasePlaceholder>> tmp_loaded_value;
};

std::shared_ptr<Node> BindProgramWithUniformsNode(std::vector<std::shared_ptr<Node>>& s_Nodes);



class SetProgramUniformNode_Func : public NodeFunctions {
public:
    void Initialize() {};
    void Run(std::string called_pin);
    void Delete();
    void NoFlowUpdatePinsValues() {};
    void UpdateNodeUI();
    void UpdateNodeInspector();
    void SaveNodeData(rapidjson::Writer<rapidjson::StringBuffer>& writer);
    void LoadNodeData(rapidjson::Value& node_obj);

    void ProgramChanged();
    void UniformChanged();
    void DeletePin();

private:
    bool continue_loading = false;

    GLuint prev_program;
    std::string current_uniform = "";
    PinType uniform_type = PinType::Float;
    bool uniform_isArr = false;
    std::shared_ptr<BasePlaceholder> tmp_loaded_value;
};

std::shared_ptr<Node> SetProgramUniformNode(std::vector<std::shared_ptr<Node>>& s_Nodes);




void ShadersNodesSearchSetup(std::vector<SearchNodeObj>& search_nodes_vector);
std::shared_ptr<Node> ShadersNodesLoadSetup(std::vector<std::shared_ptr<Node>>& s_Nodes, std::string node_key);

#endif