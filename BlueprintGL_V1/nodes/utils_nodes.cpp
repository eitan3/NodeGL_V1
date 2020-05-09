#include "utils_nodes.h"
#include "../EditorConfig.h"
#include "../InstanceConfig.h"

void PrintString_Func::Initialize()
{

}

void PrintString_Func::Run()
{
    // GetInputPinValue
    std::string input_value = GetInputPinValue<std::string>(parent_node, "value");
    std::cout << input_value << std::endl;

    RunNextNodeFunc(parent_node, "next");
}

void PrintString_Func::Delete()
{
    parent_node = nullptr;
}

void PrintString_Func::NoFlowUpdatePinsValues()
{
}

std::shared_ptr<Node> PrintString(std::vector<std::shared_ptr<Node>>& s_Nodes)
{
    s_Nodes.emplace_back(new Node(GetNextId(), "Print String"));

    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<BasePin>>("enter", new BasePin("enter", 0, GetNextId(), "Enter", PinType::Flow)));
    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<PinValue<std::string>>>("value", new PinValue<std::string>("value", 1, GetNextId(), "String", PinType::String, "")));
    s_Nodes.back()->outputs.insert(std::pair<std::string, std::shared_ptr<BasePin>>("next", new BasePin("next", 0, GetNextId(), "Next", PinType::Flow)));

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
    if (parent_node->outputs.at("out")->type == PinType::String)
    {
        std::shared_ptr<PinValue<std::string>> output_pin = std::dynamic_pointer_cast<PinValue<std::string>>(parent_node->outputs.at("out"));
        if (parent_node->inputs.at("in")->type == PinType::String)
        {
            output_pin->value = GetInputPinValue<std::string>(parent_node, "in");
        }
        else if (parent_node->inputs.at("in")->type == PinType::Int)
        {
            output_pin->value = std::to_string(GetInputPinValue<int>(parent_node, "in"));
        }
        else if (parent_node->inputs.at("in")->type == PinType::Float)
        {
            output_pin->value = std::to_string(GetInputPinValue<float>(parent_node, "in"));
        }
        else if (parent_node->inputs.at("in")->type == PinType::Bool)
        {
            if (GetInputPinValue<bool>(parent_node, "in"))
                output_pin->value = "True";
            else
                output_pin->value = "False";
        }
    }
    else if (parent_node->outputs.at("out")->type == PinType::Bool)
    {
        std::shared_ptr<PinValue<bool>> output_pin = std::dynamic_pointer_cast<PinValue<bool>>(parent_node->outputs.at("out"));
        if (parent_node->inputs.at("in")->type == PinType::String)
        {
            output_pin->value = !GetInputPinValue<std::string>(parent_node, "in").empty();
        }
        else if (parent_node->inputs.at("in")->type == PinType::Int)
        {
            output_pin->value = GetInputPinValue<int>(parent_node, "in") != 0;
        }
        else if (parent_node->inputs.at("in")->type == PinType::Float)
        {
            output_pin->value = GetInputPinValue<float>(parent_node, "in") != 0;
        }
        else if (parent_node->inputs.at("in")->type == PinType::Bool)
        {
            output_pin->value = GetInputPinValue<bool>(parent_node, "in");
        }
    }
    else if (parent_node->outputs.at("out")->type == PinType::Int)
    {
        std::shared_ptr<PinValue<int>> output_pin = std::dynamic_pointer_cast<PinValue<int>>(parent_node->outputs.at("out"));
        if (parent_node->inputs.at("in")->type == PinType::String)
        {
            std::string tmp_str = GetInputPinValue<std::string>(parent_node, "in");
            try {
                output_pin->value = std::stoi(tmp_str);
            }
            catch (...)
            {
                output_pin->value = 0;
            }
        }
        else if (parent_node->inputs.at("in")->type == PinType::Int)
        {
            output_pin->value = GetInputPinValue<int>(parent_node, "in");
        }
        else if (parent_node->inputs.at("in")->type == PinType::Float)
        {
            output_pin->value = (int)GetInputPinValue<float>(parent_node, "in");
        }
        else if (parent_node->inputs.at("in")->type == PinType::Bool)
        {
            if (GetInputPinValue<bool>(parent_node, "in"))
                output_pin->value = 1;
            else
                output_pin->value = 0;
        }
    }
    else if (parent_node->outputs.at("out")->type == PinType::Float)
    {
        std::shared_ptr<PinValue<float>> output_pin = std::dynamic_pointer_cast<PinValue<float>>(parent_node->outputs.at("out"));
        if (parent_node->inputs.at("in")->type == PinType::String)
        {
            std::string tmp_str = GetInputPinValue<std::string>(parent_node, "in");
            try {
                output_pin->value = std::stof(tmp_str);
            }
            catch (...)
            {
                output_pin->value = 0;
            }
        }
        else if (parent_node->inputs.at("in")->type == PinType::Int)
        {
            output_pin->value = GetInputPinValue<int>(parent_node, "in");
        }
        else if (parent_node->inputs.at("in")->type == PinType::Float)
        {
            output_pin->value = GetInputPinValue<float>(parent_node, "in");
        }
        else if (parent_node->inputs.at("in")->type == PinType::Bool)
        {
            if (GetInputPinValue<bool>(parent_node, "in"))
                output_pin->value = 1.0;
            else
                output_pin->value = 0.0;
        }
    }
}

