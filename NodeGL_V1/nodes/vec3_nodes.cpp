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





void Vec3NodesSearchSetup(std::vector<SearchNodeObj>& search_nodes_vector)
{
    std::function<std::shared_ptr<Node>(std::vector<std::shared_ptr<Node>>&)> func_1 = MakeVector3Node;
    std::vector<std::string> keywords_1{ "Make", "Vector", "3" };
    search_nodes_vector.push_back(SearchNodeObj("Make Vector 3", "Vector 3", keywords_1, func_1));

    std::function<std::shared_ptr<Node>(std::vector<std::shared_ptr<Node>>&)> func_2 = BreakVector3Node;
    std::vector<std::string> keywords_2{ "Break", "Vector", "3" };
    search_nodes_vector.push_back(SearchNodeObj("Break Vector 3", "Vector 3", keywords_2, func_2));
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
    return loaded_node;
}