#include "math_nodes.h"

void MathPlusNode_Func::Delete()
{
    parent_node = nullptr;
}

void MathPlusNode_Func::NoFlowUpdatePinsValues()
{
    if (parent_node->inputs.at("x_1")->type == PinType::Int && parent_node->inputs.at("x_2")->type == PinType::Int)
    {
        int pin_0_value = GetInputPinValue<int>(parent_node, "x_1");
        int pin_1_value = GetInputPinValue<int>(parent_node, "x_2");
        if (parent_node->outputs.at("out")->type == PinType::Int)
        {
            std::shared_ptr<PinValue<int>> output_pin = std::dynamic_pointer_cast<PinValue<int>>(parent_node->outputs.at("out"));
            output_pin->value = (int)(pin_0_value + pin_1_value);
        }
        else if (parent_node->outputs.at("out")->type == PinType::Float)
        {
            std::shared_ptr<PinValue<float>> output_pin = std::dynamic_pointer_cast<PinValue<float>>(parent_node->outputs.at("out"));
            output_pin->value = pin_0_value + pin_1_value;
        }
    }
    else if (parent_node->inputs.at("x_1")->type == PinType::Float && parent_node->inputs.at("x_2")->type == PinType::Int)
    {
        float pin_0_value = GetInputPinValue<float>(parent_node, "x_1");
        int pin_1_value = GetInputPinValue<int>(parent_node, "x_2");
        if (parent_node->outputs.at("out")->type == PinType::Int)
        {
            std::shared_ptr<PinValue<int>> output_pin = std::dynamic_pointer_cast<PinValue<int>>(parent_node->outputs.at("out"));
            output_pin->value = (int)(pin_0_value + pin_1_value);
        }
        else if (parent_node->outputs.at("out")->type == PinType::Float)
        {
            std::shared_ptr<PinValue<float>> output_pin = std::dynamic_pointer_cast<PinValue<float>>(parent_node->outputs.at("out"));
            output_pin->value = pin_0_value + pin_1_value;
        }
    }
    else if (parent_node->inputs.at("x_1")->type == PinType::Int && parent_node->inputs.at("x_2")->type == PinType::Float)
    {
        int pin_0_value = GetInputPinValue<int>(parent_node, "x_1");
        float pin_1_value = GetInputPinValue<float>(parent_node, "x_2");
        if (parent_node->outputs.at("out")->type == PinType::Int)
        {
            std::shared_ptr<PinValue<int>> output_pin = std::dynamic_pointer_cast<PinValue<int>>(parent_node->outputs.at("out"));
            output_pin->value = (int)(pin_0_value + pin_1_value);
        }
        else if (parent_node->outputs.at("out")->type == PinType::Float)
        {
            std::shared_ptr<PinValue<float>> output_pin = std::dynamic_pointer_cast<PinValue<float>>(parent_node->outputs.at("out"));
            output_pin->value = pin_0_value + pin_1_value;
        }
    }
    else if (parent_node->inputs.at("x_1")->type == PinType::Float && parent_node->inputs.at("x_2")->type == PinType::Float)
    {
        float pin_0_value = GetInputPinValue<float>(parent_node, "x_1");
        float pin_1_value = GetInputPinValue<float>(parent_node, "x_2");
        if (parent_node->outputs.at("out")->type == PinType::Int)
        {
            std::shared_ptr<PinValue<int>> output_pin = std::dynamic_pointer_cast<PinValue<int>>(parent_node->outputs.at("out"));
            output_pin->value = (int)(pin_0_value + pin_1_value);
        }
        else if (parent_node->outputs.at("out")->type == PinType::Float)
        {
            std::shared_ptr<PinValue<float>> output_pin = std::dynamic_pointer_cast<PinValue<float>>(parent_node->outputs.at("out"));
            output_pin->value = pin_0_value + pin_1_value;
        }
    }
}

void MathPlusNode_Func::SaveNodeData(rapidjson::Writer<rapidjson::StringBuffer>& writer)
{
    writer.Key("x_1");
    if (parent_node->inputs.at("x_1")->type == PinType::Float)
    {
        writer.Double(std::dynamic_pointer_cast<PinValue<float>>(parent_node->inputs.at("x_1"))->default_value);
    }
    else if (parent_node->inputs.at("x_1")->type == PinType::Int)
    {
        writer.Int(std::dynamic_pointer_cast<PinValue<int>>(parent_node->inputs.at("x_1"))->default_value);
    }
    writer.Key("x_1_type");
    writer.String(PinTypeToString(parent_node->inputs.at("x_1")->type).c_str());

    writer.Key("x_2");
    if (parent_node->inputs.at("x_2")->type == PinType::Float)
    {
        writer.Double(std::dynamic_pointer_cast<PinValue<float>>(parent_node->inputs.at("x_2"))->default_value);
    }
    else if (parent_node->inputs.at("x_2")->type == PinType::Int)
    {
        writer.Int(std::dynamic_pointer_cast<PinValue<int>>(parent_node->inputs.at("x_2"))->default_value);
    }
    writer.Key("x_2_type");
    writer.String(PinTypeToString(parent_node->inputs.at("x_2")->type).c_str());
    writer.Key("out_type");
    writer.String(PinTypeToString(parent_node->outputs.at("out")->type).c_str());
}

