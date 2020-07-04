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




void MakeVectorI2_Func::Delete()
{
    parent_node = nullptr;
}

void MakeVectorI2_Func::NoFlowUpdatePinsValues()
{
    int pin_0_value = GetInputPinValue<int>(parent_node, "x");
    int pin_1_value = GetInputPinValue<int>(parent_node, "y");
    std::shared_ptr<PinValue<glm::ivec2>> output_pin = std::dynamic_pointer_cast<PinValue<glm::ivec2>>(parent_node->outputs.at("out"));
    output_pin->value = glm::ivec2(pin_0_value, pin_1_value);
}

void MakeVectorI2_Func::SaveNodeData(rapidjson::Writer<rapidjson::StringBuffer>& writer)
{
    writer.Key("x");
    writer.Int(std::dynamic_pointer_cast<PinValue<int>>(parent_node->inputs.at("x"))->default_value);
    writer.Key("y");
    writer.Int(std::dynamic_pointer_cast<PinValue<int>>(parent_node->inputs.at("y"))->default_value);
}

void MakeVectorI2_Func::LoadNodeData(rapidjson::Value& node_obj)
{
    std::dynamic_pointer_cast<PinValue<int>>(parent_node->inputs.at("x"))->default_value = node_obj["x"].GetInt();
    std::dynamic_pointer_cast<PinValue<int>>(parent_node->inputs.at("y"))->default_value = node_obj["y"].GetInt();
}

std::string makeVectorI2NodeName = "Make Vector Int 2";
std::shared_ptr<Node> MakeVectorI2Node(std::vector<std::shared_ptr<Node>>& s_Nodes)
{
    s_Nodes.emplace_back(new Node(GetNextId(), makeVectorI2NodeName.c_str(), true));
    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<PinValue<int>>>("x", new PinValue<int>("x", 0, GetNextId(), "X", PinType::Int, 0)));
    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<PinValue<int>>>("y", new PinValue<int>("y", 1, GetNextId(), "Y", PinType::Int, 0)));
    s_Nodes.back()->outputs.insert(std::pair<std::string, std::shared_ptr<PinValue<glm::ivec2>>>("out", new PinValue<glm::ivec2>("out", 0, GetNextId(), "Out", PinType::VectorI2, glm::ivec2(0))));

    s_Nodes.back()->node_funcs = std::make_shared<MakeVectorI2_Func>();
    std::dynamic_pointer_cast<MakeVectorI2_Func>(s_Nodes.back()->node_funcs)->parent_node = s_Nodes.back();

    s_Nodes.back()->node_funcs->Initialize();

    BuildNode(s_Nodes.back());

    return s_Nodes.back();
}




void BreakVectorI2_Func::Delete()
{
    parent_node = nullptr;
}

void BreakVectorI2_Func::NoFlowUpdatePinsValues()
{
    glm::ivec2 pin_0_value = GetInputPinValue<glm::ivec2>(parent_node, "in");
    std::shared_ptr<PinValue<int>> output_pin_1 = std::dynamic_pointer_cast<PinValue<int>>(parent_node->outputs.at("x"));
    std::shared_ptr<PinValue<int>> output_pin_2 = std::dynamic_pointer_cast<PinValue<int>>(parent_node->outputs.at("y"));
    output_pin_1->value = pin_0_value.x;
    output_pin_2->value = pin_0_value.y;
}

void BreakVectorI2_Func::SaveNodeData(rapidjson::Writer<rapidjson::StringBuffer>& writer)
{
    glm::ivec2 pin_0_value = std::dynamic_pointer_cast<PinValue<glm::ivec2>>(parent_node->inputs.at("in"))->default_value;
    writer.Key("x");
    writer.Int(pin_0_value.x);
    writer.Key("y");
    writer.Int(pin_0_value.y);
}

void BreakVectorI2_Func::LoadNodeData(rapidjson::Value& node_obj)
{
    int x = node_obj["x"].GetInt();
    int y = node_obj["y"].GetInt();
    std::dynamic_pointer_cast<PinValue<glm::ivec2>>(parent_node->inputs.at("in"))->default_value = glm::ivec2(x, y);
}

