#include "vec3_nodes.h"

void MakeVector3_Func::Delete()
{
    parent_node = nullptr;
}

void MakeVector3_Func::NoFlowUpdatePinsValues()
{
    float pin_0_value = GetInputPinValue<float>(parent_node, "x");
    float pin_1_value = GetInputPinValue<float>(parent_node, "y");
    float pin_2_value = GetInputPinValue<float>(parent_node, "z");
    std::shared_ptr<PinValue<glm::vec3>> output_pin = std::dynamic_pointer_cast<PinValue<glm::vec3>>(parent_node->outputs.at("out"));
    output_pin->value = glm::vec3(pin_0_value, pin_1_value, pin_2_value);
}

void MakeVector3_Func::SaveNodeData(rapidjson::Writer<rapidjson::StringBuffer>& writer)
{
    writer.Key("x");
    writer.Double(std::dynamic_pointer_cast<PinValue<float>>(parent_node->inputs.at("x"))->default_value);
    writer.Key("y");
    writer.Double(std::dynamic_pointer_cast<PinValue<float>>(parent_node->inputs.at("y"))->default_value);
    writer.Key("z");
    writer.Double(std::dynamic_pointer_cast<PinValue<float>>(parent_node->inputs.at("z"))->default_value);
}

void MakeVector3_Func::LoadNodeData(rapidjson::Value& node_obj)
{
    std::dynamic_pointer_cast<PinValue<float>>(parent_node->inputs.at("x"))->default_value = node_obj["x"].GetFloat();
    std::dynamic_pointer_cast<PinValue<float>>(parent_node->inputs.at("y"))->default_value = node_obj["y"].GetFloat();
    std::dynamic_pointer_cast<PinValue<float>>(parent_node->inputs.at("z"))->default_value = node_obj["z"].GetFloat();
}

std::string makeVector3NodeName = "Make Vector 3";
std::shared_ptr<Node> MakeVector3Node(std::vector<std::shared_ptr<Node>>& s_Nodes)
{
    s_Nodes.emplace_back(new Node(GetNextId(), makeVector3NodeName.c_str(), true));
    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<PinValue<float>>>("x", new PinValue<float>("x", 0, GetNextId(), "X", PinType::Float, 0)));
    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<PinValue<float>>>("y", new PinValue<float>("y", 1, GetNextId(), "Y", PinType::Float, 0)));
    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<PinValue<float>>>("z", new PinValue<float>("z", 2, GetNextId(), "Z", PinType::Float, 0)));
    s_Nodes.back()->outputs.insert(std::pair<std::string, std::shared_ptr<PinValue<glm::vec3>>>("out", new PinValue<glm::vec3>("out", 0, GetNextId(), "Out", PinType::Vector3, glm::vec3(0))));

    s_Nodes.back()->node_funcs = std::make_shared<MakeVector3_Func>();
    std::dynamic_pointer_cast<MakeVector3_Func>(s_Nodes.back()->node_funcs)->parent_node = s_Nodes.back();

    s_Nodes.back()->node_funcs->Initialize();

    BuildNode(s_Nodes.back());

    return s_Nodes.back();
}





void BreakVector3_Func::Delete()
{
    parent_node = nullptr;
}

void BreakVector3_Func::NoFlowUpdatePinsValues()
{
    glm::vec3 pin_0_value = GetInputPinValue<glm::vec3>(parent_node, "in");
    std::shared_ptr<PinValue<float>> output_pin_1 = std::dynamic_pointer_cast<PinValue<float>>(parent_node->outputs.at("x"));
    std::shared_ptr<PinValue<float>> output_pin_2 = std::dynamic_pointer_cast<PinValue<float>>(parent_node->outputs.at("y"));
    std::shared_ptr<PinValue<float>> output_pin_3 = std::dynamic_pointer_cast<PinValue<float>>(parent_node->outputs.at("z"));
    output_pin_1->value = pin_0_value.x;
    output_pin_2->value = pin_0_value.y;
    output_pin_3->value = pin_0_value.z;
}

void BreakVector3_Func::SaveNodeData(rapidjson::Writer<rapidjson::StringBuffer>& writer)
{
    glm::vec3 pin_0_value = std::dynamic_pointer_cast<PinValue<glm::vec3>>(parent_node->inputs.at("in"))->default_value;
    writer.Key("x");
    writer.Double(pin_0_value.x);
    writer.Key("y");
    writer.Double(pin_0_value.y);
    writer.Key("z");
    writer.Double(pin_0_value.z);
}

