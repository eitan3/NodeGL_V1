#pragma once
#ifndef MESHES_NODES_H
#define MESHES_NODES_H

#include "node_function_interface.h"
#include "../nodes_builder.h"
#include "../utils.h"
#include "../objects/mesh_object.h"
#include "../InstanceConfig.h"


class CreateCubeNode_Func : public NodeFunctions {
public:
    void Initialize() {};
    void Run() {};
    void Delete();
    void NoFlowUpdatePinsValues();
    void UpdateNodeUI() {};
    void UpdateNodeInspector() {};
    void SaveNodeData(rapidjson::Writer<rapidjson::StringBuffer>& writer);
    void LoadNodeData(rapidjson::Value& node_obj);
    void SetupMesh();

    std::string name;
    float min_x;
    float min_y;
    float min_z;
    float max_x;
    float max_y;
    float max_z;
    bool calc_normals;
    bool calc_tangents;

    std::shared_ptr<MeshObject> mesh_obj;
};

std::shared_ptr<Node> CreateCubeNode(std::vector<std::shared_ptr<Node>>& s_Nodes);




class DrawMeshNode_Func : public NodeFunctions {
public:
    void Initialize() {};
    void Run();
    void Delete();
    void NoFlowUpdatePinsValues() {};
    void UpdateNodeUI() {};
    void UpdateNodeInspector() {};
    void SaveNodeData(rapidjson::Writer<rapidjson::StringBuffer>& writer) {};
    void LoadNodeData(rapidjson::Value& node_obj) {};
};

std::shared_ptr<Node> DrawMeshNode(std::vector<std::shared_ptr<Node>>& s_Nodes);



void MeshesNodesSearchSetup(std::vector<SearchNodeObj>& search_nodes_vector);
std::shared_ptr<Node> MeshesNodesLoadSetup(std::vector<std::shared_ptr<Node>>& s_Nodes, std::string node_key);

#endif