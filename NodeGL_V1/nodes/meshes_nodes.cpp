#include "meshes_nodes.h"

void CreateCubeNode_Func::Delete()
{
    mesh_obj = nullptr;
	parent_node = nullptr;
}

void CreateCubeNode_Func::NoFlowUpdatePinsValues()
{
    std::string in_name = GetInputPinValue<std::string>(parent_node, "name");
    float in_min_x = GetInputPinValue<float>(parent_node, "min_x");
    float in_min_y = GetInputPinValue<float>(parent_node, "min_y");
    float in_min_z = GetInputPinValue<float>(parent_node, "min_z");
    float in_max_x = GetInputPinValue<float>(parent_node, "max_x");
    float in_max_y = GetInputPinValue<float>(parent_node, "max_y");
    float in_max_z = GetInputPinValue<float>(parent_node, "max_z");
    bool in_calc_normals = GetInputPinValue<bool>(parent_node, "calc_normal");
    bool in_calc_tangents = GetInputPinValue<bool>(parent_node, "calc_tangents");

    name = in_name;
    if (in_min_x != min_x || in_min_y != min_y || in_min_z != min_z ||
        in_max_x != max_x || in_max_y != max_y || in_max_z != max_z || 
        in_calc_normals != calc_normals || in_calc_tangents != calc_tangents)
    {
        min_x = in_min_x;
        min_y = in_min_y;
        min_z = in_min_z;
        max_x = in_max_x;
        max_y = in_max_y;
        max_z = in_max_z;
        calc_normals = in_calc_normals;
        calc_tangents = in_calc_tangents;
        SetupMesh();
    }

    if (mesh_obj)
    {
        if (mesh_obj->object_name != in_name)
        {
            mesh_obj->object_name = in_name;
        }
    }
}

void CreateCubeNode_Func::SaveNodeData(rapidjson::Writer<rapidjson::StringBuffer>& writer)
{
    writer.Key("min_x");
    writer.Double(std::dynamic_pointer_cast<PinValue<float>>(parent_node->inputs.at("min_x"))->default_value);
    writer.Key("min_y");
    writer.Double(std::dynamic_pointer_cast<PinValue<float>>(parent_node->inputs.at("min_y"))->default_value);
    writer.Key("min_z");
    writer.Double(std::dynamic_pointer_cast<PinValue<float>>(parent_node->inputs.at("min_z"))->default_value);
    writer.Key("max_x");
    writer.Double(std::dynamic_pointer_cast<PinValue<float>>(parent_node->inputs.at("max_x"))->default_value);
    writer.Key("max_y");
    writer.Double(std::dynamic_pointer_cast<PinValue<float>>(parent_node->inputs.at("max_y"))->default_value);
    writer.Key("max_z");
    writer.Double(std::dynamic_pointer_cast<PinValue<float>>(parent_node->inputs.at("max_z"))->default_value);
    writer.Key("calc_normal");
    writer.Bool(std::dynamic_pointer_cast<PinValue<bool>>(parent_node->inputs.at("calc_normal"))->default_value);
    writer.Key("calc_tangents");
    writer.Bool(std::dynamic_pointer_cast<PinValue<bool>>(parent_node->inputs.at("calc_tangents"))->default_value);
}

void CreateCubeNode_Func::LoadNodeData(rapidjson::Value& node_obj)
{
    std::dynamic_pointer_cast<PinValue<float>>(parent_node->inputs.at("min_x"))->default_value = node_obj["min_x"].GetFloat();
    std::dynamic_pointer_cast<PinValue<float>>(parent_node->inputs.at("min_y"))->default_value = node_obj["min_y"].GetFloat();
    std::dynamic_pointer_cast<PinValue<float>>(parent_node->inputs.at("min_z"))->default_value = node_obj["min_z"].GetFloat();
    std::dynamic_pointer_cast<PinValue<float>>(parent_node->inputs.at("max_x"))->default_value = node_obj["max_x"].GetFloat();
    std::dynamic_pointer_cast<PinValue<float>>(parent_node->inputs.at("max_y"))->default_value = node_obj["max_y"].GetFloat();
    std::dynamic_pointer_cast<PinValue<float>>(parent_node->inputs.at("max_z"))->default_value = node_obj["max_z"].GetFloat();
    std::dynamic_pointer_cast<PinValue<bool>>(parent_node->inputs.at("calc_normal"))->default_value = node_obj["calc_normal"].GetBool();
    std::dynamic_pointer_cast<PinValue<bool>>(parent_node->inputs.at("calc_tangents"))->default_value = node_obj["calc_tangents"].GetBool();
}