void MathPlusNode_Func::LoadNodeData(rapidjson::Value& node_obj)
{
    PinType x1_type = StringToPinType(std::string(node_obj["x_1_type"].GetString()));
    PinType x2_type = StringToPinType(std::string(node_obj["x_2_type"].GetString()));
    PinType out_type = StringToPinType(std::string(node_obj["out_type"].GetString()));
    UtilsChangePinType(parent_node, PinKind::Input, "x_1", x1_type, false);
    UtilsChangePinType(parent_node, PinKind::Input, "x_2", x2_type, false);
    UtilsChangePinType(parent_node, PinKind::Output, "out", out_type, false);
    
    if (parent_node->inputs.at("x_1")->type == PinType::Float)
        std::dynamic_pointer_cast<PinValue<float>>(parent_node->inputs.at("x_1"))->default_value = node_obj["x_1"].GetFloat();
    else if (parent_node->inputs.at("x_1")->type == PinType::Int)
        std::dynamic_pointer_cast<PinValue<int>>(parent_node->inputs.at("x_1"))->default_value = node_obj["x_1"].GetInt();
    
    if (parent_node->inputs.at("x_2")->type == PinType::Float)
        std::dynamic_pointer_cast<PinValue<float>>(parent_node->inputs.at("x_2"))->default_value = node_obj["x_2"].GetFloat();
    else if (parent_node->inputs.at("x_2")->type == PinType::Int)
        std::dynamic_pointer_cast<PinValue<int>>(parent_node->inputs.at("x_2"))->default_value = node_obj["x_2"].GetInt();
}

std::string mathPlusNodeName = "Plus ( + )";
std::shared_ptr<Node> MathPlusNode(std::vector<std::shared_ptr<Node>>& s_Nodes)
{
    s_Nodes.emplace_back(new Node(GetNextId(), mathPlusNodeName.c_str(), true));
    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<PinValue<float>>>("x_1", new PinValue<float>("x_1", 0, GetNextId(), "X 1", PinType::Float, 0)));
    s_Nodes.back()->inputs.at("x_1")->isTemplate = true;;
    s_Nodes.back()->inputs.at("x_1")->template_allowed_types.push_back(PinType::Float);
    s_Nodes.back()->inputs.at("x_1")->template_allowed_types.push_back(PinType::Int);
    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<PinValue<float>>>("x_2", new PinValue<float>("x_2", 1, GetNextId(), "X 2", PinType::Float, 0)));
    s_Nodes.back()->inputs.at("x_2")->isTemplate = true;;
    s_Nodes.back()->inputs.at("x_2")->template_allowed_types.push_back(PinType::Float);
    s_Nodes.back()->inputs.at("x_2")->template_allowed_types.push_back(PinType::Int);
    s_Nodes.back()->outputs.insert(std::pair<std::string, std::shared_ptr<PinValue<float>>>("out", new PinValue<float>("out", 0, GetNextId(), "Out", PinType::Float, 0)));
    s_Nodes.back()->outputs.at("out")->isTemplate = true;
    s_Nodes.back()->outputs.at("out")->template_allowed_types.push_back(PinType::Float);
    s_Nodes.back()->outputs.at("out")->template_allowed_types.push_back(PinType::Int);

    s_Nodes.back()->node_funcs = std::make_shared<MathPlusNode_Func>();
    std::dynamic_pointer_cast<MathPlusNode_Func>(s_Nodes.back()->node_funcs)->parent_node = s_Nodes.back();

    s_Nodes.back()->node_funcs->Initialize();

    BuildNode(s_Nodes.back());

    return s_Nodes.back();
}





void MathMinusNode_Func::Delete()
{
    parent_node = nullptr;
}

void MathMinusNode_Func::NoFlowUpdatePinsValues()
{
    if (parent_node->inputs.at("x_1")->type == PinType::Int && parent_node->inputs.at("x_2")->type == PinType::Int)
    {
        int pin_0_value = GetInputPinValue<int>(parent_node, "x_1");
        int pin_1_value = GetInputPinValue<int>(parent_node, "x_2");
        if (parent_node->outputs.at("out")->type == PinType::Int)
        {
            std::shared_ptr<PinValue<int>> output_pin = std::dynamic_pointer_cast<PinValue<int>>(parent_node->outputs.at("out"));
            output_pin->value = (int)(pin_0_value - pin_1_value);
        }
        else if (parent_node->outputs.at("out")->type == PinType::Float)
        {
            std::shared_ptr<PinValue<float>> output_pin = std::dynamic_pointer_cast<PinValue<float>>(parent_node->outputs.at("out"));
            output_pin->value = pin_0_value - pin_1_value;
        }
    }
    else if (parent_node->inputs.at("x_1")->type == PinType::Float && parent_node->inputs.at("x_2")->type == PinType::Int)
    {
        float pin_0_value = GetInputPinValue<float>(parent_node, "x_1");
        int pin_1_value = GetInputPinValue<int>(parent_node, "x_2");
        if (parent_node->outputs.at("out")->type == PinType::Int)
        {
            std::shared_ptr<PinValue<int>> output_pin = std::dynamic_pointer_cast<PinValue<int>>(parent_node->outputs.at("out"));
            output_pin->value = (int)(pin_0_value - pin_1_value);
        }
        else if (parent_node->outputs.at("out")->type == PinType::Float)
        {
            std::shared_ptr<PinValue<float>> output_pin = std::dynamic_pointer_cast<PinValue<float>>(parent_node->outputs.at("out"));
            output_pin->value = pin_0_value - pin_1_value;
        }
    }
    else if (parent_node->inputs.at("x_1")->type == PinType::Int && parent_node->inputs.at("x_2")->type == PinType::Float)
    {
        int pin_0_value = GetInputPinValue<int>(parent_node, "x_1");
        float pin_1_value = GetInputPinValue<float>(parent_node, "x_2");
        if (parent_node->outputs.at("out")->type == PinType::Int)
        {
            std::shared_ptr<PinValue<int>> output_pin = std::dynamic_pointer_cast<PinValue<int>>(parent_node->outputs.at("out"));
            output_pin->value = (int)(pin_0_value - pin_1_value);
        }
        else if (parent_node->outputs.at("out")->type == PinType::Float)
        {
            std::shared_ptr<PinValue<float>> output_pin = std::dynamic_pointer_cast<PinValue<float>>(parent_node->outputs.at("out"));
            output_pin->value = pin_0_value - pin_1_value;
        }
    }
    else if (parent_node->inputs.at("x_1")->type == PinType::Float && parent_node->inputs.at("x_2")->type == PinType::Float)
    {
        float pin_0_value = GetInputPinValue<float>(parent_node, "x_1");
        float pin_1_value = GetInputPinValue<float>(parent_node, "x_2");
        if (parent_node->outputs.at("out")->type == PinType::Int)
        {
            std::shared_ptr<PinValue<int>> output_pin = std::dynamic_pointer_cast<PinValue<int>>(parent_node->outputs.at("out"));
            output_pin->value = (int)(pin_0_value - pin_1_value);
        }
        else if (parent_node->outputs.at("out")->type == PinType::Float)
        {
            std::shared_ptr<PinValue<float>> output_pin = std::dynamic_pointer_cast<PinValue<float>>(parent_node->outputs.at("out"));
            output_pin->value = pin_0_value - pin_1_value;
        }
    }
}

