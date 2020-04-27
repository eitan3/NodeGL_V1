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
    if (parent_node->inputs.at(0)->type == PinType::Int && parent_node->inputs.at(1)->type == PinType::Int)
    {
        int pin_0_value = GetInputPinValue<int>(parent_node, 0);
        int pin_1_value = GetInputPinValue<int>(parent_node, 1);
        if (parent_node->outputs.at(0)->type == PinType::Int)
        {
            std::shared_ptr<PinValue<int>> output_pin = std::dynamic_pointer_cast<PinValue<int>>(parent_node->outputs.at(0));
            output_pin->value = (int)(pin_0_value + pin_1_value);
        }
        else if (parent_node->outputs.at(0)->type == PinType::Float)
        {
            std::shared_ptr<PinValue<float>> output_pin = std::dynamic_pointer_cast<PinValue<float>>(parent_node->outputs.at(0));
            output_pin->value = pin_0_value + pin_1_value;
        }
    }
    else if (parent_node->inputs.at(0)->type == PinType::Float && parent_node->inputs.at(1)->type == PinType::Int)
    {
        float pin_0_value = GetInputPinValue<float>(parent_node, 0);
        int pin_1_value = GetInputPinValue<int>(parent_node, 1);
        if (parent_node->outputs.at(0)->type == PinType::Int)
        {
            std::shared_ptr<PinValue<int>> output_pin = std::dynamic_pointer_cast<PinValue<int>>(parent_node->outputs.at(0));
            output_pin->value = (int)(pin_0_value + pin_1_value);
        }
        else if (parent_node->outputs.at(0)->type == PinType::Float)
        {
            std::shared_ptr<PinValue<float>> output_pin = std::dynamic_pointer_cast<PinValue<float>>(parent_node->outputs.at(0));
            output_pin->value = pin_0_value + pin_1_value;
        }
    }
    else if (parent_node->inputs.at(0)->type == PinType::Int && parent_node->inputs.at(1)->type == PinType::Float)
    {
        int pin_0_value = GetInputPinValue<int>(parent_node, 0);
        float pin_1_value = GetInputPinValue<float>(parent_node, 1);
        if (parent_node->outputs.at(0)->type == PinType::Int)
        {
            std::shared_ptr<PinValue<int>> output_pin = std::dynamic_pointer_cast<PinValue<int>>(parent_node->outputs.at(0));
            output_pin->value = (int)(pin_0_value + pin_1_value);
        }
        else if (parent_node->outputs.at(0)->type == PinType::Float)
        {
            std::shared_ptr<PinValue<float>> output_pin = std::dynamic_pointer_cast<PinValue<float>>(parent_node->outputs.at(0));
            output_pin->value = pin_0_value + pin_1_value;
        }
    }
    else if (parent_node->inputs.at(0)->type == PinType::Float && parent_node->inputs.at(1)->type == PinType::Float)
    {
        float pin_0_value = GetInputPinValue<float>(parent_node, 0);
        float pin_1_value = GetInputPinValue<float>(parent_node, 1);
        if (parent_node->outputs.at(0)->type == PinType::Int)
        {
            std::shared_ptr<PinValue<int>> output_pin = std::dynamic_pointer_cast<PinValue<int>>(parent_node->outputs.at(0));
            output_pin->value = (int)(pin_0_value + pin_1_value);
        }
        else if (parent_node->outputs.at(0)->type == PinType::Float)
        {
            std::shared_ptr<PinValue<float>> output_pin = std::dynamic_pointer_cast<PinValue<float>>(parent_node->outputs.at(0));
            output_pin->value = pin_0_value + pin_1_value;
        }
    }
}

void MathPlusNode_Func::ChangePinType(PinKind kind, int index, PinType type)
{
    UtilsChangePinType(parent_node, kind, index, type);
    BuildNode(parent_node);
}