void CreateCubeNode_Func::SetupMesh()
{
    mesh_obj = nullptr;
    std::vector<Vertex> vertices;

    vertices.push_back(Vertex(glm::vec3(max_x, max_y, min_z), glm::vec2(1, 1), glm::vec3(0), glm::vec3(0), glm::vec3(0)));
    vertices.push_back(Vertex(glm::vec3(max_x, min_y, min_z), glm::vec2(1, 0), glm::vec3(0), glm::vec3(0), glm::vec3(0)));
    vertices.push_back(Vertex(glm::vec3(min_x, min_y, min_z), glm::vec2(0, 0), glm::vec3(0), glm::vec3(0), glm::vec3(0)));
    vertices.push_back(Vertex(glm::vec3(min_x, min_y, min_z), glm::vec2(0, 0), glm::vec3(0), glm::vec3(0), glm::vec3(0)));
    vertices.push_back(Vertex(glm::vec3(min_x, max_y, min_z), glm::vec2(0, 1), glm::vec3(0), glm::vec3(0), glm::vec3(0)));
    vertices.push_back(Vertex(glm::vec3(max_x, max_y, min_z), glm::vec2(1, 1), glm::vec3(0), glm::vec3(0), glm::vec3(0)));

    vertices.push_back(Vertex(glm::vec3(min_x, min_y, max_z), glm::vec2(0, 0), glm::vec3(0), glm::vec3(0), glm::vec3(0)));
    vertices.push_back(Vertex(glm::vec3(max_x, min_y, max_z), glm::vec2(1, 0), glm::vec3(0), glm::vec3(0), glm::vec3(0)));
    vertices.push_back(Vertex(glm::vec3(max_x, max_y, max_z), glm::vec2(1, 1), glm::vec3(0), glm::vec3(0), glm::vec3(0)));
    vertices.push_back(Vertex(glm::vec3(max_x, max_y, max_z), glm::vec2(1, 1), glm::vec3(0), glm::vec3(0), glm::vec3(0)));
    vertices.push_back(Vertex(glm::vec3(min_x, max_y, max_z), glm::vec2(0, 1), glm::vec3(0), glm::vec3(0), glm::vec3(0)));
    vertices.push_back(Vertex(glm::vec3(min_x, min_y, max_z), glm::vec2(1, 0), glm::vec3(0), glm::vec3(0), glm::vec3(0)));

    vertices.push_back(Vertex(glm::vec3(min_x, max_y, max_z), glm::vec2(1, 1), glm::vec3(0), glm::vec3(0), glm::vec3(0)));
    vertices.push_back(Vertex(glm::vec3(min_x, max_y, min_z), glm::vec2(0, 1), glm::vec3(0), glm::vec3(0), glm::vec3(0)));
    vertices.push_back(Vertex(glm::vec3(min_x, min_y, min_z), glm::vec2(0, 0), glm::vec3(0), glm::vec3(0), glm::vec3(0)));
    vertices.push_back(Vertex(glm::vec3(min_x, min_y, min_z), glm::vec2(0, 0), glm::vec3(0), glm::vec3(0), glm::vec3(0)));
    vertices.push_back(Vertex(glm::vec3(min_x, min_y, max_z), glm::vec2(1, 0), glm::vec3(0), glm::vec3(0), glm::vec3(0)));
    vertices.push_back(Vertex(glm::vec3(min_x, max_y, max_z), glm::vec2(1, 1), glm::vec3(0), glm::vec3(0), glm::vec3(0)));

    vertices.push_back(Vertex(glm::vec3(max_x, min_y, min_z), glm::vec2(0, 0), glm::vec3(0), glm::vec3(0), glm::vec3(0)));
    vertices.push_back(Vertex(glm::vec3(max_x, max_y, min_z), glm::vec2(1, 0), glm::vec3(0), glm::vec3(0), glm::vec3(0)));
    vertices.push_back(Vertex(glm::vec3(max_x, max_y, max_z), glm::vec2(1, 1), glm::vec3(0), glm::vec3(0), glm::vec3(0)));
    vertices.push_back(Vertex(glm::vec3(max_x, max_y, max_z), glm::vec2(1, 1), glm::vec3(0), glm::vec3(0), glm::vec3(0)));
    vertices.push_back(Vertex(glm::vec3(max_x, min_y, max_z), glm::vec2(0, 1), glm::vec3(0), glm::vec3(0), glm::vec3(0)));
    vertices.push_back(Vertex(glm::vec3(max_x, min_y, min_z), glm::vec2(0, 0), glm::vec3(0), glm::vec3(0), glm::vec3(0)));

    vertices.push_back(Vertex(glm::vec3(min_x, min_y, min_z), glm::vec2(0, 0), glm::vec3(0), glm::vec3(0), glm::vec3(0)));
    vertices.push_back(Vertex(glm::vec3(max_x, min_y, min_z), glm::vec2(1, 0), glm::vec3(0), glm::vec3(0), glm::vec3(0)));
    vertices.push_back(Vertex(glm::vec3(max_x, min_y, max_z), glm::vec2(1, 1), glm::vec3(0), glm::vec3(0), glm::vec3(0)));
    vertices.push_back(Vertex(glm::vec3(max_x, min_y, max_z), glm::vec2(1, 1), glm::vec3(0), glm::vec3(0), glm::vec3(0)));
    vertices.push_back(Vertex(glm::vec3(min_x, min_y, max_z), glm::vec2(0, 1), glm::vec3(0), glm::vec3(0), glm::vec3(0)));
    vertices.push_back(Vertex(glm::vec3(min_x, min_y, min_z), glm::vec2(0, 0), glm::vec3(0), glm::vec3(0), glm::vec3(0)));

    vertices.push_back(Vertex(glm::vec3(max_x, max_y, max_z), glm::vec2(1, 1), glm::vec3(0), glm::vec3(0), glm::vec3(0)));
    vertices.push_back(Vertex(glm::vec3(max_x, max_y, min_z), glm::vec2(1, 0), glm::vec3(0), glm::vec3(0), glm::vec3(0)));
    vertices.push_back(Vertex(glm::vec3(min_x, max_y, min_z), glm::vec2(0, 0), glm::vec3(0), glm::vec3(0), glm::vec3(0)));
    vertices.push_back(Vertex(glm::vec3(min_x, max_y, min_z), glm::vec2(0, 0), glm::vec3(0), glm::vec3(0), glm::vec3(0)));
    vertices.push_back(Vertex(glm::vec3(min_x, max_y, max_z), glm::vec2(0, 1), glm::vec3(0), glm::vec3(0), glm::vec3(0)));
    vertices.push_back(Vertex(glm::vec3(max_x, max_y, max_z), glm::vec2(1, 1), glm::vec3(0), glm::vec3(0), glm::vec3(0)));

    std::vector<unsigned int> indices;
    for (int i = 0; i < vertices.size(); i++)
        indices.push_back(i);

    if (calc_normals)
    {
        CalculateNormals(vertices, indices);
    }

    if (calc_tangents)
    {
        if (calc_normals == false)
            CalculateNormals(vertices, indices);
        CalculateTangents(vertices, indices);
    }

    mesh_obj = std::make_shared<MeshObject>(name, vertices, indices);
    std::shared_ptr<PinValue<std::shared_ptr<MeshObject>>> output_pin = std::dynamic_pointer_cast<PinValue<std::shared_ptr<MeshObject>>>(parent_node->outputs.at("out"));
    output_pin->value = mesh_obj;
}

