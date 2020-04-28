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
    void Run();
    void Delete();
    void NoFlowUpdatePinsValues();
    void ChangePinType(PinKind kind, int index, PinType type);

private:
    void SetupFrameBuffer();
    void DeleteFrameBuffer();

private:
    std::string object_prefix;
    int output_width;
    int output_height;
};

std::shared_ptr<Node> GlMainLoop(std::vector<std::shared_ptr<Node>>& s_Nodes);



class GlClear_Func : public NodeFunctions {
public:
    void Initialize();
    void Run();
    void Delete();
    void NoFlowUpdatePinsValues();
    void ChangePinType(PinKind kind, int index, PinType type);
};

std::shared_ptr<Node> GlClearNode(std::vector<std::shared_ptr<Node>>& s_Nodes);



class GlRenderToTexture_Func : public NodeFunctions {
public:
    void Initialize();
    void Run();
    void Delete();
    void NoFlowUpdatePinsValues();
    void ChangePinType(PinKind kind, int index, PinType type);

private:
    void SetupFrameBuffer();
    void DeleteFrameBuffer();

private:
    std::string object_prefix;
    int output_width;
    int output_height;
};

std::shared_ptr<Node> GlRenderToTexture(std::vector<std::shared_ptr<Node>>& s_Nodes);




void GlNodes1_SearchSetup(std::vector<SearchNodeObj>& search_nodes_vector);

#endif