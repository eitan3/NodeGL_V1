#include "math_nodes.h"

void MathPlusNode_Func::Initialize()
{
}

void MathPlusNode_Func::Run()
{
}

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
        if (parent_node->outputs.at("x_1")->type == PinType::Int)
        {
            std::shared_ptr<PinValue<int>> output_pin = std::dynamic_pointer_cast<PinValue<int>>(parent_node->outputs.at("out"));
            output_pin->value = (int)(pin_0_value + pin_1_value);
        }
        else if (parent_node->outputs.at("x_1")->type == PinType::Float)
        {
            std::shared_ptr<PinValue<float>> output_pin = std::dynamic_pointer_cast<PinValue<float>>(parent_node->outputs.at("out"));
            output_pin->value = pin_0_value + pin_1_value;
        }
    }
    else if (parent_node->inputs.at("x_1")->type == PinType::Float && parent_node->inputs.at("x_2")->type == PinType::Int)
    {
        float pin_0_value = GetInputPinValue<float>(parent_node, "x_1");
        int pin_1_value = GetInputPinValue<int>(parent_node, "x_2");
        if (parent_node->outputs.at("x_1")->type == PinType::Int)
        {
            std::shared_ptr<PinValue<int>> output_pin = std::dynamic_pointer_cast<PinValue<int>>(parent_node->outputs.at("out"));
            output_pin->value = (int)(pin_0_value + pin_1_value);
        }
        else if (parent_node->outputs.at("x_1")->type == PinType::Float)
        {
            std::shared_ptr<PinValue<float>> output_pin = std::dynamic_pointer_cast<PinValue<float>>(parent_node->outputs.at("out"));
            output_pin->value = pin_0_value + pin_1_value;
        }
    }
    else if (parent_node->inputs.at("x_1")->type == PinType::Int && parent_node->inputs.at("x_2")->type == PinType::Float)
    {
        int pin_0_value = GetInputPinValue<int>(parent_node, "x_1");
        float pin_1_value = GetInputPinValue<float>(parent_node, "x_2");
        if (parent_node->outputs.at("x_1")->type == PinType::Int)
        {
            std::shared_ptr<PinValue<int>> output_pin = std::dynamic_pointer_cast<PinValue<int>>(parent_node->outputs.at("out"));
            output_pin->value = (int)(pin_0_value + pin_1_value);
        }
        else if (parent_node->outputs.at("x_1")->type == PinType::Float)
        {
            std::shared_ptr<PinValue<float>> output_pin = std::dynamic_pointer_cast<PinValue<float>>(parent_node->outputs.at("out"));
            output_pin->value = pin_0_value + pin_1_value;
        }
    }
    else if (parent_node->inputs.at("x_1")->type == PinType::Float && parent_node->inputs.at("x_2")->type == PinType::Float)
    {
        float pin_0_value = GetInputPinValue<float>(parent_node, "x_1");
        float pin_1_value = GetInputPinValue<float>(parent_node, "x_2");
        if (parent_node->outputs.at("x_1")->type == PinType::Int)
        {
            std::shared_ptr<PinValue<int>> output_pin = std::dynamic_pointer_cast<PinValue<int>>(parent_node->outputs.at("out"));
            output_pin->value = (int)(pin_0_value + pin_1_value);
        }
        else if (parent_node->outputs.at("x_1")->type == PinType::Float)
        {
            std::shared_ptr<PinValue<float>> output_pin = std::dynamic_pointer_cast<PinValue<float>>(parent_node->outputs.at("out"));
            output_pin->value = pin_0_value + pin_1_value;
        }
    }
}