void MathMinusNode_Func::SaveNodeData(rapidjson::Writer<rapidjson::StringBuffer>& writer)
{
    writer.Key("x_1");
    if (parent_node->inputs.at("x_1")->type == PinType::Float)
    {
        writer.Double(std::dynamic_pointer_cast<PinValue<float>>(parent_node->inputs.at("x_1"))->default_value);
    }
    else if (parent_node->inputs.at("x_1")->type == PinType::Int)
    {
        writer.Int(std::dynamic_pointer_cast<PinValue<int>>(parent_node->inputs.at("x_1"))->default_value);
    }
    writer.Key("x_1_type");
    writer.String(PinTypeToString(parent_node->inputs.at("x_1")->type).c_str());

    writer.Key("x_2");
    if (parent_node->inputs.at("x_2")->type == PinType::Float)
    {
        writer.Double(std::dynamic_pointer_cast<PinValue<float>>(parent_node->inputs.at("x_2"))->default_value);
    }
    else if (parent_node->inputs.at("x_2")->type == PinType::Int)
    {
        writer.Int(std::dynamic_pointer_cast<PinValue<int>>(parent_node->inputs.at("x_2"))->default_value);
    }
    writer.Key("x_2_type");
    writer.String(PinTypeToString(parent_node->inputs.at("x_2")->type).c_str());
    writer.Key("out_type");
    writer.String(PinTypeToString(parent_node->outputs.at("out")->type).c_str());
}

void MathMinusNode_Func::LoadNodeData(rapidjson::Value& node_obj)
{
    PinType x1_type = StringToPinType(std::string(node_obj["x_1_type"].GetString()));
    PinType x2_type = StringToPinType(std::string(node_obj["x_2_type"].GetString()));
    PinType out_type = StringToPinType(std::string(node_obj["out_type"].GetString()));
    UtilsChangePinType(parent_node, PinKind::Input, "x_1", x1_type, false);
    UtilsChangePinType(parent_node, PinKind::Input, "x_2", x2_type, false);
    UtilsChangePinType(parent_node, PinKind::Output, "out", out_type, false);

    if (parent_node->inputs.at("x_1")->type == PinType::Float)
        std::dynamic_pointer_cast<PinValue<float>>(parent_node->inputs.at("x_1"))->default_value = node_obj["x_1"].GetFloat();
    else if (parent_node->inputs.at("x_1")->type == PinType::Int)
        std::dynamic_pointer_cast<PinValue<int>>(parent_node->inputs.at("x_1"))->default_value = node_obj["x_1"].GetInt();

    if (parent_node->inputs.at("x_2")->type == PinType::Float)
        std::dynamic_pointer_cast<PinValue<float>>(parent_node->inputs.at("x_2"))->default_value = node_obj["x_2"].GetFloat();
    else if (parent_node->inputs.at("x_2")->type == PinType::Int)
        std::dynamic_pointer_cast<PinValue<int>>(parent_node->inputs.at("x_2"))->default_value = node_obj["x_2"].GetInt();
}

std::string mathMinusNodeName = "Minus ( - )";
std::shared_ptr<Node> MathMinusNode(std::vector<std::shared_ptr<Node>>& s_Nodes)
{
    s_Nodes.emplace_back(new Node(GetNextId(), mathMinusNodeName.c_str(), true));

    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<PinValue<float>>>("x_1", new PinValue<float>("x_1", 0, GetNextId(), "X 1", PinType::Float, 0)));
    s_Nodes.back()->inputs.at("x_1")->isTemplate = true;;
    s_Nodes.back()->inputs.at("x_1")->template_allowed_types.push_back(PinType::Float);
    s_Nodes.back()->inputs.at("x_1")->template_allowed_types.push_back(PinType::Int);
    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<PinValue<float>>>("x_2", new PinValue<float>("x_2", 1, GetNextId(), "X 2", PinType::Float, 0)));
    s_Nodes.back()->inputs.at("x_2")->isTemplate = true;;
    s_Nodes.back()->inputs.at("x_2")->template_allowed_types.push_back(PinType::Float);
    s_Nodes.back()->inputs.at("x_2")->template_allowed_types.push_back(PinType::Int);
    s_Nodes.back()->outputs.insert(std::pair<std::string, std::shared_ptr<PinValue<float>>>("out", new PinValue<float>("out", 0, GetNextId(), "Out", PinType::Float, 0)));
    s_Nodes.back()->outputs.at("out")->isTemplate = true;
    s_Nodes.back()->outputs.at("out")->template_allowed_types.push_back(PinType::Float);
    s_Nodes.back()->outputs.at("out")->template_allowed_types.push_back(PinType::Int);

    s_Nodes.back()->node_funcs = std::make_shared<MathMinusNode_Func>();
    std::dynamic_pointer_cast<MathMinusNode_Func>(s_Nodes.back()->node_funcs)->parent_node = s_Nodes.back();

    s_Nodes.back()->node_funcs->Initialize();

    BuildNode(s_Nodes.back());

    return s_Nodes.back();
}





void MathMultiplyNode_Func::Delete()
{
    parent_node = nullptr;
}

