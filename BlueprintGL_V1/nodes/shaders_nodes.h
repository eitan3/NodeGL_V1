#pragma once
#ifndef SHADERS_NODES_H
#define SHADERS_NODES_H

#include <ImGuiFileBrowser.h>
#include <TextEditor.h>
#include <fstream>
#include <iostream>
#include "node_function_interface.h"
#include "../nodes_builder.h"
#include "../utils.h"
#include "../objects/shader_object.h"

class CreateSahder_Func : public NodeFunctions {
public:
    void Initialize();
    void Run() {};
    void Delete();
    void DeleteShader();
    void NoFlowUpdatePinsValues() {};
    void ChangePinType(PinKind kind, int index, PinType type) {};
    void PressButton(PinKind, int index);
    void UpdateUI();

    void ShowShaderEditorWindow(bool* show = nullptr);
    void ShowFileBrowserWindow(bool* show = nullptr);

    std::string object_prefix;
    imgui_addons::ImGuiFileBrowser file_dialog;
    TextEditor editor;
    bool showShaderEditorWindow;
    bool showFileBrowserWindow;
    const char* current_shader_type = NULL;

    std::shared_ptr<ShaderObject> shader_obj;
};

std::shared_ptr<Node> CreateSahder(std::vector<std::shared_ptr<Node>>& s_Nodes);



class CreateProgram_Func : public NodeFunctions {
public:
    void Initialize();
    void Run() {};
    void Delete();
    void DeleteProgram();
    void NoFlowUpdatePinsValues();
    void ChangePinType(PinKind kind, int index, PinType type) {};
    void PressButton(PinKind, int index) {};
    void UpdateUI();

    void CreateProgram(GLuint vertex_shader, GLuint fragment_shader);

    std::string object_prefix;
    std::shared_ptr<ProgramObject> program_obj;
};

std::shared_ptr<Node> CreateProgram(std::vector<std::shared_ptr<Node>>& s_Nodes);




void ShadersNodesSearchSetup(std::vector<SearchNodeObj>& search_nodes_vector);

#endif