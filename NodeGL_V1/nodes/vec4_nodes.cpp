#include "vec4_nodes.h"

void MakeVector4_Func::Delete()
{
    parent_node = nullptr;
}

void MakeVector4_Func::NoFlowUpdatePinsValues()
{
    float pin_0_value = GetInputPinValue<float>(parent_node, "x");
    float pin_1_value = GetInputPinValue<float>(parent_node, "y");
    float pin_2_value = GetInputPinValue<float>(parent_node, "z");
    float pin_3_value = GetInputPinValue<float>(parent_node, "w");
    std::shared_ptr<PinValue<glm::vec4>> output_pin = std::dynamic_pointer_cast<PinValue<glm::vec4>>(parent_node->outputs.at("out"));
    output_pin->value = glm::vec4(pin_0_value, pin_1_value, pin_2_value, pin_3_value);
}

void MakeVector4_Func::SaveNodeData(rapidjson::Writer<rapidjson::StringBuffer>& writer)
{
    writer.Key("x");
    writer.Double(std::dynamic_pointer_cast<PinValue<float>>(parent_node->inputs.at("x"))->default_value);
    writer.Key("y");
    writer.Double(std::dynamic_pointer_cast<PinValue<float>>(parent_node->inputs.at("y"))->default_value);
    writer.Key("z");
    writer.Double(std::dynamic_pointer_cast<PinValue<float>>(parent_node->inputs.at("z"))->default_value);
    writer.Key("w");
    writer.Double(std::dynamic_pointer_cast<PinValue<float>>(parent_node->inputs.at("w"))->default_value);
}

void MakeVector4_Func::LoadNodeData(rapidjson::Value& node_obj)
{
    std::dynamic_pointer_cast<PinValue<float>>(parent_node->inputs.at("x"))->default_value = node_obj["x"].GetFloat();
    std::dynamic_pointer_cast<PinValue<float>>(parent_node->inputs.at("y"))->default_value = node_obj["y"].GetFloat();
    std::dynamic_pointer_cast<PinValue<float>>(parent_node->inputs.at("z"))->default_value = node_obj["z"].GetFloat();
    std::dynamic_pointer_cast<PinValue<float>>(parent_node->inputs.at("w"))->default_value = node_obj["w"].GetFloat();
}

std::string makeVector4NodeName = "Make Vector 4";
std::shared_ptr<Node> MakeVector4Node(std::vector<std::shared_ptr<Node>>& s_Nodes)
{
    s_Nodes.emplace_back(new Node(GetNextId(), makeVector4NodeName.c_str(), true));
    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<PinValue<float>>>("x", new PinValue<float>("x", 0, GetNextId(), "X", PinType::Float, 0)));
    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<PinValue<float>>>("y", new PinValue<float>("y", 1, GetNextId(), "Y", PinType::Float, 0)));
    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<PinValue<float>>>("z", new PinValue<float>("z", 2, GetNextId(), "Z", PinType::Float, 0)));
    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<PinValue<float>>>("w", new PinValue<float>("w", 3, GetNextId(), "W", PinType::Float, 0)));
    s_Nodes.back()->outputs.insert(std::pair<std::string, std::shared_ptr<PinValue<glm::vec4>>>("out", new PinValue<glm::vec4>("out", 0, GetNextId(), "Out", PinType::Vector4, glm::vec4(0))));

    s_Nodes.back()->node_funcs = std::make_shared<MakeVector4_Func>();
    std::dynamic_pointer_cast<MakeVector4_Func>(s_Nodes.back()->node_funcs)->parent_node = s_Nodes.back();

    s_Nodes.back()->node_funcs->Initialize();

    BuildNode(s_Nodes.back());

    return s_Nodes.back();
}





void BreakVector4_Func::Delete()
{
    parent_node = nullptr;
}

void BreakVector4_Func::NoFlowUpdatePinsValues()
{
    glm::vec4 pin_0_value = GetInputPinValue<glm::vec4>(parent_node, "in");
    std::shared_ptr<PinValue<float>> output_pin_1 = std::dynamic_pointer_cast<PinValue<float>>(parent_node->outputs.at("x"));
    std::shared_ptr<PinValue<float>> output_pin_2 = std::dynamic_pointer_cast<PinValue<float>>(parent_node->outputs.at("y"));
    std::shared_ptr<PinValue<float>> output_pin_3 = std::dynamic_pointer_cast<PinValue<float>>(parent_node->outputs.at("z"));
    std::shared_ptr<PinValue<float>> output_pin_4 = std::dynamic_pointer_cast<PinValue<float>>(parent_node->outputs.at("w"));
    output_pin_1->value = pin_0_value.x;
    output_pin_2->value = pin_0_value.y;
    output_pin_3->value = pin_0_value.z;
    output_pin_4->value = pin_0_value.w;
}

