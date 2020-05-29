#include "matrices_nodes.h"

void Mat4IdentityNode_Func::Delete()
{
    parent_node = nullptr;
}

void Mat4IdentityNode_Func::NoFlowUpdatePinsValues()
{
}

void Mat4IdentityNode_Func::SaveNodeData(rapidjson::Writer<rapidjson::StringBuffer>& writer)
{
}

void Mat4IdentityNode_Func::LoadNodeData(rapidjson::Value& node_obj)
{
}

std::string mat4IdentityNodeName = "Matrix 4 - Identidy";
std::shared_ptr<Node> Mat4IdentityNode(std::vector<std::shared_ptr<Node>>& s_Nodes)
{
    s_Nodes.emplace_back(new Node(GetNextId(), mat4IdentityNodeName.c_str(), true));
    s_Nodes.back()->outputs.insert(std::pair<std::string, std::shared_ptr<PinValue<glm::mat4>>>("out", new PinValue<glm::mat4>("out", 0, GetNextId(), "Out", PinType::Matrix4x4, glm::mat4(1.0))));

    s_Nodes.back()->node_funcs = std::make_shared<Mat4IdentityNode_Func>();
    std::dynamic_pointer_cast<Mat4IdentityNode_Func>(s_Nodes.back()->node_funcs)->parent_node = s_Nodes.back();

    s_Nodes.back()->node_funcs->Initialize();

    BuildNode(s_Nodes.back());

    return s_Nodes.back();
}





void Mat4TranslateNode_Func::Delete()
{
    parent_node = nullptr;
}

void Mat4TranslateNode_Func::NoFlowUpdatePinsValues()
{
    glm::mat4 in_mat = GetInputPinValue<glm::mat4>(parent_node, "in_mat4");
    glm::vec3 in_pos = GetInputPinValue<glm::vec3>(parent_node, "in_pos");
    
    if (in_mat != prev_in_mat || in_pos != prev_pos)
    {
        prev_in_mat = in_mat;
        prev_pos = in_pos;
        glm::mat4 translate = glm::mat4(1.0);
        translate = glm::translate(translate, in_pos);

        std::dynamic_pointer_cast<PinValue<glm::mat4>>(parent_node->outputs.at("out"))->value = translate * in_mat;
    }
}

void Mat4TranslateNode_Func::SaveNodeData(rapidjson::Writer<rapidjson::StringBuffer>& writer)
{
    writer.Key("in_mat4");
    writer.StartArray();
    glm::mat4 in_mat = std::dynamic_pointer_cast<PinValue<glm::mat4>>(parent_node->inputs.at("in_mat4"))->default_value;
    const float* pSource = (const float*)glm::value_ptr(in_mat);
    for (int i = 0; i < 16; ++i)
        writer.Double(pSource[i]);
    writer.EndArray();

    writer.Key("in_pos");
    writer.StartArray();
    glm::vec3 in_pos = std::dynamic_pointer_cast<PinValue<glm::vec3>>(parent_node->inputs.at("in_pos"))->default_value;
    writer.Double(in_pos.x);
    writer.Double(in_pos.y);
    writer.Double(in_pos.z);
    writer.EndArray();
}

void Mat4TranslateNode_Func::LoadNodeData(rapidjson::Value& node_obj)
{
    float* pSource = (float*)glm::value_ptr(std::dynamic_pointer_cast<PinValue<glm::mat4>>(parent_node->inputs.at("in_mat4"))->default_value);
    for (int i = 0; i < 16; ++i)
        pSource[i] = node_obj["in_mat4"].GetArray()[i].GetFloat();

    glm::vec3 loaded_pos;
    loaded_pos.x = node_obj["in_pos"].GetArray()[0].GetFloat();
    loaded_pos.y = node_obj["in_pos"].GetArray()[1].GetFloat();
    loaded_pos.z = node_obj["in_pos"].GetArray()[2].GetFloat();
    std::dynamic_pointer_cast<PinValue<glm::vec3>>(parent_node->inputs.at("in_pos"))->default_value = loaded_pos;
}

std::string mat4TranslateNodeName = "Matrix 4 - Translate";
std::shared_ptr<Node> Mat4TranslateNode(std::vector<std::shared_ptr<Node>>& s_Nodes)
{
    s_Nodes.emplace_back(new Node(GetNextId(), mat4TranslateNodeName.c_str(), true));
    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<PinValue<glm::mat4>>>("in_mat4", new PinValue<glm::mat4>("in_mat4", 0, GetNextId(), "In Matrix", PinType::Matrix4x4, glm::mat4(1.0))));
    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<PinValue<glm::vec3>>>("in_pos", new PinValue<glm::vec3>("in_pos", 1, GetNextId(), "In Position", PinType::Vector3, glm::vec3(0,0,0))));
    
    s_Nodes.back()->outputs.insert(std::pair<std::string, std::shared_ptr<PinValue<glm::mat4>>>("out", new PinValue<glm::mat4>("out", 0, GetNextId(), "Out", PinType::Matrix4x4, glm::mat4(1.0))));

    s_Nodes.back()->node_funcs = std::make_shared<Mat4TranslateNode_Func>();
    std::dynamic_pointer_cast<Mat4TranslateNode_Func>(s_Nodes.back()->node_funcs)->parent_node = s_Nodes.back();

    s_Nodes.back()->node_funcs->Initialize();

    BuildNode(s_Nodes.back());

    return s_Nodes.back();
}





void Mat4RotateNode_Func::Delete()
{
    parent_node = nullptr;
}

