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





void SetPlaceholder_Func::Initialize()
{
    placeholder = nullptr;
}

void SetPlaceholder_Func::Run()
{
    if (placeholder)
    {
        if (parent_node->inputs.at(1)->type == PinType::String)
        {
            std::string placeholder_value = GetInputPinValue<std::string>(parent_node, 1);
            std::shared_ptr<PlaceholderValue<std::string>> ph_value = std::dynamic_pointer_cast<PlaceholderValue<std::string>>(placeholder);
            ph_value->value = placeholder_value;
        }
        else if (parent_node->inputs.at(1)->type == PinType::Int)
        {
            int placeholder_value = GetInputPinValue<int>(parent_node, 1);
            std::shared_ptr<PlaceholderValue<int>> ph_value = std::dynamic_pointer_cast<PlaceholderValue<int>>(placeholder);
            ph_value->value = placeholder_value;
        }
        else if (parent_node->inputs.at(1)->type == PinType::Float)
        {
            float placeholder_value = GetInputPinValue<float>(parent_node, 1);
            std::shared_ptr<PlaceholderValue<float>> ph_value = std::dynamic_pointer_cast<PlaceholderValue<float>>(placeholder);
            ph_value->value = placeholder_value;
        }
        else if (parent_node->inputs.at(1)->type == PinType::Bool)
        {
            bool placeholder_value = GetInputPinValue<bool>(parent_node, 1);
            std::shared_ptr<PlaceholderValue<bool>> ph_value = std::dynamic_pointer_cast<PlaceholderValue<bool>>(placeholder);
            ph_value->value = placeholder_value;
        }
        else if (parent_node->inputs.at(1)->type == PinType::TextureObject)
        {
            std::shared_ptr<TextureObject> placeholder_value = GetInputPinValue<std::shared_ptr<TextureObject>>(parent_node, 1);
            std::shared_ptr<PlaceholderValue<std::shared_ptr<TextureObject>>> ph_value = std::dynamic_pointer_cast<PlaceholderValue<std::shared_ptr<TextureObject>>>(placeholder);
            ph_value->value = placeholder_value;
        }
    }
    RunNextNodeFunc(parent_node, 0);
}

void SetPlaceholder_Func::Delete()
{
    if (placeholder)
    {
        placeholder->nodesID_vec.erase(std::remove(placeholder->nodesID_vec.begin(), placeholder->nodesID_vec.end(), parent_node->id), placeholder->nodesID_vec.end());
    }
    placeholder = nullptr;
    parent_node = nullptr;
}

void SetPlaceholder_Func::NoFlowUpdatePinsValues()
{
}

void SetPlaceholder_Func::ChangePinType(PinKind kind, int index, PinType type)
{
    UtilsChangePinType(parent_node, kind, index, type);
    BuildNode(parent_node);
}

std::shared_ptr<Node> SetPlaceholder(std::vector<std::shared_ptr<Node>>& s_Nodes)
{
    s_Nodes.emplace_back(new Node(GetNextId(), "Set Placeholder"));
    s_Nodes.back()->inputs.emplace_back(new BasePin(s_Nodes.back()->inputs.size(), GetNextId(), "Enter", PinType::Flow));
    s_Nodes.back()->inputs.emplace_back(new PinValue<std::string>(s_Nodes.back()->inputs.size(), GetNextId(), "Value", PinType::String, ""));
    s_Nodes.back()->outputs.emplace_back(new BasePin(s_Nodes.back()->outputs.size(), GetNextId(), "Next", PinType::Flow));

    s_Nodes.back()->is_set_placeholder = true;
    s_Nodes.back()->node_funcs = std::make_shared<SetPlaceholder_Func>();
    std::dynamic_pointer_cast<SetPlaceholder_Func>(s_Nodes.back()->node_funcs)->parent_node = s_Nodes.back();

    s_Nodes.back()->node_funcs->Initialize();

    BuildNode(s_Nodes.back());

    return s_Nodes.back();
}





void GetPlaceholder_Func::Initialize()
{
    placeholder = nullptr;
}

void GetPlaceholder_Func::Run()
{
}