std::shared_ptr<Node> MathPlusNode(std::vector<std::shared_ptr<Node>>& s_Nodes)
{
    s_Nodes.emplace_back(new Node(GetNextId(), "Plus", true));
    s_Nodes.back()->inputs.emplace_back(new PinValue<float>(s_Nodes.back()->inputs.size(), GetNextId(), "X_1", PinType::Float, 0));
    s_Nodes.back()->inputs.back()->isTemplate = true;;
    s_Nodes.back()->inputs.back()->template_allowed_types.push_back(PinType::Float);
    s_Nodes.back()->inputs.back()->template_allowed_types.push_back(PinType::Int);
    s_Nodes.back()->inputs.emplace_back(new PinValue<float>(s_Nodes.back()->inputs.size(), GetNextId(), "X_2", PinType::Float, 0));
    s_Nodes.back()->inputs.back()->isTemplate = true;;
    s_Nodes.back()->inputs.back()->template_allowed_types.push_back(PinType::Float);
    s_Nodes.back()->inputs.back()->template_allowed_types.push_back(PinType::Int);
    s_Nodes.back()->outputs.emplace_back(new PinValue<float>(s_Nodes.back()->outputs.size(), GetNextId(), "Out", PinType::Float, 0));
    s_Nodes.back()->outputs.back()->isTemplate = true;
    s_Nodes.back()->outputs.back()->template_allowed_types.push_back(PinType::Float);
    s_Nodes.back()->outputs.back()->template_allowed_types.push_back(PinType::Int);

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
    if (parent_node->inputs.at(0)->type == PinType::Int && parent_node->inputs.at(1)->type == PinType::Int)
    {
        int pin_0_value = GetInputPinValue<int>(parent_node, 0);
        int pin_1_value = GetInputPinValue<int>(parent_node, 1);
        if (parent_node->outputs.at(0)->type == PinType::Int)
        {
            std::shared_ptr<PinValue<int>> output_pin = std::dynamic_pointer_cast<PinValue<int>>(parent_node->outputs.at(0));
            output_pin->value = (int)(pin_0_value - pin_1_value);
        }
        else if (parent_node->outputs.at(0)->type == PinType::Float)
        {
            std::shared_ptr<PinValue<float>> output_pin = std::dynamic_pointer_cast<PinValue<float>>(parent_node->outputs.at(0));
            output_pin->value = pin_0_value - pin_1_value;
        }
    }
    else if (parent_node->inputs.at(0)->type == PinType::Float && parent_node->inputs.at(1)->type == PinType::Int)
    {
        float pin_0_value = GetInputPinValue<float>(parent_node, 0);
        int pin_1_value = GetInputPinValue<int>(parent_node, 1);
        if (parent_node->outputs.at(0)->type == PinType::Int)
        {
            std::shared_ptr<PinValue<int>> output_pin = std::dynamic_pointer_cast<PinValue<int>>(parent_node->outputs.at(0));
            output_pin->value = (int)(pin_0_value - pin_1_value);
        }
        else if (parent_node->outputs.at(0)->type == PinType::Float)
        {
            std::shared_ptr<PinValue<float>> output_pin = std::dynamic_pointer_cast<PinValue<float>>(parent_node->outputs.at(0));
            output_pin->value = pin_0_value - pin_1_value;
        }
    }
    else if (parent_node->inputs.at(0)->type == PinType::Int && parent_node->inputs.at(1)->type == PinType::Float)
    {
        int pin_0_value = GetInputPinValue<int>(parent_node, 0);
        float pin_1_value = GetInputPinValue<float>(parent_node, 1);
        if (parent_node->outputs.at(0)->type == PinType::Int)
        {
            std::shared_ptr<PinValue<int>> output_pin = std::dynamic_pointer_cast<PinValue<int>>(parent_node->outputs.at(0));
            output_pin->value = (int)(pin_0_value - pin_1_value);
        }
        else if (parent_node->outputs.at(0)->type == PinType::Float)
        {
            std::shared_ptr<PinValue<float>> output_pin = std::dynamic_pointer_cast<PinValue<float>>(parent_node->outputs.at(0));
            output_pin->value = pin_0_value - pin_1_value;
        }
    }
    else if (parent_node->inputs.at(0)->type == PinType::Float && parent_node->inputs.at(1)->type == PinType::Float)
    {
        float pin_0_value = GetInputPinValue<float>(parent_node, 0);
        float pin_1_value = GetInputPinValue<float>(parent_node, 1);
        if (parent_node->outputs.at(0)->type == PinType::Int)
        {
            std::shared_ptr<PinValue<int>> output_pin = std::dynamic_pointer_cast<PinValue<int>>(parent_node->outputs.at(0));
            output_pin->value = (int)(pin_0_value - pin_1_value);
        }
        else if (parent_node->outputs.at(0)->type == PinType::Float)
        {
            std::shared_ptr<PinValue<float>> output_pin = std::dynamic_pointer_cast<PinValue<float>>(parent_node->outputs.at(0));
            output_pin->value = pin_0_value - pin_1_value;
        }
    }
}

void MathMinusNode_Func::ChangePinType(PinKind kind, int index, PinType type)
{
    UtilsChangePinType(parent_node, kind, index, type);
    BuildNode(parent_node);
}