std::shared_ptr<Node> ConvertTo(std::vector<std::shared_ptr<Node>>& s_Nodes)
{
    s_Nodes.emplace_back(new Node(GetNextId(), "Convert To", true));
    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<PinValue<float>>>("in", new PinValue<float>("in", 0, GetNextId(), "In", PinType::Float, 0)));
    s_Nodes.back()->inputs.at("in")->isTemplate = true;
    s_Nodes.back()->inputs.at("in")->template_allowed_types.push_back(PinType::Bool);
    s_Nodes.back()->inputs.at("in")->template_allowed_types.push_back(PinType::Float);
    s_Nodes.back()->inputs.at("in")->template_allowed_types.push_back(PinType::Int);
    s_Nodes.back()->inputs.at("in")->template_allowed_types.push_back(PinType::String);
    s_Nodes.back()->outputs.insert(std::pair<std::string, std::shared_ptr<PinValue<float>>>("out", new PinValue<float>("out", 0, GetNextId(), "Out", PinType::Float, 0)));
    s_Nodes.back()->outputs.at("out")->isTemplate = true;
    s_Nodes.back()->outputs.at("out")->template_allowed_types.push_back(PinType::Bool);
    s_Nodes.back()->outputs.at("out")->template_allowed_types.push_back(PinType::Float);
    s_Nodes.back()->outputs.at("out")->template_allowed_types.push_back(PinType::Int);
    s_Nodes.back()->outputs.at("out")->template_allowed_types.push_back(PinType::String);

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
        if (parent_node->inputs.at("placeholder_pin")->type == PinType::String)
        {
            std::string placeholder_value = GetInputPinValue<std::string>(parent_node, "placeholder_pin");
            std::shared_ptr<PlaceholderValue<std::string>> ph_value = std::dynamic_pointer_cast<PlaceholderValue<std::string>>(placeholder);
            ph_value->value = placeholder_value;
        }
        else if (parent_node->inputs.at("placeholder_pin")->type == PinType::Int)
        {
            int placeholder_value = GetInputPinValue<int>(parent_node, "placeholder_pin");
            std::shared_ptr<PlaceholderValue<int>> ph_value = std::dynamic_pointer_cast<PlaceholderValue<int>>(placeholder);
            ph_value->value = placeholder_value;
        }
        else if (parent_node->inputs.at("placeholder_pin")->type == PinType::Float)
        {
            float placeholder_value = GetInputPinValue<float>(parent_node, "placeholder_pin");
            std::shared_ptr<PlaceholderValue<float>> ph_value = std::dynamic_pointer_cast<PlaceholderValue<float>>(placeholder);
            ph_value->value = placeholder_value;
        }
        else if (parent_node->inputs.at("placeholder_pin")->type == PinType::Bool)
        {
            bool placeholder_value = GetInputPinValue<bool>(parent_node, "placeholder_pin");
            std::shared_ptr<PlaceholderValue<bool>> ph_value = std::dynamic_pointer_cast<PlaceholderValue<bool>>(placeholder);
            ph_value->value = placeholder_value;
        }
        else if (parent_node->inputs.at("placeholder_pin")->type == PinType::TextureObject)
        {
            std::shared_ptr<TextureObject> placeholder_value = GetInputPinValue<std::shared_ptr<TextureObject>>(parent_node, "placeholder_pin");
            std::shared_ptr<PlaceholderValue<std::shared_ptr<TextureObject>>> ph_value = std::dynamic_pointer_cast<PlaceholderValue<std::shared_ptr<TextureObject>>>(placeholder);
            ph_value->value = placeholder_value;
        }
        else if (parent_node->inputs.at("placeholder_pin")->type == PinType::ProgramObject)
        {
            std::shared_ptr<ProgramObject> placeholder_value = GetInputPinValue<std::shared_ptr<ProgramObject>>(parent_node, "placeholder_pin");
            std::shared_ptr<PlaceholderValue<std::shared_ptr<ProgramObject>>> ph_value = std::dynamic_pointer_cast<PlaceholderValue<std::shared_ptr<ProgramObject>>>(placeholder);
            ph_value->value = placeholder_value;
        }
        else if (parent_node->inputs.at("placeholder_pin")->type == PinType::VertexShaderObject)
        {
            std::shared_ptr<ShaderObject> placeholder_value = GetInputPinValue<std::shared_ptr<ShaderObject>>(parent_node, "placeholder_pin");
            std::shared_ptr<PlaceholderValue<std::shared_ptr<ShaderObject>>> ph_value = std::dynamic_pointer_cast<PlaceholderValue<std::shared_ptr<ShaderObject>>>(placeholder);
            ph_value->value = placeholder_value;
        }
        else if (parent_node->inputs.at("placeholder_pin")->type == PinType::FragmentShaderObject)
        {
            std::shared_ptr<ShaderObject> placeholder_value = GetInputPinValue<std::shared_ptr<ShaderObject>>(parent_node, "placeholder_pin");
            std::shared_ptr<PlaceholderValue<std::shared_ptr<ShaderObject>>> ph_value = std::dynamic_pointer_cast<PlaceholderValue<std::shared_ptr<ShaderObject>>>(placeholder);
            ph_value->value = placeholder_value;
        }
    }
    RunNextNodeFunc(parent_node, "next");
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