void Mat4RotateNode_Func::NoFlowUpdatePinsValues()
{
    glm::mat4 in_mat = GetInputPinValue<glm::mat4>(parent_node, "in_mat4");
    
    glm::vec3 in_rot_angles = GetInputPinValue<glm::vec3>(parent_node, "in_rot_angles");
    bool is_degrees = GetInputPinValue<bool>(parent_node, "is_degrees");
    bool rotate_x = GetInputPinValue<bool>(parent_node, "rotate_x");
    bool rotate_y = GetInputPinValue<bool>(parent_node, "rotate_y");
    bool rotate_z = GetInputPinValue<bool>(parent_node, "rotate_z");
    if (in_mat != prev_in_mat || in_rot_angles != prev_rot_angles || 
        is_degrees != prev_is_degrees || rotate_x != prev_rotate_x || rotate_y != prev_rotate_y || rotate_z != prev_rotate_z)
    {
        prev_in_mat = in_mat;
        prev_rot_angles = in_rot_angles;
        prev_is_degrees = is_degrees;
        prev_rotate_x = rotate_x;
        prev_rotate_y = rotate_y;
        prev_rotate_z = rotate_z;
        if (is_degrees)
        {
            in_rot_angles.x = glm::radians(in_rot_angles.x);
            in_rot_angles.y = glm::radians(in_rot_angles.y);
            in_rot_angles.z = glm::radians(in_rot_angles.z);
        }

        glm::mat4 rotate = glm::mat4(1.0);
        if (rotate_x)
            rotate = glm::rotate(rotate, in_rot_angles.x, glm::vec3(1, 0, 0));
        if (rotate_y)
            rotate = glm::rotate(rotate, in_rot_angles.y, glm::vec3(0, 1, 0));
        if (rotate_z)
            rotate = glm::rotate(rotate, in_rot_angles.z, glm::vec3(0, 0, 1));

        std::dynamic_pointer_cast<PinValue<glm::mat4>>(parent_node->outputs.at("out"))->value = rotate * in_mat;
    }
}

void Mat4RotateNode_Func::SaveNodeData(rapidjson::Writer<rapidjson::StringBuffer>& writer)
{
    writer.Key("in_mat4");
    writer.StartArray();
    glm::mat4 in_mat = std::dynamic_pointer_cast<PinValue<glm::mat4>>(parent_node->inputs.at("in_mat4"))->default_value;
    const float* pSource = (const float*)glm::value_ptr(in_mat);
    for (int i = 0; i < 16; ++i)
        writer.Double(pSource[i]);
    writer.EndArray();

    writer.Key("in_rot_angles");
    writer.StartArray();
    glm::vec3 in_rot_angles = std::dynamic_pointer_cast<PinValue<glm::vec3>>(parent_node->inputs.at("in_rot_angles"))->default_value;
    writer.Double(in_rot_angles.x);
    writer.Double(in_rot_angles.y);
    writer.Double(in_rot_angles.z);
    writer.EndArray();

    writer.Key("is_degrees");
    writer.Bool(std::dynamic_pointer_cast<PinValue<bool>>(parent_node->inputs.at("is_degrees"))->default_value);

    writer.Key("rotate_x");
    writer.Bool(std::dynamic_pointer_cast<PinValue<bool>>(parent_node->inputs.at("rotate_x"))->default_value);
    writer.Key("rotate_y");
    writer.Bool(std::dynamic_pointer_cast<PinValue<bool>>(parent_node->inputs.at("rotate_y"))->default_value);
    writer.Key("rotate_z");
    writer.Bool(std::dynamic_pointer_cast<PinValue<bool>>(parent_node->inputs.at("rotate_z"))->default_value);
}

void Mat4RotateNode_Func::LoadNodeData(rapidjson::Value& node_obj)
{
    float* pSource = (float*)glm::value_ptr(std::dynamic_pointer_cast<PinValue<glm::mat4>>(parent_node->inputs.at("in_mat4"))->default_value);
    for (int i = 0; i < 16; ++i)
        pSource[i] = node_obj["in_mat4"].GetArray()[i].GetFloat();

    glm::vec3 loaded_rot;
    loaded_rot.x = node_obj["in_rot_angles"].GetArray()[0].GetFloat();
    loaded_rot.y = node_obj["in_rot_angles"].GetArray()[1].GetFloat();
    loaded_rot.z = node_obj["in_rot_angles"].GetArray()[2].GetFloat();
    std::dynamic_pointer_cast<PinValue<glm::vec3>>(parent_node->inputs.at("in_rot_angles"))->default_value = loaded_rot;

    std::dynamic_pointer_cast<PinValue<bool>>(parent_node->inputs.at("is_degrees"))->default_value = node_obj["is_degrees"].GetBool();
    std::dynamic_pointer_cast<PinValue<bool>>(parent_node->inputs.at("rotate_x"))->default_value = node_obj["rotate_x"].GetBool();
    std::dynamic_pointer_cast<PinValue<bool>>(parent_node->inputs.at("rotate_y"))->default_value = node_obj["rotate_y"].GetBool();
    std::dynamic_pointer_cast<PinValue<bool>>(parent_node->inputs.at("rotate_z"))->default_value = node_obj["rotate_z"].GetBool();
}

std::string mat4RotateNodeName = "Matrix 4 - Rotate";
std::shared_ptr<Node> Mat4RotateNode(std::vector<std::shared_ptr<Node>>& s_Nodes)
{
    s_Nodes.emplace_back(new Node(GetNextId(), mat4RotateNodeName.c_str(), true));
    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<PinValue<glm::mat4>>>("in_mat4", new PinValue<glm::mat4>("in_mat4", 0, GetNextId(), "In Matrix", PinType::Matrix4x4, glm::mat4(1.0))));
    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<PinValue<glm::vec3>>>("in_rot_angles", new PinValue<glm::vec3>("in_rot_angles", 1, GetNextId(), "In Rotation", PinType::Vector3, glm::vec3(0, 0, 0))));
    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<PinValue<bool>>>("is_degrees", new PinValue<bool>("is_degrees", 2, GetNextId(), "Use Degrees?", PinType::Bool, true)));
    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<PinValue<bool>>>("rotate_x", new PinValue<bool>("rotate_x", 3, GetNextId(), "Rotate X Axis", PinType::Bool, true)));
    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<PinValue<bool>>>("rotate_y", new PinValue<bool>("rotate_y", 4, GetNextId(), "Rotate Y Axis", PinType::Bool, true)));
    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<PinValue<bool>>>("rotate_z", new PinValue<bool>("rotate_z", 5, GetNextId(), "Rotate Z Axis", PinType::Bool, true)));

    s_Nodes.back()->outputs.insert(std::pair<std::string, std::shared_ptr<PinValue<glm::mat4>>>("out", new PinValue<glm::mat4>("out", 0, GetNextId(), "Out", PinType::Matrix4x4, glm::mat4(1.0))));
    
    s_Nodes.back()->node_funcs = std::make_shared<Mat4RotateNode_Func>();
    std::dynamic_pointer_cast<Mat4RotateNode_Func>(s_Nodes.back()->node_funcs)->parent_node = s_Nodes.back();

    s_Nodes.back()->node_funcs->Initialize();

    BuildNode(s_Nodes.back());

    return s_Nodes.back();
}