void BreakVector4_Func::SaveNodeData(rapidjson::Writer<rapidjson::StringBuffer>& writer)
{
    glm::vec4 pin_0_value = std::dynamic_pointer_cast<PinValue<glm::vec4>>(parent_node->inputs.at("in"))->default_value;
    writer.Key("x");
    writer.Double(pin_0_value.x);
    writer.Key("y");
    writer.Double(pin_0_value.y);
    writer.Key("z");
    writer.Double(pin_0_value.z);
    writer.Key("w");
    writer.Double(pin_0_value.w);
}

void BreakVector4_Func::LoadNodeData(rapidjson::Value& node_obj)
{
    float x = node_obj["x"].GetFloat();
    float y = node_obj["y"].GetFloat();
    float z = node_obj["z"].GetFloat();
    float w = node_obj["w"].GetFloat();
    std::dynamic_pointer_cast<PinValue<glm::vec4>>(parent_node->inputs.at("in"))->default_value = glm::vec4(x, y, z, w);
}

std::string breakVector4NodeName = "Break Vector 4";
std::shared_ptr<Node> BreakVector4Node(std::vector<std::shared_ptr<Node>>& s_Nodes)
{
    s_Nodes.emplace_back(new Node(GetNextId(), breakVector4NodeName.c_str(), true));
    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<PinValue<glm::vec4>>>("in", new PinValue<glm::vec4>("in", 0, GetNextId(), "In", PinType::Vector4, glm::vec4(0))));
    s_Nodes.back()->outputs.insert(std::pair<std::string, std::shared_ptr<PinValue<float>>>("x", new PinValue<float>("x", 0, GetNextId(), "X", PinType::Float, 0)));
    s_Nodes.back()->outputs.insert(std::pair<std::string, std::shared_ptr<PinValue<float>>>("y", new PinValue<float>("y", 1, GetNextId(), "Y", PinType::Float, 0)));
    s_Nodes.back()->outputs.insert(std::pair<std::string, std::shared_ptr<PinValue<float>>>("z", new PinValue<float>("z", 2, GetNextId(), "Z", PinType::Float, 0)));
    s_Nodes.back()->outputs.insert(std::pair<std::string, std::shared_ptr<PinValue<float>>>("w", new PinValue<float>("w", 3, GetNextId(), "W", PinType::Float, 0)));

    s_Nodes.back()->node_funcs = std::make_shared<BreakVector4_Func>();
    std::dynamic_pointer_cast<BreakVector4_Func>(s_Nodes.back()->node_funcs)->parent_node = s_Nodes.back();

    s_Nodes.back()->node_funcs->Initialize();

    BuildNode(s_Nodes.back());

    return s_Nodes.back();
}





void Vec4NodesSearchSetup(std::vector<SearchNodeObj>& search_nodes_vector)
{
    std::function<std::shared_ptr<Node>(std::vector<std::shared_ptr<Node>>&)> func_1 = MakeVector4Node;
    std::vector<std::string> keywords_1{ "Make", "Vector", "4" };
    search_nodes_vector.push_back(SearchNodeObj("Make Vector 4", "Vector 4", keywords_1, func_1));

    std::function<std::shared_ptr<Node>(std::vector<std::shared_ptr<Node>>&)> func_2 = BreakVector4Node;
    std::vector<std::string> keywords_2{ "Break", "Vector", "4" };
    search_nodes_vector.push_back(SearchNodeObj("Break Vector 4", "Vector 4", keywords_2, func_2));
}

std::shared_ptr<Node> Vec4NodesLoadSetup(std::vector<std::shared_ptr<Node>>& s_Nodes, std::string node_key)
{
    std::shared_ptr<Node> loaded_node = nullptr;
    if (loaded_node == nullptr && node_key.rfind(makeVector4NodeName, 0) == 0) {
        loaded_node = MakeVector4Node(s_Nodes);
    }
    else if (loaded_node == nullptr && node_key.rfind(breakVector4NodeName, 0) == 0) {
        loaded_node = BreakVector4Node(s_Nodes);
    }
    return loaded_node;
}