void SetPlaceholder_Func::UpdateNodeInspector()
{
    auto editor_config = EditorConfig::instance();
    auto config = InstanceConfig::instance();
    std::string ph_name = "";
    if (placeholder)
            ph_name = placeholder->name;
    if (ph_name != "")
        ImGui::Text(((std::string)("Placeholder Name: " + ph_name)).c_str());
    if (ImGui::BeginTabItem("Placeholder"))
    {
        if (ImGui::Button("Create Placeholder"))
        {
            editor_config->showCreatePlaceholderWindow = true;
        }
        if (config->GetPlaceholdersMapKeys().size() > 0)
        {
            if (ImGui::Button("Select Placeholder"))
            {
                editor_config->showSelectPlaceholderWindow = true;
            }
        }
    }
}

std::shared_ptr<Node> SetPlaceholder(std::vector<std::shared_ptr<Node>>& s_Nodes)
{
    s_Nodes.emplace_back(new Node(GetNextId(), "Set Placeholder"));
    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<BasePin>>("enter", new BasePin("enter", 0, GetNextId(), "Enter", PinType::Flow)));
    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<PinValue<std::string>>>("placeholder_pin", new PinValue<std::string>("placeholder_pin", 1, GetNextId(), "Value", PinType::String, "")));
    s_Nodes.back()->outputs.insert(std::pair<std::string, std::shared_ptr<BasePin>>("next", new BasePin("next", 0, GetNextId(), "Next", PinType::Flow)));

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
        std::shared_ptr<PinValue<std::string>> output_pin = std::dynamic_pointer_cast<PinValue<std::string>>(parent_node->outputs.at("placeholder_pin"));
        output_pin->value = ph_value;
    }
    else if (placeholder_type == PinType::Bool)
    {
        bool ph_value = false;
        if (placeholder)
            ph_value = std::dynamic_pointer_cast<PlaceholderValue<bool>>(placeholder)->value;
        std::shared_ptr<PinValue<bool>> output_pin = std::dynamic_pointer_cast<PinValue<bool>>(parent_node->outputs.at("placeholder_pin"));
        output_pin->value = ph_value;
    }
    else if (placeholder_type == PinType::Float)
    {
        float ph_value = 0;
        if (placeholder)
            ph_value = std::dynamic_pointer_cast<PlaceholderValue<float>>(placeholder)->value;
        std::shared_ptr<PinValue<float>> output_pin = std::dynamic_pointer_cast<PinValue<float>>(parent_node->outputs.at("placeholder_pin"));
        output_pin->value = ph_value;
    }
    else if (placeholder_type == PinType::Int)
    {
        int ph_value = 0;
        if (placeholder)
            ph_value = std::dynamic_pointer_cast<PlaceholderValue<int>>(placeholder)->value;
        std::shared_ptr<PinValue<int>> output_pin = std::dynamic_pointer_cast<PinValue<int>>(parent_node->outputs.at("placeholder_pin"));
        output_pin->value = ph_value;
    }
    else if (placeholder_type == PinType::TextureObject)
    {
        std::shared_ptr<TextureObject> ph_value = nullptr;
        if (placeholder)
            ph_value = std::dynamic_pointer_cast<PlaceholderValue<std::shared_ptr<TextureObject>>>(placeholder)->value;
        std::shared_ptr<PinValue<std::shared_ptr<TextureObject>>> output_pin = std::dynamic_pointer_cast<PinValue<std::shared_ptr<TextureObject>>>(parent_node->outputs.at("placeholder_pin"));
        output_pin->value = ph_value;
    }
    else if (placeholder_type == PinType::ProgramObject)
    {
        std::shared_ptr<ProgramObject> ph_value = nullptr;
        if (placeholder)
            ph_value = std::dynamic_pointer_cast<PlaceholderValue<std::shared_ptr<ProgramObject>>>(placeholder)->value;
        std::shared_ptr<PinValue<std::shared_ptr<ProgramObject>>> output_pin = std::dynamic_pointer_cast<PinValue<std::shared_ptr<ProgramObject>>>(parent_node->outputs.at("placeholder_pin"));
        output_pin->value = ph_value;
    }
    else if (placeholder_type == PinType::VertexShaderObject)
    {
        std::shared_ptr<ShaderObject> ph_value = nullptr;
        if (placeholder)
            ph_value = std::dynamic_pointer_cast<PlaceholderValue<std::shared_ptr<ShaderObject>>>(placeholder)->value;
        std::shared_ptr<PinValue<std::shared_ptr<ShaderObject>>> output_pin = std::dynamic_pointer_cast<PinValue<std::shared_ptr<ShaderObject>>>(parent_node->outputs.at("placeholder_pin"));
        output_pin->value = ph_value;
    }
    else if (placeholder_type == PinType::FragmentShaderObject)
    {
        std::shared_ptr<ShaderObject> ph_value = nullptr;
        if (placeholder)
            ph_value = std::dynamic_pointer_cast<PlaceholderValue<std::shared_ptr<ShaderObject>>>(placeholder)->value;
        std::shared_ptr<PinValue<std::shared_ptr<ShaderObject>>> output_pin = std::dynamic_pointer_cast<PinValue<std::shared_ptr<ShaderObject>>>(parent_node->outputs.at("placeholder_pin"));
        output_pin->value = ph_value;
    }
}