std::string breakVectorI2NodeName = "Break Vector Int 2";
std::shared_ptr<Node> BreakVectorI2Node(std::vector<std::shared_ptr<Node>>& s_Nodes)
{
    s_Nodes.emplace_back(new Node(GetNextId(), breakVectorI2NodeName.c_str(), true));
    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<PinValue<glm::ivec2>>>("in", new PinValue<glm::ivec2>("in", 0, GetNextId(), "In", PinType::VectorI2, glm::ivec2(0))));
    s_Nodes.back()->outputs.insert(std::pair<std::string, std::shared_ptr<PinValue<int>>>("x", new PinValue<int>("x", 0, GetNextId(), "X", PinType::Int, 0)));
    s_Nodes.back()->outputs.insert(std::pair<std::string, std::shared_ptr<PinValue<int>>>("y", new PinValue<int>("y", 1, GetNextId(), "Y", PinType::Int, 0)));

    s_Nodes.back()->node_funcs = std::make_shared<BreakVectorI2_Func>();
    std::dynamic_pointer_cast<BreakVectorI2_Func>(s_Nodes.back()->node_funcs)->parent_node = s_Nodes.back();

    s_Nodes.back()->node_funcs->Initialize();

    BuildNode(s_Nodes.back());

    return s_Nodes.back();
}




void Vector2Normalize_Func::Delete()
{
    parent_node = nullptr;
}

void Vector2Normalize_Func::NoFlowUpdatePinsValues()
{
    glm::vec2 pin_1_value = GetInputPinValue<glm::vec2>(parent_node, "in_1");
    glm::vec2 out_val = glm::normalize(pin_1_value);
    std::shared_ptr<PinValue<glm::vec2>> output_pin = std::dynamic_pointer_cast<PinValue<glm::vec2>>(parent_node->outputs.at("out"));
    output_pin->value = out_val;
}

void Vector2Normalize_Func::SaveNodeData(rapidjson::Writer<rapidjson::StringBuffer>& writer)
{
    glm::vec2 pin_1_value = std::dynamic_pointer_cast<PinValue<glm::vec2>>(parent_node->inputs.at("in_1"))->default_value;
    writer.Key("x_1");
    writer.Double(pin_1_value.x);
    writer.Key("y_1");
    writer.Double(pin_1_value.y);
}

void Vector2Normalize_Func::LoadNodeData(rapidjson::Value& node_obj)
{
    float x_1 = node_obj["x_1"].GetFloat();
    float y_1 = node_obj["y_1"].GetFloat();
    std::dynamic_pointer_cast<PinValue<glm::vec2>>(parent_node->inputs.at("in_1"))->default_value = glm::vec2(x_1, y_1);
}

std::string vector2NormalizeNodeName = "Normalize - Vector 2";
std::shared_ptr<Node> Vector2NormalizeNode(std::vector<std::shared_ptr<Node>>& s_Nodes)
{
    s_Nodes.emplace_back(new Node(GetNextId(), vector2NormalizeNodeName.c_str(), true));
    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<PinValue<glm::vec2>>>("in_1", new PinValue<glm::vec2>("in_1", 0, GetNextId(), "In 1", PinType::Vector2, glm::vec2(1))));

    s_Nodes.back()->outputs.insert(std::pair<std::string, std::shared_ptr<PinValue<glm::vec2>>>("out", new PinValue<glm::vec2>("out", 0, GetNextId(), "Out", PinType::Vector2, glm::vec2(0))));

    s_Nodes.back()->node_funcs = std::make_shared<Vector2Normalize_Func>();
    std::dynamic_pointer_cast<Vector2Normalize_Func>(s_Nodes.back()->node_funcs)->parent_node = s_Nodes.back();

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

    std::function<std::shared_ptr<Node>(std::vector<std::shared_ptr<Node>>&)> func_3 = MakeVectorI2Node;
    std::vector<std::string> keywords_3{ "Make", "Vector", "Int", "2" };
    search_nodes_vector.push_back(SearchNodeObj("Make Vector Int 2", "Vector 2", keywords_3, func_3));

    std::function<std::shared_ptr<Node>(std::vector<std::shared_ptr<Node>>&)> func_4 = BreakVectorI2Node;
    std::vector<std::string> keywords_4{ "Break", "Vector", "Int", "2" };
    search_nodes_vector.push_back(SearchNodeObj("Break Vector Int 2", "Vector 2", keywords_4, func_4));

    std::function<std::shared_ptr<Node>(std::vector<std::shared_ptr<Node>>&)> func_5 = Vector2NormalizeNode;
    std::vector<std::string> keywords_5{ "Normalize", "Vector", "2" };
    search_nodes_vector.push_back(SearchNodeObj("Normalize - Vector 2", "Vector 2", keywords_5, func_5));
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
    else if (loaded_node == nullptr && node_key.rfind(makeVectorI2NodeName, 0) == 0) {
        loaded_node = MakeVectorI2Node(s_Nodes);
    }
    else if (loaded_node == nullptr && node_key.rfind(breakVectorI2NodeName, 0) == 0) {
        loaded_node = BreakVectorI2Node(s_Nodes);
    }
    else if (loaded_node == nullptr && node_key.rfind(vector2NormalizeNodeName, 0) == 0) {
        loaded_node = Vector2NormalizeNode(s_Nodes);
    }
    return loaded_node;
}