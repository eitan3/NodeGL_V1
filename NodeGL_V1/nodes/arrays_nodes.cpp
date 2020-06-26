#include "arrays_nodes.h"
#include "../EditorConfig.h"
#include "../InstanceConfig.h"





void GetArrayNode_Func::Initialize()
{
    arrayPH = nullptr;
}

void GetArrayNode_Func::Delete()
{
    if (arrayPH)
    {
        arrayPH->nodesID_vec.erase(std::remove(arrayPH->nodesID_vec.begin(), arrayPH->nodesID_vec.end(), parent_node->id), arrayPH->nodesID_vec.end());
    }
    arrayPH = nullptr;
    parent_node = nullptr;
}

void GetArrayNode_Func::NoFlowUpdatePinsValues()
{
    if (arrayPH_type == PinType::String)
    {
        std::shared_ptr<std::vector<std::string>> ph_value;
        std::shared_ptr<std::vector<std::string>> ph_def_value;
        if (arrayPH)
        {
            ph_value = std::dynamic_pointer_cast<ArrayValue<std::string>>(arrayPH)->value;
            ph_def_value = std::dynamic_pointer_cast<ArrayValue<std::string>>(arrayPH)->default_value;
        }
        std::shared_ptr<PinArrValue<std::string>> output_pin = std::dynamic_pointer_cast<PinArrValue<std::string>>(parent_node->outputs.at("array_pin"));
        output_pin->value = ph_value;
        output_pin->default_value = ph_def_value;
    }
    else if (arrayPH_type == PinType::Bool)
    {
        std::shared_ptr<std::vector<bool>> ph_value;
        std::shared_ptr<std::vector<bool>> ph_def_value;
        if (arrayPH)
        {
            ph_value = std::dynamic_pointer_cast<ArrayValue<bool>>(arrayPH)->value;
            ph_def_value = std::dynamic_pointer_cast<ArrayValue<bool>>(arrayPH)->default_value;
        }
        std::shared_ptr<PinArrValue<bool>> output_pin = std::dynamic_pointer_cast<PinArrValue<bool>>(parent_node->outputs.at("array_pin"));
        output_pin->value = ph_value;
        output_pin->default_value = ph_def_value;
    }
    else if (arrayPH_type == PinType::Float)
    {
        std::shared_ptr<std::vector<float>> ph_value;
        std::shared_ptr<std::vector<float>> ph_def_value;
        if (arrayPH)
        {
            ph_value = std::dynamic_pointer_cast<ArrayValue<float>>(arrayPH)->value;
            ph_def_value = std::dynamic_pointer_cast<ArrayValue<float>>(arrayPH)->default_value;
        }
        std::shared_ptr<PinArrValue<float>> output_pin = std::dynamic_pointer_cast<PinArrValue<float>>(parent_node->outputs.at("array_pin"));
        output_pin->value = ph_value;
        output_pin->default_value = ph_def_value;
    }
    else if (arrayPH_type == PinType::Int)
    {
        std::shared_ptr<std::vector<int>> ph_value;
        std::shared_ptr<std::vector<int>> ph_def_value;
        if (arrayPH)
        {
            ph_value = std::dynamic_pointer_cast<ArrayValue<int>>(arrayPH)->value;
            ph_def_value = std::dynamic_pointer_cast<ArrayValue<int>>(arrayPH)->default_value;
        }
        std::shared_ptr<PinArrValue<int>> output_pin = std::dynamic_pointer_cast<PinArrValue<int>>(parent_node->outputs.at("array_pin"));
        output_pin->value = ph_value;
        output_pin->default_value = ph_def_value;
    }
    else if (arrayPH_type == PinType::Vector2)
    {
        std::shared_ptr<std::vector<glm::vec2>> ph_value;
        std::shared_ptr<std::vector<glm::vec2>> ph_def_value;
        if (arrayPH)
        {
            ph_value = std::dynamic_pointer_cast<ArrayValue<glm::vec2>>(arrayPH)->value;
            ph_def_value = std::dynamic_pointer_cast<ArrayValue<glm::vec2>>(arrayPH)->default_value;
        }
        std::shared_ptr<PinArrValue<glm::vec2>> output_pin = std::dynamic_pointer_cast<PinArrValue<glm::vec2>>(parent_node->outputs.at("array_pin"));
        output_pin->value = ph_value;
        output_pin->default_value = ph_def_value;
    }
    else if (arrayPH_type == PinType::Vector3)
    {
        std::shared_ptr<std::vector<glm::vec3>> ph_value;
        std::shared_ptr<std::vector<glm::vec3>> ph_def_value;
        if (arrayPH)
        {
            ph_value = std::dynamic_pointer_cast<ArrayValue<glm::vec3>>(arrayPH)->value;
            ph_def_value = std::dynamic_pointer_cast<ArrayValue<glm::vec3>>(arrayPH)->default_value;
        }
        std::shared_ptr<PinArrValue<glm::vec3>> output_pin = std::dynamic_pointer_cast<PinArrValue<glm::vec3>>(parent_node->outputs.at("array_pin"));
        output_pin->value = ph_value;
        output_pin->default_value = ph_def_value;
    }
    else if (arrayPH_type == PinType::Vector4)
    {
        std::shared_ptr<std::vector<glm::vec4>> ph_value;
        std::shared_ptr<std::vector<glm::vec4>> ph_def_value;
        if (arrayPH)
        {
            ph_value = std::dynamic_pointer_cast<ArrayValue<glm::vec4>>(arrayPH)->value;
            ph_def_value = std::dynamic_pointer_cast<ArrayValue<glm::vec4>>(arrayPH)->default_value;
        }
        std::shared_ptr<PinArrValue<glm::vec4>> output_pin = std::dynamic_pointer_cast<PinArrValue<glm::vec4>>(parent_node->outputs.at("array_pin"));
        output_pin->value = ph_value;
        output_pin->default_value = ph_def_value;
    }
    else if (arrayPH_type == PinType::Matrix4x4)
    {
        std::shared_ptr<std::vector<glm::mat4>> ph_value;
        std::shared_ptr<std::vector<glm::mat4>> ph_def_value;
        if (arrayPH)
        {
            ph_value = std::dynamic_pointer_cast<ArrayValue<glm::mat4>>(arrayPH)->value;
            ph_def_value = std::dynamic_pointer_cast<ArrayValue<glm::mat4>>(arrayPH)->default_value;
        }
        std::shared_ptr<PinArrValue<glm::mat4>> output_pin = std::dynamic_pointer_cast<PinArrValue<glm::mat4>>(parent_node->outputs.at("array_pin"));
        output_pin->value = ph_value;
        output_pin->default_value = ph_def_value;
    }
    else if (arrayPH_type == PinType::TextureObject)
    {
        std::shared_ptr<std::vector<std::shared_ptr<TextureObject>>> ph_value;
        std::shared_ptr<std::vector<std::shared_ptr<TextureObject>>> ph_def_value;
        if (arrayPH)
        {
            ph_value = std::dynamic_pointer_cast<ArrayValue<std::shared_ptr<TextureObject>>>(arrayPH)->value;
            ph_def_value = std::dynamic_pointer_cast<ArrayValue<std::shared_ptr<TextureObject>>>(arrayPH)->default_value;
        }
        std::shared_ptr<PinArrValue<std::shared_ptr<TextureObject>>> output_pin = std::dynamic_pointer_cast<PinArrValue<std::shared_ptr<TextureObject>>>(parent_node->outputs.at("array_pin"));
        output_pin->value = ph_value;
        output_pin->default_value = ph_def_value;
    }
    else if (arrayPH_type == PinType::ProgramObject)
    {
        std::shared_ptr<std::vector<std::shared_ptr<ProgramObject>>> ph_value;
        std::shared_ptr<std::vector<std::shared_ptr<ProgramObject>>> ph_def_value;
        if (arrayPH)
        {
            ph_value = std::dynamic_pointer_cast<ArrayValue<std::shared_ptr<ProgramObject>>>(arrayPH)->value;
            ph_def_value = std::dynamic_pointer_cast<ArrayValue<std::shared_ptr<ProgramObject>>>(arrayPH)->default_value;
        }
        std::shared_ptr<PinArrValue<std::shared_ptr<ProgramObject>>> output_pin = std::dynamic_pointer_cast<PinArrValue<std::shared_ptr<ProgramObject>>>(parent_node->outputs.at("array_pin"));
        output_pin->value = ph_value;
        output_pin->default_value = ph_def_value;
    }
    else if (arrayPH_type == PinType::VertexShaderObject)
    {
        std::shared_ptr<std::vector<std::shared_ptr<ShaderObject>>> ph_value;
        std::shared_ptr<std::vector<std::shared_ptr<ShaderObject>>> ph_def_value;
        if (arrayPH)
        {
            ph_value = std::dynamic_pointer_cast<ArrayValue<std::shared_ptr<ShaderObject>>>(arrayPH)->value;
            ph_def_value = std::dynamic_pointer_cast<ArrayValue<std::shared_ptr<ShaderObject>>>(arrayPH)->default_value;
        }
        std::shared_ptr<PinArrValue<std::shared_ptr<ShaderObject>>> output_pin = std::dynamic_pointer_cast<PinArrValue<std::shared_ptr<ShaderObject>>>(parent_node->outputs.at("array_pin"));
        output_pin->value = ph_value;
        output_pin->default_value = ph_def_value;
    }
    else if (arrayPH_type == PinType::FragmentShaderObject)
    {
        std::shared_ptr<std::vector<std::shared_ptr<ShaderObject>>> ph_value;
        std::shared_ptr<std::vector<std::shared_ptr<ShaderObject>>> ph_def_value;
        if (arrayPH)
        {
            ph_value = std::dynamic_pointer_cast<ArrayValue<std::shared_ptr<ShaderObject>>>(arrayPH)->value;
            ph_def_value = std::dynamic_pointer_cast<ArrayValue<std::shared_ptr<ShaderObject>>>(arrayPH)->default_value;
        }
        std::shared_ptr<PinArrValue<std::shared_ptr<ShaderObject>>> output_pin = std::dynamic_pointer_cast<PinArrValue<std::shared_ptr<ShaderObject>>>(parent_node->outputs.at("array_pin"));
        output_pin->value = ph_value;
        output_pin->default_value = ph_def_value;
    }
    else if (arrayPH_type == PinType::MeshObject)
    {
        std::shared_ptr<std::vector<std::shared_ptr<MeshObject>>> ph_value;
        std::shared_ptr<std::vector<std::shared_ptr<MeshObject>>> ph_def_value;
        if (arrayPH)
        {
            ph_value = std::dynamic_pointer_cast<ArrayValue<std::shared_ptr<MeshObject>>>(arrayPH)->value;
            ph_def_value = std::dynamic_pointer_cast<ArrayValue<std::shared_ptr<MeshObject>>>(arrayPH)->default_value;
        }
        std::shared_ptr<PinArrValue<std::shared_ptr<MeshObject>>> output_pin = std::dynamic_pointer_cast<PinArrValue<std::shared_ptr<MeshObject>>>(parent_node->outputs.at("array_pin"));
        output_pin->value = ph_value;
        output_pin->default_value = ph_def_value;
    }
}

void GetArrayNode_Func::UpdateNodeInspector()
{
    auto editor_config = EditorConfig::instance();
    auto config = InstanceConfig::instance();
    std::string ph_name = "";
    if (arrayPH)
        ph_name = arrayPH->name;
    if (ph_name != "")
        ImGui::Text(((std::string)("Array Name: " + ph_name)).c_str());
    if (ImGui::BeginTabItem("Array"))
    {
        if (ImGui::Button("Create Array"))
        {
            editor_config->showCreateArrayWindow = true;
        }
        if (config->GetArraysMapKeys().size() > 0)
        {
            if (ImGui::Button("Select Array"))
            {
                editor_config->showSelectArrayWindow = true;
            }
        }
    }
}

void GetArrayNode_Func::SaveNodeData(rapidjson::Writer<rapidjson::StringBuffer>& writer)
{
    if (arrayPH)
    {
        writer.Key("arrayPH_name");
        writer.String(arrayPH->name.c_str());
    }
}

void GetArrayNode_Func::LoadNodeData(rapidjson::Value& node_obj)
{
    if (node_obj.HasMember("arrayPH_name"))
    {
        auto config = InstanceConfig::instance();
        std::string ph_name = std::string(node_obj["arrayPH_name"].GetString());
        std::shared_ptr<BaseArray> ph = config->GetArray(ph_name);
        parent_node->outputs.insert(std::pair<std::string, std::shared_ptr<PinArrValue<std::string>>>("array_pin", new PinArrValue<std::string>("array_pin", 0, GetNextId(), "Value", PinType::String, std::make_shared<std::vector<std::string>>())));
        BuildNode(parent_node);
        UtilsChangePinType(parent_node, PinKind::Output, "array_pin", ph->type, true);
        ph->nodesID_vec.push_back(parent_node->id);
        arrayPH = ph;
        arrayPH_type = ph->type;
    }
}