void BreakVector3_Func::LoadNodeData(rapidjson::Value& node_obj)
{
    float x = node_obj["x"].GetFloat();
    float y = node_obj["y"].GetFloat();
    float z = node_obj["z"].GetFloat();
    std::dynamic_pointer_cast<PinValue<glm::vec3>>(parent_node->inputs.at("in"))->default_value = glm::vec3(x, y, z);
}

std::string breakVector3NodeName = "Break Vector 3";
std::shared_ptr<Node> BreakVector3Node(std::vector<std::shared_ptr<Node>>& s_Nodes)
{
    s_Nodes.emplace_back(new Node(GetNextId(), breakVector3NodeName.c_str(), true));
    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<PinValue<glm::vec3>>>("in", new PinValue<glm::vec3>("in", 0, GetNextId(), "In", PinType::Vector3, glm::vec3(0))));
    s_Nodes.back()->outputs.insert(std::pair<std::string, std::shared_ptr<PinValue<float>>>("x", new PinValue<float>("x", 0, GetNextId(), "X", PinType::Float, 0)));
    s_Nodes.back()->outputs.insert(std::pair<std::string, std::shared_ptr<PinValue<float>>>("y", new PinValue<float>("y", 1, GetNextId(), "Y", PinType::Float, 0)));
    s_Nodes.back()->outputs.insert(std::pair<std::string, std::shared_ptr<PinValue<float>>>("z", new PinValue<float>("z", 2, GetNextId(), "Z", PinType::Float, 0)));

    s_Nodes.back()->node_funcs = std::make_shared<BreakVector3_Func>();
    std::dynamic_pointer_cast<BreakVector3_Func>(s_Nodes.back()->node_funcs)->parent_node = s_Nodes.back();

    s_Nodes.back()->node_funcs->Initialize();

    BuildNode(s_Nodes.back());

    return s_Nodes.back();
}




void MakeVectorI3_Func::Delete()
{
    parent_node = nullptr;
}

void MakeVectorI3_Func::NoFlowUpdatePinsValues()
{
    int pin_0_value = GetInputPinValue<int>(parent_node, "x");
    int pin_1_value = GetInputPinValue<int>(parent_node, "y");
    int pin_2_value = GetInputPinValue<int>(parent_node, "z");
    std::shared_ptr<PinValue<glm::ivec3>> output_pin = std::dynamic_pointer_cast<PinValue<glm::ivec3>>(parent_node->outputs.at("out"));
    output_pin->value = glm::ivec3(pin_0_value, pin_1_value, pin_2_value);
}

void MakeVectorI3_Func::SaveNodeData(rapidjson::Writer<rapidjson::StringBuffer>& writer)
{
    writer.Key("x");
    writer.Int(std::dynamic_pointer_cast<PinValue<int>>(parent_node->inputs.at("x"))->default_value);
    writer.Key("y");
    writer.Int(std::dynamic_pointer_cast<PinValue<int>>(parent_node->inputs.at("y"))->default_value);
    writer.Key("z");
    writer.Int(std::dynamic_pointer_cast<PinValue<int>>(parent_node->inputs.at("z"))->default_value);
}

void MakeVectorI3_Func::LoadNodeData(rapidjson::Value& node_obj)
{
    std::dynamic_pointer_cast<PinValue<int>>(parent_node->inputs.at("x"))->default_value = node_obj["x"].GetInt();
    std::dynamic_pointer_cast<PinValue<int>>(parent_node->inputs.at("y"))->default_value = node_obj["y"].GetInt();
    std::dynamic_pointer_cast<PinValue<int>>(parent_node->inputs.at("z"))->default_value = node_obj["z"].GetInt();
}

std::string makeVectorI3NodeName = "Make Vector Int 3";
std::shared_ptr<Node> MakeVectorI3Node(std::vector<std::shared_ptr<Node>>& s_Nodes)
{
    s_Nodes.emplace_back(new Node(GetNextId(), makeVectorI3NodeName.c_str(), true));
    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<PinValue<int>>>("x", new PinValue<int>("x", 0, GetNextId(), "X", PinType::Int, 0)));
    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<PinValue<int>>>("y", new PinValue<int>("y", 1, GetNextId(), "Y", PinType::Int, 0)));
    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<PinValue<int>>>("z", new PinValue<int>("z", 2, GetNextId(), "Z", PinType::Int, 0)));
    s_Nodes.back()->outputs.insert(std::pair<std::string, std::shared_ptr<PinValue<glm::ivec3>>>("out", new PinValue<glm::ivec3>("out", 0, GetNextId(), "Out", PinType::VectorI3, glm::ivec3(0))));

    s_Nodes.back()->node_funcs = std::make_shared<MakeVectorI3_Func>();
    std::dynamic_pointer_cast<MakeVectorI3_Func>(s_Nodes.back()->node_funcs)->parent_node = s_Nodes.back();

    s_Nodes.back()->node_funcs->Initialize();

    BuildNode(s_Nodes.back());

    return s_Nodes.back();
}





