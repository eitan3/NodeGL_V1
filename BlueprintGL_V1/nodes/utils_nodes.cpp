#include "utils_nodes.h"

void PrintString_Func::Initialize()
{

}

void PrintString_Func::Run()
{
    // GetInputPinValue
    std::string input_value = GetInputPinValue<std::string>(parent_node, 1);
    std::cout << input_value << std::endl;

    RunNextNodeFunc(parent_node, 0);
}

void PrintString_Func::Delete()
{
    parent_node = nullptr;
}

void PrintString_Func::NoFlowUpdatePinsValues()
{
}

void PrintString_Func::ChangePinType(PinKind kind, int index, PinType type)
{
}

std::shared_ptr<Node> PrintString(std::vector<std::shared_ptr<Node>>& s_Nodes)
{
    s_Nodes.emplace_back(new Node(GetNextId(), "Print String"));
    s_Nodes.back()->inputs.emplace_back(new BasePin(s_Nodes.back()->inputs.size(), GetNextId(), "Enter", PinType::Flow));
    s_Nodes.back()->inputs.emplace_back(new PinValue<std::string>(s_Nodes.back()->inputs.size(), GetNextId(), "String", PinType::String, ""));
    s_Nodes.back()->outputs.emplace_back(new BasePin(s_Nodes.back()->outputs.size(), GetNextId(), "Next", PinType::Flow));

    s_Nodes.back()->node_funcs = std::make_shared<PrintString_Func>();
    std::dynamic_pointer_cast<PrintString_Func>(s_Nodes.back()->node_funcs)->parent_node = s_Nodes.back();

    s_Nodes.back()->node_funcs->Initialize();

    BuildNode(s_Nodes.back());

    return s_Nodes.back();
}





void ConvertTo_Func::Initialize()
{
}

void ConvertTo_Func::Run()
{
}

void ConvertTo_Func::Delete()
{
    parent_node = nullptr;
}

void ConvertTo_Func::NoFlowUpdatePinsValues()
{
    if (parent_node->outputs.at(0)->type == PinType::String)
    {
        std::shared_ptr<PinValue<std::string>> output_pin = std::dynamic_pointer_cast<PinValue<std::string>>(parent_node->outputs.at(0));
        if (parent_node->inputs.at(0)->type == PinType::String)
        {
            output_pin->value = GetInputPinValue<std::string>(parent_node, 0);
        }
        else if (parent_node->inputs.at(0)->type == PinType::Int)
        {
            output_pin->value = std::to_string(GetInputPinValue<int>(parent_node, 0));
        }
        else if (parent_node->inputs.at(0)->type == PinType::Float)
        {
            output_pin->value = std::to_string(GetInputPinValue<float>(parent_node, 0));
        }
        else if (parent_node->inputs.at(0)->type == PinType::Bool)
        {
            if (GetInputPinValue<bool>(parent_node, 0))
                output_pin->value = "True";
            else
                output_pin->value = "False";
        }
    }
    else if (parent_node->outputs.at(0)->type == PinType::Bool)
    {
        std::shared_ptr<PinValue<bool>> output_pin = std::dynamic_pointer_cast<PinValue<bool>>(parent_node->outputs.at(0));
        if (parent_node->inputs.at(0)->type == PinType::String)
        {
            output_pin->value = !GetInputPinValue<std::string>(parent_node, 0).empty();
        }
        else if (parent_node->inputs.at(0)->type == PinType::Int)
        {
            output_pin->value = GetInputPinValue<int>(parent_node, 0) != 0;
        }
        else if (parent_node->inputs.at(0)->type == PinType::Float)
        {
            output_pin->value = GetInputPinValue<float>(parent_node, 0) != 0;
        }
        else if (parent_node->inputs.at(0)->type == PinType::Bool)
        {
            output_pin->value = GetInputPinValue<bool>(parent_node, 0);
        }
    }
    else if (parent_node->outputs.at(0)->type == PinType::Int)
    {
        std::shared_ptr<PinValue<int>> output_pin = std::dynamic_pointer_cast<PinValue<int>>(parent_node->outputs.at(0));
        if (parent_node->inputs.at(0)->type == PinType::String)
        {
            std::string tmp_str = GetInputPinValue<std::string>(parent_node, 0);
            try {
                output_pin->value = std::stoi(tmp_str);
            }
            catch (...)
            {
                output_pin->value = 0;
            }
        }
        else if (parent_node->inputs.at(0)->type == PinType::Int)
        {
            output_pin->value = GetInputPinValue<int>(parent_node, 0);
        }
        else if (parent_node->inputs.at(0)->type == PinType::Float)
        {
            output_pin->value = (int)GetInputPinValue<float>(parent_node, 0);
        }
        else if (parent_node->inputs.at(0)->type == PinType::Bool)
        {
            if (GetInputPinValue<bool>(parent_node, 0))
                output_pin->value = 1;
            else
                output_pin->value = 0;
        }
    }
    else if (parent_node->outputs.at(0)->type == PinType::Float)
    {
        std::shared_ptr<PinValue<float>> output_pin = std::dynamic_pointer_cast<PinValue<float>>(parent_node->outputs.at(0));
        if (parent_node->inputs.at(0)->type == PinType::String)
        {
            std::string tmp_str = GetInputPinValue<std::string>(parent_node, 0);
            try {
                output_pin->value = std::stof(tmp_str);
            }
            catch (...)
            {
                output_pin->value = 0;
            }
        }
        else if (parent_node->inputs.at(0)->type == PinType::Int)
        {
            output_pin->value = GetInputPinValue<int>(parent_node, 0);
        }
        else if (parent_node->inputs.at(0)->type == PinType::Float)
        {
            output_pin->value = GetInputPinValue<float>(parent_node, 0);
        }
        else if (parent_node->inputs.at(0)->type == PinType::Bool)
        {
            if (GetInputPinValue<bool>(parent_node, 0))
                output_pin->value = 1.0;
            else
                output_pin->value = 0.0;
        }
    }
}