std::string getArrayNodeName = "Get Array";
std::shared_ptr<Node> GetArrayNode(std::vector<std::shared_ptr<Node>>& s_Nodes)
{
    s_Nodes.emplace_back(new Node(GetNextId(), getArrayNodeName.c_str(), true));
    //s_Nodes.back()->outputs.insert(std::pair<std::string, std::shared_ptr<PinValue<std::string>>>("array_pin", new PinValue<std::string>("array_pin", 0, GetNextId(), "Value", PinType::String, "")));

    s_Nodes.back()->is_get_array = true;
    s_Nodes.back()->node_funcs = std::make_shared<GetArrayNode_Func>();
    std::dynamic_pointer_cast<GetArrayNode_Func>(s_Nodes.back()->node_funcs)->parent_node = s_Nodes.back();

    s_Nodes.back()->node_funcs->Initialize();

    BuildNode(s_Nodes.back());

    return s_Nodes.back();
}





void GetArraySizeNode_Func::Delete()
{
    parent_node = nullptr;
}

void GetArraySizeNode_Func::NoFlowUpdatePinsValues()
{
    if (parent_node->inputs.at("input")->type == PinType::String)
    {
        std::shared_ptr<std::vector<std::string>> input = GetInputPinArrValue<std::string>(parent_node, "input");
        std::shared_ptr<PinValue<int>> output_pin = std::dynamic_pointer_cast<PinValue<int>>(parent_node->outputs.at("size"));
        output_pin->value = input->size();
    }
    else if (parent_node->inputs.at("input")->type == PinType::Bool)
    {
        std::shared_ptr<std::vector<bool>> input = GetInputPinArrValue<bool>(parent_node, "input");
        std::shared_ptr<PinValue<int>> output_pin = std::dynamic_pointer_cast<PinValue<int>>(parent_node->outputs.at("size"));
        output_pin->value = input->size();
    }
    else if (parent_node->inputs.at("input")->type == PinType::Float)
    {
        std::shared_ptr<std::vector<float>> input = GetInputPinArrValue<float>(parent_node, "input");
        std::shared_ptr<PinValue<int>> output_pin = std::dynamic_pointer_cast<PinValue<int>>(parent_node->outputs.at("size"));
        output_pin->value = input->size();
    }
    else if (parent_node->inputs.at("input")->type == PinType::Int)
    {
        std::shared_ptr<std::vector<int>> input = GetInputPinArrValue<int>(parent_node, "input");
        std::shared_ptr<PinValue<int>> output_pin = std::dynamic_pointer_cast<PinValue<int>>(parent_node->outputs.at("size"));
        output_pin->value = input->size();
    }
    else if (parent_node->inputs.at("input")->type == PinType::Vector2)
    {
        std::shared_ptr<std::vector<glm::vec2>> input = GetInputPinArrValue<glm::vec2>(parent_node, "input");
        std::shared_ptr<PinValue<int>> output_pin = std::dynamic_pointer_cast<PinValue<int>>(parent_node->outputs.at("size"));
        output_pin->value = input->size();
    }
    else if (parent_node->inputs.at("input")->type == PinType::Vector3)
    {
        std::shared_ptr<std::vector<glm::vec3>> input = GetInputPinArrValue<glm::vec3>(parent_node, "input");
        std::shared_ptr<PinValue<int>> output_pin = std::dynamic_pointer_cast<PinValue<int>>(parent_node->outputs.at("size"));
        output_pin->value = input->size();
    }
    else if (parent_node->inputs.at("input")->type == PinType::Vector4)
    {
        std::shared_ptr<std::vector<glm::vec4>> input = GetInputPinArrValue<glm::vec4>(parent_node, "input");
        std::shared_ptr<PinValue<int>> output_pin = std::dynamic_pointer_cast<PinValue<int>>(parent_node->outputs.at("size"));
        output_pin->value = input->size();
    }
    else if (parent_node->inputs.at("input")->type == PinType::Matrix4x4)
    {
        std::shared_ptr<std::vector<glm::mat4>> input = GetInputPinArrValue<glm::mat4>(parent_node, "input");
        std::shared_ptr<PinValue<int>> output_pin = std::dynamic_pointer_cast<PinValue<int>>(parent_node->outputs.at("size"));
        output_pin->value = input->size();
    }
    else if (parent_node->inputs.at("input")->type == PinType::TextureObject)
    {
        std::shared_ptr<std::vector<std::shared_ptr<TextureObject>>> input = GetInputPinArrValue<std::shared_ptr<TextureObject>>(parent_node, "input");
        std::shared_ptr<PinValue<int>> output_pin = std::dynamic_pointer_cast<PinValue<int>>(parent_node->outputs.at("size"));
        output_pin->value = input->size();
    }
    else if (parent_node->inputs.at("input")->type == PinType::ProgramObject)
    {
        std::shared_ptr<std::vector<std::shared_ptr<ProgramObject>>> input = GetInputPinArrValue<std::shared_ptr<ProgramObject>>(parent_node, "input");
        std::shared_ptr<PinValue<int>> output_pin = std::dynamic_pointer_cast<PinValue<int>>(parent_node->outputs.at("size"));
        output_pin->value = input->size();
    }
    else if (parent_node->inputs.at("input")->type == PinType::VertexShaderObject)
    {
        std::shared_ptr<std::vector<std::shared_ptr<ShaderObject>>> input = GetInputPinArrValue<std::shared_ptr<ShaderObject>>(parent_node, "input");
        std::shared_ptr<PinValue<int>> output_pin = std::dynamic_pointer_cast<PinValue<int>>(parent_node->outputs.at("size"));
        output_pin->value = input->size();
    }
    else if (parent_node->inputs.at("input")->type == PinType::FragmentShaderObject)
    {
        std::shared_ptr<std::vector<std::shared_ptr<ShaderObject>>> input = GetInputPinArrValue<std::shared_ptr<ShaderObject>>(parent_node, "input");
        std::shared_ptr<PinValue<int>> output_pin = std::dynamic_pointer_cast<PinValue<int>>(parent_node->outputs.at("size"));
        output_pin->value = input->size();
    }
    else if (parent_node->inputs.at("input")->type == PinType::MeshObject)
    {
        std::shared_ptr<std::vector<std::shared_ptr<MeshObject>>> input = GetInputPinArrValue<std::shared_ptr<MeshObject>>(parent_node, "input");
        std::shared_ptr<PinValue<int>> output_pin = std::dynamic_pointer_cast<PinValue<int>>(parent_node->outputs.at("size"));
        output_pin->value = input->size();
    }
}

std::string getArraySizeNodeName = "Array - Get Size";
std::shared_ptr<Node> GetArraySizeNode(std::vector<std::shared_ptr<Node>>& s_Nodes)
{
    s_Nodes.emplace_back(new Node(GetNextId(), getArraySizeNodeName.c_str(), true));
    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<PinArrValue<std::string>>>("input", new PinArrValue<std::string>("input", 0, GetNextId(), "Array", PinType::String, std::make_shared<std::vector<std::string>>())));
    s_Nodes.back()->inputs.at("input")->isGeneralArray = true;

    s_Nodes.back()->outputs.insert(std::pair<std::string, std::shared_ptr<PinValue<int>>>("size", new PinValue<int>("size", 0, GetNextId(), "Size", PinType::Int, 0)));
    //s_Nodes.back()->outputs.insert(std::pair<std::string, std::shared_ptr<PinArrValue<std::string>>>("array_pin", new PinArrValue<std::string>("array_pin", 0, GetNextId(), "Value", PinType::String, "")));

    s_Nodes.back()->node_funcs = std::make_shared<GetArraySizeNode_Func>();
    std::dynamic_pointer_cast<GetArraySizeNode_Func>(s_Nodes.back()->node_funcs)->parent_node = s_Nodes.back();

    s_Nodes.back()->node_funcs->Initialize();

    BuildNode(s_Nodes.back());

    return s_Nodes.back();
}





void ArrayInsertNode_Func::Run(std::string called_pin)
{
    UpdateNodeUI();
    if (parent_node->inputs.at("input")->type == PinType::String)
    {
        std::shared_ptr<std::vector<std::string>> input = GetInputPinArrValue<std::string>(parent_node, "input");
        std::string obj = GetInputPinValue<std::string>(parent_node, "object");
        input->push_back(obj);
    }
    else if (parent_node->inputs.at("input")->type == PinType::Bool)
    {
        std::shared_ptr<std::vector<bool>> input = GetInputPinArrValue<bool>(parent_node, "input");
        bool obj = GetInputPinValue<bool>(parent_node, "object");
        input->push_back(obj);
    }
    else if (parent_node->inputs.at("input")->type == PinType::Float)
    {
        std::shared_ptr<std::vector<float>> input = GetInputPinArrValue<float>(parent_node, "input");
        float obj = GetInputPinValue<float>(parent_node, "object");
        input->push_back(obj);
    }
    else if (parent_node->inputs.at("input")->type == PinType::Int)
    {
        std::shared_ptr<std::vector<int>> input = GetInputPinArrValue<int>(parent_node, "input");
        int obj = GetInputPinValue<int>(parent_node, "object");
        input->push_back(obj);
    }
    else if (parent_node->inputs.at("input")->type == PinType::Vector2)
    {
        std::shared_ptr<std::vector<glm::vec2>> input = GetInputPinArrValue<glm::vec2>(parent_node, "input");
        glm::vec2 obj = GetInputPinValue<glm::vec2>(parent_node, "object");
        input->push_back(obj);
    }
    else if (parent_node->inputs.at("input")->type == PinType::Vector3)
    {
        std::shared_ptr<std::vector<glm::vec3>> input = GetInputPinArrValue<glm::vec3>(parent_node, "input");
        glm::vec3 obj = GetInputPinValue<glm::vec3>(parent_node, "object");
        input->push_back(obj);
    }
    else if (parent_node->inputs.at("input")->type == PinType::Vector4)
    {
        std::shared_ptr<std::vector<glm::vec4>> input = GetInputPinArrValue<glm::vec4>(parent_node, "input");
        glm::vec4 obj = GetInputPinValue<glm::vec4>(parent_node, "object");
        input->push_back(obj);
    }
    else if (parent_node->inputs.at("input")->type == PinType::Matrix4x4)
    {
        std::shared_ptr<std::vector<glm::mat4>> input = GetInputPinArrValue<glm::mat4>(parent_node, "input");
        glm::mat4 obj = GetInputPinValue<glm::mat4>(parent_node, "object");
        input->push_back(obj);
    }
    else if (parent_node->inputs.at("input")->type == PinType::TextureObject)
    {
        std::shared_ptr<std::vector<std::shared_ptr<TextureObject>>> input = GetInputPinArrValue<std::shared_ptr<TextureObject>>(parent_node, "input");
        std::shared_ptr<TextureObject> obj = GetInputPinValue<std::shared_ptr<TextureObject>>(parent_node, "object");
        input->push_back(obj);
    }
    else if (parent_node->inputs.at("input")->type == PinType::ProgramObject)
    {
        std::shared_ptr<std::vector<std::shared_ptr<ProgramObject>>> input = GetInputPinArrValue<std::shared_ptr<ProgramObject>>(parent_node, "input");
        std::shared_ptr<ProgramObject> obj = GetInputPinValue<std::shared_ptr<ProgramObject>>(parent_node, "object");
        input->push_back(obj);
    }
    else if (parent_node->inputs.at("input")->type == PinType::VertexShaderObject)
    {
        std::shared_ptr<std::vector<std::shared_ptr<ShaderObject>>> input = GetInputPinArrValue<std::shared_ptr<ShaderObject>>(parent_node, "input");
        std::shared_ptr<ShaderObject> obj = GetInputPinValue<std::shared_ptr<ShaderObject>>(parent_node, "object");
        input->push_back(obj);
    }
    else if (parent_node->inputs.at("input")->type == PinType::FragmentShaderObject)
    {
        std::shared_ptr<std::vector<std::shared_ptr<ShaderObject>>> input = GetInputPinArrValue<std::shared_ptr<ShaderObject>>(parent_node, "input");
        std::shared_ptr<ShaderObject> obj = GetInputPinValue<std::shared_ptr<ShaderObject>>(parent_node, "object");
        input->push_back(obj);
    }
    else if (parent_node->inputs.at("input")->type == PinType::MeshObject)
    {
        std::shared_ptr<std::vector<std::shared_ptr<MeshObject>>> input = GetInputPinArrValue<std::shared_ptr<MeshObject>>(parent_node, "input");
        std::shared_ptr<MeshObject> obj = GetInputPinValue<std::shared_ptr<MeshObject>>(parent_node, "object");
        input->push_back(obj);
    }
    RunNextNodeFunc(parent_node, "next");
}