void MathMultiplyNode_Func::NoFlowUpdatePinsValues()
{
    if (parent_node->inputs.at("x_1")->type == PinType::Int && parent_node->inputs.at("x_2")->type == PinType::Int)
    {
        int pin_0_value = GetInputPinValue<int>(parent_node, "x_1");
        int pin_1_value = GetInputPinValue<int>(parent_node, "x_2");
        if (parent_node->outputs.at("out")->type == PinType::Int)
        {
            std::shared_ptr<PinValue<int>> output_pin = std::dynamic_pointer_cast<PinValue<int>>(parent_node->outputs.at("out"));
            output_pin->value = (int)(pin_0_value * pin_1_value);
        }
        else if (parent_node->outputs.at("out")->type == PinType::Float)
        {
            std::shared_ptr<PinValue<float>> output_pin = std::dynamic_pointer_cast<PinValue<float>>(parent_node->outputs.at("out"));
            output_pin->value = pin_0_value * pin_1_value;
        }
    }
    else if (parent_node->inputs.at("x_1")->type == PinType::Float && parent_node->inputs.at("x_2")->type == PinType::Int)
    {
        float pin_0_value = GetInputPinValue<float>(parent_node, "x_1");
        int pin_1_value = GetInputPinValue<int>(parent_node, "x_2");
        if (parent_node->outputs.at("out")->type == PinType::Int)
        {
            std::shared_ptr<PinValue<int>> output_pin = std::dynamic_pointer_cast<PinValue<int>>(parent_node->outputs.at("out"));
            output_pin->value = (int)(pin_0_value * pin_1_value);
        }
        else if (parent_node->outputs.at("out")->type == PinType::Float)
        {
            std::shared_ptr<PinValue<float>> output_pin = std::dynamic_pointer_cast<PinValue<float>>(parent_node->outputs.at("out"));
            output_pin->value = pin_0_value * pin_1_value;
        }
    }
    else if (parent_node->inputs.at("x_1")->type == PinType::Int && parent_node->inputs.at("x_2")->type == PinType::Float)
    {
        int pin_0_value = GetInputPinValue<int>(parent_node, "x_1");
        float pin_1_value = GetInputPinValue<float>(parent_node, "x_2");
        if (parent_node->outputs.at("out")->type == PinType::Int)
        {
            std::shared_ptr<PinValue<int>> output_pin = std::dynamic_pointer_cast<PinValue<int>>(parent_node->outputs.at("out"));
            output_pin->value = (int)(pin_0_value * pin_1_value);
        }
        else if (parent_node->outputs.at("out")->type == PinType::Float)
        {
            std::shared_ptr<PinValue<float>> output_pin = std::dynamic_pointer_cast<PinValue<float>>(parent_node->outputs.at("out"));
            output_pin->value = pin_0_value * pin_1_value;
        }
    }
    else if (parent_node->inputs.at("x_1")->type == PinType::Float && parent_node->inputs.at("x_2")->type == PinType::Float)
    {
        float pin_0_value = GetInputPinValue<float>(parent_node, "x_1");
        float pin_1_value = GetInputPinValue<float>(parent_node, "x_2");
        if (parent_node->outputs.at("out")->type == PinType::Int)
        {
            std::shared_ptr<PinValue<int>> output_pin = std::dynamic_pointer_cast<PinValue<int>>(parent_node->outputs.at("out"));
            output_pin->value = (int)(pin_0_value * pin_1_value);
        }
        else if (parent_node->outputs.at("out")->type == PinType::Float)
        {
            std::shared_ptr<PinValue<float>> output_pin = std::dynamic_pointer_cast<PinValue<float>>(parent_node->outputs.at("out"));
            output_pin->value = pin_0_value * pin_1_value;
        }
    }
}

void MathMultiplyNode_Func::SaveNodeData(rapidjson::Writer<rapidjson::StringBuffer>& writer)
{
    writer.Key("x_1");
    if (parent_node->inputs.at("x_1")->type == PinType::Float)
    {
        writer.Double(std::dynamic_pointer_cast<PinValue<float>>(parent_node->inputs.at("x_1"))->default_value);
    }
    else if (parent_node->inputs.at("x_1")->type == PinType::Int)
    {
        writer.Int(std::dynamic_pointer_cast<PinValue<int>>(parent_node->inputs.at("x_1"))->default_value);
    }
    writer.Key("x_1_type");
    writer.String(PinTypeToString(parent_node->inputs.at("x_1")->type).c_str());

    writer.Key("x_2");
    if (parent_node->inputs.at("x_2")->type == PinType::Float)
    {
        writer.Double(std::dynamic_pointer_cast<PinValue<float>>(parent_node->inputs.at("x_2"))->default_value);
    }
    else if (parent_node->inputs.at("x_2")->type == PinType::Int)
    {
        writer.Int(std::dynamic_pointer_cast<PinValue<int>>(parent_node->inputs.at("x_2"))->default_value);
    }
    writer.Key("x_2_type");
    writer.String(PinTypeToString(parent_node->inputs.at("x_2")->type).c_str());
    writer.Key("out_type");
    writer.String(PinTypeToString(parent_node->outputs.at("out")->type).c_str());
}

void MathMultiplyNode_Func::LoadNodeData(rapidjson::Value& node_obj)
{
    PinType x1_type = StringToPinType(std::string(node_obj["x_1_type"].GetString()));
    PinType x2_type = StringToPinType(std::string(node_obj["x_2_type"].GetString()));
    PinType out_type = StringToPinType(std::string(node_obj["out_type"].GetString()));
    UtilsChangePinType(parent_node, PinKind::Input, "x_1", x1_type, false);
    UtilsChangePinType(parent_node, PinKind::Input, "x_2", x2_type, false);
    UtilsChangePinType(parent_node, PinKind::Output, "out", out_type, false);

    if (parent_node->inputs.at("x_1")->type == PinType::Float)
        std::dynamic_pointer_cast<PinValue<float>>(parent_node->inputs.at("x_1"))->default_value = node_obj["x_1"].GetFloat();
    else if (parent_node->inputs.at("x_1")->type == PinType::Int)
        std::dynamic_pointer_cast<PinValue<int>>(parent_node->inputs.at("x_1"))->default_value = node_obj["x_1"].GetInt();

    if (parent_node->inputs.at("x_2")->type == PinType::Float)
        std::dynamic_pointer_cast<PinValue<float>>(parent_node->inputs.at("x_2"))->default_value = node_obj["x_2"].GetFloat();
    else if (parent_node->inputs.at("x_2")->type == PinType::Int)
        std::dynamic_pointer_cast<PinValue<int>>(parent_node->inputs.at("x_2"))->default_value = node_obj["x_2"].GetInt();
}