std::shared_ptr<Node> MathPlusNode(std::vector<std::shared_ptr<Node>>& s_Nodes)
{
    s_Nodes.emplace_back(new Node(GetNextId(), "Plus", true));
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





void MathMinusNode_Func::Initialize()
{
}

void MathMinusNode_Func::Run()
{
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
        if (parent_node->outputs.at("x_1")->type == PinType::Int)
        {
            std::shared_ptr<PinValue<int>> output_pin = std::dynamic_pointer_cast<PinValue<int>>(parent_node->outputs.at("out"));
            output_pin->value = (int)(pin_0_value - pin_1_value);
        }
        else if (parent_node->outputs.at("x_1")->type == PinType::Float)
        {
            std::shared_ptr<PinValue<float>> output_pin = std::dynamic_pointer_cast<PinValue<float>>(parent_node->outputs.at("out"));
            output_pin->value = pin_0_value - pin_1_value;
        }
    }
    else if (parent_node->inputs.at("x_1")->type == PinType::Float && parent_node->inputs.at("x_2")->type == PinType::Int)
    {
        float pin_0_value = GetInputPinValue<float>(parent_node, "x_1");
        int pin_1_value = GetInputPinValue<int>(parent_node, "x_2");
        if (parent_node->outputs.at("x_1")->type == PinType::Int)
        {
            std::shared_ptr<PinValue<int>> output_pin = std::dynamic_pointer_cast<PinValue<int>>(parent_node->outputs.at("out"));
            output_pin->value = (int)(pin_0_value - pin_1_value);
        }
        else if (parent_node->outputs.at("x_1")->type == PinType::Float)
        {
            std::shared_ptr<PinValue<float>> output_pin = std::dynamic_pointer_cast<PinValue<float>>(parent_node->outputs.at("out"));
            output_pin->value = pin_0_value - pin_1_value;
        }
    }
    else if (parent_node->inputs.at("x_1")->type == PinType::Int && parent_node->inputs.at("x_2")->type == PinType::Float)
    {
        int pin_0_value = GetInputPinValue<int>(parent_node, "x_1");
        float pin_1_value = GetInputPinValue<float>(parent_node, "x_2");
        if (parent_node->outputs.at("x_1")->type == PinType::Int)
        {
            std::shared_ptr<PinValue<int>> output_pin = std::dynamic_pointer_cast<PinValue<int>>(parent_node->outputs.at("out"));
            output_pin->value = (int)(pin_0_value - pin_1_value);
        }
        else if (parent_node->outputs.at("x_1")->type == PinType::Float)
        {
            std::shared_ptr<PinValue<float>> output_pin = std::dynamic_pointer_cast<PinValue<float>>(parent_node->outputs.at("out"));
            output_pin->value = pin_0_value - pin_1_value;
        }
    }
    else if (parent_node->inputs.at("x_1")->type == PinType::Float && parent_node->inputs.at("x_2")->type == PinType::Float)
    {
        float pin_0_value = GetInputPinValue<float>(parent_node, "x_1");
        float pin_1_value = GetInputPinValue<float>(parent_node, "x_2");
        if (parent_node->outputs.at("x_1")->type == PinType::Int)
        {
            std::shared_ptr<PinValue<int>> output_pin = std::dynamic_pointer_cast<PinValue<int>>(parent_node->outputs.at("out"));
            output_pin->value = (int)(pin_0_value - pin_1_value);
        }
        else if (parent_node->outputs.at("x_1")->type == PinType::Float)
        {
            std::shared_ptr<PinValue<float>> output_pin = std::dynamic_pointer_cast<PinValue<float>>(parent_node->outputs.at("out"));
            output_pin->value = pin_0_value - pin_1_value;
        }
    }
}

std::shared_ptr<Node> MathMinusNode(std::vector<std::shared_ptr<Node>>& s_Nodes)
{
    s_Nodes.emplace_back(new Node(GetNextId(), "Minus", true));

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





void MathMultiplyNode_Func::Initialize()
{
}

void MathMultiplyNode_Func::Run()
{
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
        if (parent_node->outputs.at("x_1")->type == PinType::Int)
        {
            std::shared_ptr<PinValue<int>> output_pin = std::dynamic_pointer_cast<PinValue<int>>(parent_node->outputs.at("out"));
            output_pin->value = (int)(pin_0_value * pin_1_value);
        }
        else if (parent_node->outputs.at("x_1")->type == PinType::Float)
        {
            std::shared_ptr<PinValue<float>> output_pin = std::dynamic_pointer_cast<PinValue<float>>(parent_node->outputs.at("out"));
            output_pin->value = pin_0_value * pin_1_value;
        }
    }
    else if (parent_node->inputs.at("x_1")->type == PinType::Float && parent_node->inputs.at("x_2")->type == PinType::Int)
    {
        float pin_0_value = GetInputPinValue<float>(parent_node, "x_1");
        int pin_1_value = GetInputPinValue<int>(parent_node, "x_2");
        if (parent_node->outputs.at("x_1")->type == PinType::Int)
        {
            std::shared_ptr<PinValue<int>> output_pin = std::dynamic_pointer_cast<PinValue<int>>(parent_node->outputs.at("out"));
            output_pin->value = (int)(pin_0_value * pin_1_value);
        }
        else if (parent_node->outputs.at("x_1")->type == PinType::Float)
        {
            std::shared_ptr<PinValue<float>> output_pin = std::dynamic_pointer_cast<PinValue<float>>(parent_node->outputs.at("out"));
            output_pin->value = pin_0_value * pin_1_value;
        }
    }
    else if (parent_node->inputs.at("x_1")->type == PinType::Int && parent_node->inputs.at("x_2")->type == PinType::Float)
    {
        int pin_0_value = GetInputPinValue<int>(parent_node, "x_1");
        float pin_1_value = GetInputPinValue<float>(parent_node, "x_2");
        if (parent_node->outputs.at("x_1")->type == PinType::Int)
        {
            std::shared_ptr<PinValue<int>> output_pin = std::dynamic_pointer_cast<PinValue<int>>(parent_node->outputs.at("out"));
            output_pin->value = (int)(pin_0_value * pin_1_value);
        }
        else if (parent_node->outputs.at("x_1")->type == PinType::Float)
        {
            std::shared_ptr<PinValue<float>> output_pin = std::dynamic_pointer_cast<PinValue<float>>(parent_node->outputs.at("out"));
            output_pin->value = pin_0_value * pin_1_value;
        }
    }
    else if (parent_node->inputs.at("x_1")->type == PinType::Float && parent_node->inputs.at("x_2")->type == PinType::Float)
    {
        float pin_0_value = GetInputPinValue<float>(parent_node, "x_1");
        float pin_1_value = GetInputPinValue<float>(parent_node, "x_2");
        if (parent_node->outputs.at("x_1")->type == PinType::Int)
        {
            std::shared_ptr<PinValue<int>> output_pin = std::dynamic_pointer_cast<PinValue<int>>(parent_node->outputs.at("out"));
            output_pin->value = (int)(pin_0_value * pin_1_value);
        }
        else if (parent_node->outputs.at("x_1")->type == PinType::Float)
        {
            std::shared_ptr<PinValue<float>> output_pin = std::dynamic_pointer_cast<PinValue<float>>(parent_node->outputs.at("out"));
            output_pin->value = pin_0_value * pin_1_value;
        }
    }
}