void ArrayInsertNode_Func::Delete()
{
    parent_node = nullptr;
}

void ArrayInsertNode_Func::UpdateNodeUI()
{
    if (parent_node->inputs.at("input")->type != parent_node->inputs.at("object")->type || tmp_loaded_value)
    {
        UtilsChangePinType(parent_node, PinKind::Input, "object", parent_node->inputs.at("input")->type, false);
        if (tmp_loaded_value)
        {
            UtilsChangePinType(parent_node, PinKind::Input, "object", tmp_loaded_value->type, false);
            if (tmp_loaded_value->type == PinType::String)
            {
                std::dynamic_pointer_cast<PinValue<std::string>>(parent_node->inputs.at("object"))->default_value = std::dynamic_pointer_cast<PlaceholderValue<std::string>>(tmp_loaded_value)->value;
            }
            else if (tmp_loaded_value->type == PinType::Bool)
            {
                std::dynamic_pointer_cast<PinValue<bool>>(parent_node->inputs.at("object"))->default_value = std::dynamic_pointer_cast<PlaceholderValue<bool>>(tmp_loaded_value)->value;
            }
            else if (tmp_loaded_value->type == PinType::Int)
            {
                std::dynamic_pointer_cast<PinValue<int>>(parent_node->inputs.at("object"))->default_value = std::dynamic_pointer_cast<PlaceholderValue<int>>(tmp_loaded_value)->value;
            }
            else if (tmp_loaded_value->type == PinType::Float)
            {
                std::dynamic_pointer_cast<PinValue<float>>(parent_node->inputs.at("object"))->default_value = std::dynamic_pointer_cast<PlaceholderValue<float>>(tmp_loaded_value)->value;
            }
            else if (tmp_loaded_value->type == PinType::Vector2)
            {
                std::dynamic_pointer_cast<PinValue<glm::vec2>>(parent_node->inputs.at("object"))->default_value = std::dynamic_pointer_cast<PlaceholderValue<glm::vec2>>(tmp_loaded_value)->value;
            }
            else if (tmp_loaded_value->type == PinType::Vector3)
            {
                std::dynamic_pointer_cast<PinValue<glm::vec3>>(parent_node->inputs.at("object"))->default_value = std::dynamic_pointer_cast<PlaceholderValue<glm::vec3>>(tmp_loaded_value)->value;
            }
            else if (tmp_loaded_value->type == PinType::Vector4)
            {
                std::dynamic_pointer_cast<PinValue<glm::vec4>>(parent_node->inputs.at("object"))->default_value = std::dynamic_pointer_cast<PlaceholderValue<glm::vec4>>(tmp_loaded_value)->value;
            }
            else if (tmp_loaded_value->type == PinType::Matrix4x4)
            {
                std::dynamic_pointer_cast<PinValue<glm::mat4>>(parent_node->inputs.at("object"))->default_value = std::dynamic_pointer_cast<PlaceholderValue<glm::mat4>>(tmp_loaded_value)->value;
            }
            if (tmp_loaded_value->type == parent_node->inputs.at("input")->type)
                tmp_loaded_value = nullptr;
        }
    }
}

void ArrayInsertNode_Func::SaveNodeData(rapidjson::Writer<rapidjson::StringBuffer>& writer)
{
    writer.Key("array_type");
    writer.String(PinTypeToString(parent_node->inputs.at("object")->type).c_str());

    if (parent_node->inputs.at("object")->type == PinType::String)
    {
        writer.Key("object");
        std::string obj_value = std::dynamic_pointer_cast<PinValue<std::string>>(parent_node->inputs.at("object"))->default_value;
        writer.String(obj_value.c_str());
    }
    else if (parent_node->inputs.at("object")->type == PinType::Int)
    {
        writer.Key("object");
        int obj_value = std::dynamic_pointer_cast<PinValue<int>>(parent_node->inputs.at("object"))->default_value;
        writer.Int(obj_value);
    }
    else if (parent_node->inputs.at("object")->type == PinType::Float)
    {
        writer.Key("object");
        float obj_value = std::dynamic_pointer_cast<PinValue<float>>(parent_node->inputs.at("object"))->default_value;
        writer.Double(obj_value);
    }
    else if (parent_node->inputs.at("object")->type == PinType::Bool)
    {
        writer.Key("object");
        bool obj_value = std::dynamic_pointer_cast<PinValue<bool>>(parent_node->inputs.at("object"))->default_value;
        writer.Bool(obj_value);
    }
    else if (parent_node->inputs.at("object")->type == PinType::Vector2)
    {
        writer.Key("object");
        glm::vec2 obj_value = std::dynamic_pointer_cast<PinValue<glm::vec2>>(parent_node->inputs.at("object"))->default_value;
        writer.StartArray();
        writer.Double(obj_value.x);
        writer.Double(obj_value.y);
        writer.EndArray();
    }
    else if (parent_node->inputs.at("object")->type == PinType::Vector3)
    {
        writer.Key("object");
        glm::vec3 obj_value = std::dynamic_pointer_cast<PinValue<glm::vec3>>(parent_node->inputs.at("object"))->default_value;
        writer.StartArray();
        writer.Double(obj_value.x);
        writer.Double(obj_value.y);
        writer.Double(obj_value.z);
        writer.EndArray();
    }
    else if (parent_node->inputs.at("object")->type == PinType::Vector4)
    {
        writer.Key("object");
        glm::vec4 obj_value = std::dynamic_pointer_cast<PinValue<glm::vec4>>(parent_node->inputs.at("object"))->default_value;
        writer.StartArray();
        writer.Double(obj_value.x);
        writer.Double(obj_value.y);
        writer.Double(obj_value.z);
        writer.Double(obj_value.w);
        writer.EndArray();
    }
    else if (parent_node->inputs.at("object")->type == PinType::Matrix4x4)
    {
        writer.Key("object");
        writer.StartArray();
        glm::mat4 obj_value = std::dynamic_pointer_cast<PinValue<glm::mat4>>(parent_node->inputs.at("object"))->default_value;
        const float* pSource = (const float*)glm::value_ptr(obj_value);
        for (int i = 0; i < 16; ++i)
            writer.Double(pSource[i]);
        writer.EndArray();
    }
}

void ArrayInsertNode_Func::LoadNodeData(rapidjson::Value& node_obj)
{
    if (!node_obj["array_type"].IsNull())
    {
        PinType array_type = StringToPinType(node_obj["array_type"].GetString());

        if (array_type == PinType::String)
        {
            std::string uni_value = std::string(node_obj["object"].GetString());
            tmp_loaded_value = std::make_shared<PlaceholderValue<std::string>>("tmp", array_type, uni_value);
        }
        else if (array_type == PinType::Bool)
        {
            bool uni_value = node_obj["object"].GetBool();
            tmp_loaded_value = std::make_shared<PlaceholderValue<bool>>("tmp", array_type, uni_value);
        }
        else if (array_type == PinType::Int)
        {
            int uni_value = node_obj["object"].GetInt();
            tmp_loaded_value = std::make_shared<PlaceholderValue<int>>("tmp", array_type, uni_value);
        }
        else if (array_type == PinType::Float)
        {
            float uni_value = node_obj["object"].GetFloat();
            tmp_loaded_value = std::make_shared<PlaceholderValue<float>>("tmp", array_type, uni_value);
        }
        if (array_type == PinType::Vector2)
        {
            glm::vec2 uni_value;
            uni_value.x = node_obj["object"].GetArray()[0].GetFloat();
            uni_value.y = node_obj["object"].GetArray()[1].GetFloat();
            tmp_loaded_value = std::make_shared<PlaceholderValue<glm::vec2>>("tmp", array_type, uni_value);
        }
        else if (array_type == PinType::Vector3)
        {
            glm::vec3 uni_value;
            uni_value.x = node_obj["object"].GetArray()[0].GetFloat();
            uni_value.y = node_obj["object"].GetArray()[1].GetFloat();
            uni_value.z = node_obj["object"].GetArray()[2].GetFloat();
            tmp_loaded_value = std::make_shared<PlaceholderValue<glm::vec3>>("tmp", array_type, uni_value);
        }
        else if (array_type == PinType::Vector4)
        {
            glm::vec4 uni_value;
            uni_value.x = node_obj["object"].GetArray()[0].GetFloat();
            uni_value.y = node_obj["object"].GetArray()[1].GetFloat();
            uni_value.z = node_obj["object"].GetArray()[2].GetFloat();
            uni_value.w = node_obj["object"].GetArray()[3].GetFloat();
            tmp_loaded_value = std::make_shared<PlaceholderValue<glm::vec4>>("tmp", array_type, uni_value);
        }
        else if (array_type == PinType::Matrix4x4)
        {
            glm::mat4 uni_value;
            float* pSource = (float*)glm::value_ptr(uni_value);
            for (int i = 0; i < 16; ++i)
            {
                pSource[i] = node_obj["object"].GetArray()[i].GetFloat();
            }
            tmp_loaded_value = std::make_shared<PlaceholderValue<glm::mat4>>("tmp", array_type, uni_value);
        }
    }
}

std::string arrayInsertNodeName = "Array - Insert Object";
std::shared_ptr<Node> ArrayInsertNode(std::vector<std::shared_ptr<Node>>& s_Nodes)
{
    s_Nodes.emplace_back(new Node(GetNextId(), arrayInsertNodeName.c_str()));
    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<BasePin>>("enter", new BasePin("enter", 0, GetNextId(), "Enter", PinType::Flow)));
    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<PinArrValue<std::string>>>("input", new PinArrValue<std::string>("input", 1, GetNextId(), "Array", PinType::String, std::make_shared<std::vector<std::string>>())));
    s_Nodes.back()->inputs.at("input")->isGeneralArray = true;
    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<PinValue<std::string>>>("object", new PinValue<std::string>("object", 2, GetNextId(), "Object", PinType::String, "")));

    s_Nodes.back()->outputs.insert(std::pair<std::string, std::shared_ptr<BasePin>>("next", new BasePin("next", 0, GetNextId(), "Next", PinType::Flow)));

    s_Nodes.back()->node_funcs = std::make_shared<ArrayInsertNode_Func>();
    std::dynamic_pointer_cast<ArrayInsertNode_Func>(s_Nodes.back()->node_funcs)->parent_node = s_Nodes.back();

    s_Nodes.back()->node_funcs->Initialize();

    BuildNode(s_Nodes.back());

    return s_Nodes.back();
}