std::string mathMultiplyNodeName = "Multiply ( * )";
std::shared_ptr<Node> MathMultiplyNode(std::vector<std::shared_ptr<Node>>& s_Nodes)
{
    s_Nodes.emplace_back(new Node(GetNextId(), mathMultiplyNodeName.c_str(), true));

    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<PinValue<float>>>("x_1", new PinValue<float>("x_1", 0, GetNextId(), "X 1", PinType::Float, 0)));
    s_Nodes.back()->inputs.at("x_1")->isTemplate = true;;
    s_Nodes.back()->inputs.at("x_1")->template_allowed_types.push_back(PinType::Float);
    s_Nodes.back()->inputs.at("x_1")->template_allowed_types.push_back(PinType::Int);
    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<PinValue<float>>>("x_2", new PinValue<float>("x_2", 1, GetNextId(), "X 2", PinType::Float, 0)));
    s_Nodes.back()->inputs.at("x_2")->isTemplate = true;;
    s_Nodes.back()->inputs.at("x_2")->template_allowed_types.push_back(PinType::Float);
    s_Nodes.back()->inputs.at("x_2")->template_allowed_types.push_back(PinType::Int);
    s_Nodes.back()->outputs.insert(std::pair<std::string, std::shared_ptr<PinValue<float>>>("out", new PinValue<float>("out", 0, GetNextId(), "Out", PinType::Float, 0)));
    s_Nodes.back()->outputs.at("out")->isTemplate = true;
    s_Nodes.back()->outputs.at("out")->template_allowed_types.push_back(PinType::Float);
    s_Nodes.back()->outputs.at("out")->template_allowed_types.push_back(PinType::Int);

    s_Nodes.back()->node_funcs = std::make_shared<MathMultiplyNode_Func>();
    std::dynamic_pointer_cast<MathMultiplyNode_Func>(s_Nodes.back()->node_funcs)->parent_node = s_Nodes.back();

    s_Nodes.back()->node_funcs->Initialize();

    BuildNode(s_Nodes.back());

    return s_Nodes.back();
}





void MathDivideNode_Func::Delete()
{
    parent_node = nullptr;
}

void MathDivideNode_Func::NoFlowUpdatePinsValues()
{
    if (parent_node->inputs.at("x_1")->type == PinType::Int && parent_node->inputs.at("x_2")->type == PinType::Int)
    {
        int pin_0_value = GetInputPinValue<int>(parent_node, "x_1");
        int pin_1_value = GetInputPinValue<int>(parent_node, "x_2");
        if (pin_1_value == 0)
            pin_1_value = 1;
        if (parent_node->outputs.at("out")->type == PinType::Int)
        {
            std::shared_ptr<PinValue<int>> output_pin = std::dynamic_pointer_cast<PinValue<int>>(parent_node->outputs.at("out"));
            output_pin->value = (int)(pin_0_value / pin_1_value);
        }
        else if (parent_node->outputs.at("out")->type == PinType::Float)
        {
            std::shared_ptr<PinValue<float>> output_pin = std::dynamic_pointer_cast<PinValue<float>>(parent_node->outputs.at("out"));
            output_pin->value = pin_0_value / pin_1_value;
        }
    }
    else if (parent_node->inputs.at("x_1")->type == PinType::Float && parent_node->inputs.at("x_2")->type == PinType::Int)
    {
        float pin_0_value = GetInputPinValue<float>(parent_node, "x_1");
        int pin_1_value = GetInputPinValue<int>(parent_node, "x_2");
        if (pin_1_value == 0)
            pin_1_value = 1;
        if (parent_node->outputs.at("out")->type == PinType::Int)
        {
            std::shared_ptr<PinValue<int>> output_pin = std::dynamic_pointer_cast<PinValue<int>>(parent_node->outputs.at("out"));
            output_pin->value = (int)(pin_0_value / pin_1_value);
        }
        else if (parent_node->outputs.at("out")->type == PinType::Float)
        {
            std::shared_ptr<PinValue<float>> output_pin = std::dynamic_pointer_cast<PinValue<float>>(parent_node->outputs.at("out"));
            output_pin->value = pin_0_value / pin_1_value;
        }
    }
    else if (parent_node->inputs.at("x_1")->type == PinType::Int && parent_node->inputs.at("x_2")->type == PinType::Float)
    {
        int pin_0_value = GetInputPinValue<int>(parent_node, "x_1");
        float pin_1_value = GetInputPinValue<float>(parent_node, "x_2");
        if (pin_1_value == 0)
            pin_1_value = 1;
        if (parent_node->outputs.at("out")->type == PinType::Int)
        {
            std::shared_ptr<PinValue<int>> output_pin = std::dynamic_pointer_cast<PinValue<int>>(parent_node->outputs.at("out"));
            output_pin->value = (int)(pin_0_value / pin_1_value);
        }
        else if (parent_node->outputs.at("out")->type == PinType::Float)
        {
            std::shared_ptr<PinValue<float>> output_pin = std::dynamic_pointer_cast<PinValue<float>>(parent_node->outputs.at("out"));
            output_pin->value = pin_0_value / pin_1_value;
        }
    }
    else if (parent_node->inputs.at("x_1")->type == PinType::Float && parent_node->inputs.at("x_2")->type == PinType::Float)
    {
        float pin_0_value = GetInputPinValue<float>(parent_node, "x_1");
        float pin_1_value = GetInputPinValue<float>(parent_node, "x_2");
        if (pin_1_value == 0)
            pin_1_value = 1;
        if (parent_node->outputs.at("out")->type == PinType::Int)
        {
            std::shared_ptr<PinValue<int>> output_pin = std::dynamic_pointer_cast<PinValue<int>>(parent_node->outputs.at("out"));
            output_pin->value = (int)(pin_0_value / pin_1_value);
        }
        else if (parent_node->outputs.at("out")->type == PinType::Float)
        {
            std::shared_ptr<PinValue<float>> output_pin = std::dynamic_pointer_cast<PinValue<float>>(parent_node->outputs.at("out"));
            output_pin->value = pin_0_value / pin_1_value;
        }
    }
}

