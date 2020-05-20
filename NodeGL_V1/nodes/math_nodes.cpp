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
    UtilsChangePinType(parent_node, PinKind::Input, "x_1", x1_type);
    UtilsChangePinType(parent_node, PinKind::Input, "x_2", x2_type);
    UtilsChangePinType(parent_node, PinKind::Output, "out", out_type);
    
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
    UtilsChangePinType(parent_node, PinKind::Input, "x_1", x1_type);
    UtilsChangePinType(parent_node, PinKind::Input, "x_2", x2_type);
    UtilsChangePinType(parent_node, PinKind::Output, "out", out_type);

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
    UtilsChangePinType(parent_node, PinKind::Input, "x_1", x1_type);
    UtilsChangePinType(parent_node, PinKind::Input, "x_2", x2_type);
    UtilsChangePinType(parent_node, PinKind::Output, "out", out_type);

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
    UtilsChangePinType(parent_node, PinKind::Input, "x_1", x1_type);
    UtilsChangePinType(parent_node, PinKind::Input, "x_2", x2_type);
    UtilsChangePinType(parent_node, PinKind::Output, "out", out_type);

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
    return loaded_node;
}