std::shared_ptr<Node> MathMultiplyNode(std::vector<std::shared_ptr<Node>>& s_Nodes)
{
    s_Nodes.emplace_back(new Node(GetNextId(), "Multiply", true));

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





void MathDivideNode_Func::Initialize()
{
}

void MathDivideNode_Func::Run()
{
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
        if (parent_node->outputs.at("x_1")->type == PinType::Int)
        {
            std::shared_ptr<PinValue<int>> output_pin = std::dynamic_pointer_cast<PinValue<int>>(parent_node->outputs.at("out"));
            output_pin->value = (int)(pin_0_value / pin_1_value);
        }
        else if (parent_node->outputs.at("x_1")->type == PinType::Float)
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
        if (parent_node->outputs.at("x_1")->type == PinType::Int)
        {
            std::shared_ptr<PinValue<int>> output_pin = std::dynamic_pointer_cast<PinValue<int>>(parent_node->outputs.at("out"));
            output_pin->value = (int)(pin_0_value / pin_1_value);
        }
        else if (parent_node->outputs.at("x_1")->type == PinType::Float)
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
        if (parent_node->outputs.at("x_1")->type == PinType::Int)
        {
            std::shared_ptr<PinValue<int>> output_pin = std::dynamic_pointer_cast<PinValue<int>>(parent_node->outputs.at("out"));
            output_pin->value = (int)(pin_0_value / pin_1_value);
        }
        else if (parent_node->outputs.at("x_1")->type == PinType::Float)
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
        if (parent_node->outputs.at("x_1")->type == PinType::Int)
        {
            std::shared_ptr<PinValue<int>> output_pin = std::dynamic_pointer_cast<PinValue<int>>(parent_node->outputs.at("out"));
            output_pin->value = (int)(pin_0_value / pin_1_value);
        }
        else if (parent_node->outputs.at("x_1")->type == PinType::Float)
        {
            std::shared_ptr<PinValue<float>> output_pin = std::dynamic_pointer_cast<PinValue<float>>(parent_node->outputs.at("out"));
            output_pin->value = pin_0_value / pin_1_value;
        }
    }
}

std::shared_ptr<Node> MathDivideNode(std::vector<std::shared_ptr<Node>>& s_Nodes)
{
    s_Nodes.emplace_back(new Node(GetNextId(), "Divide", true));

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
    search_nodes_vector.push_back(SearchNodeObj("+ Operator", keywords_1, func_1));

    std::function<std::shared_ptr<Node>(std::vector<std::shared_ptr<Node>>&)> func_2 = MathMinusNode;
    std::vector<std::string> keywords_2{ "-", "Minus", "Operator", "Math" };
    search_nodes_vector.push_back(SearchNodeObj("- Operator", keywords_2, func_2));

    std::function<std::shared_ptr<Node>(std::vector<std::shared_ptr<Node>>&)> func_3 = MathMultiplyNode;
    std::vector<std::string> keywords_3{ "*", "Multiply", "Operator", "Math" };
    search_nodes_vector.push_back(SearchNodeObj("* Operator", keywords_3, func_3));

    std::function<std::shared_ptr<Node>(std::vector<std::shared_ptr<Node>>&)> func_4 = MathDivideNode;
    std::vector<std::string> keywords_4{ "/", "Divide", "Operator", "Math" };
    search_nodes_vector.push_back(SearchNodeObj("/ Operator", keywords_4, func_4));
}