void BreakVectorI3_Func::Delete()
{
    parent_node = nullptr;
}

void BreakVectorI3_Func::NoFlowUpdatePinsValues()
{
    glm::ivec3 pin_0_value = GetInputPinValue<glm::ivec3>(parent_node, "in");
    std::shared_ptr<PinValue<int>> output_pin_1 = std::dynamic_pointer_cast<PinValue<int>>(parent_node->outputs.at("x"));
    std::shared_ptr<PinValue<int>> output_pin_2 = std::dynamic_pointer_cast<PinValue<int>>(parent_node->outputs.at("y"));
    std::shared_ptr<PinValue<int>> output_pin_3 = std::dynamic_pointer_cast<PinValue<int>>(parent_node->outputs.at("z"));
    output_pin_1->value = pin_0_value.x;
    output_pin_2->value = pin_0_value.y;
    output_pin_3->value = pin_0_value.z;
}

void BreakVectorI3_Func::SaveNodeData(rapidjson::Writer<rapidjson::StringBuffer>& writer)
{
    glm::ivec3 pin_0_value = std::dynamic_pointer_cast<PinValue<glm::ivec3>>(parent_node->inputs.at("in"))->default_value;
    writer.Key("x");
    writer.Int(pin_0_value.x);
    writer.Key("y");
    writer.Int(pin_0_value.y);
    writer.Key("z");
    writer.Int(pin_0_value.z);
}

void BreakVectorI3_Func::LoadNodeData(rapidjson::Value& node_obj)
{
    int x = node_obj["x"].GetInt();
    int y = node_obj["y"].GetInt();
    int z = node_obj["z"].GetInt();
    std::dynamic_pointer_cast<PinValue<glm::ivec3>>(parent_node->inputs.at("in"))->default_value = glm::ivec3(x, y, z);
}

std::string breakVectorI3NodeName = "Break Vector Int 3";
std::shared_ptr<Node> BreakVectorI3Node(std::vector<std::shared_ptr<Node>>& s_Nodes)
{
    s_Nodes.emplace_back(new Node(GetNextId(), breakVectorI3NodeName.c_str(), true));
    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<PinValue<glm::ivec3>>>("in", new PinValue<glm::ivec3>("in", 0, GetNextId(), "In", PinType::VectorI3, glm::ivec3(0))));
    s_Nodes.back()->outputs.insert(std::pair<std::string, std::shared_ptr<PinValue<int>>>("x", new PinValue<int>("x", 0, GetNextId(), "X", PinType::Int, 0)));
    s_Nodes.back()->outputs.insert(std::pair<std::string, std::shared_ptr<PinValue<int>>>("y", new PinValue<int>("y", 1, GetNextId(), "Y", PinType::Int, 0)));
    s_Nodes.back()->outputs.insert(std::pair<std::string, std::shared_ptr<PinValue<int>>>("z", new PinValue<int>("z", 2, GetNextId(), "Z", PinType::Int, 0)));

    s_Nodes.back()->node_funcs = std::make_shared<BreakVectorI3_Func>();
    std::dynamic_pointer_cast<BreakVectorI3_Func>(s_Nodes.back()->node_funcs)->parent_node = s_Nodes.back();

    s_Nodes.back()->node_funcs->Initialize();

    BuildNode(s_Nodes.back());

    return s_Nodes.back();
}




void Vector3Cross_Func::Delete()
{
    parent_node = nullptr;
}

void Vector3Cross_Func::NoFlowUpdatePinsValues()
{
    glm::vec3 pin_1_value = GetInputPinValue<glm::vec3>(parent_node, "in_1");
    glm::vec3 pin_2_value = GetInputPinValue<glm::vec3>(parent_node, "in_2");
    glm::vec3 out_val = glm::cross(pin_1_value, pin_2_value);
    std::shared_ptr<PinValue<glm::vec3>> output_pin = std::dynamic_pointer_cast<PinValue<glm::vec3>>(parent_node->outputs.at("out"));
    output_pin->value = out_val;
}