void GetPlaceholder_Func::Delete()
{
    if (placeholder)
    {
        placeholder->nodesID_vec.erase(std::remove(placeholder->nodesID_vec.begin(), placeholder->nodesID_vec.end(), parent_node->id), placeholder->nodesID_vec.end());
    }
    placeholder = nullptr;
    parent_node = nullptr;
}

void GetPlaceholder_Func::NoFlowUpdatePinsValues()
{
    if (placeholder_type == PinType::String)
    {
        std::string ph_value = "";
        if (placeholder)
            ph_value = std::dynamic_pointer_cast<PlaceholderValue<std::string>>(placeholder)->value;
        std::shared_ptr<PinValue<std::string>> output_pin = std::dynamic_pointer_cast<PinValue<std::string>>(parent_node->outputs.at(0));
        output_pin->value = ph_value;
    }
    else if (placeholder_type == PinType::Bool)
    {
        bool ph_value = false;
        if (placeholder)
            ph_value = std::dynamic_pointer_cast<PlaceholderValue<bool>>(placeholder)->value;
        std::shared_ptr<PinValue<bool>> output_pin = std::dynamic_pointer_cast<PinValue<bool>>(parent_node->outputs.at(0));
        output_pin->value = ph_value;
    }
    else if (placeholder_type == PinType::Float)
    {
        float ph_value = 0;
        if (placeholder)
            ph_value = std::dynamic_pointer_cast<PlaceholderValue<float>>(placeholder)->value;
        std::shared_ptr<PinValue<float>> output_pin = std::dynamic_pointer_cast<PinValue<float>>(parent_node->outputs.at(0));
        output_pin->value = ph_value;
    }
    else if (placeholder_type == PinType::Int)
    {
        int ph_value = 0;
        if (placeholder)
            ph_value = std::dynamic_pointer_cast<PlaceholderValue<int>>(placeholder)->value;
        std::shared_ptr<PinValue<int>> output_pin = std::dynamic_pointer_cast<PinValue<int>>(parent_node->outputs.at(0));
        output_pin->value = ph_value;
    }
    else if (placeholder_type == PinType::TextureObject)
    {
        std::shared_ptr<TextureObject> ph_value = nullptr;
        if (placeholder)
            ph_value = std::dynamic_pointer_cast<PlaceholderValue<std::shared_ptr<TextureObject>>>(placeholder)->value;
        std::shared_ptr<PinValue<std::shared_ptr<TextureObject>>> output_pin = std::dynamic_pointer_cast<PinValue<std::shared_ptr<TextureObject>>>(parent_node->outputs.at(0));
        output_pin->value = ph_value;
    }
}

void GetPlaceholder_Func::ChangePinType(PinKind kind, int index, PinType type)
{
    UtilsChangePinType(parent_node, kind, index, type);
    BuildNode(parent_node);
}

std::shared_ptr<Node> GetPlaceholder(std::vector<std::shared_ptr<Node>>& s_Nodes)
{
    s_Nodes.emplace_back(new Node(GetNextId(), "Get Placeholder", true));
    s_Nodes.back()->outputs.emplace_back(new PinValue<std::string>(s_Nodes.back()->outputs.size(), GetNextId(), "Value", PinType::String, ""));

    s_Nodes.back()->is_get_placeholder = true;
    s_Nodes.back()->node_funcs = std::make_shared<GetPlaceholder_Func>();
    std::dynamic_pointer_cast<GetPlaceholder_Func>(s_Nodes.back()->node_funcs)->parent_node = s_Nodes.back();

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

    std::function<std::shared_ptr<Node>(std::vector<std::shared_ptr<Node>>&)> func_3 = SetPlaceholder;
    std::vector<std::string> keywords_3{ "Set", "Placeholder" };
    search_nodes_vector.push_back(SearchNodeObj("Set Placeholder", keywords_3, func_3));

    std::function<std::shared_ptr<Node>(std::vector<std::shared_ptr<Node>>&)> func_4 = GetPlaceholder;
    std::vector<std::string> keywords_4{ "Get", "Placeholder" };
    search_nodes_vector.push_back(SearchNodeObj("Get Placeholder", keywords_4, func_4));
}