std::shared_ptr<Node> MathMinusNode(std::vector<std::shared_ptr<Node>>& s_Nodes)
{
    s_Nodes.emplace_back(new Node(GetNextId(), "Minus", true));
    s_Nodes.back()->inputs.emplace_back(new PinValue<float>(s_Nodes.back()->inputs.size(), GetNextId(), "X_1", PinType::Float, 0));
    s_Nodes.back()->inputs.back()->isTemplate = true;;
    s_Nodes.back()->inputs.back()->template_allowed_types.push_back(PinType::Float);
    s_Nodes.back()->inputs.back()->template_allowed_types.push_back(PinType::Int);
    s_Nodes.back()->inputs.emplace_back(new PinValue<float>(s_Nodes.back()->inputs.size(), GetNextId(), "X_2", PinType::Float, 0));
    s_Nodes.back()->inputs.back()->isTemplate = true;;
    s_Nodes.back()->inputs.back()->template_allowed_types.push_back(PinType::Float);
    s_Nodes.back()->inputs.back()->template_allowed_types.push_back(PinType::Int);
    s_Nodes.back()->outputs.emplace_back(new PinValue<float>(s_Nodes.back()->outputs.size(), GetNextId(), "Out", PinType::Float, 0));
    s_Nodes.back()->outputs.back()->isTemplate = true;
    s_Nodes.back()->outputs.back()->template_allowed_types.push_back(PinType::Float);
    s_Nodes.back()->outputs.back()->template_allowed_types.push_back(PinType::Int);

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
    if (parent_node->inputs.at(0)->type == PinType::Int && parent_node->inputs.at(1)->type == PinType::Int)
    {
        int pin_0_value = GetInputPinValue<int>(parent_node, 0);
        int pin_1_value = GetInputPinValue<int>(parent_node, 1);
        if (parent_node->outputs.at(0)->type == PinType::Int)
        {
            std::shared_ptr<PinValue<int>> output_pin = std::dynamic_pointer_cast<PinValue<int>>(parent_node->outputs.at(0));
            output_pin->value = (int)(pin_0_value * pin_1_value);
        }
        else if (parent_node->outputs.at(0)->type == PinType::Float)
        {
            std::shared_ptr<PinValue<float>> output_pin = std::dynamic_pointer_cast<PinValue<float>>(parent_node->outputs.at(0));
            output_pin->value = pin_0_value * pin_1_value;
        }
    }
    else if (parent_node->inputs.at(0)->type == PinType::Float && parent_node->inputs.at(1)->type == PinType::Int)
    {
        float pin_0_value = GetInputPinValue<float>(parent_node, 0);
        int pin_1_value = GetInputPinValue<int>(parent_node, 1);
        if (parent_node->outputs.at(0)->type == PinType::Int)
        {
            std::shared_ptr<PinValue<int>> output_pin = std::dynamic_pointer_cast<PinValue<int>>(parent_node->outputs.at(0));
            output_pin->value = (int)(pin_0_value * pin_1_value);
        }
        else if (parent_node->outputs.at(0)->type == PinType::Float)
        {
            std::shared_ptr<PinValue<float>> output_pin = std::dynamic_pointer_cast<PinValue<float>>(parent_node->outputs.at(0));
            output_pin->value = pin_0_value * pin_1_value;
        }
    }
    else if (parent_node->inputs.at(0)->type == PinType::Int && parent_node->inputs.at(1)->type == PinType::Float)
    {
        int pin_0_value = GetInputPinValue<int>(parent_node, 0);
        float pin_1_value = GetInputPinValue<float>(parent_node, 1);
        if (parent_node->outputs.at(0)->type == PinType::Int)
        {
            std::shared_ptr<PinValue<int>> output_pin = std::dynamic_pointer_cast<PinValue<int>>(parent_node->outputs.at(0));
            output_pin->value = (int)(pin_0_value * pin_1_value);
        }
        else if (parent_node->outputs.at(0)->type == PinType::Float)
        {
            std::shared_ptr<PinValue<float>> output_pin = std::dynamic_pointer_cast<PinValue<float>>(parent_node->outputs.at(0));
            output_pin->value = pin_0_value * pin_1_value;
        }
    }
    else if (parent_node->inputs.at(0)->type == PinType::Float && parent_node->inputs.at(1)->type == PinType::Float)
    {
        float pin_0_value = GetInputPinValue<float>(parent_node, 0);
        float pin_1_value = GetInputPinValue<float>(parent_node, 1);
        if (parent_node->outputs.at(0)->type == PinType::Int)
        {
            std::shared_ptr<PinValue<int>> output_pin = std::dynamic_pointer_cast<PinValue<int>>(parent_node->outputs.at(0));
            output_pin->value = (int)(pin_0_value * pin_1_value);
        }
        else if (parent_node->outputs.at(0)->type == PinType::Float)
        {
            std::shared_ptr<PinValue<float>> output_pin = std::dynamic_pointer_cast<PinValue<float>>(parent_node->outputs.at(0));
            output_pin->value = pin_0_value * pin_1_value;
        }
    }
}