void MathDivideNode_Func::SaveNodeData(rapidjson::Writer<rapidjson::StringBuffer>& writer)
{
    writer.Key("x_1");
    if (parent_node->inputs.at("x_1")->type == PinType::Float)
    {
        writer.Double(std::dynamic_pointer_cast<PinValue<float>>(parent_node->inputs.at("x_1"))->default_value);
    }
    else if (parent_node->inputs.at("x_1")->type == PinType::Int)
    {
        writer.Int(std::dynamic_pointer_cast<PinValue<int>>(parent_node->inputs.at("x_1"))->default_value);
    }
    writer.Key("x_1_type");
    writer.String(PinTypeToString(parent_node->inputs.at("x_1")->type).c_str());

    writer.Key("x_2");
    if (parent_node->inputs.at("x_2")->type == PinType::Float)
    {
        writer.Double(std::dynamic_pointer_cast<PinValue<float>>(parent_node->inputs.at("x_2"))->default_value);
    }
    else if (parent_node->inputs.at("x_2")->type == PinType::Int)
    {
        writer.Int(std::dynamic_pointer_cast<PinValue<int>>(parent_node->inputs.at("x_2"))->default_value);
    }
    writer.Key("x_2_type");
    writer.String(PinTypeToString(parent_node->inputs.at("x_2")->type).c_str());
    writer.Key("out_type");
    writer.String(PinTypeToString(parent_node->outputs.at("out")->type).c_str());
}

void MathDivideNode_Func::LoadNodeData(rapidjson::Value& node_obj)
{
    PinType x1_type = StringToPinType(std::string(node_obj["x_1_type"].GetString()));
    PinType x2_type = StringToPinType(std::string(node_obj["x_2_type"].GetString()));
    PinType out_type = StringToPinType(std::string(node_obj["out_type"].GetString()));
    UtilsChangePinType(parent_node, PinKind::Input, "x_1", x1_type, false);
    UtilsChangePinType(parent_node, PinKind::Input, "x_2", x2_type, false);
    UtilsChangePinType(parent_node, PinKind::Output, "out", out_type, false);

    if (parent_node->inputs.at("x_1")->type == PinType::Float)
        std::dynamic_pointer_cast<PinValue<float>>(parent_node->inputs.at("x_1"))->default_value = node_obj["x_1"].GetFloat();
    else if (parent_node->inputs.at("x_1")->type == PinType::Int)
        std::dynamic_pointer_cast<PinValue<int>>(parent_node->inputs.at("x_1"))->default_value = node_obj["x_1"].GetInt();

    if (parent_node->inputs.at("x_2")->type == PinType::Float)
        std::dynamic_pointer_cast<PinValue<float>>(parent_node->inputs.at("x_2"))->default_value = node_obj["x_2"].GetFloat();
    else if (parent_node->inputs.at("x_2")->type == PinType::Int)
        std::dynamic_pointer_cast<PinValue<int>>(parent_node->inputs.at("x_2"))->default_value = node_obj["x_2"].GetInt();
}

std::string mathDivideNodeName = "Divide ( / )";
std::shared_ptr<Node> MathDivideNode(std::vector<std::shared_ptr<Node>>& s_Nodes)
{
    s_Nodes.emplace_back(new Node(GetNextId(), mathDivideNodeName.c_str(), true));

    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<PinValue<float>>>("x_1", new PinValue<float>("x_1", 0, GetNextId(), "X 1", PinType::Float, 1)));
    s_Nodes.back()->inputs.at("x_1")->isTemplate = true;;
    s_Nodes.back()->inputs.at("x_1")->template_allowed_types.push_back(PinType::Float);
    s_Nodes.back()->inputs.at("x_1")->template_allowed_types.push_back(PinType::Int);
    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<PinValue<float>>>("x_2", new PinValue<float>("x_2", 1, GetNextId(), "X 2", PinType::Float, 1)));
    s_Nodes.back()->inputs.at("x_2")->isTemplate = true;;
    s_Nodes.back()->inputs.at("x_2")->template_allowed_types.push_back(PinType::Float);
    s_Nodes.back()->inputs.at("x_2")->template_allowed_types.push_back(PinType::Int);
    s_Nodes.back()->outputs.insert(std::pair<std::string, std::shared_ptr<PinValue<float>>>("out", new PinValue<float>("out", 0, GetNextId(), "Out", PinType::Float, 0)));
    s_Nodes.back()->outputs.at("out")->isTemplate = true;
    s_Nodes.back()->outputs.at("out")->template_allowed_types.push_back(PinType::Float);
    s_Nodes.back()->outputs.at("out")->template_allowed_types.push_back(PinType::Int);

    s_Nodes.back()->node_funcs = std::make_shared<MathDivideNode_Func>();
    std::dynamic_pointer_cast<MathDivideNode_Func>(s_Nodes.back()->node_funcs)->parent_node = s_Nodes.back();

    s_Nodes.back()->node_funcs->Initialize();

    BuildNode(s_Nodes.back());

    return s_Nodes.back();
}





void MathSinNode_Func::Delete()
{
    parent_node = nullptr;
}

void MathSinNode_Func::NoFlowUpdatePinsValues()
{
    float in_value = GetInputPinValue<float>(parent_node, "in");
    std::shared_ptr<PinValue<float>> output_pin = std::dynamic_pointer_cast<PinValue<float>>(parent_node->outputs.at("out"));
    output_pin->value = glm::sin(glm::radians(in_value));
}