void ArrayInsertDefaultNode_Func::Run(std::string called_pin)
{
    UpdateNodeUI();
    if (parent_node->inputs.at("input")->type == PinType::String)
    {
        std::shared_ptr<std::vector<std::string>> input = GetInputPinArrDefaultValue<std::string>(parent_node, "input");
        std::string obj = GetInputPinValue<std::string>(parent_node, "object");
        input->push_back(obj);
    }
    else if (parent_node->inputs.at("input")->type == PinType::Bool)
    {
        std::shared_ptr<std::vector<bool>> input = GetInputPinArrDefaultValue<bool>(parent_node, "input");
        bool obj = GetInputPinValue<bool>(parent_node, "object");
        input->push_back(obj);
    }
    else if (parent_node->inputs.at("input")->type == PinType::Float)
    {
        std::shared_ptr<std::vector<float>> input = GetInputPinArrDefaultValue<float>(parent_node, "input");
        float obj = GetInputPinValue<float>(parent_node, "object");
        input->push_back(obj);
    }
    else if (parent_node->inputs.at("input")->type == PinType::Int)
    {
        std::shared_ptr<std::vector<int>> input = GetInputPinArrDefaultValue<int>(parent_node, "input");
        int obj = GetInputPinValue<int>(parent_node, "object");
        input->push_back(obj);
    }
    else if (parent_node->inputs.at("input")->type == PinType::Vector2)
    {
        std::shared_ptr<std::vector<glm::vec2>> input = GetInputPinArrDefaultValue<glm::vec2>(parent_node, "input");
        glm::vec2 obj = GetInputPinValue<glm::vec2>(parent_node, "object");
        input->push_back(obj);
    }
    else if (parent_node->inputs.at("input")->type == PinType::Vector3)
    {
        std::shared_ptr<std::vector<glm::vec3>> input = GetInputPinArrDefaultValue<glm::vec3>(parent_node, "input");
        glm::vec3 obj = GetInputPinValue<glm::vec3>(parent_node, "object");
        input->push_back(obj);
    }
    else if (parent_node->inputs.at("input")->type == PinType::Vector4)
    {
        std::shared_ptr<std::vector<glm::vec4>> input = GetInputPinArrDefaultValue<glm::vec4>(parent_node, "input");
        glm::vec4 obj = GetInputPinValue<glm::vec4>(parent_node, "object");
        input->push_back(obj);
    }
    else if (parent_node->inputs.at("input")->type == PinType::Matrix4x4)
    {
        std::shared_ptr<std::vector<glm::mat4>> input = GetInputPinArrDefaultValue<glm::mat4>(parent_node, "input");
        glm::mat4 obj = GetInputPinValue<glm::mat4>(parent_node, "object");
        input->push_back(obj);
    }
    else if (parent_node->inputs.at("input")->type == PinType::TextureObject)
    {
        std::shared_ptr<std::vector<std::shared_ptr<TextureObject>>> input = GetInputPinArrDefaultValue<std::shared_ptr<TextureObject>>(parent_node, "input");
        std::shared_ptr<TextureObject> obj = GetInputPinValue<std::shared_ptr<TextureObject>>(parent_node, "object");
        input->push_back(obj);
    }
    else if (parent_node->inputs.at("input")->type == PinType::ProgramObject)
    {
        std::shared_ptr<std::vector<std::shared_ptr<ProgramObject>>> input = GetInputPinArrDefaultValue<std::shared_ptr<ProgramObject>>(parent_node, "input");
        std::shared_ptr<ProgramObject> obj = GetInputPinValue<std::shared_ptr<ProgramObject>>(parent_node, "object");
        input->push_back(obj);
    }
    else if (parent_node->inputs.at("input")->type == PinType::VertexShaderObject)
    {
        std::shared_ptr<std::vector<std::shared_ptr<ShaderObject>>> input = GetInputPinArrDefaultValue<std::shared_ptr<ShaderObject>>(parent_node, "input");
        std::shared_ptr<ShaderObject> obj = GetInputPinValue<std::shared_ptr<ShaderObject>>(parent_node, "object");
        input->push_back(obj);
    }
    else if (parent_node->inputs.at("input")->type == PinType::FragmentShaderObject)
    {
        std::shared_ptr<std::vector<std::shared_ptr<ShaderObject>>> input = GetInputPinArrDefaultValue<std::shared_ptr<ShaderObject>>(parent_node, "input");
        std::shared_ptr<ShaderObject> obj = GetInputPinValue<std::shared_ptr<ShaderObject>>(parent_node, "object");
        input->push_back(obj);
    }
    else if (parent_node->inputs.at("input")->type == PinType::MeshObject)
    {
        std::shared_ptr<std::vector<std::shared_ptr<MeshObject>>> input = GetInputPinArrDefaultValue<std::shared_ptr<MeshObject>>(parent_node, "input");
        std::shared_ptr<MeshObject> obj = GetInputPinValue<std::shared_ptr<MeshObject>>(parent_node, "object");
        input->push_back(obj);
    }
    RunNextNodeFunc(parent_node, "next");
}

void ArrayInsertDefaultNode_Func::Delete()
{
    parent_node = nullptr;
}

void ArrayInsertDefaultNode_Func::UpdateNodeUI()
{
    if (parent_node->inputs.at("input")->type != parent_node->inputs.at("object")->type || tmp_loaded_value)
    {
        UtilsChangePinType(parent_node, PinKind::Input, "object", parent_node->inputs.at("input")->type, false);
        if (tmp_loaded_value)
        {
            UtilsChangePinType(parent_node, PinKind::Input, "object", tmp_loaded_value->type, false);
            if (tmp_loaded_value->type == PinType::String)
            {
                std::dynamic_pointer_cast<PinValue<std::string>>(parent_node->inputs.at("object"))->default_value = std::dynamic_pointer_cast<PlaceholderValue<std::string>>(tmp_loaded_value)->value;
            }
            else if (tmp_loaded_value->type == PinType::Bool)
            {
                std::dynamic_pointer_cast<PinValue<bool>>(parent_node->inputs.at("object"))->default_value = std::dynamic_pointer_cast<PlaceholderValue<bool>>(tmp_loaded_value)->value;
            }
            else if (tmp_loaded_value->type == PinType::Int)
            {
                std::dynamic_pointer_cast<PinValue<int>>(parent_node->inputs.at("object"))->default_value = std::dynamic_pointer_cast<PlaceholderValue<int>>(tmp_loaded_value)->value;
            }
            else if (tmp_loaded_value->type == PinType::Float)
            {
                std::dynamic_pointer_cast<PinValue<float>>(parent_node->inputs.at("object"))->default_value = std::dynamic_pointer_cast<PlaceholderValue<float>>(tmp_loaded_value)->value;
            }
            else if (tmp_loaded_value->type == PinType::Vector2)
            {
                std::dynamic_pointer_cast<PinValue<glm::vec2>>(parent_node->inputs.at("object"))->default_value = std::dynamic_pointer_cast<PlaceholderValue<glm::vec2>>(tmp_loaded_value)->value;
            }
            else if (tmp_loaded_value->type == PinType::Vector3)
            {
                std::dynamic_pointer_cast<PinValue<glm::vec3>>(parent_node->inputs.at("object"))->default_value = std::dynamic_pointer_cast<PlaceholderValue<glm::vec3>>(tmp_loaded_value)->value;
            }
            else if (tmp_loaded_value->type == PinType::Vector4)
            {
                std::dynamic_pointer_cast<PinValue<glm::vec4>>(parent_node->inputs.at("object"))->default_value = std::dynamic_pointer_cast<PlaceholderValue<glm::vec4>>(tmp_loaded_value)->value;
            }
            else if (tmp_loaded_value->type == PinType::Matrix4x4)
            {
                std::dynamic_pointer_cast<PinValue<glm::mat4>>(parent_node->inputs.at("object"))->default_value = std::dynamic_pointer_cast<PlaceholderValue<glm::mat4>>(tmp_loaded_value)->value;
            }
            if (tmp_loaded_value->type == parent_node->inputs.at("input")->type)
                tmp_loaded_value = nullptr;
        }
    }
}

void ArrayInsertDefaultNode_Func::SaveNodeData(rapidjson::Writer<rapidjson::StringBuffer>& writer)
{
    writer.Key("array_type");
    writer.String(PinTypeToString(parent_node->inputs.at("object")->type).c_str());

    if (parent_node->inputs.at("object")->type == PinType::String)
    {
        writer.Key("object");
        std::string obj_value = std::dynamic_pointer_cast<PinValue<std::string>>(parent_node->inputs.at("object"))->default_value;
        writer.String(obj_value.c_str());
    }
    else if (parent_node->inputs.at("object")->type == PinType::Int)
    {
        writer.Key("object");
        int obj_value = std::dynamic_pointer_cast<PinValue<int>>(parent_node->inputs.at("object"))->default_value;
        writer.Int(obj_value);
    }
    else if (parent_node->inputs.at("object")->type == PinType::Float)
    {
        writer.Key("object");
        float obj_value = std::dynamic_pointer_cast<PinValue<float>>(parent_node->inputs.at("object"))->default_value;
        writer.Double(obj_value);
    }
    else if (parent_node->inputs.at("object")->type == PinType::Bool)
    {
        writer.Key("object");
        bool obj_value = std::dynamic_pointer_cast<PinValue<bool>>(parent_node->inputs.at("object"))->default_value;
        writer.Bool(obj_value);
    }
    else if (parent_node->inputs.at("object")->type == PinType::Vector2)
    {
        writer.Key("object");
        glm::vec2 obj_value = std::dynamic_pointer_cast<PinValue<glm::vec2>>(parent_node->inputs.at("object"))->default_value;
        writer.StartArray();
        writer.Double(obj_value.x);
        writer.Double(obj_value.y);
        writer.EndArray();
    }
    else if (parent_node->inputs.at("object")->type == PinType::Vector3)
    {
        writer.Key("object");
        glm::vec3 obj_value = std::dynamic_pointer_cast<PinValue<glm::vec3>>(parent_node->inputs.at("object"))->default_value;
        writer.StartArray();
        writer.Double(obj_value.x);
        writer.Double(obj_value.y);
        writer.Double(obj_value.z);
        writer.EndArray();
    }
    else if (parent_node->inputs.at("object")->type == PinType::Vector4)
    {
        writer.Key("object");
        glm::vec4 obj_value = std::dynamic_pointer_cast<PinValue<glm::vec4>>(parent_node->inputs.at("object"))->default_value;
        writer.StartArray();
        writer.Double(obj_value.x);
        writer.Double(obj_value.y);
        writer.Double(obj_value.z);
        writer.Double(obj_value.w);
        writer.EndArray();
    }
    else if (parent_node->inputs.at("object")->type == PinType::Matrix4x4)
    {
        writer.Key("object");
        writer.StartArray();
        glm::mat4 obj_value = std::dynamic_pointer_cast<PinValue<glm::mat4>>(parent_node->inputs.at("object"))->default_value;
        const float* pSource = (const float*)glm::value_ptr(obj_value);
        for (int i = 0; i < 16; ++i)
            writer.Double(pSource[i]);
        writer.EndArray();
    }
}

void ArrayInsertDefaultNode_Func::LoadNodeData(rapidjson::Value& node_obj)
{
    if (!node_obj["array_type"].IsNull())
    {
        PinType array_type = StringToPinType(node_obj["array_type"].GetString());

        if (array_type == PinType::String)
        {
            std::string uni_value = std::string(node_obj["object"].GetString());
            tmp_loaded_value = std::make_shared<PlaceholderValue<std::string>>("tmp", array_type, uni_value);
        }
        else if (array_type == PinType::Bool)
        {
            bool uni_value = node_obj["object"].GetBool();
            tmp_loaded_value = std::make_shared<PlaceholderValue<bool>>("tmp", array_type, uni_value);
        }
        else if (array_type == PinType::Int)
        {
            int uni_value = node_obj["object"].GetInt();
            tmp_loaded_value = std::make_shared<PlaceholderValue<int>>("tmp", array_type, uni_value);
        }
        else if (array_type == PinType::Float)
        {
            float uni_value = node_obj["object"].GetFloat();
            tmp_loaded_value = std::make_shared<PlaceholderValue<float>>("tmp", array_type, uni_value);
        }
        if (array_type == PinType::Vector2)
        {
            glm::vec2 uni_value;
            uni_value.x = node_obj["object"].GetArray()[0].GetFloat();
            uni_value.y = node_obj["object"].GetArray()[1].GetFloat();
            tmp_loaded_value = std::make_shared<PlaceholderValue<glm::vec2>>("tmp", array_type, uni_value);
        }
        else if (array_type == PinType::Vector3)
        {
            glm::vec3 uni_value;
            uni_value.x = node_obj["object"].GetArray()[0].GetFloat();
            uni_value.y = node_obj["object"].GetArray()[1].GetFloat();
            uni_value.z = node_obj["object"].GetArray()[2].GetFloat();
            tmp_loaded_value = std::make_shared<PlaceholderValue<glm::vec3>>("tmp", array_type, uni_value);
        }
        else if (array_type == PinType::Vector4)
        {
            glm::vec4 uni_value;
            uni_value.x = node_obj["object"].GetArray()[0].GetFloat();
            uni_value.y = node_obj["object"].GetArray()[1].GetFloat();
            uni_value.z = node_obj["object"].GetArray()[2].GetFloat();
            uni_value.w = node_obj["object"].GetArray()[3].GetFloat();
            tmp_loaded_value = std::make_shared<PlaceholderValue<glm::vec4>>("tmp", array_type, uni_value);
        }
        else if (array_type == PinType::Matrix4x4)
        {
            glm::mat4 uni_value;
            float* pSource = (float*)glm::value_ptr(uni_value);
            for (int i = 0; i < 16; ++i)
            {
                pSource[i] = node_obj["object"].GetArray()[i].GetFloat();
            }
            tmp_loaded_value = std::make_shared<PlaceholderValue<glm::mat4>>("tmp", array_type, uni_value);
        }
    }
}

std::string arrayInsertDefaultNodeName = "Array - Insert Default Object";
std::shared_ptr<Node> ArrayInsertDefaultNode(std::vector<std::shared_ptr<Node>>& s_Nodes)
{
    s_Nodes.emplace_back(new Node(GetNextId(), arrayInsertDefaultNodeName.c_str()));
    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<BasePin>>("enter", new BasePin("enter", 0, GetNextId(), "Enter", PinType::Flow)));
    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<PinArrValue<std::string>>>("input", new PinArrValue<std::string>("input", 1, GetNextId(), "Array", PinType::String, std::make_shared<std::vector<std::string>>())));
    s_Nodes.back()->inputs.at("input")->isGeneralArray = true;
    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<PinValue<std::string>>>("object", new PinValue<std::string>("object", 2, GetNextId(), "Object", PinType::String, "")));

    s_Nodes.back()->outputs.insert(std::pair<std::string, std::shared_ptr<BasePin>>("next", new BasePin("next", 0, GetNextId(), "Next", PinType::Flow)));

    s_Nodes.back()->node_funcs = std::make_shared<ArrayInsertDefaultNode_Func>();
    std::dynamic_pointer_cast<ArrayInsertDefaultNode_Func>(s_Nodes.back()->node_funcs)->parent_node = s_Nodes.back();

    s_Nodes.back()->node_funcs->Initialize();

    BuildNode(s_Nodes.back());

    return s_Nodes.back();
}