void Mat4ScaleNode_Func::Delete()
{
    parent_node = nullptr;
}

void Mat4ScaleNode_Func::NoFlowUpdatePinsValues()
{
    glm::mat4 in_mat = GetInputPinValue<glm::mat4>(parent_node, "in_mat4");
    glm::vec3 in_scale = GetInputPinValue<glm::vec3>(parent_node, "in_scale");
    
    if (in_mat != prev_in_mat || in_scale != prev_scale)
    {
        prev_in_mat = in_mat;
        prev_scale = in_scale;
        glm::mat4 scale = glm::mat4(1.0);
        scale = glm::scale(scale, in_scale);

        std::dynamic_pointer_cast<PinValue<glm::mat4>>(parent_node->outputs.at("out"))->value = scale * in_mat;
    }
}

void Mat4ScaleNode_Func::SaveNodeData(rapidjson::Writer<rapidjson::StringBuffer>& writer)
{
    writer.Key("in_mat4");
    writer.StartArray();
    glm::mat4 in_mat = std::dynamic_pointer_cast<PinValue<glm::mat4>>(parent_node->inputs.at("in_mat4"))->default_value;
    const float* pSource = (const float*)glm::value_ptr(in_mat);
    for (int i = 0; i < 16; ++i)
        writer.Double(pSource[i]);
    writer.EndArray();

    writer.Key("in_scale");
    writer.StartArray();
    glm::vec3 in_scale = std::dynamic_pointer_cast<PinValue<glm::vec3>>(parent_node->inputs.at("in_scale"))->default_value;
    writer.Double(in_scale.x);
    writer.Double(in_scale.y);
    writer.Double(in_scale.z);
    writer.EndArray();
}

void Mat4ScaleNode_Func::LoadNodeData(rapidjson::Value& node_obj)
{
    float* pSource = (float*)glm::value_ptr(std::dynamic_pointer_cast<PinValue<glm::mat4>>(parent_node->inputs.at("in_mat4"))->default_value);
    for (int i = 0; i < 16; ++i)
        pSource[i] = node_obj["in_mat4"].GetArray()[i].GetFloat();

    glm::vec3 loaded_pos;
    loaded_pos.x = node_obj["in_scale"].GetArray()[0].GetFloat();
    loaded_pos.y = node_obj["in_scale"].GetArray()[1].GetFloat();
    loaded_pos.z = node_obj["in_scale"].GetArray()[2].GetFloat();
    std::dynamic_pointer_cast<PinValue<glm::vec3>>(parent_node->inputs.at("in_scale"))->default_value = loaded_pos;
}

std::string mat4ScaleNodeName = "Matrix 4 - Scale";
std::shared_ptr<Node> Mat4ScaleNode(std::vector<std::shared_ptr<Node>>& s_Nodes)
{
    s_Nodes.emplace_back(new Node(GetNextId(), mat4ScaleNodeName.c_str(), true));
    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<PinValue<glm::mat4>>>("in_mat4", new PinValue<glm::mat4>("in_mat4", 0, GetNextId(), "In Matrix", PinType::Matrix4x4, glm::mat4(1.0))));
    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<PinValue<glm::vec3>>>("in_scale", new PinValue<glm::vec3>("in_scale", 1, GetNextId(), "In Scale", PinType::Vector3, glm::vec3(0, 0, 0))));

    s_Nodes.back()->outputs.insert(std::pair<std::string, std::shared_ptr<PinValue<glm::mat4>>>("out", new PinValue<glm::mat4>("out", 0, GetNextId(), "Out", PinType::Matrix4x4, glm::mat4(1.0))));

    s_Nodes.back()->node_funcs = std::make_shared<Mat4ScaleNode_Func>();
    std::dynamic_pointer_cast<Mat4ScaleNode_Func>(s_Nodes.back()->node_funcs)->parent_node = s_Nodes.back();

    s_Nodes.back()->node_funcs->Initialize();

    BuildNode(s_Nodes.back());

    return s_Nodes.back();
}





void Mat4TransformNode_Func::Delete()
{
    parent_node = nullptr;
}