void MathSinNode_Func::SaveNodeData(rapidjson::Writer<rapidjson::StringBuffer>& writer)
{
    writer.Key("in");
    writer.Double(std::dynamic_pointer_cast<PinValue<float>>(parent_node->inputs.at("in"))->default_value);
}

void MathSinNode_Func::LoadNodeData(rapidjson::Value& node_obj)
{
    std::dynamic_pointer_cast<PinValue<float>>(parent_node->inputs.at("in"))->default_value = node_obj["in"].GetFloat();
}

std::string mathSinNodeName = "Sin";
std::shared_ptr<Node> MathSinNode(std::vector<std::shared_ptr<Node>>& s_Nodes)
{
    s_Nodes.emplace_back(new Node(GetNextId(), mathSinNodeName.c_str(), true));

    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<PinValue<float>>>("in", new PinValue<float>("in", 0, GetNextId(), "In", PinType::Float, 0)));
    s_Nodes.back()->outputs.insert(std::pair<std::string, std::shared_ptr<PinValue<float>>>("out", new PinValue<float>("out", 0, GetNextId(), "Out", PinType::Float, 0)));

    s_Nodes.back()->node_funcs = std::make_shared<MathSinNode_Func>();
    std::dynamic_pointer_cast<MathSinNode_Func>(s_Nodes.back()->node_funcs)->parent_node = s_Nodes.back();

    s_Nodes.back()->node_funcs->Initialize();

    BuildNode(s_Nodes.back());

    return s_Nodes.back();
}





void MathCosNode_Func::Delete()
{
    parent_node = nullptr;
}

void MathCosNode_Func::NoFlowUpdatePinsValues()
{
    float in_value = GetInputPinValue<float>(parent_node, "in");
    std::shared_ptr<PinValue<float>> output_pin = std::dynamic_pointer_cast<PinValue<float>>(parent_node->outputs.at("out"));
    output_pin->value = glm::cos(glm::radians(in_value));
}

void MathCosNode_Func::SaveNodeData(rapidjson::Writer<rapidjson::StringBuffer>& writer)
{
    writer.Key("in");
    writer.Double(std::dynamic_pointer_cast<PinValue<float>>(parent_node->inputs.at("in"))->default_value);
}

void MathCosNode_Func::LoadNodeData(rapidjson::Value& node_obj)
{
    std::dynamic_pointer_cast<PinValue<float>>(parent_node->inputs.at("in"))->default_value = node_obj["in"].GetFloat();
}

std::string mathCosNodeName = "Cos";
std::shared_ptr<Node> MathCosNode(std::vector<std::shared_ptr<Node>>& s_Nodes)
{
    s_Nodes.emplace_back(new Node(GetNextId(), mathCosNodeName.c_str(), true));

    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<PinValue<float>>>("in", new PinValue<float>("in", 0, GetNextId(), "In", PinType::Float, 0)));
    s_Nodes.back()->outputs.insert(std::pair<std::string, std::shared_ptr<PinValue<float>>>("out", new PinValue<float>("out", 0, GetNextId(), "Out", PinType::Float, 0)));

    s_Nodes.back()->node_funcs = std::make_shared<MathCosNode_Func>();
    std::dynamic_pointer_cast<MathCosNode_Func>(s_Nodes.back()->node_funcs)->parent_node = s_Nodes.back();

    s_Nodes.back()->node_funcs->Initialize();

    BuildNode(s_Nodes.back());

    return s_Nodes.back();
}





void MathToDegreesNode_Func::Delete()
{
    parent_node = nullptr;
}

void MathToDegreesNode_Func::NoFlowUpdatePinsValues()
{
    float in_value = GetInputPinValue<float>(parent_node, "in");
    std::shared_ptr<PinValue<float>> output_pin = std::dynamic_pointer_cast<PinValue<float>>(parent_node->outputs.at("out"));
    output_pin->value = glm::degrees(in_value);
}

void MathToDegreesNode_Func::SaveNodeData(rapidjson::Writer<rapidjson::StringBuffer>& writer)
{
    writer.Key("in");
    writer.Double(std::dynamic_pointer_cast<PinValue<float>>(parent_node->inputs.at("in"))->default_value);
}

void MathToDegreesNode_Func::LoadNodeData(rapidjson::Value& node_obj)
{
    std::dynamic_pointer_cast<PinValue<float>>(parent_node->inputs.at("in"))->default_value = node_obj["in"].GetFloat();
}

std::string mathToDegreesNodeName = "To Degrees";
std::shared_ptr<Node> MathToDegreesNode(std::vector<std::shared_ptr<Node>>& s_Nodes)
{
    s_Nodes.emplace_back(new Node(GetNextId(), mathToDegreesNodeName.c_str(), true));

    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<PinValue<float>>>("in", new PinValue<float>("in", 0, GetNextId(), "In", PinType::Float, 0)));
    s_Nodes.back()->outputs.insert(std::pair<std::string, std::shared_ptr<PinValue<float>>>("out", new PinValue<float>("out", 0, GetNextId(), "Out", PinType::Float, 0)));

    s_Nodes.back()->node_funcs = std::make_shared<MathToDegreesNode_Func>();
    std::dynamic_pointer_cast<MathToDegreesNode_Func>(s_Nodes.back()->node_funcs)->parent_node = s_Nodes.back();

    s_Nodes.back()->node_funcs->Initialize();

    BuildNode(s_Nodes.back());

    return s_Nodes.back();
}





void MathToRadiansNode_Func::Delete()
{
    parent_node = nullptr;
}

void MathToRadiansNode_Func::NoFlowUpdatePinsValues()
{
    float in_value = GetInputPinValue<float>(parent_node, "in");
    std::shared_ptr<PinValue<float>> output_pin = std::dynamic_pointer_cast<PinValue<float>>(parent_node->outputs.at("out"));
    output_pin->value = glm::radians(in_value);
}