std::string createCubeNodeName = "Create Cube Mesh";
std::shared_ptr<Node> CreateCubeNode(std::vector<std::shared_ptr<Node>>& s_Nodes)
{
    s_Nodes.emplace_back(new Node(GetNextId(), createCubeNodeName.c_str(), true));

    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<PinValue<std::string>>>("name", new PinValue<std::string>("name", 0, GetNextId(), "Name", PinType::String, "CubeMesh_" + std::to_string(s_Nodes.back()->id.Get()))));
    s_Nodes.back()->inputs.at("name")->always_expose = false;
    s_Nodes.back()->inputs.at("name")->exposed = false;
    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<PinValue<float>>>("min_x", new PinValue<float>("min_x", 1, GetNextId(), "Min X Boundary", PinType::Float, -1)));
    s_Nodes.back()->inputs.at("min_x")->always_expose = false;
    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<PinValue<float>>>("min_y", new PinValue<float>("min_y", 2, GetNextId(), "Min Y Boundary", PinType::Float, -1)));
    s_Nodes.back()->inputs.at("min_y")->always_expose = false;
    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<PinValue<float>>>("min_z", new PinValue<float>("min_z", 3, GetNextId(), "Min Z Boundary", PinType::Float, -1)));
    s_Nodes.back()->inputs.at("min_z")->always_expose = false;
    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<PinValue<float>>>("max_x", new PinValue<float>("max_x", 4, GetNextId(), "Max X Boundary", PinType::Float, 1)));
    s_Nodes.back()->inputs.at("max_x")->always_expose = false;
    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<PinValue<float>>>("max_y", new PinValue<float>("max_y", 5, GetNextId(), "Max Y Boundary", PinType::Float, 1)));
    s_Nodes.back()->inputs.at("max_y")->always_expose = false;
    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<PinValue<float>>>("max_z", new PinValue<float>("max_z", 6, GetNextId(), "Max Z Boundary", PinType::Float, 1)));
    s_Nodes.back()->inputs.at("max_z")->always_expose = false;
    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<PinValue<bool>>>("calc_normal", new PinValue<bool>("calc_normal", 7, GetNextId(), "Calculate Normals", PinType::Bool, true)));
    s_Nodes.back()->inputs.at("calc_normal")->always_expose = false;
    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<PinValue<bool>>>("calc_tangents", new PinValue<bool>("calc_tangents", 8, GetNextId(), "Calculate Tangents", PinType::Bool, true)));
    s_Nodes.back()->inputs.at("calc_tangents")->always_expose = false;
    
    s_Nodes.back()->outputs.insert(std::pair<std::string, std::shared_ptr<PinValue<std::shared_ptr<MeshObject>>>>("out", new PinValue<std::shared_ptr<MeshObject>>("out", 0, GetNextId(), "Mesh", PinType::MeshObject, nullptr)));

    s_Nodes.back()->node_funcs = std::make_shared<CreateCubeNode_Func>();
    std::dynamic_pointer_cast<CreateCubeNode_Func>(s_Nodes.back()->node_funcs)->parent_node = s_Nodes.back();

    s_Nodes.back()->node_funcs->Initialize();

    BuildNode(s_Nodes.back());

    return s_Nodes.back();
}