void Mat4TransformNode_Func::NoFlowUpdatePinsValues()
{
    glm::mat4 in_mat = GetInputPinValue<glm::mat4>(parent_node, "in_mat4");

    bool a_translate = GetInputPinValue<bool>(parent_node, "a_translate");
    glm::vec3 in_pos = GetInputPinValue<glm::vec3>(parent_node, "in_pos");

    glm::vec3 in_rot_angles = GetInputPinValue<glm::vec3>(parent_node, "in_rot_angles");
    bool is_degrees = GetInputPinValue<bool>(parent_node, "is_degrees");
    bool rotate_x = GetInputPinValue<bool>(parent_node, "rotate_x");
    bool rotate_y = GetInputPinValue<bool>(parent_node, "rotate_y");
    bool rotate_z = GetInputPinValue<bool>(parent_node, "rotate_z");

    bool a_scale = GetInputPinValue<bool>(parent_node, "a_scale");
    glm::vec3 in_scale = GetInputPinValue<glm::vec3>(parent_node, "in_scale");
    
    if (in_mat != prev_in_mat || a_translate != prev_a_translate || in_pos != prev_pos ||
        in_rot_angles != prev_rot_angles || is_degrees != prev_is_degrees || rotate_x != prev_rotate_x || rotate_y != prev_rotate_y || rotate_z != prev_rotate_z || 
        a_scale != prev_a_scale || in_scale != prev_scale)
    {
        prev_in_mat = in_mat;
        prev_a_translate = a_translate;
        prev_pos = in_pos;
        prev_rot_angles = in_rot_angles;
        prev_is_degrees = is_degrees;
        prev_rotate_x = rotate_x;
        prev_rotate_y = rotate_y;
        prev_rotate_z = rotate_z;
        prev_a_scale = a_scale;
        prev_scale = in_scale;

        glm::mat4 translate = glm::mat4(1.0);
        if (a_translate)
            translate = glm::translate(translate, in_pos);

        if (is_degrees)
        {
            in_rot_angles.x = glm::radians(in_rot_angles.x);
            in_rot_angles.y = glm::radians(in_rot_angles.y);
            in_rot_angles.z = glm::radians(in_rot_angles.z);
        }

        glm::mat4 rotate = glm::mat4(1.0);
        if (rotate_x)
            rotate = glm::rotate(rotate, in_rot_angles.x, glm::vec3(1, 0, 0));
        if (rotate_y)
            rotate = glm::rotate(rotate, in_rot_angles.y, glm::vec3(0, 1, 0));
        if (rotate_z)
            rotate = glm::rotate(rotate, in_rot_angles.z, glm::vec3(0, 0, 1));

        glm::mat4 scale = glm::mat4(1.0);
        if (a_scale)
            scale = glm::scale(scale, in_scale);

        std::dynamic_pointer_cast<PinValue<glm::mat4>>(parent_node->outputs.at("out"))->value = translate * rotate * scale * in_mat;
    }

}

void Mat4TransformNode_Func::SaveNodeData(rapidjson::Writer<rapidjson::StringBuffer>& writer)
{
    writer.Key("in_mat4");
    writer.StartArray();
    glm::mat4 in_mat = std::dynamic_pointer_cast<PinValue<glm::mat4>>(parent_node->inputs.at("in_mat4"))->default_value;
    const float* pSource = (const float*)glm::value_ptr(in_mat);
    for (int i = 0; i < 16; ++i)
        writer.Double(pSource[i]);
    writer.EndArray();

    writer.Key("a_translate");
    writer.Bool(std::dynamic_pointer_cast<PinValue<bool>>(parent_node->inputs.at("a_translate"))->default_value);
    writer.Key("in_pos");
    writer.StartArray();
    glm::vec3 in_pos = std::dynamic_pointer_cast<PinValue<glm::vec3>>(parent_node->inputs.at("in_pos"))->default_value;
    writer.Double(in_pos.x);
    writer.Double(in_pos.y);
    writer.Double(in_pos.z);
    writer.EndArray();

    writer.Key("in_rot_angles");
    writer.StartArray();
    glm::vec3 in_rot_angles = std::dynamic_pointer_cast<PinValue<glm::vec3>>(parent_node->inputs.at("in_rot_angles"))->default_value;
    writer.Double(in_rot_angles.x);
    writer.Double(in_rot_angles.y);
    writer.Double(in_rot_angles.z);
    writer.EndArray();
    writer.Key("is_degrees");
    writer.Bool(std::dynamic_pointer_cast<PinValue<bool>>(parent_node->inputs.at("is_degrees"))->default_value);
    writer.Key("rotate_x");
    writer.Bool(std::dynamic_pointer_cast<PinValue<bool>>(parent_node->inputs.at("rotate_x"))->default_value);
    writer.Key("rotate_y");
    writer.Bool(std::dynamic_pointer_cast<PinValue<bool>>(parent_node->inputs.at("rotate_y"))->default_value);
    writer.Key("rotate_z");
    writer.Bool(std::dynamic_pointer_cast<PinValue<bool>>(parent_node->inputs.at("rotate_z"))->default_value);

    writer.Key("a_scale");
    writer.Bool(std::dynamic_pointer_cast<PinValue<bool>>(parent_node->inputs.at("a_scale"))->default_value);
    writer.Key("in_scale");
    writer.StartArray();
    glm::vec3 in_scale = std::dynamic_pointer_cast<PinValue<glm::vec3>>(parent_node->inputs.at("in_scale"))->default_value;
    writer.Double(in_scale.x);
    writer.Double(in_scale.y);
    writer.Double(in_scale.z);
    writer.EndArray();
}