void ArrayClearValuesNode_Func::Run(std::string called_pin)
{
    if (parent_node->inputs.at("input")->type == PinType::String)
    {
        std::shared_ptr<std::vector<std::string>> input = GetInputPinArrValue<std::string>(parent_node, "input");
        input->clear();
    }
    else if (parent_node->inputs.at("input")->type == PinType::Bool)
    {
        std::shared_ptr<std::vector<bool>> input = GetInputPinArrValue<bool>(parent_node, "input");
        input->clear();
    }
    else if (parent_node->inputs.at("input")->type == PinType::Float)
    {
        std::shared_ptr<std::vector<float>> input = GetInputPinArrValue<float>(parent_node, "input");
        input->clear();
    }
    else if (parent_node->inputs.at("input")->type == PinType::Int)
    {
        std::shared_ptr<std::vector<int>> input = GetInputPinArrValue<int>(parent_node, "input");
        input->clear();
    }
    else if (parent_node->inputs.at("input")->type == PinType::Vector2)
    {
        std::shared_ptr<std::vector<glm::vec2>> input = GetInputPinArrValue<glm::vec2>(parent_node, "input");
        input->clear();
    }
    else if (parent_node->inputs.at("input")->type == PinType::Vector3)
    {
        std::shared_ptr<std::vector<glm::vec3>> input = GetInputPinArrValue<glm::vec3>(parent_node, "input");
        input->clear();
    }
    else if (parent_node->inputs.at("input")->type == PinType::Vector4)
    {
        std::shared_ptr<std::vector<glm::vec4>> input = GetInputPinArrValue<glm::vec4>(parent_node, "input");
        input->clear();
    }
    else if (parent_node->inputs.at("input")->type == PinType::Matrix4x4)
    {
        std::shared_ptr<std::vector<glm::mat4>> input = GetInputPinArrValue<glm::mat4>(parent_node, "input");
        input->clear();
    }
    else if (parent_node->inputs.at("input")->type == PinType::TextureObject)
    {
        std::shared_ptr<std::vector<std::shared_ptr<TextureObject>>> input = GetInputPinArrValue<std::shared_ptr<TextureObject>>(parent_node, "input");
        input->clear();
    }
    else if (parent_node->inputs.at("input")->type == PinType::ProgramObject)
    {
        std::shared_ptr<std::vector<std::shared_ptr<ProgramObject>>> input = GetInputPinArrValue<std::shared_ptr<ProgramObject>>(parent_node, "input");
        input->clear();
    }
    else if (parent_node->inputs.at("input")->type == PinType::VertexShaderObject)
    {
        std::shared_ptr<std::vector<std::shared_ptr<ShaderObject>>> input = GetInputPinArrValue<std::shared_ptr<ShaderObject>>(parent_node, "input");
        input->clear();
    }
    else if (parent_node->inputs.at("input")->type == PinType::FragmentShaderObject)
    {
        std::shared_ptr<std::vector<std::shared_ptr<ShaderObject>>> input = GetInputPinArrValue<std::shared_ptr<ShaderObject>>(parent_node, "input");
        input->clear();
    }
    else if (parent_node->inputs.at("input")->type == PinType::MeshObject)
    {
        std::shared_ptr<std::vector<std::shared_ptr<MeshObject>>> input = GetInputPinArrValue<std::shared_ptr<MeshObject>>(parent_node, "input");
        input->clear();
    }
    RunNextNodeFunc(parent_node, "next");
}

void ArrayClearValuesNode_Func::Delete()
{
    parent_node = nullptr;
}

std::string arrayClearValuesNodeName = "Array - Clear Values";
std::shared_ptr<Node> ArrayClearValuesNode(std::vector<std::shared_ptr<Node>>& s_Nodes)
{
    s_Nodes.emplace_back(new Node(GetNextId(), arrayClearValuesNodeName.c_str()));
    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<BasePin>>("enter", new BasePin("enter", 0, GetNextId(), "Enter", PinType::Flow)));
    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<PinArrValue<std::string>>>("input", new PinArrValue<std::string>("input", 1, GetNextId(), "Array", PinType::String, std::make_shared<std::vector<std::string>>())));
    s_Nodes.back()->inputs.at("input")->isGeneralArray = true;

    s_Nodes.back()->outputs.insert(std::pair<std::string, std::shared_ptr<BasePin>>("next", new BasePin("next", 0, GetNextId(), "Next", PinType::Flow)));

    s_Nodes.back()->node_funcs = std::make_shared<ArrayClearValuesNode_Func>();
    std::dynamic_pointer_cast<ArrayClearValuesNode_Func>(s_Nodes.back()->node_funcs)->parent_node = s_Nodes.back();

    s_Nodes.back()->node_funcs->Initialize();

    BuildNode(s_Nodes.back());

    return s_Nodes.back();
}





void ArrayClearDefaultValuesNode_Func::Run(std::string called_pin)
{
    if (parent_node->inputs.at("input")->type == PinType::String)
    {
        std::shared_ptr<std::vector<std::string>> input = GetInputPinArrDefaultValue<std::string>(parent_node, "input");
        input->clear();
    }
    else if (parent_node->inputs.at("input")->type == PinType::Bool)
    {
        std::shared_ptr<std::vector<bool>> input = GetInputPinArrDefaultValue<bool>(parent_node, "input");
        input->clear();
    }
    else if (parent_node->inputs.at("input")->type == PinType::Float)
    {
        std::shared_ptr<std::vector<float>> input = GetInputPinArrDefaultValue<float>(parent_node, "input");
        input->clear();
    }
    else if (parent_node->inputs.at("input")->type == PinType::Int)
    {
        std::shared_ptr<std::vector<int>> input = GetInputPinArrDefaultValue<int>(parent_node, "input");
        input->clear();
    }
    else if (parent_node->inputs.at("input")->type == PinType::Vector2)
    {
        std::shared_ptr<std::vector<glm::vec2>> input = GetInputPinArrDefaultValue<glm::vec2>(parent_node, "input");
        input->clear();
    }
    else if (parent_node->inputs.at("input")->type == PinType::Vector3)
    {
        std::shared_ptr<std::vector<glm::vec3>> input = GetInputPinArrDefaultValue<glm::vec3>(parent_node, "input");
        input->clear();
    }
    else if (parent_node->inputs.at("input")->type == PinType::Vector4)
    {
        std::shared_ptr<std::vector<glm::vec4>> input = GetInputPinArrDefaultValue<glm::vec4>(parent_node, "input");
        input->clear();
    }
    else if (parent_node->inputs.at("input")->type == PinType::Matrix4x4)
    {
        std::shared_ptr<std::vector<glm::mat4>> input = GetInputPinArrDefaultValue<glm::mat4>(parent_node, "input");
        input->clear();
    }
    else if (parent_node->inputs.at("input")->type == PinType::TextureObject)
    {
        std::shared_ptr<std::vector<std::shared_ptr<TextureObject>>> input = GetInputPinArrDefaultValue<std::shared_ptr<TextureObject>>(parent_node, "input");
        input->clear();
    }
    else if (parent_node->inputs.at("input")->type == PinType::ProgramObject)
    {
        std::shared_ptr<std::vector<std::shared_ptr<ProgramObject>>> input = GetInputPinArrDefaultValue<std::shared_ptr<ProgramObject>>(parent_node, "input");
        input->clear();
    }
    else if (parent_node->inputs.at("input")->type == PinType::VertexShaderObject)
    {
        std::shared_ptr<std::vector<std::shared_ptr<ShaderObject>>> input = GetInputPinArrDefaultValue<std::shared_ptr<ShaderObject>>(parent_node, "input");
        input->clear();
    }
    else if (parent_node->inputs.at("input")->type == PinType::FragmentShaderObject)
    {
        std::shared_ptr<std::vector<std::shared_ptr<ShaderObject>>> input = GetInputPinArrDefaultValue<std::shared_ptr<ShaderObject>>(parent_node, "input");
        input->clear();
    }
    else if (parent_node->inputs.at("input")->type == PinType::MeshObject)
    {
        std::shared_ptr<std::vector<std::shared_ptr<MeshObject>>> input = GetInputPinArrDefaultValue<std::shared_ptr<MeshObject>>(parent_node, "input");
        input->clear();
    }
    RunNextNodeFunc(parent_node, "next");
}

void ArrayClearDefaultValuesNode_Func::Delete()
{
    parent_node = nullptr;
}

std::string arrayClearDefaultValuesNodeName = "Array - Clear Default Values";
std::shared_ptr<Node> ArrayClearDefaultValuesNode(std::vector<std::shared_ptr<Node>>& s_Nodes)
{
    s_Nodes.emplace_back(new Node(GetNextId(), arrayClearDefaultValuesNodeName.c_str()));
    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<BasePin>>("enter", new BasePin("enter", 0, GetNextId(), "Enter", PinType::Flow)));
    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<PinArrValue<std::string>>>("input", new PinArrValue<std::string>("input", 1, GetNextId(), "Array", PinType::String, std::make_shared<std::vector<std::string>>())));
    s_Nodes.back()->inputs.at("input")->isGeneralArray = true;

    s_Nodes.back()->outputs.insert(std::pair<std::string, std::shared_ptr<BasePin>>("next", new BasePin("next", 0, GetNextId(), "Next", PinType::Flow)));

    s_Nodes.back()->node_funcs = std::make_shared<ArrayClearDefaultValuesNode_Func>();
    std::dynamic_pointer_cast<ArrayClearDefaultValuesNode_Func>(s_Nodes.back()->node_funcs)->parent_node = s_Nodes.back();

    s_Nodes.back()->node_funcs->Initialize();

    BuildNode(s_Nodes.back());

    return s_Nodes.back();
}