void DrawMeshNode_Func::Run(std::string called_pin)
{
    std::shared_ptr<MeshObject> in_mesh = GetInputPinValue<std::shared_ptr<MeshObject>>(parent_node, "mesh");
    if (in_mesh)
    {
        auto config = InstanceConfig::instance();
        GLuint old_vao = config->current_vao;
        config->current_vao = in_mesh->GetVAO();

        glBindVertexArray(config->current_vao);
        glDrawElements(GL_TRIANGLES, in_mesh->GetIndicesSize(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(old_vao);
    }
    RunNextNodeFunc(parent_node, "next");
}

void DrawMeshNode_Func::Delete()
{
    parent_node = nullptr;
}

std::string drawMeshNodeName = "Draw Mesh";
std::shared_ptr<Node> DrawMeshNode(std::vector<std::shared_ptr<Node>>& s_Nodes)
{
    s_Nodes.emplace_back(new Node(GetNextId(), drawMeshNodeName.c_str()));

    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<BasePin>>("enter", new BasePin("enter", 0, GetNextId(), "Enter", PinType::Flow)));
    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<PinValue<std::shared_ptr<MeshObject>>>>("mesh", new PinValue<std::shared_ptr<MeshObject>>("mesh", 1, GetNextId(), "Mesh", PinType::MeshObject, nullptr)));
    
    s_Nodes.back()->outputs.insert(std::pair<std::string, std::shared_ptr<BasePin>>("next", new BasePin("next", 0, GetNextId(), "Next", PinType::Flow)));

    s_Nodes.back()->node_funcs = std::make_shared<DrawMeshNode_Func>();
    std::dynamic_pointer_cast<DrawMeshNode_Func>(s_Nodes.back()->node_funcs)->parent_node = s_Nodes.back();

    s_Nodes.back()->node_funcs->Initialize();

    BuildNode(s_Nodes.back());

    return s_Nodes.back();
}





void MeshesNodesSearchSetup(std::vector<SearchNodeObj>& search_nodes_vector)
{
    std::function<std::shared_ptr<Node>(std::vector<std::shared_ptr<Node>>&)> func_1 = CreateCubeNode;
    std::vector<std::string> keywords_1{ "Create", "Cube", "Mesh" };
    search_nodes_vector.push_back(SearchNodeObj("Create Mesh Cube", "Mesh Object", keywords_1, func_1));

    std::function<std::shared_ptr<Node>(std::vector<std::shared_ptr<Node>>&)> func_2 = DrawMeshNode;
    std::vector<std::string> keywords_2{ "Draw", "Mesh" };
    search_nodes_vector.push_back(SearchNodeObj("Draw Mesh", "Mesh Object", keywords_2, func_2));
}

std::shared_ptr<Node> MeshesNodesLoadSetup(std::vector<std::shared_ptr<Node>>& s_Nodes, std::string node_key)
{
    std::shared_ptr<Node> loaded_node = nullptr;
    if (loaded_node == nullptr && node_key.rfind(createCubeNodeName, 0) == 0) {
        loaded_node = CreateCubeNode(s_Nodes);
    }
    else if (loaded_node == nullptr && node_key.rfind(drawMeshNodeName, 0) == 0) {
        loaded_node = DrawMeshNode(s_Nodes);
    }
    return loaded_node;
}