void Mat4TransformNode_Func::LoadNodeData(rapidjson::Value& node_obj)
{
    float* pSource = (float*)glm::value_ptr(std::dynamic_pointer_cast<PinValue<glm::mat4>>(parent_node->inputs.at("in_mat4"))->default_value);
    for (int i = 0; i < 16; ++i)
        pSource[i] = node_obj["in_mat4"].GetArray()[i].GetFloat();

    std::dynamic_pointer_cast<PinValue<bool>>(parent_node->inputs.at("a_translate"))->default_value = node_obj["a_translate"].GetBool();
    glm::vec3 loaded_pos;
    loaded_pos.x = node_obj["in_pos"].GetArray()[0].GetFloat();
    loaded_pos.y = node_obj["in_pos"].GetArray()[1].GetFloat();
    loaded_pos.z = node_obj["in_pos"].GetArray()[2].GetFloat();
    std::dynamic_pointer_cast<PinValue<glm::vec3>>(parent_node->inputs.at("in_pos"))->default_value = loaded_pos;

    glm::vec3 loaded_rot;
    loaded_rot.x = node_obj["in_rot_angles"].GetArray()[0].GetFloat();
    loaded_rot.y = node_obj["in_rot_angles"].GetArray()[1].GetFloat();
    loaded_rot.z = node_obj["in_rot_angles"].GetArray()[2].GetFloat();
    std::dynamic_pointer_cast<PinValue<glm::vec3>>(parent_node->inputs.at("in_rot_angles"))->default_value = loaded_rot;
    std::dynamic_pointer_cast<PinValue<bool>>(parent_node->inputs.at("is_degrees"))->default_value = node_obj["is_degrees"].GetBool();
    std::dynamic_pointer_cast<PinValue<bool>>(parent_node->inputs.at("rotate_x"))->default_value = node_obj["rotate_x"].GetBool();
    std::dynamic_pointer_cast<PinValue<bool>>(parent_node->inputs.at("rotate_y"))->default_value = node_obj["rotate_y"].GetBool();
    std::dynamic_pointer_cast<PinValue<bool>>(parent_node->inputs.at("rotate_z"))->default_value = node_obj["rotate_z"].GetBool();

    std::dynamic_pointer_cast<PinValue<bool>>(parent_node->inputs.at("a_scale"))->default_value = node_obj["a_scale"].GetBool();
    glm::vec3 loaded_scale;
    loaded_scale.x = node_obj["in_scale"].GetArray()[0].GetFloat();
    loaded_scale.y = node_obj["in_scale"].GetArray()[1].GetFloat();
    loaded_scale.z = node_obj["in_scale"].GetArray()[2].GetFloat();
    std::dynamic_pointer_cast<PinValue<glm::vec3>>(parent_node->inputs.at("in_scale"))->default_value = loaded_scale;
}

std::string mat4TransformNodeName = "Matrix 4 - Transform";
std::shared_ptr<Node> Mat4TransformNode(std::vector<std::shared_ptr<Node>>& s_Nodes)
{
    s_Nodes.emplace_back(new Node(GetNextId(), mat4TransformNodeName.c_str(), true));
    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<PinValue<glm::mat4>>>("in_mat4", new PinValue<glm::mat4>("in_mat4", 0, GetNextId(), "In Matrix", PinType::Matrix4x4, glm::mat4(1.0))));
    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<PinValue<bool>>>("a_translate", new PinValue<bool>("a_translate", 1, GetNextId(), "Active Translate", PinType::Bool, false)));
    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<PinValue<glm::vec3>>>("in_pos", new PinValue<glm::vec3>("in_pos", 2, GetNextId(), "In Position", PinType::Vector3, glm::vec3(0, 0, 0))));

    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<PinValue<glm::vec3>>>("in_rot_angles", new PinValue<glm::vec3>("in_rot_angles", 3, GetNextId(), "In Rotation", PinType::Vector3, glm::vec3(0, 0, 0))));
    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<PinValue<bool>>>("is_degrees", new PinValue<bool>("is_degrees", 4, GetNextId(), "Use Degrees?", PinType::Bool, true)));
    s_Nodes.back()->inputs.at("is_degrees")->always_expose = false;
    s_Nodes.back()->inputs.at("is_degrees")->exposed = false;
    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<PinValue<bool>>>("rotate_x", new PinValue<bool>("rotate_x", 5, GetNextId(), "Rotate X Axis", PinType::Bool, false)));
    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<PinValue<bool>>>("rotate_y", new PinValue<bool>("rotate_y", 6, GetNextId(), "Rotate Y Axis", PinType::Bool, false)));
    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<PinValue<bool>>>("rotate_z", new PinValue<bool>("rotate_z", 7, GetNextId(), "Rotate Z Axis", PinType::Bool, false)));

    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<PinValue<bool>>>("a_scale", new PinValue<bool>("a_scale", 8, GetNextId(), "Active Scale", PinType::Bool, false)));
    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<PinValue<glm::vec3>>>("in_scale", new PinValue<glm::vec3>("in_scale", 9, GetNextId(), "In Scale", PinType::Vector3, glm::vec3(0, 0, 0))));

    s_Nodes.back()->outputs.insert(std::pair<std::string, std::shared_ptr<PinValue<glm::mat4>>>("out", new PinValue<glm::mat4>("out", 0, GetNextId(), "Out", PinType::Matrix4x4, glm::mat4(1.0))));

    s_Nodes.back()->node_funcs = std::make_shared<Mat4TransformNode_Func>();
    std::dynamic_pointer_cast<Mat4TransformNode_Func>(s_Nodes.back()->node_funcs)->parent_node = s_Nodes.back();

    s_Nodes.back()->node_funcs->Initialize();

    BuildNode(s_Nodes.back());

    return s_Nodes.back();
}





void OrthoProjNode_Func::Delete()
{
    parent_node = nullptr;
}

void OrthoProjNode_Func::NoFlowUpdatePinsValues()
{
    float left = GetInputPinValue<float>(parent_node, "left");
    float right = GetInputPinValue<float>(parent_node, "right");
    float bottom = GetInputPinValue<float>(parent_node, "bottom");
    float top = GetInputPinValue<float>(parent_node, "top");
    float zNear = GetInputPinValue<float>(parent_node, "zNear");
    float zFar = GetInputPinValue<float>(parent_node, "zFar");

    if (left != p_left || right != p_right || bottom != p_bottom || top != p_top || zNear != p_zNear || zFar != p_zFar)
    {
        p_left = left;
        p_right = right;
        p_bottom = bottom;
        p_top = top;
        p_zNear = zNear;
        p_zFar = zFar;

        glm::mat4 proj = glm::ortho(left, right, bottom, top, zNear, zFar);
        std::dynamic_pointer_cast<PinValue<glm::mat4>>(parent_node->outputs.at("proj"))->value = proj;
    }
}

