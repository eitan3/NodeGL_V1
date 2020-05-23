#include "vec2_nodes.h"

void MakeVector2_Func::Delete()
{
    parent_node = nullptr;
}

void MakeVector2_Func::NoFlowUpdatePinsValues()
{
    float pin_0_value = GetInputPinValue<float>(parent_node, "x");
    float pin_1_value = GetInputPinValue<float>(parent_node, "y");
    std::shared_ptr<PinValue<glm::vec2>> output_pin = std::dynamic_pointer_cast<PinValue<glm::vec2>>(parent_node->outputs.at("out"));
    output_pin->value = glm::vec2(pin_0_value, pin_1_value);
}

void MakeVector2_Func::SaveNodeData(rapidjson::Writer<rapidjson::StringBuffer>& writer)
{
    writer.Key("x");
    writer.Double(std::dynamic_pointer_cast<PinValue<float>>(parent_node->inputs.at("x"))->default_value);
    writer.Key("y");
    writer.Double(std::dynamic_pointer_cast<PinValue<float>>(parent_node->inputs.at("y"))->default_value);
}

void MakeVector2_Func::LoadNodeData(rapidjson::Value& node_obj)
{
    std::dynamic_pointer_cast<PinValue<float>>(parent_node->inputs.at("x"))->default_value = node_obj["x"].GetFloat();
    std::dynamic_pointer_cast<PinValue<float>>(parent_node->inputs.at("y"))->default_value = node_obj["y"].GetFloat();
}

std::string makeVector2NodeName = "Make Vector 2";
std::shared_ptr<Node> MakeVector2Node(std::vector<std::shared_ptr<Node>>& s_Nodes)
{
    s_Nodes.emplace_back(new Node(GetNextId(), makeVector2NodeName.c_str(), true));
    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<PinValue<float>>>("x", new PinValue<float>("x", 0, GetNextId(), "X", PinType::Float, 0)));
    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<PinValue<float>>>("y", new PinValue<float>("y", 1, GetNextId(), "Y", PinType::Float, 0)));
    s_Nodes.back()->outputs.insert(std::pair<std::string, std::shared_ptr<PinValue<glm::vec2>>>("out", new PinValue<glm::vec2>("out", 0, GetNextId(), "Out", PinType::Vector2, glm::vec2(0))));

    s_Nodes.back()->node_funcs = std::make_shared<MakeVector2_Func>();
    std::dynamic_pointer_cast<MakeVector2_Func>(s_Nodes.back()->node_funcs)->parent_node = s_Nodes.back();

    s_Nodes.back()->node_funcs->Initialize();

    BuildNode(s_Nodes.back());

    return s_Nodes.back();
}





void BreakVector2_Func::Delete()
{
    parent_node = nullptr;
}

void BreakVector2_Func::NoFlowUpdatePinsValues()
{
    glm::vec2 pin_0_value = GetInputPinValue<glm::vec2>(parent_node, "in");
    std::shared_ptr<PinValue<float>> output_pin_1 = std::dynamic_pointer_cast<PinValue<float>>(parent_node->outputs.at("x"));
    std::shared_ptr<PinValue<float>> output_pin_2 = std::dynamic_pointer_cast<PinValue<float>>(parent_node->outputs.at("y"));
    output_pin_1->value = pin_0_value.x;
    output_pin_2->value = pin_0_value.y;
}

void BreakVector2_Func::SaveNodeData(rapidjson::Writer<rapidjson::StringBuffer>& writer)
{
    glm::vec2 pin_0_value = std::dynamic_pointer_cast<PinValue<glm::vec2>>(parent_node->inputs.at("in"))->default_value;
    writer.Key("x");
    writer.Double(pin_0_value.x);
    writer.Key("y");
    writer.Double(pin_0_value.y);
}

void BreakVector2_Func::LoadNodeData(rapidjson::Value& node_obj)
{
    float x = node_obj["x"].GetFloat();
    float y = node_obj["y"].GetFloat();
    std::dynamic_pointer_cast<PinValue<glm::vec2>>(parent_node->inputs.at("in"))->default_value = glm::vec2(x, y);
}

std::string breakVector2NodeName = "Break Vector 2";
std::shared_ptr<Node> BreakVector2Node(std::vector<std::shared_ptr<Node>>& s_Nodes)
{
    s_Nodes.emplace_back(new Node(GetNextId(), breakVector2NodeName.c_str(), true));
    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<PinValue<glm::vec2>>>("in", new PinValue<glm::vec2>("in", 0, GetNextId(), "In", PinType::Vector2, glm::vec2(0))));
    s_Nodes.back()->outputs.insert(std::pair<std::string, std::shared_ptr<PinValue<float>>>("x", new PinValue<float>("x", 0, GetNextId(), "X", PinType::Float, 0)));
    s_Nodes.back()->outputs.insert(std::pair<std::string, std::shared_ptr<PinValue<float>>>("y", new PinValue<float>("y", 1, GetNextId(), "Y", PinType::Float, 0)));

    s_Nodes.back()->node_funcs = std::make_shared<BreakVector2_Func>();
    std::dynamic_pointer_cast<BreakVector2_Func>(s_Nodes.back()->node_funcs)->parent_node = s_Nodes.back();

    s_Nodes.back()->node_funcs->Initialize();

    BuildNode(s_Nodes.back());

    return s_Nodes.back();
}





void Vec2NodesSearchSetup(std::vector<SearchNodeObj>& search_nodes_vector)
{
    std::function<std::shared_ptr<Node>(std::vector<std::shared_ptr<Node>>&)> func_1 = MakeVector2Node;
    std::vector<std::string> keywords_1{ "Make", "Vector", "2" };
    search_nodes_vector.push_back(SearchNodeObj("Make Vector 2", "Vector 2", keywords_1, func_1));

    std::function<std::shared_ptr<Node>(std::vector<std::shared_ptr<Node>>&)> func_2 = BreakVector2Node;
    std::vector<std::string> keywords_2{ "Break", "Vector", "2" };
    search_nodes_vector.push_back(SearchNodeObj("Break Vector 2", "Vector 2", keywords_2, func_2));
}

std::shared_ptr<Node> Vec2NodesLoadSetup(std::vector<std::shared_ptr<Node>>& s_Nodes, std::string node_key)
{
    std::shared_ptr<Node> loaded_node = nullptr;
    if (loaded_node == nullptr && node_key.rfind(makeVector2NodeName, 0) == 0) {
        loaded_node = MakeVector2Node(s_Nodes);
    }
    else if (loaded_node == nullptr && node_key.rfind(breakVector2NodeName, 0) == 0) {
        loaded_node = BreakVector2Node(s_Nodes);
    }
    return loaded_node;
}