void MathMultiplyNode_Func::ChangePinType(PinKind kind, int index, PinType type)
{
    UtilsChangePinType(parent_node, kind, index, type);
    BuildNode(parent_node);
}

std::shared_ptr<Node> MathMultiplyNode(std::vector<std::shared_ptr<Node>>& s_Nodes)
{
    s_Nodes.emplace_back(new Node(GetNextId(), "Multiply", true));
    s_Nodes.back()->inputs.emplace_back(new PinValue<float>(s_Nodes.back()->inputs.size(), GetNextId(), "X_1", PinType::Float, 0));
    s_Nodes.back()->inputs.back()->isTemplate = true;;
    s_Nodes.back()->inputs.back()->template_allowed_types.push_back(PinType::Float);
    s_Nodes.back()->inputs.back()->template_allowed_types.push_back(PinType::Int);
    s_Nodes.back()->inputs.emplace_back(new PinValue<float>(s_Nodes.back()->inputs.size(), GetNextId(), "X_2", PinType::Float, 0));
    s_Nodes.back()->inputs.back()->isTemplate = true;;
    s_Nodes.back()->inputs.back()->template_allowed_types.push_back(PinType::Float);
    s_Nodes.back()->inputs.back()->template_allowed_types.push_back(PinType::Int);
    s_Nodes.back()->outputs.emplace_back(new PinValue<float>(s_Nodes.back()->outputs.size(), GetNextId(), "Out", PinType::Float, 0));
    s_Nodes.back()->outputs.back()->isTemplate = true;
    s_Nodes.back()->outputs.back()->template_allowed_types.push_back(PinType::Float);
    s_Nodes.back()->outputs.back()->template_allowed_types.push_back(PinType::Int);

    s_Nodes.back()->node_funcs = std::make_shared<MathMultiplyNode_Func>();
    std::dynamic_pointer_cast<MathMultiplyNode_Func>(s_Nodes.back()->node_funcs)->parent_node = s_Nodes.back();

    s_Nodes.back()->node_funcs->Initialize();

    BuildNode(s_Nodes.back());

    return s_Nodes.back();
}





void MathSubtractNode_Func::Initialize()
{
}

void MathSubtractNode_Func::Run()
{
}

void MathSubtractNode_Func::Delete()
{
    parent_node = nullptr;
}