void GetPlaceholder_Func::UpdateNodeInspector()
{
    auto editor_config = EditorConfig::instance();
    auto config = InstanceConfig::instance();
    std::string ph_name = "";
    if (placeholder)
        ph_name = placeholder->name;
    if (ph_name != "")
        ImGui::Text(((std::string)("Placeholder Name: " + ph_name)).c_str());
    if (ImGui::BeginTabItem("Placeholder"))
    {
        if (ImGui::Button("Create Placeholder"))
        {
            editor_config->showCreatePlaceholderWindow = true;
        }
        if (config->GetPlaceholdersMapKeys().size() > 0)
        {
            if (ImGui::Button("Select Placeholder"))
            {
                editor_config->showSelectPlaceholderWindow = true;
            }
        }
    }
}

std::shared_ptr<Node> GetPlaceholder(std::vector<std::shared_ptr<Node>>& s_Nodes)
{
    s_Nodes.emplace_back(new Node(GetNextId(), "Get Placeholder", true));
    s_Nodes.back()->outputs.insert(std::pair<std::string, std::shared_ptr<PinValue<std::string>>>("placeholder_pin", new PinValue<std::string>("placeholder_pin", 0, GetNextId(), "Value", PinType::String, "")));

    s_Nodes.back()->is_get_placeholder = true;
    s_Nodes.back()->node_funcs = std::make_shared<GetPlaceholder_Func>();
    std::dynamic_pointer_cast<GetPlaceholder_Func>(s_Nodes.back()->node_funcs)->parent_node = s_Nodes.back();

    s_Nodes.back()->node_funcs->Initialize();

    BuildNode(s_Nodes.back());

    return s_Nodes.back();
}