void MathToRadiansNode_Func::SaveNodeData(rapidjson::Writer<rapidjson::StringBuffer>& writer)
{
    writer.Key("in");
    writer.Double(std::dynamic_pointer_cast<PinValue<float>>(parent_node->inputs.at("in"))->default_value);
}

void MathToRadiansNode_Func::LoadNodeData(rapidjson::Value& node_obj)
{
    std::dynamic_pointer_cast<PinValue<float>>(parent_node->inputs.at("in"))->default_value = node_obj["in"].GetFloat();
}

std::string mathToRadiansNodeName = "To Radians";
std::shared_ptr<Node> MathToRadiansNode(std::vector<std::shared_ptr<Node>>& s_Nodes)
{
    s_Nodes.emplace_back(new Node(GetNextId(), mathToRadiansNodeName.c_str(), true));

    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<PinValue<float>>>("in", new PinValue<float>("in", 0, GetNextId(), "In", PinType::Float, 0)));
    s_Nodes.back()->outputs.insert(std::pair<std::string, std::shared_ptr<PinValue<float>>>("out", new PinValue<float>("out", 0, GetNextId(), "Out", PinType::Float, 0)));

    s_Nodes.back()->node_funcs = std::make_shared<MathToRadiansNode_Func>();
    std::dynamic_pointer_cast<MathToRadiansNode_Func>(s_Nodes.back()->node_funcs)->parent_node = s_Nodes.back();

    s_Nodes.back()->node_funcs->Initialize();

    BuildNode(s_Nodes.back());

    return s_Nodes.back();
}





void MathNodesSearchSetup(std::vector<SearchNodeObj>& search_nodes_vector)
{
    std::function<std::shared_ptr<Node>(std::vector<std::shared_ptr<Node>>&)> func_1 = MathPlusNode;
    std::vector<std::string> keywords_1{ "+", "Plus", "Operator", "Math" };
    search_nodes_vector.push_back(SearchNodeObj("+ Operator", "Math (Scalar)", keywords_1, func_1));

    std::function<std::shared_ptr<Node>(std::vector<std::shared_ptr<Node>>&)> func_2 = MathMinusNode;
    std::vector<std::string> keywords_2{ "-", "Minus", "Operator", "Math" };
    search_nodes_vector.push_back(SearchNodeObj("- Operator", "Math (Scalar)", keywords_2, func_2));

    std::function<std::shared_ptr<Node>(std::vector<std::shared_ptr<Node>>&)> func_3 = MathMultiplyNode;
    std::vector<std::string> keywords_3{ "*", "Multiply", "Operator", "Math" };
    search_nodes_vector.push_back(SearchNodeObj("* Operator", "Math (Scalar)", keywords_3, func_3));

    std::function<std::shared_ptr<Node>(std::vector<std::shared_ptr<Node>>&)> func_4 = MathDivideNode;
    std::vector<std::string> keywords_4{ "/", "Divide", "Operator", "Math" };
    search_nodes_vector.push_back(SearchNodeObj("/ Operator", "Math (Scalar)", keywords_4, func_4));

    std::function<std::shared_ptr<Node>(std::vector<std::shared_ptr<Node>>&)> func_5 = MathSinNode;
    std::vector<std::string> keywords_5{ "Sin", "Math" };
    search_nodes_vector.push_back(SearchNodeObj("Sin", "Math (Scalar)", keywords_5, func_5));

    std::function<std::shared_ptr<Node>(std::vector<std::shared_ptr<Node>>&)> func_6 = MathCosNode;
    std::vector<std::string> keywords_6{ "Cos", "Math" };
    search_nodes_vector.push_back(SearchNodeObj("Cos", "Math (Scalar)", keywords_6, func_6));

    std::function<std::shared_ptr<Node>(std::vector<std::shared_ptr<Node>>&)> func_7 = MathToDegreesNode;
    std::vector<std::string> keywords_7{ "To", "Degrees", "Math" };
    search_nodes_vector.push_back(SearchNodeObj("To Degrees", "Math (Scalar)", keywords_7, func_7));

    std::function<std::shared_ptr<Node>(std::vector<std::shared_ptr<Node>>&)> func_8 = MathToRadiansNode;
    std::vector<std::string> keywords_8{ "To", "Radians", "Math" };
    search_nodes_vector.push_back(SearchNodeObj("To Radians", "Math (Scalar)", keywords_8, func_8));
}

std::shared_ptr<Node> MathNodesLoadSetup(std::vector<std::shared_ptr<Node>>& s_Nodes, std::string node_key)
{
    std::shared_ptr<Node> loaded_node = nullptr;
    if (loaded_node == nullptr && node_key.rfind(mathPlusNodeName, 0) == 0) {
        loaded_node = MathPlusNode(s_Nodes);
    }
    else if (loaded_node == nullptr && node_key.rfind(mathMinusNodeName, 0) == 0) {
        loaded_node = MathMinusNode(s_Nodes);
    }
    else if (loaded_node == nullptr && node_key.rfind(mathMultiplyNodeName, 0) == 0) {
        loaded_node = MathMultiplyNode(s_Nodes);
    }
    else if (loaded_node == nullptr && node_key.rfind(mathDivideNodeName, 0) == 0) {
        loaded_node = MathDivideNode(s_Nodes);
    }
    else if (loaded_node == nullptr && node_key.rfind(mathSinNodeName, 0) == 0) {
        loaded_node = MathSinNode(s_Nodes);
    }
    else if (loaded_node == nullptr && node_key.rfind(mathCosNodeName, 0) == 0) {
        loaded_node = MathCosNode(s_Nodes);
    }
    else if (loaded_node == nullptr && node_key.rfind(mathToDegreesNodeName, 0) == 0) {
        loaded_node = MathToDegreesNode(s_Nodes);
    }
    else if (loaded_node == nullptr && node_key.rfind(mathToRadiansNodeName, 0) == 0) {
        loaded_node = MathToRadiansNode(s_Nodes);
    }
    return loaded_node;
}