void OrthoProjNode_Func::SaveNodeData(rapidjson::Writer<rapidjson::StringBuffer>& writer)
{
    writer.Key("left");
    writer.Double(std::dynamic_pointer_cast<PinValue<float>>(parent_node->inputs.at("left"))->default_value);
    writer.Key("right");
    writer.Double(std::dynamic_pointer_cast<PinValue<float>>(parent_node->inputs.at("right"))->default_value);
    writer.Key("bottom");
    writer.Double(std::dynamic_pointer_cast<PinValue<float>>(parent_node->inputs.at("bottom"))->default_value);
    writer.Key("top");
    writer.Double(std::dynamic_pointer_cast<PinValue<float>>(parent_node->inputs.at("top"))->default_value);
    writer.Key("zNear");
    writer.Double(std::dynamic_pointer_cast<PinValue<float>>(parent_node->inputs.at("zNear"))->default_value);
    writer.Key("zFar");
    writer.Double(std::dynamic_pointer_cast<PinValue<float>>(parent_node->inputs.at("zFar"))->default_value);
}

void OrthoProjNode_Func::LoadNodeData(rapidjson::Value& node_obj)
{
    std::dynamic_pointer_cast<PinValue<float>>(parent_node->inputs.at("left"))->default_value = node_obj["left"].GetFloat();
    std::dynamic_pointer_cast<PinValue<float>>(parent_node->inputs.at("right"))->default_value = node_obj["right"].GetFloat();
    std::dynamic_pointer_cast<PinValue<float>>(parent_node->inputs.at("bottom"))->default_value = node_obj["bottom"].GetFloat();
    std::dynamic_pointer_cast<PinValue<float>>(parent_node->inputs.at("top"))->default_value = node_obj["top"].GetFloat();
    std::dynamic_pointer_cast<PinValue<float>>(parent_node->inputs.at("zNear"))->default_value = node_obj["zNear"].GetFloat();
    std::dynamic_pointer_cast<PinValue<float>>(parent_node->inputs.at("zFar"))->default_value = node_obj["zFar"].GetFloat();
}

std::string orthoProjNodeName = "Orthographic Projection";
std::shared_ptr<Node> OrthoProjNode(std::vector<std::shared_ptr<Node>>& s_Nodes)
{
    s_Nodes.emplace_back(new Node(GetNextId(), orthoProjNodeName.c_str(), true));
    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<PinValue<float>>>("left", new PinValue<float>("left", 0, GetNextId(), "Left", PinType::Float, 0)));
    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<PinValue<float>>>("right", new PinValue<float>("right", 1, GetNextId(), "Right", PinType::Float, 1024)));
    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<PinValue<float>>>("bottom", new PinValue<float>("bottom", 2, GetNextId(), "Bottom", PinType::Float, 768)));
    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<PinValue<float>>>("top", new PinValue<float>("top", 3, GetNextId(), "top", PinType::Float, 0)));
    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<PinValue<float>>>("zNear", new PinValue<float>("zNear", 4, GetNextId(), "Z Near", PinType::Float, 0.000001)));
    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<PinValue<float>>>("zFar", new PinValue<float>("zFar", 5, GetNextId(), "Z Far", PinType::Float, 10000)));

    s_Nodes.back()->outputs.insert(std::pair<std::string, std::shared_ptr<PinValue<glm::mat4>>>("proj", new PinValue<glm::mat4>("proj", 0, GetNextId(), "Projection", PinType::Matrix4x4, glm::mat4(1.0))));

    s_Nodes.back()->node_funcs = std::make_shared<OrthoProjNode_Func>();
    std::dynamic_pointer_cast<OrthoProjNode_Func>(s_Nodes.back()->node_funcs)->parent_node = s_Nodes.back();

    s_Nodes.back()->node_funcs->Initialize();

    BuildNode(s_Nodes.back());

    return s_Nodes.back();
}





void PerspectiveProjNode_Func::Delete()
{
    parent_node = nullptr;
}

void PerspectiveProjNode_Func::NoFlowUpdatePinsValues()
{
    float fovy = GetInputPinValue<float>(parent_node, "fovy");
    float width = GetInputPinValue<float>(parent_node, "width");
    float height = GetInputPinValue<float>(parent_node, "height");
    float zNear = GetInputPinValue<float>(parent_node, "zNear");
    float zFar = GetInputPinValue<float>(parent_node, "zFar");

    if (fovy != p_fovy || width != p_width || height != p_height || zNear != p_zNear || zFar != p_zFar)
    {
        p_fovy = fovy;
        p_width = width;
        p_height = height;
        p_zNear = zNear;
        p_zFar = zFar;

        float aspect = width / height;
        glm::mat4 proj = glm::perspective(glm::radians(fovy), aspect, zNear, zFar);
        std::dynamic_pointer_cast<PinValue<glm::mat4>>(parent_node->outputs.at("proj"))->value = proj;
    }
}

void PerspectiveProjNode_Func::SaveNodeData(rapidjson::Writer<rapidjson::StringBuffer>& writer)
{
    writer.Key("fovy");
    writer.Double(std::dynamic_pointer_cast<PinValue<float>>(parent_node->inputs.at("fovy"))->default_value);
    writer.Key("width");
    writer.Double(std::dynamic_pointer_cast<PinValue<float>>(parent_node->inputs.at("width"))->default_value);
    writer.Key("height");
    writer.Double(std::dynamic_pointer_cast<PinValue<float>>(parent_node->inputs.at("height"))->default_value);
    writer.Key("zNear");
    writer.Double(std::dynamic_pointer_cast<PinValue<float>>(parent_node->inputs.at("zNear"))->default_value);
    writer.Key("zFar");
    writer.Double(std::dynamic_pointer_cast<PinValue<float>>(parent_node->inputs.at("zFar"))->default_value);
}