void SpoutSender_Func::Initialize()
{
    bInitialized = false;
}

void SpoutSender_Func::Run()
{
    std::shared_ptr<TextureObject> texutre_obj = GetInputPinValue<std::shared_ptr<TextureObject>>(parent_node, "texture");
    if (texutre_obj)
    {
        if (texutre_obj->width != width || texutre_obj->height != height || texutre_obj->object_name != spout_name || bInitialized == false)
        {
            DeleteSpout();
            width = texutre_obj->width;
            height = texutre_obj->height;
            spout_name = texutre_obj->object_name;
            bInitialized = spoutsender.CreateSender(spout_name.c_str(), width, height);
        }
        spoutsender.SendTexture(texutre_obj->object_id, GL_TEXTURE_2D, width, height);
    }
    else
    {
        DeleteSpout();
    }
}

void SpoutSender_Func::Delete()
{
    parent_node = nullptr;
    DeleteSpout();
}

void SpoutSender_Func::DeleteSpout()
{
    if (bInitialized)
    {
        spoutsender.ReleaseSender();
        bInitialized = false;
    }
}

std::shared_ptr<Node> SpoutSenderNode(std::vector<std::shared_ptr<Node>>& s_Nodes)
{
    s_Nodes.emplace_back(new Node(GetNextId(), "Spout Sender"));

    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<BasePin>>("enter", new BasePin("enter", 0, GetNextId(), "Enter", PinType::Flow)));
    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<PinValue<std::shared_ptr<TextureObject>>>>("texture", new PinValue<std::shared_ptr<TextureObject>>("texture", 1, GetNextId(), "Texture", PinType::TextureObject, nullptr)));
    s_Nodes.back()->outputs.insert(std::pair<std::string, std::shared_ptr<BasePin>>("next", new BasePin("next", 0, GetNextId(), "Next", PinType::Flow)));

    s_Nodes.back()->node_funcs = std::make_shared<SpoutSender_Func>();
    std::dynamic_pointer_cast<SpoutSender_Func>(s_Nodes.back()->node_funcs)->parent_node = s_Nodes.back();

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

    std::function<std::shared_ptr<Node>(std::vector<std::shared_ptr<Node>>&)> func_5 = SpoutSenderNode;
    std::vector<std::string> keywords_5{ "Spout", "Sender" };
    search_nodes_vector.push_back(SearchNodeObj("Spout Sender", keywords_5, func_5));
}