void Vector3Cross_Func::SaveNodeData(rapidjson::Writer<rapidjson::StringBuffer>& writer)
{
    glm::vec3 pin_1_value = std::dynamic_pointer_cast<PinValue<glm::vec3>>(parent_node->inputs.at("in_1"))->default_value;
    writer.Key("x_1");
    writer.Double(pin_1_value.x);
    writer.Key("y_1");
    writer.Double(pin_1_value.y);
    writer.Key("z_1");
    writer.Double(pin_1_value.z);
    glm::vec3 pin_2_value = std::dynamic_pointer_cast<PinValue<glm::vec3>>(parent_node->inputs.at("in_2"))->default_value;
    writer.Key("x_2");
    writer.Double(pin_2_value.x);
    writer.Key("y_2");
    writer.Double(pin_2_value.y);
    writer.Key("z_2");
    writer.Double(pin_2_value.z);
}

void Vector3Cross_Func::LoadNodeData(rapidjson::Value& node_obj)
{
    float x_1 = node_obj["x_1"].GetFloat();
    float y_1 = node_obj["y_1"].GetFloat();
    float z_1 = node_obj["z_1"].GetFloat();
    std::dynamic_pointer_cast<PinValue<glm::vec3>>(parent_node->inputs.at("in_1"))->default_value = glm::vec3(x_1, y_1, z_1);
    float x_2 = node_obj["x_2"].GetFloat();
    float y_2 = node_obj["y_2"].GetFloat();
    float z_2 = node_obj["z_2"].GetFloat();
    std::dynamic_pointer_cast<PinValue<glm::vec3>>(parent_node->inputs.at("in_2"))->default_value = glm::vec3(x_2, y_2, z_2);
}

std::string vector3CrossNodeName = "Cross Product - Vector 3";
std::shared_ptr<Node> Vector3CrossNode(std::vector<std::shared_ptr<Node>>& s_Nodes)
{
    s_Nodes.emplace_back(new Node(GetNextId(), vector3CrossNodeName.c_str(), true));
    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<PinValue<glm::vec3>>>("in_1", new PinValue<glm::vec3>("in_1", 0, GetNextId(), "In 1", PinType::Vector3, glm::vec3(0))));
    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<PinValue<glm::vec3>>>("in_2", new PinValue<glm::vec3>("in_2", 1, GetNextId(), "In 2", PinType::Vector3, glm::vec3(0))));

    s_Nodes.back()->outputs.insert(std::pair<std::string, std::shared_ptr<PinValue<glm::vec3>>>("out", new PinValue<glm::vec3>("out", 0, GetNextId(), "Out", PinType::Vector3, glm::vec3(0))));

    s_Nodes.back()->node_funcs = std::make_shared<Vector3Cross_Func>();
    std::dynamic_pointer_cast<Vector3Cross_Func>(s_Nodes.back()->node_funcs)->parent_node = s_Nodes.back();

    s_Nodes.back()->node_funcs->Initialize();

    BuildNode(s_Nodes.back());

    return s_Nodes.back();
}





void Vector3Normalize_Func::Delete()
{
    parent_node = nullptr;
}

void Vector3Normalize_Func::NoFlowUpdatePinsValues()
{
    glm::vec3 pin_1_value = GetInputPinValue<glm::vec3>(parent_node, "in_1");
    glm::vec3 out_val = glm::normalize(pin_1_value);
    std::shared_ptr<PinValue<glm::vec3>> output_pin = std::dynamic_pointer_cast<PinValue<glm::vec3>>(parent_node->outputs.at("out"));
    output_pin->value = out_val;
}

void Vector3Normalize_Func::SaveNodeData(rapidjson::Writer<rapidjson::StringBuffer>& writer)
{
    glm::vec3 pin_1_value = std::dynamic_pointer_cast<PinValue<glm::vec3>>(parent_node->inputs.at("in_1"))->default_value;
    writer.Key("x_1");
    writer.Double(pin_1_value.x);
    writer.Key("y_1");
    writer.Double(pin_1_value.y);
    writer.Key("z_1");
    writer.Double(pin_1_value.z);
}

void Vector3Normalize_Func::LoadNodeData(rapidjson::Value& node_obj)
{
    float x_1 = node_obj["x_1"].GetFloat();
    float y_1 = node_obj["y_1"].GetFloat();
    float z_1 = node_obj["z_1"].GetFloat();
    std::dynamic_pointer_cast<PinValue<glm::vec3>>(parent_node->inputs.at("in_1"))->default_value = glm::vec3(x_1, y_1, z_1);
}