void PerspectiveProjNode_Func::LoadNodeData(rapidjson::Value& node_obj)
{
    std::dynamic_pointer_cast<PinValue<float>>(parent_node->inputs.at("fovy"))->default_value = node_obj["fovy"].GetFloat();
    std::dynamic_pointer_cast<PinValue<float>>(parent_node->inputs.at("width"))->default_value = node_obj["width"].GetFloat();
    std::dynamic_pointer_cast<PinValue<float>>(parent_node->inputs.at("height"))->default_value = node_obj["height"].GetFloat();
    std::dynamic_pointer_cast<PinValue<float>>(parent_node->inputs.at("zNear"))->default_value = node_obj["zNear"].GetFloat();
    std::dynamic_pointer_cast<PinValue<float>>(parent_node->inputs.at("zFar"))->default_value = node_obj["zFar"].GetFloat();
}

std::string perspectiveProjNodeName = "Perspective Projection";
std::shared_ptr<Node> PerspectiveProjNode(std::vector<std::shared_ptr<Node>>& s_Nodes)
{
    s_Nodes.emplace_back(new Node(GetNextId(), perspectiveProjNodeName.c_str(), true));
    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<PinValue<float>>>("fovy", new PinValue<float>("fovy", 0, GetNextId(), "FOV Y", PinType::Float, 60)));
    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<PinValue<float>>>("width", new PinValue<float>("width", 1, GetNextId(), "Width (For Aspect Ratio)", PinType::Float, 1920)));
    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<PinValue<float>>>("height", new PinValue<float>("height", 2, GetNextId(), "Height (For Aspect Ratio)", PinType::Float, 1080)));
    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<PinValue<float>>>("zNear", new PinValue<float>("zNear", 3, GetNextId(), "Z Near", PinType::Float, 0.000001)));
    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<PinValue<float>>>("zFar", new PinValue<float>("zFar", 4, GetNextId(), "Z Far", PinType::Float, 10000)));

    s_Nodes.back()->outputs.insert(std::pair<std::string, std::shared_ptr<PinValue<glm::mat4>>>("proj", new PinValue<glm::mat4>("proj", 0, GetNextId(), "Projection", PinType::Matrix4x4, glm::mat4(1.0))));

    s_Nodes.back()->node_funcs = std::make_shared<PerspectiveProjNode_Func>();
    std::dynamic_pointer_cast<PerspectiveProjNode_Func>(s_Nodes.back()->node_funcs)->parent_node = s_Nodes.back();

    s_Nodes.back()->node_funcs->Initialize();

    BuildNode(s_Nodes.back());

    return s_Nodes.back();
}





void LookAtNode_Func::Delete()
{
    parent_node = nullptr;
}

void LookAtNode_Func::NoFlowUpdatePinsValues()
{
    glm::vec3 position = GetInputPinValue<glm::vec3>(parent_node, "position");
    float yaw = GetInputPinValue<float>(parent_node, "yaw");
    float pitch = GetInputPinValue<float>(parent_node, "pitch");
    bool is_degrees = GetInputPinValue<bool>(parent_node, "is_degrees");

    if (position != p_position || yaw != p_yaw || pitch != p_pitch || is_degrees != p_is_degrees)
    {
        p_position = position;
        p_yaw = yaw;
        p_pitch = pitch;
        p_is_degrees = is_degrees;

        glm::vec3 front;
        if (is_degrees)
        {
            front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
            front.y = sin(glm::radians(pitch));
            front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        }
        else
        {
            front.x = cos(yaw) * cos(pitch);
            front.y = sin(pitch);
            front.z = sin(yaw) * cos(pitch);
        }
        front = glm::normalize(front);
        glm::vec3 right = glm::normalize(glm::cross(front, glm::vec3(0.0, 1.0, 0.0)));
        glm::vec3 up = glm::normalize(glm::cross(right, front));

        glm::mat4 lookAt = glm::lookAt(position, position + front, up);
        std::dynamic_pointer_cast<PinValue<glm::mat4>>(parent_node->outputs.at("out"))->value = lookAt;
    }
}

void LookAtNode_Func::SaveNodeData(rapidjson::Writer<rapidjson::StringBuffer>& writer)
{
    glm::vec3 position_value = std::dynamic_pointer_cast<PinValue<glm::vec3>>(parent_node->inputs.at("position"))->default_value;
    writer.Key("x");
    writer.Double(position_value.x);
    writer.Key("y");
    writer.Double(position_value.y);
    writer.Key("z");
    writer.Double(position_value.z);

    writer.Key("yaw");
    writer.Double(std::dynamic_pointer_cast<PinValue<float>>(parent_node->inputs.at("yaw"))->default_value);
    writer.Key("pitch");
    writer.Double(std::dynamic_pointer_cast<PinValue<float>>(parent_node->inputs.at("pitch"))->default_value);
    writer.Key("is_degrees");
    writer.Bool(std::dynamic_pointer_cast<PinValue<bool>>(parent_node->inputs.at("is_degrees"))->default_value);
}

void LookAtNode_Func::LoadNodeData(rapidjson::Value& node_obj)
{
    float x = node_obj["x"].GetFloat();
    float y = node_obj["y"].GetFloat();
    float z = node_obj["z"].GetFloat();
    std::dynamic_pointer_cast<PinValue<glm::vec3>>(parent_node->inputs.at("position"))->default_value = glm::vec3(x, y, z);

    std::dynamic_pointer_cast<PinValue<float>>(parent_node->inputs.at("yaw"))->default_value = node_obj["yaw"].GetFloat();
    std::dynamic_pointer_cast<PinValue<float>>(parent_node->inputs.at("pitch"))->default_value = node_obj["pitch"].GetFloat();
    std::dynamic_pointer_cast<PinValue<bool>>(parent_node->inputs.at("is_degrees"))->default_value = node_obj["is_degrees"].GetBool();
}