void ConvertTo_Func::ChangePinType(PinKind kind, int index, PinType type)
{
    UtilsChangePinType(parent_node, kind, index, type);
    BuildNode(parent_node);
}

std::shared_ptr<Node> ConvertTo(std::vector<std::shared_ptr<Node>>& s_Nodes)
{
    s_Nodes.emplace_back(new Node(GetNextId(), "Convert To", true));
    s_Nodes.back()->inputs.emplace_back(new PinValue<float>(s_Nodes.back()->inputs.size(), GetNextId(), "In", PinType::Float, 0));
    s_Nodes.back()->inputs.back()->isTemplate = true;
    s_Nodes.back()->inputs.back()->template_allowed_types.push_back(PinType::Bool);
    s_Nodes.back()->inputs.back()->template_allowed_types.push_back(PinType::Float);
    s_Nodes.back()->inputs.back()->template_allowed_types.push_back(PinType::Int);
    s_Nodes.back()->inputs.back()->template_allowed_types.push_back(PinType::String);
    s_Nodes.back()->outputs.emplace_back(new PinValue<float>(s_Nodes.back()->outputs.size(), GetNextId(), "Out", PinType::Float, 0));
    s_Nodes.back()->outputs.back()->isTemplate = true;
    s_Nodes.back()->outputs.back()->template_allowed_types.push_back(PinType::Bool);
    s_Nodes.back()->outputs.back()->template_allowed_types.push_back(PinType::Float);
    s_Nodes.back()->outputs.back()->template_allowed_types.push_back(PinType::Int);
    s_Nodes.back()->outputs.back()->template_allowed_types.push_back(PinType::String);

    s_Nodes.back()->node_funcs = std::make_shared<ConvertTo_Func>();
    std::dynamic_pointer_cast<ConvertTo_Func>(s_Nodes.back()->node_funcs)->parent_node = s_Nodes.back();

    s_Nodes.back()->node_funcs->Initialize();

    BuildNode(s_Nodes.back());

    return s_Nodes.back();
}





void NodesUtilsSearchSetup(std::vector<SearchNodeObj>& search_nodes_vector)
{
    std::function<std::shared_ptr<Node>(std::vector<std::shared_ptr<Node>>&)> func_1 = ConvertTo;
    std::vector<std::string> keywords_1{ "Convert", "To" };
    search_nodes_vector.push_back(SearchNodeObj("Convert To", keywords_1, func_1));

    std::function<std::shared_ptr<Node>(std::vector<std::shared_ptr<Node>>&)> func_2 = PrintString;
    std::vector<std::string> keywords_2{ "Print", "String" };
    search_nodes_vector.push_back(SearchNodeObj("Print String", keywords_2, func_2));
}