void MathSubtractNode_Func::NoFlowUpdatePinsValues()
{
    if (parent_node->inputs.at(0)->type == PinType::Int && parent_node->inputs.at(1)->type == PinType::Int)
    {
        int pin_0_value = GetInputPinValue<int>(parent_node, 0);
        int pin_1_value = GetInputPinValue<int>(parent_node, 1);
        if (pin_1_value == 0)
            pin_1_value = 1;
        if (parent_node->outputs.at(0)->type == PinType::Int)
        {
            std::shared_ptr<PinValue<int>> output_pin = std::dynamic_pointer_cast<PinValue<int>>(parent_node->outputs.at(0));
            output_pin->value = (int)(pin_0_value / pin_1_value);
        }
        else if (parent_node->outputs.at(0)->type == PinType::Float)
        {
            std::shared_ptr<PinValue<float>> output_pin = std::dynamic_pointer_cast<PinValue<float>>(parent_node->outputs.at(0));
            output_pin->value = pin_0_value / pin_1_value;
        }
    }
    else if (parent_node->inputs.at(0)->type == PinType::Float && parent_node->inputs.at(1)->type == PinType::Int)
    {
        float pin_0_value = GetInputPinValue<float>(parent_node, 0);
        int pin_1_value = GetInputPinValue<int>(parent_node, 1);
        if (pin_1_value == 0)
            pin_1_value = 1;
        if (parent_node->outputs.at(0)->type == PinType::Int)
        {
            std::shared_ptr<PinValue<int>> output_pin = std::dynamic_pointer_cast<PinValue<int>>(parent_node->outputs.at(0));
            output_pin->value = (int)(pin_0_value / pin_1_value);
        }
        else if (parent_node->outputs.at(0)->type == PinType::Float)
        {
            std::shared_ptr<PinValue<float>> output_pin = std::dynamic_pointer_cast<PinValue<float>>(parent_node->outputs.at(0));
            output_pin->value = pin_0_value / pin_1_value;
        }
    }
    else if (parent_node->inputs.at(0)->type == PinType::Int && parent_node->inputs.at(1)->type == PinType::Float)
    {
        int pin_0_value = GetInputPinValue<int>(parent_node, 0);
        float pin_1_value = GetInputPinValue<float>(parent_node, 1);
        if (pin_1_value == 0)
            pin_1_value = 1;
        if (parent_node->outputs.at(0)->type == PinType::Int)
        {
            std::shared_ptr<PinValue<int>> output_pin = std::dynamic_pointer_cast<PinValue<int>>(parent_node->outputs.at(0));
            output_pin->value = (int)(pin_0_value / pin_1_value);
        }
        else if (parent_node->outputs.at(0)->type == PinType::Float)
        {
            std::shared_ptr<PinValue<float>> output_pin = std::dynamic_pointer_cast<PinValue<float>>(parent_node->outputs.at(0));
            output_pin->value = pin_0_value / pin_1_value;
        }
    }
    else if (parent_node->inputs.at(0)->type == PinType::Float && parent_node->inputs.at(1)->type == PinType::Float)
    {
        float pin_0_value = GetInputPinValue<float>(parent_node, 0);
        float pin_1_value = GetInputPinValue<float>(parent_node, 1);
        if (pin_1_value == 0)
            pin_1_value = 1;
        if (parent_node->outputs.at(0)->type == PinType::Int)
        {
            std::shared_ptr<PinValue<int>> output_pin = std::dynamic_pointer_cast<PinValue<int>>(parent_node->outputs.at(0));
            output_pin->value = (int)(pin_0_value / pin_1_value);
        }
        else if (parent_node->outputs.at(0)->type == PinType::Float)
        {
            std::shared_ptr<PinValue<float>> output_pin = std::dynamic_pointer_cast<PinValue<float>>(parent_node->outputs.at(0));
            output_pin->value = pin_0_value / pin_1_value;
        }
    }
}

void MathSubtractNode_Func::ChangePinType(PinKind kind, int index, PinType type)
{
    UtilsChangePinType(parent_node, kind, index, type);
    BuildNode(parent_node);
}

std::shared_ptr<Node> MathSubtractNode(std::vector<std::shared_ptr<Node>>& s_Nodes)
{
    s_Nodes.emplace_back(new Node(GetNextId(), "Subtract", true));
    s_Nodes.back()->inputs.emplace_back(new PinValue<float>(s_Nodes.back()->inputs.size(), GetNextId(), "X_1", PinType::Float, 0));
    s_Nodes.back()->inputs.back()->isTemplate = true;;
    s_Nodes.back()->inputs.back()->template_allowed_types.push_back(PinType::Float);
    s_Nodes.back()->inputs.back()->template_allowed_types.push_back(PinType::Int);
    s_Nodes.back()->inputs.emplace_back(new PinValue<float>(s_Nodes.back()->inputs.size(), GetNextId(), "X_2", PinType::Float, 0));
    s_Nodes.back()->inputs.back()->isTemplate = true;;
    s_Nodes.back()->inputs.back()->template_allowed_types.push_back(PinType::Float);
    s_Nodes.back()->inputs.back()->template_allowed_types.push_back(PinType::Int);
    s_Nodes.back()->outputs.emplace_back(new PinValue<float>(s_Nodes.back()->outputs.size(), GetNextId(), "Out", PinType::Float, 0));
    s_Nodes.back()->outputs.back()->isTemplate = true;
    s_Nodes.back()->outputs.back()->template_allowed_types.push_back(PinType::Float);
    s_Nodes.back()->outputs.back()->template_allowed_types.push_back(PinType::Int);

    s_Nodes.back()->node_funcs = std::make_shared<MathSubtractNode_Func>();
    std::dynamic_pointer_cast<MathSubtractNode_Func>(s_Nodes.back()->node_funcs)->parent_node = s_Nodes.back();

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

    std::function<std::shared_ptr<Node>(std::vector<std::shared_ptr<Node>>&)> func_4 = MathSubtractNode;
    std::vector<std::string> keywords_4{ "/", "Subtract", "Operator", "Math" };
    search_nodes_vector.push_back(SearchNodeObj("/ Operator", keywords_4, func_4));
}