std::string lookAtNodeName = "Look At Matrix";
std::shared_ptr<Node> LookAtNode(std::vector<std::shared_ptr<Node>>& s_Nodes)
{
    s_Nodes.emplace_back(new Node(GetNextId(), lookAtNodeName.c_str(), true));
    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<PinValue<glm::vec3>>>("position", new PinValue<glm::vec3>("position", 0, GetNextId(), "Position", PinType::Vector3, glm::vec3(0, 0, 0))));
    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<PinValue<float>>>("yaw", new PinValue<float>("yaw", 1, GetNextId(), "Yaw", PinType::Float, 0)));
    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<PinValue<float>>>("pitch", new PinValue<float>("pitch", 2, GetNextId(), "Pitch", PinType::Float, 0)));
    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<PinValue<bool>>>("is_degrees", new PinValue<bool>("is_degrees", 3, GetNextId(), "Is Degrees ?", PinType::Bool, true)));

    s_Nodes.back()->outputs.insert(std::pair<std::string, std::shared_ptr<PinValue<glm::mat4>>>("out", new PinValue<glm::mat4>("out", 0, GetNextId(), "Matrix", PinType::Matrix4x4, glm::mat4(1.0))));

    s_Nodes.back()->node_funcs = std::make_shared<LookAtNode_Func>();
    std::dynamic_pointer_cast<LookAtNode_Func>(s_Nodes.back()->node_funcs)->parent_node = s_Nodes.back();

    s_Nodes.back()->node_funcs->Initialize();

    BuildNode(s_Nodes.back());

    return s_Nodes.back();
}





void MatricesNodes_SearchSetup(std::vector<SearchNodeObj>& search_nodes_vector)
{
    std::function<std::shared_ptr<Node>(std::vector<std::shared_ptr<Node>>&)> func_1 = Mat4IdentityNode;
    std::vector<std::string> keywords_1{ "Matrix4", "Identity", "Math" };
    search_nodes_vector.push_back(SearchNodeObj("Mat 4 - Identity", "Matrix 4x4", keywords_1, func_1));

    std::function<std::shared_ptr<Node>(std::vector<std::shared_ptr<Node>>&)> func_2 = Mat4TranslateNode;
    std::vector<std::string> keywords_2{ "Matrix4", "Translate", "Math" };
    search_nodes_vector.push_back(SearchNodeObj("Mat 4 - Translate", "Matrix 4x4", keywords_2, func_2));

    std::function<std::shared_ptr<Node>(std::vector<std::shared_ptr<Node>>&)> func_3 = Mat4ScaleNode;
    std::vector<std::string> keywords_3{ "Matrix4", "Scale", "Math" };
    search_nodes_vector.push_back(SearchNodeObj("Mat 4 - Scale", "Matrix 4x4", keywords_3, func_3));

    std::function<std::shared_ptr<Node>(std::vector<std::shared_ptr<Node>>&)> func_4 = Mat4RotateNode;
    std::vector<std::string> keywords_4{ "Matrix4", "Rotate", "Math" };
    search_nodes_vector.push_back(SearchNodeObj("Mat 4 - Rotate", "Matrix 4x4", keywords_4, func_4));

    std::function<std::shared_ptr<Node>(std::vector<std::shared_ptr<Node>>&)> func_5 = Mat4TransformNode;
    std::vector<std::string> keywords_5{ "Matrix4", "Transform", "Math" };
    search_nodes_vector.push_back(SearchNodeObj("Mat 4 - Transform", "Matrix 4x4", keywords_5, func_5));

    std::function<std::shared_ptr<Node>(std::vector<std::shared_ptr<Node>>&)> func_6 = OrthoProjNode;
    std::vector<std::string> keywords_6{ "Orthographic", "Projection", "Matrix4" };
    search_nodes_vector.push_back(SearchNodeObj("Orthographic Projection", "Matrix 4x4", keywords_6, func_6));

    std::function<std::shared_ptr<Node>(std::vector<std::shared_ptr<Node>>&)> func_7 = PerspectiveProjNode;
    std::vector<std::string> keywords_7{ "Perspective", "Projection", "Matrix4" };
    search_nodes_vector.push_back(SearchNodeObj("Perspective Projection", "Matrix 4x4", keywords_7, func_7));

    std::function<std::shared_ptr<Node>(std::vector<std::shared_ptr<Node>>&)> func_8 = LookAtNode;
    std::vector<std::string> keywords_8{ "Look", "At", "Matrix4" };
    search_nodes_vector.push_back(SearchNodeObj("Look At Matrix", "Matrix 4x4", keywords_8, func_8));
}

std::shared_ptr<Node> MatricesNodes_LoadSetup(std::vector<std::shared_ptr<Node>>& s_Nodes, std::string node_key)
{
    std::shared_ptr<Node> loaded_node = nullptr;
    if (loaded_node == nullptr && node_key.rfind(mat4IdentityNodeName, 0) == 0) {
        loaded_node = Mat4IdentityNode(s_Nodes);
    }
    else if (loaded_node == nullptr && node_key.rfind(mat4TranslateNodeName, 0) == 0) {
        loaded_node = Mat4TranslateNode(s_Nodes);
    }
    else if (loaded_node == nullptr && node_key.rfind(mat4ScaleNodeName, 0) == 0) {
        loaded_node = Mat4ScaleNode(s_Nodes);
    }
    else if (loaded_node == nullptr && node_key.rfind(mat4RotateNodeName, 0) == 0) {
        loaded_node = Mat4RotateNode(s_Nodes);
    }
    else if (loaded_node == nullptr && node_key.rfind(mat4TransformNodeName, 0) == 0) {
        loaded_node = Mat4TransformNode(s_Nodes);
    }
    else if (loaded_node == nullptr && node_key.rfind(orthoProjNodeName, 0) == 0) {
        loaded_node = OrthoProjNode(s_Nodes);
    }
    else if (loaded_node == nullptr && node_key.rfind(perspectiveProjNodeName, 0) == 0) {
        loaded_node = PerspectiveProjNode(s_Nodes);
    }
    else if (loaded_node == nullptr && node_key.rfind(lookAtNodeName, 0) == 0) {
        loaded_node = LookAtNode(s_Nodes);
    }
    return loaded_node;
}