std::string vector3NormalizeNodeName = "Normalize - Vector 3";
std::shared_ptr<Node> Vector3NormalizeNode(std::vector<std::shared_ptr<Node>>& s_Nodes)
{
    s_Nodes.emplace_back(new Node(GetNextId(), vector3NormalizeNodeName.c_str(), true));
    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<PinValue<glm::vec3>>>("in_1", new PinValue<glm::vec3>("in_1", 0, GetNextId(), "In 1", PinType::Vector3, glm::vec3(1))));
    
    s_Nodes.back()->outputs.insert(std::pair<std::string, std::shared_ptr<PinValue<glm::vec3>>>("out", new PinValue<glm::vec3>("out", 0, GetNextId(), "Out", PinType::Vector3, glm::vec3(0))));

    s_Nodes.back()->node_funcs = std::make_shared<Vector3Normalize_Func>();
    std::dynamic_pointer_cast<Vector3Normalize_Func>(s_Nodes.back()->node_funcs)->parent_node = s_Nodes.back();

    s_Nodes.back()->node_funcs->Initialize();

    BuildNode(s_Nodes.back());

    return s_Nodes.back();
}





void Vec3NodesSearchSetup(std::vector<SearchNodeObj>& search_nodes_vector)
{
    std::function<std::shared_ptr<Node>(std::vector<std::shared_ptr<Node>>&)> func_1 = MakeVector3Node;
    std::vector<std::string> keywords_1{ "Make", "Vector", "3" };
    search_nodes_vector.push_back(SearchNodeObj("Make Vector 3", "Vector 3", keywords_1, func_1));

    std::function<std::shared_ptr<Node>(std::vector<std::shared_ptr<Node>>&)> func_2 = BreakVector3Node;
    std::vector<std::string> keywords_2{ "Break", "Vector", "3" };
    search_nodes_vector.push_back(SearchNodeObj("Break Vector 3", "Vector 3", keywords_2, func_2));

    std::function<std::shared_ptr<Node>(std::vector<std::shared_ptr<Node>>&)> func_3 = MakeVectorI3Node;
    std::vector<std::string> keywords_3{ "Make", "Vector", "Int", "3" };
    search_nodes_vector.push_back(SearchNodeObj("Make Vector Int 3", "Vector 3", keywords_3, func_3));

    std::function<std::shared_ptr<Node>(std::vector<std::shared_ptr<Node>>&)> func_4 = BreakVectorI3Node;
    std::vector<std::string> keywords_4{ "Break", "Vector", "Int", "3" };
    search_nodes_vector.push_back(SearchNodeObj("Break Vector Int 3", "Vector 3", keywords_4, func_4));

    std::function<std::shared_ptr<Node>(std::vector<std::shared_ptr<Node>>&)> func_5 = Vector3CrossNode;
    std::vector<std::string> keywords_5{ "Cross", "Product", "Vector", "3" };
    search_nodes_vector.push_back(SearchNodeObj("Cross Product - Vector 3", "Vector 3", keywords_5, func_5));

    std::function<std::shared_ptr<Node>(std::vector<std::shared_ptr<Node>>&)> func_6 = Vector3NormalizeNode;
    std::vector<std::string> keywords_6{ "Normalize", "Vector", "3" };
    search_nodes_vector.push_back(SearchNodeObj("Normalize - Vector 3", "Vector 3", keywords_6, func_6));
}

std::shared_ptr<Node> Vec3NodesLoadSetup(std::vector<std::shared_ptr<Node>>& s_Nodes, std::string node_key)
{
    std::shared_ptr<Node> loaded_node = nullptr;
    if (loaded_node == nullptr && node_key.rfind(makeVector3NodeName, 0) == 0) {
        loaded_node = MakeVector3Node(s_Nodes);
    }
    else if (loaded_node == nullptr && node_key.rfind(breakVector3NodeName, 0) == 0) {
        loaded_node = BreakVector3Node(s_Nodes);
    }
    else if (loaded_node == nullptr && node_key.rfind(makeVectorI3NodeName, 0) == 0) {
        loaded_node = MakeVectorI3Node(s_Nodes);
    }
    else if (loaded_node == nullptr && node_key.rfind(breakVectorI3NodeName, 0) == 0) {
        loaded_node = BreakVectorI3Node(s_Nodes);
    }
    else if (loaded_node == nullptr && node_key.rfind(vector3CrossNodeName, 0) == 0) {
        loaded_node = Vector3CrossNode(s_Nodes);
    }
    else if (loaded_node == nullptr && node_key.rfind(vector3NormalizeNodeName, 0) == 0) {
        loaded_node = Vector3NormalizeNode(s_Nodes);
    }
    return loaded_node;
}