void ArrayClearToDefaultValuesNode_Func::Run(std::string called_pin)
{
    if (parent_node->inputs.at("input")->type == PinType::String)
    {
        std::shared_ptr<std::vector<std::string>> input = GetInputPinArrValue<std::string>(parent_node, "input");
        input->clear();
        std::shared_ptr<std::vector<std::string>> default_input = GetInputPinArrDefaultValue<std::string>(parent_node, "input");
        for (int i = 0; i < default_input->size(); i++)
        {
            input->push_back(default_input->at(i));
        }
    }
    else if (parent_node->inputs.at("input")->type == PinType::Bool)
    {
        std::shared_ptr<std::vector<bool>> input = GetInputPinArrValue<bool>(parent_node, "input");
        input->clear();
        std::shared_ptr<std::vector<bool>> default_input = GetInputPinArrDefaultValue<bool>(parent_node, "input");
        for (int i = 0; i < default_input->size(); i++)
        {
            input->push_back(default_input->at(i));
        }
    }
    else if (parent_node->inputs.at("input")->type == PinType::Float)
    {
        std::shared_ptr<std::vector<float>> input = GetInputPinArrValue<float>(parent_node, "input");
        input->clear();
        std::shared_ptr<std::vector<float>> default_input = GetInputPinArrDefaultValue<float>(parent_node, "input");
        for (int i = 0; i < default_input->size(); i++)
        {
            input->push_back(default_input->at(i));
        }
    }
    else if (parent_node->inputs.at("input")->type == PinType::Int)
    {
        std::shared_ptr<std::vector<int>> input = GetInputPinArrValue<int>(parent_node, "input");
        input->clear();
        std::shared_ptr<std::vector<int>> default_input = GetInputPinArrDefaultValue<int>(parent_node, "input");
        for (int i = 0; i < default_input->size(); i++)
        {
            input->push_back(default_input->at(i));
        }
    }
    else if (parent_node->inputs.at("input")->type == PinType::Vector2)
    {
        std::shared_ptr<std::vector<glm::vec2>> input = GetInputPinArrValue<glm::vec2>(parent_node, "input");
        input->clear();
        std::shared_ptr<std::vector<glm::vec2>> default_input = GetInputPinArrDefaultValue<glm::vec2>(parent_node, "input");
        for (int i = 0; i < default_input->size(); i++)
        {
            input->push_back(default_input->at(i));
        }
    }
    else if (parent_node->inputs.at("input")->type == PinType::Vector3)
    {
        std::shared_ptr<std::vector<glm::vec3>> input = GetInputPinArrValue<glm::vec3>(parent_node, "input");
        input->clear();
        std::shared_ptr<std::vector<glm::vec3>> default_input = GetInputPinArrDefaultValue<glm::vec3>(parent_node, "input");
        for (int i = 0; i < default_input->size(); i++)
        {
            input->push_back(default_input->at(i));
        }
    }
    else if (parent_node->inputs.at("input")->type == PinType::Vector4)
    {
        std::shared_ptr<std::vector<glm::vec4>> input = GetInputPinArrValue<glm::vec4>(parent_node, "input");
        input->clear();
        std::shared_ptr<std::vector<glm::vec4>> default_input = GetInputPinArrDefaultValue<glm::vec4>(parent_node, "input");
        for (int i = 0; i < default_input->size(); i++)
        {
            input->push_back(default_input->at(i));
        }
    }
    else if (parent_node->inputs.at("input")->type == PinType::Matrix4x4)
    {
        std::shared_ptr<std::vector<glm::mat4>> input = GetInputPinArrValue<glm::mat4>(parent_node, "input");
        input->clear();
        std::shared_ptr<std::vector<glm::mat4>> default_input = GetInputPinArrDefaultValue<glm::mat4>(parent_node, "input");
        for (int i = 0; i < default_input->size(); i++)
        {
            input->push_back(default_input->at(i));
        }
    }
    else if (parent_node->inputs.at("input")->type == PinType::TextureObject)
    {
        std::shared_ptr<std::vector<std::shared_ptr<TextureObject>>> input = GetInputPinArrValue<std::shared_ptr<TextureObject>>(parent_node, "input");
        input->clear();
        std::shared_ptr<std::vector<std::shared_ptr<TextureObject>>> default_input = GetInputPinArrDefaultValue<std::shared_ptr<TextureObject>>(parent_node, "input");
        for (int i = 0; i < default_input->size(); i++)
        {
            input->push_back(default_input->at(i));
        }
    }
    else if (parent_node->inputs.at("input")->type == PinType::ProgramObject)
    {
        std::shared_ptr<std::vector<std::shared_ptr<ProgramObject>>> input = GetInputPinArrValue<std::shared_ptr<ProgramObject>>(parent_node, "input");
        input->clear();
        std::shared_ptr<std::vector<std::shared_ptr<ProgramObject>>> default_input = GetInputPinArrDefaultValue<std::shared_ptr<ProgramObject>>(parent_node, "input");
        for (int i = 0; i < default_input->size(); i++)
        {
            input->push_back(default_input->at(i));
        }
    }
    else if (parent_node->inputs.at("input")->type == PinType::VertexShaderObject)
    {
        std::shared_ptr<std::vector<std::shared_ptr<ShaderObject>>> input = GetInputPinArrValue<std::shared_ptr<ShaderObject>>(parent_node, "input");
        input->clear();
        std::shared_ptr<std::vector<std::shared_ptr<ShaderObject>>> default_input = GetInputPinArrDefaultValue<std::shared_ptr<ShaderObject>>(parent_node, "input");
        for (int i = 0; i < default_input->size(); i++)
        {
            input->push_back(default_input->at(i));
        }
    }
    else if (parent_node->inputs.at("input")->type == PinType::FragmentShaderObject)
    {
        std::shared_ptr<std::vector<std::shared_ptr<ShaderObject>>> input = GetInputPinArrValue<std::shared_ptr<ShaderObject>>(parent_node, "input");
        input->clear();
        std::shared_ptr<std::vector<std::shared_ptr<ShaderObject>>> default_input = GetInputPinArrDefaultValue<std::shared_ptr<ShaderObject>>(parent_node, "input");
        for (int i = 0; i < default_input->size(); i++)
        {
            input->push_back(default_input->at(i));
        }
    }
    else if (parent_node->inputs.at("input")->type == PinType::MeshObject)
    {
        std::shared_ptr<std::vector<std::shared_ptr<MeshObject>>> input = GetInputPinArrValue<std::shared_ptr<MeshObject>>(parent_node, "input");
        input->clear();
        std::shared_ptr<std::vector<std::shared_ptr<MeshObject>>> default_input = GetInputPinArrDefaultValue<std::shared_ptr<MeshObject>>(parent_node, "input");
        for (int i = 0; i < default_input->size(); i++)
        {
            input->push_back(default_input->at(i));
        }
    }
    RunNextNodeFunc(parent_node, "next");
}

void ArrayClearToDefaultValuesNode_Func::Delete()
{
    parent_node = nullptr;
}

std::string arrayClearToDefaultValuesNodeName = "Array - Clear To Default Values";
std::shared_ptr<Node> ArrayClearToDefaultValuesNode(std::vector<std::shared_ptr<Node>>& s_Nodes)
{
    s_Nodes.emplace_back(new Node(GetNextId(), arrayClearToDefaultValuesNodeName.c_str()));
    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<BasePin>>("enter", new BasePin("enter", 0, GetNextId(), "Enter", PinType::Flow)));
    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<PinArrValue<std::string>>>("input", new PinArrValue<std::string>("input", 1, GetNextId(), "Array", PinType::String, std::make_shared<std::vector<std::string>>())));
    s_Nodes.back()->inputs.at("input")->isGeneralArray = true;

    s_Nodes.back()->outputs.insert(std::pair<std::string, std::shared_ptr<BasePin>>("next", new BasePin("next", 0, GetNextId(), "Next", PinType::Flow)));

    s_Nodes.back()->node_funcs = std::make_shared<ArrayClearToDefaultValuesNode_Func>();
    std::dynamic_pointer_cast<ArrayClearToDefaultValuesNode_Func>(s_Nodes.back()->node_funcs)->parent_node = s_Nodes.back();

    s_Nodes.back()->node_funcs->Initialize();

    BuildNode(s_Nodes.back());

    return s_Nodes.back();
}





void ArraySetValueNode_Func::Run(std::string called_pin)
{
    UpdateNodeUI();
    if (parent_node->inputs.at("input")->type == PinType::String)
    {
        std::shared_ptr<std::vector<std::string>> input = GetInputPinArrValue<std::string>(parent_node, "input");
        std::string obj = GetInputPinValue<std::string>(parent_node, "object");
        int inx = GetInputPinValue<int>(parent_node, "index");
        if (input)
        {
            if (inx < input->size() && inx >= 0)
            {
                input->at(inx) = obj;
            }
        }
    }
    else if (parent_node->inputs.at("input")->type == PinType::Bool)
    {
        std::shared_ptr<std::vector<bool>> input = GetInputPinArrValue<bool>(parent_node, "input");
        bool obj = GetInputPinValue<bool>(parent_node, "object");
        int inx = GetInputPinValue<int>(parent_node, "index");
        if (input)
        {
            if (inx < input->size() && inx >= 0)
            {
                input->at(inx) = obj;
            }
        }
    }
    else if (parent_node->inputs.at("input")->type == PinType::Float)
    {
        std::shared_ptr<std::vector<float>> input = GetInputPinArrValue<float>(parent_node, "input");
        float obj = GetInputPinValue<float>(parent_node, "object");
        int inx = GetInputPinValue<int>(parent_node, "index");
        if (input)
        {
            if (inx < input->size() && inx >= 0)
            {
                input->at(inx) = obj;
            }
        }
    }
    else if (parent_node->inputs.at("input")->type == PinType::Int)
    {
        std::shared_ptr<std::vector<int>> input = GetInputPinArrValue<int>(parent_node, "input");
        int obj = GetInputPinValue<int>(parent_node, "object");
        int inx = GetInputPinValue<int>(parent_node, "index");
        if (input)
        {
            if (inx < input->size() && inx >= 0)
            {
                input->at(inx) = obj;
            }
        }
    }
    else if (parent_node->inputs.at("input")->type == PinType::Vector2)
    {
        std::shared_ptr<std::vector<glm::vec2>> input = GetInputPinArrValue<glm::vec2>(parent_node, "input");
        glm::vec2 obj = GetInputPinValue<glm::vec2>(parent_node, "object");
        int inx = GetInputPinValue<int>(parent_node, "index");
        if (input)
        {
            if (inx < input->size() && inx >= 0)
            {
                input->at(inx) = obj;
            }
        }
    }
    else if (parent_node->inputs.at("input")->type == PinType::Vector3)
    {
        std::shared_ptr<std::vector<glm::vec3>> input = GetInputPinArrValue<glm::vec3>(parent_node, "input");
        glm::vec3 obj = GetInputPinValue<glm::vec3>(parent_node, "object");
        int inx = GetInputPinValue<int>(parent_node, "index");
        if (input)
        {
            if (inx < input->size() && inx >= 0)
            {
                input->at(inx) = obj;
            }
        }
    }
    else if (parent_node->inputs.at("input")->type == PinType::Vector4)
    {
        std::shared_ptr<std::vector<glm::vec4>> input = GetInputPinArrValue<glm::vec4>(parent_node, "input");
        glm::vec4 obj = GetInputPinValue<glm::vec4>(parent_node, "object");
        int inx = GetInputPinValue<int>(parent_node, "index");
        if (input)
        {
            if (inx < input->size() && inx >= 0)
            {
                input->at(inx) = obj;
            }
        }
    }
    else if (parent_node->inputs.at("input")->type == PinType::Matrix4x4)
    {
        std::shared_ptr<std::vector<glm::mat4>> input = GetInputPinArrValue<glm::mat4>(parent_node, "input");
        glm::mat4 obj = GetInputPinValue<glm::mat4>(parent_node, "object");
        int inx = GetInputPinValue<int>(parent_node, "index");
        if (input)
        {
            if (inx < input->size() && inx >= 0)
            {
                input->at(inx) = obj;
            }
        }
    }
    else if (parent_node->inputs.at("input")->type == PinType::TextureObject)
    {
        std::shared_ptr<std::vector<std::shared_ptr<TextureObject>>> input = GetInputPinArrValue<std::shared_ptr<TextureObject>>(parent_node, "input");
        std::shared_ptr<TextureObject> obj = GetInputPinValue<std::shared_ptr<TextureObject>>(parent_node, "object");
        int inx = GetInputPinValue<int>(parent_node, "index");
        if (input)
        {
            if (inx < input->size() && inx >= 0)
            {
                input->at(inx) = obj;
            }
        }
    }
    else if (parent_node->inputs.at("input")->type == PinType::ProgramObject)
    {
        std::shared_ptr<std::vector<std::shared_ptr<ProgramObject>>> input = GetInputPinArrValue<std::shared_ptr<ProgramObject>>(parent_node, "input");
        std::shared_ptr<ProgramObject> obj = GetInputPinValue<std::shared_ptr<ProgramObject>>(parent_node, "object");
        int inx = GetInputPinValue<int>(parent_node, "index");
        if (input)
        {
            if (inx < input->size() && inx >= 0)
            {
                input->at(inx) = obj;
            }
        }
    }
    else if (parent_node->inputs.at("input")->type == PinType::VertexShaderObject)
    {
        std::shared_ptr<std::vector<std::shared_ptr<ShaderObject>>> input = GetInputPinArrValue<std::shared_ptr<ShaderObject>>(parent_node, "input");
        std::shared_ptr<ShaderObject> obj = GetInputPinValue<std::shared_ptr<ShaderObject>>(parent_node, "object");
        int inx = GetInputPinValue<int>(parent_node, "index");
        if (input)
        {
            if (inx < input->size() && inx >= 0)
            {
                input->at(inx) = obj;
            }
        }
    }
    else if (parent_node->inputs.at("input")->type == PinType::FragmentShaderObject)
    {
        std::shared_ptr<std::vector<std::shared_ptr<ShaderObject>>> input = GetInputPinArrValue<std::shared_ptr<ShaderObject>>(parent_node, "input");
        std::shared_ptr<ShaderObject> obj = GetInputPinValue<std::shared_ptr<ShaderObject>>(parent_node, "object");
        int inx = GetInputPinValue<int>(parent_node, "index");
        if (input)
        {
            if (inx < input->size() && inx >= 0)
            {
                input->at(inx) = obj;
            }
        }
    }
    else if (parent_node->inputs.at("input")->type == PinType::MeshObject)
    {
        std::shared_ptr<std::vector<std::shared_ptr<MeshObject>>> input = GetInputPinArrValue<std::shared_ptr<MeshObject>>(parent_node, "input");
        std::shared_ptr<MeshObject> obj = GetInputPinValue<std::shared_ptr<MeshObject>>(parent_node, "object");
        int inx = GetInputPinValue<int>(parent_node, "index");
        if (input)
        {
            if (inx < input->size() && inx >= 0)
            {
                input->at(inx) = obj;
            }
        }
    }
    RunNextNodeFunc(parent_node, "next");
}

void ArraySetValueNode_Func::Delete()
{
    parent_node = nullptr;
}

void ArraySetValueNode_Func::UpdateNodeUI()
{
    if (parent_node->inputs.at("input")->type != parent_node->inputs.at("object")->type || tmp_loaded_value)
    {
        UtilsChangePinType(parent_node, PinKind::Input, "object", parent_node->inputs.at("input")->type, false);
        if (tmp_loaded_value)
        {
            UtilsChangePinType(parent_node, PinKind::Input, "object", tmp_loaded_value->type, false);
            if (tmp_loaded_value->type == PinType::String)
            {
                std::dynamic_pointer_cast<PinValue<std::string>>(parent_node->inputs.at("object"))->default_value = std::dynamic_pointer_cast<PlaceholderValue<std::string>>(tmp_loaded_value)->value;
            }
            else if (tmp_loaded_value->type == PinType::Bool)
            {
                std::dynamic_pointer_cast<PinValue<bool>>(parent_node->inputs.at("object"))->default_value = std::dynamic_pointer_cast<PlaceholderValue<bool>>(tmp_loaded_value)->value;
            }
            else if (tmp_loaded_value->type == PinType::Int)
            {
                std::dynamic_pointer_cast<PinValue<int>>(parent_node->inputs.at("object"))->default_value = std::dynamic_pointer_cast<PlaceholderValue<int>>(tmp_loaded_value)->value;
            }
            else if (tmp_loaded_value->type == PinType::Float)
            {
                std::dynamic_pointer_cast<PinValue<float>>(parent_node->inputs.at("object"))->default_value = std::dynamic_pointer_cast<PlaceholderValue<float>>(tmp_loaded_value)->value;
            }
            else if (tmp_loaded_value->type == PinType::Vector2)
            {
                std::dynamic_pointer_cast<PinValue<glm::vec2>>(parent_node->inputs.at("object"))->default_value = std::dynamic_pointer_cast<PlaceholderValue<glm::vec2>>(tmp_loaded_value)->value;
            }
            else if (tmp_loaded_value->type == PinType::Vector3)
            {
                std::dynamic_pointer_cast<PinValue<glm::vec3>>(parent_node->inputs.at("object"))->default_value = std::dynamic_pointer_cast<PlaceholderValue<glm::vec3>>(tmp_loaded_value)->value;
            }
            else if (tmp_loaded_value->type == PinType::Vector4)
            {
                std::dynamic_pointer_cast<PinValue<glm::vec4>>(parent_node->inputs.at("object"))->default_value = std::dynamic_pointer_cast<PlaceholderValue<glm::vec4>>(tmp_loaded_value)->value;
            }
            else if (tmp_loaded_value->type == PinType::Matrix4x4)
            {
                std::dynamic_pointer_cast<PinValue<glm::mat4>>(parent_node->inputs.at("object"))->default_value = std::dynamic_pointer_cast<PlaceholderValue<glm::mat4>>(tmp_loaded_value)->value;
            }
            if (tmp_loaded_value->type == parent_node->inputs.at("input")->type)
                tmp_loaded_value = nullptr;
        }
    }
}

void ArraySetValueNode_Func::SaveNodeData(rapidjson::Writer<rapidjson::StringBuffer>& writer)
{
    writer.Key("index");
    writer.Int(std::dynamic_pointer_cast<PinValue<int>>(parent_node->inputs.at("index"))->default_value);

    writer.Key("array_type");
    writer.String(PinTypeToString(parent_node->inputs.at("object")->type).c_str());

    if (parent_node->inputs.at("object")->type == PinType::String)
    {
        writer.Key("object");
        std::string obj_value = std::dynamic_pointer_cast<PinValue<std::string>>(parent_node->inputs.at("object"))->default_value;
        writer.String(obj_value.c_str());
    }
    else if (parent_node->inputs.at("object")->type == PinType::Int)
    {
        writer.Key("object");
        int obj_value = std::dynamic_pointer_cast<PinValue<int>>(parent_node->inputs.at("object"))->default_value;
        writer.Int(obj_value);
    }
    else if (parent_node->inputs.at("object")->type == PinType::Float)
    {
        writer.Key("object");
        float obj_value = std::dynamic_pointer_cast<PinValue<float>>(parent_node->inputs.at("object"))->default_value;
        writer.Double(obj_value);
    }
    else if (parent_node->inputs.at("object")->type == PinType::Bool)
    {
        writer.Key("object");
        bool obj_value = std::dynamic_pointer_cast<PinValue<bool>>(parent_node->inputs.at("object"))->default_value;
        writer.Bool(obj_value);
    }
    else if (parent_node->inputs.at("object")->type == PinType::Vector2)
    {
        writer.Key("object");
        glm::vec2 obj_value = std::dynamic_pointer_cast<PinValue<glm::vec2>>(parent_node->inputs.at("object"))->default_value;
        writer.StartArray();
        writer.Double(obj_value.x);
        writer.Double(obj_value.y);
        writer.EndArray();
    }
    else if (parent_node->inputs.at("object")->type == PinType::Vector3)
    {
        writer.Key("object");
        glm::vec3 obj_value = std::dynamic_pointer_cast<PinValue<glm::vec3>>(parent_node->inputs.at("object"))->default_value;
        writer.StartArray();
        writer.Double(obj_value.x);
        writer.Double(obj_value.y);
        writer.Double(obj_value.z);
        writer.EndArray();
    }
    else if (parent_node->inputs.at("object")->type == PinType::Vector4)
    {
        writer.Key("object");
        glm::vec4 obj_value = std::dynamic_pointer_cast<PinValue<glm::vec4>>(parent_node->inputs.at("object"))->default_value;
        writer.StartArray();
        writer.Double(obj_value.x);
        writer.Double(obj_value.y);
        writer.Double(obj_value.z);
        writer.Double(obj_value.w);
        writer.EndArray();
    }
    else if (parent_node->inputs.at("object")->type == PinType::Matrix4x4)
    {
        writer.Key("object");
        writer.StartArray();
        glm::mat4 obj_value = std::dynamic_pointer_cast<PinValue<glm::mat4>>(parent_node->inputs.at("object"))->default_value;
        const float* pSource = (const float*)glm::value_ptr(obj_value);
        for (int i = 0; i < 16; ++i)
            writer.Double(pSource[i]);
        writer.EndArray();
    }
}

void ArraySetValueNode_Func::LoadNodeData(rapidjson::Value& node_obj)
{
    if (!node_obj["index"].IsNull())
        std::dynamic_pointer_cast<PinValue<int>>(parent_node->inputs.at("index"))->default_value = node_obj["index"].GetInt();

    if (!node_obj["array_type"].IsNull())
    {
        PinType array_type = StringToPinType(node_obj["array_type"].GetString());

        if (array_type == PinType::String)
        {
            std::string uni_value = std::string(node_obj["object"].GetString());
            tmp_loaded_value = std::make_shared<PlaceholderValue<std::string>>("tmp", array_type, uni_value);
        }
        else if (array_type == PinType::Bool)
        {
            bool uni_value = node_obj["object"].GetBool();
            tmp_loaded_value = std::make_shared<PlaceholderValue<bool>>("tmp", array_type, uni_value);
        }
        else if (array_type == PinType::Int)
        {
            int uni_value = node_obj["object"].GetInt();
            tmp_loaded_value = std::make_shared<PlaceholderValue<int>>("tmp", array_type, uni_value);
        }
        else if (array_type == PinType::Float)
        {
            float uni_value = node_obj["object"].GetFloat();
            tmp_loaded_value = std::make_shared<PlaceholderValue<float>>("tmp", array_type, uni_value);
        }
        if (array_type == PinType::Vector2)
        {
            glm::vec2 uni_value;
            uni_value.x = node_obj["object"].GetArray()[0].GetFloat();
            uni_value.y = node_obj["object"].GetArray()[1].GetFloat();
            tmp_loaded_value = std::make_shared<PlaceholderValue<glm::vec2>>("tmp", array_type, uni_value);
        }
        else if (array_type == PinType::Vector3)
        {
            glm::vec3 uni_value;
            uni_value.x = node_obj["object"].GetArray()[0].GetFloat();
            uni_value.y = node_obj["object"].GetArray()[1].GetFloat();
            uni_value.z = node_obj["object"].GetArray()[2].GetFloat();
            tmp_loaded_value = std::make_shared<PlaceholderValue<glm::vec3>>("tmp", array_type, uni_value);
        }
        else if (array_type == PinType::Vector4)
        {
            glm::vec4 uni_value;
            uni_value.x = node_obj["object"].GetArray()[0].GetFloat();
            uni_value.y = node_obj["object"].GetArray()[1].GetFloat();
            uni_value.z = node_obj["object"].GetArray()[2].GetFloat();
            uni_value.w = node_obj["object"].GetArray()[3].GetFloat();
            tmp_loaded_value = std::make_shared<PlaceholderValue<glm::vec4>>("tmp", array_type, uni_value);
        }
        else if (array_type == PinType::Matrix4x4)
        {
            glm::mat4 uni_value;
            float* pSource = (float*)glm::value_ptr(uni_value);
            for (int i = 0; i < 16; ++i)
            {
                pSource[i] = node_obj["object"].GetArray()[i].GetFloat();
            }
            tmp_loaded_value = std::make_shared<PlaceholderValue<glm::mat4>>("tmp", array_type, uni_value);
        }
    }
}

std::string arraySetValueNodeName = "Array - Set Value";
std::shared_ptr<Node> ArraySetValueNode(std::vector<std::shared_ptr<Node>>& s_Nodes)
{
    s_Nodes.emplace_back(new Node(GetNextId(), arraySetValueNodeName.c_str()));
    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<BasePin>>("enter", new BasePin("enter", 0, GetNextId(), "Enter", PinType::Flow)));
    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<PinArrValue<std::string>>>("input", new PinArrValue<std::string>("input", 1, GetNextId(), "Array", PinType::String, std::make_shared<std::vector<std::string>>())));
    s_Nodes.back()->inputs.at("input")->isGeneralArray = true;
    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<PinValue<std::string>>>("object", new PinValue<std::string>("object", 2, GetNextId(), "Object", PinType::String, "")));
    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<PinValue<int>>>("index", new PinValue<int>("index", 3, GetNextId(), "Index", PinType::Int, 0)));

    s_Nodes.back()->outputs.insert(std::pair<std::string, std::shared_ptr<BasePin>>("next", new BasePin("next", 0, GetNextId(), "Next", PinType::Flow)));

    s_Nodes.back()->node_funcs = std::make_shared<ArraySetValueNode_Func>();
    std::dynamic_pointer_cast<ArraySetValueNode_Func>(s_Nodes.back()->node_funcs)->parent_node = s_Nodes.back();

    s_Nodes.back()->node_funcs->Initialize();

    BuildNode(s_Nodes.back());

    return s_Nodes.back();
}





void ArrayGetValueNode_Func::Delete()
{
    parent_node = nullptr;
}

void ArrayGetValueNode_Func::NoFlowUpdatePinsValues()
{
    UpdateNodeUI();
    if (parent_node->inputs.at("input")->type == PinType::String)
    {
        std::shared_ptr<std::vector<std::string>> input = GetInputPinArrValue<std::string>(parent_node, "input");
        std::shared_ptr<PinValue<std::string>> output_pin = std::dynamic_pointer_cast<PinValue<std::string>>(parent_node->outputs.at("object"));
        int inx = GetInputPinValue<int>(parent_node, "index");
        if (input)
        {
            if (inx < input->size() && inx >= 0)
            {
                output_pin->value = input->at(inx);
            }
        }
    }
    else if (parent_node->inputs.at("input")->type == PinType::Bool)
    {
        std::shared_ptr<std::vector<bool>> input = GetInputPinArrValue<bool>(parent_node, "input");
        std::shared_ptr<PinValue<bool>> output_pin = std::dynamic_pointer_cast<PinValue<bool>>(parent_node->outputs.at("object"));
        int inx = GetInputPinValue<int>(parent_node, "index");
        if (input)
        {
            if (inx < input->size() && inx >= 0)
            {
                output_pin->value = input->at(inx);
            }
        }
    }
    else if (parent_node->inputs.at("input")->type == PinType::Float)
    {
        std::shared_ptr<std::vector<float>> input = GetInputPinArrValue<float>(parent_node, "input");
        std::shared_ptr<PinValue<float>> output_pin = std::dynamic_pointer_cast<PinValue<float>>(parent_node->outputs.at("object"));
        int inx = GetInputPinValue<int>(parent_node, "index");
        if (input)
        {
            if (inx < input->size() && inx >= 0)
            {
                output_pin->value = input->at(inx);
            }
        }
    }
    else if (parent_node->inputs.at("input")->type == PinType::Int)
    {
        std::shared_ptr<std::vector<int>> input = GetInputPinArrValue<int>(parent_node, "input");
        std::shared_ptr<PinValue<int>> output_pin = std::dynamic_pointer_cast<PinValue<int>>(parent_node->outputs.at("object"));
        int inx = GetInputPinValue<int>(parent_node, "index");
        if (input)
        {
            if (inx < input->size() && inx >= 0)
            {
                output_pin->value = input->at(inx);
            }
        }
    }
    else if (parent_node->inputs.at("input")->type == PinType::Vector2)
    {
        std::shared_ptr<std::vector<glm::vec2>> input = GetInputPinArrValue<glm::vec2>(parent_node, "input");
        std::shared_ptr<PinValue<glm::vec2>> output_pin = std::dynamic_pointer_cast<PinValue<glm::vec2>>(parent_node->outputs.at("object"));
        int inx = GetInputPinValue<int>(parent_node, "index");
        if (input)
        {
            if (inx < input->size() && inx >= 0)
            {
                output_pin->value = input->at(inx);
            }
        }
    }
    else if (parent_node->inputs.at("input")->type == PinType::Vector3)
    {
        std::shared_ptr<std::vector<glm::vec3>> input = GetInputPinArrValue<glm::vec3>(parent_node, "input");
        std::shared_ptr<PinValue<glm::vec3>> output_pin = std::dynamic_pointer_cast<PinValue<glm::vec3>>(parent_node->outputs.at("object"));
        int inx = GetInputPinValue<int>(parent_node, "index");
        if (input)
        {
            if (inx < input->size() && inx >= 0)
            {
                output_pin->value = input->at(inx);
            }
        }
    }
    else if (parent_node->inputs.at("input")->type == PinType::Vector4)
    {
        std::shared_ptr<std::vector<glm::vec4>> input = GetInputPinArrValue<glm::vec4>(parent_node, "input");
        std::shared_ptr<PinValue<glm::vec4>> output_pin = std::dynamic_pointer_cast<PinValue<glm::vec4>>(parent_node->outputs.at("object"));
        int inx = GetInputPinValue<int>(parent_node, "index");
        if (input)
        {
            if (inx < input->size() && inx >= 0)
            {
                output_pin->value = input->at(inx);
            }
        }
    }
    else if (parent_node->inputs.at("input")->type == PinType::Matrix4x4)
    {
        std::shared_ptr<std::vector<glm::mat4>> input = GetInputPinArrValue<glm::mat4>(parent_node, "input");
        std::shared_ptr<PinValue<glm::mat4>> output_pin = std::dynamic_pointer_cast<PinValue<glm::mat4>>(parent_node->outputs.at("object"));
        int inx = GetInputPinValue<int>(parent_node, "index");
        if (input)
        {
            if (inx < input->size() && inx >= 0)
            {
                output_pin->value = input->at(inx);
            }
        }
    }
    else if (parent_node->inputs.at("input")->type == PinType::TextureObject)
    {
        std::shared_ptr<std::vector<std::shared_ptr<TextureObject>>> input = GetInputPinArrValue<std::shared_ptr<TextureObject>>(parent_node, "input");
        std::shared_ptr<PinValue<std::shared_ptr<TextureObject>>> output_pin = std::dynamic_pointer_cast<PinValue<std::shared_ptr<TextureObject>>>(parent_node->outputs.at("object"));
        int inx = GetInputPinValue<int>(parent_node, "index");
        if (input)
        {
            if (inx < input->size() && inx >= 0)
            {
                output_pin->value = input->at(inx);
            }
        }
    }
    else if (parent_node->inputs.at("input")->type == PinType::ProgramObject)
    {
        std::shared_ptr<std::vector<std::shared_ptr<ProgramObject>>> input = GetInputPinArrValue<std::shared_ptr<ProgramObject>>(parent_node, "input");
        std::shared_ptr<PinValue<std::shared_ptr<ProgramObject>>> output_pin = std::dynamic_pointer_cast<PinValue<std::shared_ptr<ProgramObject>>>(parent_node->outputs.at("object"));
        int inx = GetInputPinValue<int>(parent_node, "index");
        if (input)
        {
            if (inx < input->size() && inx >= 0)
            {
                output_pin->value = input->at(inx);
            }
        }
    }
    else if (parent_node->inputs.at("input")->type == PinType::VertexShaderObject)
    {
        std::shared_ptr<std::vector<std::shared_ptr<ShaderObject>>> input = GetInputPinArrValue<std::shared_ptr<ShaderObject>>(parent_node, "input");
        std::shared_ptr<PinValue<std::shared_ptr<ShaderObject>>> output_pin = std::dynamic_pointer_cast<PinValue<std::shared_ptr<ShaderObject>>>(parent_node->outputs.at("object"));
        int inx = GetInputPinValue<int>(parent_node, "index");
        if (input)
        {
            if (inx < input->size() && inx >= 0)
            {
                output_pin->value = input->at(inx);
            }
        }
    }
    else if (parent_node->inputs.at("input")->type == PinType::FragmentShaderObject)
    {
        std::shared_ptr<std::vector<std::shared_ptr<ShaderObject>>> input = GetInputPinArrValue<std::shared_ptr<ShaderObject>>(parent_node, "input");
        std::shared_ptr<PinValue<std::shared_ptr<ShaderObject>>> output_pin = std::dynamic_pointer_cast<PinValue<std::shared_ptr<ShaderObject>>>(parent_node->outputs.at("object"));
        int inx = GetInputPinValue<int>(parent_node, "index");
        if (input)
        {
            if (inx < input->size() && inx >= 0)
            {
                output_pin->value = input->at(inx);
            }
        }
    }
    else if (parent_node->inputs.at("input")->type == PinType::MeshObject)
    {
        std::shared_ptr<std::vector<std::shared_ptr<MeshObject>>> input = GetInputPinArrValue<std::shared_ptr<MeshObject>>(parent_node, "input");
        std::shared_ptr<PinValue<std::shared_ptr<MeshObject>>> output_pin = std::dynamic_pointer_cast<PinValue<std::shared_ptr<MeshObject>>>(parent_node->outputs.at("object"));
        int inx = GetInputPinValue<int>(parent_node, "index");
        if (input)
        {
            if (inx < input->size() && inx >= 0)
            {
                output_pin->value = input->at(inx);
            }
        }
    }
}

void ArrayGetValueNode_Func::UpdateNodeUI()
{
    if (parent_node->inputs.at("input")->type != parent_node->outputs.at("object")->type)
    {
        UtilsDeleteLinks(parent_node->outputs.at("object"));
        UtilsChangePinType(parent_node, PinKind::Output, "object", parent_node->inputs.at("input")->type, false);
    }
}

void ArrayGetValueNode_Func::SaveNodeData(rapidjson::Writer<rapidjson::StringBuffer>& writer)
{
    writer.Key("index");
    writer.Int(std::dynamic_pointer_cast<PinValue<int>>(parent_node->inputs.at("index"))->default_value);
}

void ArrayGetValueNode_Func::LoadNodeData(rapidjson::Value& node_obj)
{
    if (!node_obj["index"].IsNull())
        std::dynamic_pointer_cast<PinValue<int>>(parent_node->inputs.at("index"))->default_value = node_obj["index"].GetInt();
}

std::string arrayGetValueNodeName = "Array - Get Value";
std::shared_ptr<Node> ArrayGetValueNode(std::vector<std::shared_ptr<Node>>& s_Nodes)
{
    s_Nodes.emplace_back(new Node(GetNextId(), arrayGetValueNodeName.c_str(), true));
    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<PinArrValue<std::string>>>("input", new PinArrValue<std::string>("input", 1, GetNextId(), "Array", PinType::String, std::make_shared<std::vector<std::string>>())));
    s_Nodes.back()->inputs.at("input")->isGeneralArray = true;
    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<PinValue<int>>>("index", new PinValue<int>("index", 2, GetNextId(), "Index", PinType::Int, 0)));

    s_Nodes.back()->outputs.insert(std::pair<std::string, std::shared_ptr<PinValue<std::string>>>("object", new PinValue<std::string>("object", 1, GetNextId(), "Object", PinType::String, "")));

    s_Nodes.back()->node_funcs = std::make_shared<ArrayGetValueNode_Func>();
    std::dynamic_pointer_cast<ArrayGetValueNode_Func>(s_Nodes.back()->node_funcs)->parent_node = s_Nodes.back();

    s_Nodes.back()->node_funcs->Initialize();

    BuildNode(s_Nodes.back());

    return s_Nodes.back();
}





void ArraysNodesSearchSetup(std::vector<SearchNodeObj>& search_nodes_vector)
{
    std::function<std::shared_ptr<Node>(std::vector<std::shared_ptr<Node>>&)> func_1 = GetArrayNode;
    std::vector<std::string> keywords_1{ "Get", "Array" };
    search_nodes_vector.push_back(SearchNodeObj("Get Array", "Arrays", keywords_1, func_1));

    std::function<std::shared_ptr<Node>(std::vector<std::shared_ptr<Node>>&)> func_2 = GetArraySizeNode;
    std::vector<std::string> keywords_2{ "Array", "Get", "Size" };
    search_nodes_vector.push_back(SearchNodeObj("Get Array Size", "Arrays", keywords_2, func_2));

    std::function<std::shared_ptr<Node>(std::vector<std::shared_ptr<Node>>&)> func_3 = ArrayInsertNode;
    std::vector<std::string> keywords_3{ "Array", "Insert", "Object" };
    search_nodes_vector.push_back(SearchNodeObj("Array - Insert Object", "Arrays", keywords_3, func_3));

    std::function<std::shared_ptr<Node>(std::vector<std::shared_ptr<Node>>&)> func_4 = ArrayInsertDefaultNode;
    std::vector<std::string> keywords_4{ "Array", "Insert", "Default", "Object" };
    search_nodes_vector.push_back(SearchNodeObj("Array - Insert Default Object", "Arrays", keywords_4, func_4));

    std::function<std::shared_ptr<Node>(std::vector<std::shared_ptr<Node>>&)> func_5 = ArrayClearValuesNode;
    std::vector<std::string> keywords_5{ "Array", "Clear", "Values" };
    search_nodes_vector.push_back(SearchNodeObj("Array - Clear Values", "Arrays", keywords_5, func_5));

    std::function<std::shared_ptr<Node>(std::vector<std::shared_ptr<Node>>&)> func_6 = ArrayClearDefaultValuesNode;
    std::vector<std::string> keywords_6{ "Array", "Clear", "Default", "Values" };
    search_nodes_vector.push_back(SearchNodeObj("Array - Clear Default Values", "Arrays", keywords_6, func_6));

    std::function<std::shared_ptr<Node>(std::vector<std::shared_ptr<Node>>&)> func_7 = ArrayClearToDefaultValuesNode;
    std::vector<std::string> keywords_7{ "Array", "Clear", "To", "Default", "Values" };
    search_nodes_vector.push_back(SearchNodeObj("Array - Clear To Default Values", "Arrays", keywords_7, func_7));

    std::function<std::shared_ptr<Node>(std::vector<std::shared_ptr<Node>>&)> func_8 = ArraySetValueNode;
    std::vector<std::string> keywords_8{ "Array", "Set", "Value" };
    search_nodes_vector.push_back(SearchNodeObj("Array - Set Value", "Arrays", keywords_8, func_8));

    std::function<std::shared_ptr<Node>(std::vector<std::shared_ptr<Node>>&)> func_9 = ArrayGetValueNode;
    std::vector<std::string> keywords_9{ "Array", "Get", "Value" };
    search_nodes_vector.push_back(SearchNodeObj("Array - Get Value", "Arrays", keywords_9, func_9));
}

std::shared_ptr<Node> ArraysNodesLoadSetup(std::vector<std::shared_ptr<Node>>& s_Nodes, std::string node_key)
{
    std::shared_ptr<Node> loaded_node = nullptr;
    if (loaded_node == nullptr && node_key.rfind(getArrayNodeName, 0) == 0) {
        loaded_node = GetArrayNode(s_Nodes);
    }
    else if (loaded_node == nullptr && node_key.rfind(getArraySizeNodeName, 0) == 0) {
        loaded_node = GetArraySizeNode(s_Nodes);
    }
    else if (loaded_node == nullptr && node_key.rfind(arrayInsertNodeName, 0) == 0) {
        loaded_node = ArrayInsertNode(s_Nodes);
    }
    else if (loaded_node == nullptr && node_key.rfind(arrayInsertDefaultNodeName, 0) == 0) {
        loaded_node = ArrayInsertDefaultNode(s_Nodes);
    }
    else if (loaded_node == nullptr && node_key.rfind(arrayClearValuesNodeName, 0) == 0) {
        loaded_node = ArrayClearValuesNode(s_Nodes);
    }
    else if (loaded_node == nullptr && node_key.rfind(arrayClearDefaultValuesNodeName, 0) == 0) {
        loaded_node = ArrayClearDefaultValuesNode(s_Nodes);
    }
    else if (loaded_node == nullptr && node_key.rfind(arrayClearToDefaultValuesNodeName, 0) == 0) {
        loaded_node = ArrayClearToDefaultValuesNode(s_Nodes);
    }
    else if (loaded_node == nullptr && node_key.rfind(arraySetValueNodeName, 0) == 0) {
        loaded_node = ArraySetValueNode(s_Nodes);
    }
    else if (loaded_node == nullptr && node_key.rfind(arrayGetValueNodeName, 0) == 0) {
        loaded_node = ArrayGetValueNode(s_Nodes);
    }
    return loaded_node;
}
