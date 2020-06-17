#include "resources_nodes.h"

const char* resources_nodes_filtering_params[] = { "GL_LINEAR", "GL_NEAREST" };
const char* resources_nodes_warp_params[] = { "GL_CLAMP_TO_EDGE", "GL_REPEAT", "GL_MIRRORED_REPEAT", "GL_CLAMP_TO_BORDER" };

void Texture2DResourceNode_Func::Initialize()
{
    object_prefix = GetInputPinValue<std::string>(parent_node, "name");
    current_min_param = (char*)resources_nodes_filtering_params[0];
    current_mag_param = (char*)resources_nodes_filtering_params[0];
    current_wrap_s = (char*)resources_nodes_warp_params[0];
    current_wrap_t = (char*)resources_nodes_warp_params[0];
}

void Texture2DResourceNode_Func::Delete()
{
    DeleteResource();
    parent_node = nullptr;
}

void Texture2DResourceNode_Func::DeleteResource()
{
    auto config = InstanceConfig::instance();
    config->DeleteTexture(object_prefix);
}

void Texture2DResourceNode_Func::NoFlowUpdatePinsValues()
{
    //glm::vec2 pin_1_value = GetInputPinValue<glm::vec2>(parent_node, "in_1");
    //glm::vec2 out_val = glm::normalize(pin_1_value);
    //std::shared_ptr<PinValue<glm::vec2>> output_pin = std::dynamic_pointer_cast<PinValue<glm::vec2>>(parent_node->outputs.at("out"));
    //output_pin->value = out_val;
}

void Texture2DResourceNode_Func::UpdateNodeUI()
{
    auto config = InstanceConfig::instance();
    if (showImportWindow)
    {
        ImGui::OpenPopup("Select File");
        if (file_dialog.showFileDialog("Select File", imgui_addons::ImGuiFileBrowser::DialogMode::OPEN, ImVec2(700, 310), ".jpeg,.jpg,.png"))
        {
            //std::cout << file_dialog.selected_fn << std::endl;      // The name of the selected file or directory in case of Select Directory dialog mode
            //std::cout << file_dialog.selected_path << std::endl;    // The absolute path to the selected file

            current_min_param = (char*)resources_nodes_filtering_params[0];
            current_mag_param = (char*)resources_nodes_filtering_params[0];
            current_wrap_s = (char*)resources_nodes_warp_params[0];
            current_wrap_t = (char*)resources_nodes_warp_params[0];
            selected_filepath = file_dialog.selected_path;
            showImportWindow = false;
        }
        else
        {
            if (file_dialog.is_cancel)
            {
                showImportWindow = false;
            }
        }
    }

    std::string new_prefix = GetInputPinValue<std::string>(parent_node, "name");
    if (new_prefix != object_prefix)
    {
        config->RenameTextureKey(object_prefix, new_prefix);
        object_prefix = new_prefix;
    }

    if (filepath != "")
    {
        if (parent_node->outputs.count("out") == 0)
        {
            std::shared_ptr<TextureObject> new_obj = config->GetTexture(object_prefix);
            parent_node->outputs.insert(std::pair<std::string, std::shared_ptr<PinValue<std::shared_ptr<TextureObject>>>>("out", new PinValue<std::shared_ptr<TextureObject>>("out", 0, GetNextId(), "Texture Object", PinType::TextureObject, new_obj)));
            BuildNode(parent_node);
        }
        else
        {
            std::shared_ptr<TextureObject> new_obj = config->GetTexture(object_prefix);
            std::dynamic_pointer_cast<PinValue<std::shared_ptr<TextureObject>>>(parent_node->outputs.at("out"))->value = new_obj;
        }
    }
}

void Texture2DResourceNode_Func::TextureParamsGui(float paneWidth)
{
    ImGui::TextUnformatted("Min Filter: ");
    ImGui::BeginHorizontal("##texture_min_filter_config_panel_1", ImVec2(paneWidth, 0), 1.0f);
    if (ImGui::BeginCombo("##min_filter_combo", current_min_param)) // The second parameter is the label previewed before opening the combo.
    {
        for (int n = 0; n < IM_ARRAYSIZE(resources_nodes_filtering_params); n++)
        {
            bool is_selected = std::string(current_min_param) == std::string(resources_nodes_filtering_params[n]); // You can store your selection however you want, outside or inside your objects
            if (ImGui::Selectable(resources_nodes_filtering_params[n], is_selected))
                current_min_param = (char*)resources_nodes_filtering_params[n];
            if (is_selected)
                ImGui::SetItemDefaultFocus();   // You may set the initial focus when opening the combo (scrolling + for keyboard navigation support)
        }
        ImGui::EndCombo();
    }
    ImGui::EndHorizontal();

    ImGui::TextUnformatted("Mag Filter: ");
    ImGui::BeginHorizontal("##texture_mag_filter_config_panel_1", ImVec2(paneWidth, 0), 1.0f);
    if (ImGui::BeginCombo("##mag_filter_combo", current_mag_param)) // The second parameter is the label previewed before opening the combo.
    {
        for (int n = 0; n < IM_ARRAYSIZE(resources_nodes_filtering_params); n++)
        {
            bool is_selected = std::string(current_mag_param) == std::string(resources_nodes_filtering_params[n]); // You can store your selection however you want, outside or inside your objects
            if (ImGui::Selectable(resources_nodes_filtering_params[n], is_selected))
                current_mag_param = (char*)resources_nodes_filtering_params[n];
            if (is_selected)
                ImGui::SetItemDefaultFocus();   // You may set the initial focus when opening the combo (scrolling + for keyboard navigation support)
        }
        ImGui::EndCombo();
    }
    ImGui::EndHorizontal();

    ImGui::TextUnformatted("Wrap S: ");
    ImGui::BeginHorizontal("##texture_wrap_s_config_panel_1", ImVec2(paneWidth, 0), 1.0f);
    if (ImGui::BeginCombo("##wrap_s_combo", current_wrap_s)) // The second parameter is the label previewed before opening the combo.
    {
        for (int n = 0; n < IM_ARRAYSIZE(resources_nodes_warp_params); n++)
        {
            bool is_selected = std::string(current_wrap_s) == std::string(resources_nodes_warp_params[n]); // You can store your selection however you want, outside or inside your objects
            if (ImGui::Selectable(resources_nodes_warp_params[n], is_selected))
                current_wrap_s = (char*)resources_nodes_warp_params[n];
            if (is_selected)
                ImGui::SetItemDefaultFocus();   // You may set the initial focus when opening the combo (scrolling + for keyboard navigation support)
        }
        ImGui::EndCombo();
    }
    ImGui::EndHorizontal();

    ImGui::TextUnformatted("Wrap t: ");
    ImGui::BeginHorizontal("##texture_wrap_t_config_panel_1", ImVec2(paneWidth, 0), 1.0f);
    if (ImGui::BeginCombo("##wrap_t_combo", current_wrap_t)) // The second parameter is the label previewed before opening the combo.
    {
        for (int n = 0; n < IM_ARRAYSIZE(resources_nodes_warp_params); n++)
        {
            bool is_selected = std::string(current_wrap_t) == std::string(resources_nodes_warp_params[n]); // You can store your selection however you want, outside or inside your objects
            if (ImGui::Selectable(resources_nodes_warp_params[n], is_selected))
                current_wrap_t = (char*)resources_nodes_warp_params[n];
            if (is_selected)
                ImGui::SetItemDefaultFocus();   // You may set the initial focus when opening the combo (scrolling + for keyboard navigation support)
        }
        ImGui::EndCombo();
    }
    ImGui::EndHorizontal();
}

void Texture2DResourceNode_Func::ImportTexture()
{
    DeleteResource();

    auto config = InstanceConfig::instance();
    GLuint tex_id;
    int width;
    int height;
    int comp;
    stbi_uc* pixels = stbi_load(selected_filepath.c_str(), &width, &height, &comp, 4);

    glGenTextures(1, &tex_id);
    glBindTexture(GL_TEXTURE_2D, tex_id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
    glPixelStorei(GL_PACK_ALIGNMENT, 1);

    glBindTexture(GL_TEXTURE_2D, 0);

    config->InsertTexture(object_prefix, std::make_shared<TextureObject>(object_prefix, tex_id, width, height));
    stbi_image_free(pixels);
}

void Texture2DResourceNode_Func::SetUpParams()
{
    auto config = InstanceConfig::instance();
    if (config->GetTexture(object_prefix))
    {
        glBindTexture(GL_TEXTURE_2D, config->GetTexture(object_prefix)->object_id);

        if (current_min_param == "GL_LINEAR")
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        else if (current_min_param == "GL_NEAREST")
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

        if (current_mag_param == "GL_LINEAR")
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        else if (current_mag_param == "GL_NEAREST")
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        if (current_wrap_s == "GL_CLAMP_TO_EDGE")
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        else if (current_wrap_s == "GL_REPEAT")
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        else if (current_wrap_s == "GL_MIRRORED_REPEAT")
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
        else if (current_wrap_s == "GL_CLAMP_TO_BORDER")
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);

        if (current_wrap_t == "GL_CLAMP_TO_EDGE")
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        else if (current_wrap_t == "GL_REPEAT")
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        else if (current_wrap_t == "GL_MIRRORED_REPEAT")
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
        else if (current_wrap_t == "GL_CLAMP_TO_BORDER")
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

        config->GetTexture(object_prefix)->current_min_param = current_min_param;
        config->GetTexture(object_prefix)->current_mag_param = current_mag_param;
        config->GetTexture(object_prefix)->current_wrap_s = current_wrap_s;
        config->GetTexture(object_prefix)->current_wrap_t = current_wrap_t;
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}

void Texture2DResourceNode_Func::UpdateNodeInspector()
{
    auto config = InstanceConfig::instance();
    if (ImGui::BeginTabItem("Resource Settings"))
    {
        float paneWidth = ImGui::GetContentRegionAvailWidth();
        if (filepath == "")
        {
            if (selected_filepath != "")
            {
                ImGui::TextUnformatted(("File Path: " + selected_filepath).c_str());
            }
            
            std::string importText = "Select File";
            if (selected_filepath != "")
                importText = "Change File";
            if (ImGui::Button(importText.c_str()))
            {
                showImportWindow = true;
            }

            if (selected_filepath != "")
            {
                TextureParamsGui(paneWidth);
                if (ImGui::Button("Import"))
                {
                    ImportTexture();
                    SetUpParams();
                    filepath = selected_filepath;
                    selected_filepath = "";
                }
            }
        }
        else
        {
            ImGui::TextUnformatted(("File Path: " + filepath).c_str());
            if (selected_filepath != "")
            {
                ImGui::TextUnformatted(("Change To: " + selected_filepath).c_str());
            }

            if (ImGui::Button("Change File"))
            {
                showImportWindow = true;
            }

            TextureParamsGui(paneWidth);
            if ((selected_filepath != "" && selected_filepath != filepath) || config->GetTexture(object_prefix)->current_min_param != current_min_param ||
                config->GetTexture(object_prefix)->current_mag_param != current_mag_param ||
                config->GetTexture(object_prefix)->current_wrap_s != current_wrap_s ||
                config->GetTexture(object_prefix)->current_wrap_t != current_wrap_t)
            {
                if (ImGui::Button("Change"))
                {
                    if (selected_filepath != "" && selected_filepath != filepath)
                    {
                        ImportTexture();
                        filepath = selected_filepath;
                    }
                    if (config->GetTexture(object_prefix)->current_min_param != current_min_param ||
                        config->GetTexture(object_prefix)->current_mag_param != current_mag_param ||
                        config->GetTexture(object_prefix)->current_wrap_s != current_wrap_s ||
                        config->GetTexture(object_prefix)->current_wrap_t != current_wrap_t)
                        SetUpParams();
                    selected_filepath = "";
                }
            }
        }

    }
}

void Texture2DResourceNode_Func::SaveNodeData(rapidjson::Writer<rapidjson::StringBuffer>& writer)
{
    writer.Key("name");
    writer.String(std::dynamic_pointer_cast<PinValue<std::string>>(parent_node->inputs.at("name"))->default_value.c_str());
    writer.Key("filepath");
    writer.String(filepath.c_str());
    writer.Key("current_min_param");
    writer.String(current_min_param);
    writer.Key("current_mag_param");
    writer.String(current_mag_param);
    writer.Key("current_wrap_s");
    writer.String(current_wrap_s);
    writer.Key("current_wrap_t");
    writer.String(current_wrap_t);
}

void Texture2DResourceNode_Func::LoadNodeData(rapidjson::Value& node_obj)
{
    std::dynamic_pointer_cast<PinValue<std::string>>(parent_node->inputs.at("name"))->default_value = std::string(node_obj["name"].GetString());
    filepath = std::string(node_obj["filepath"].GetString());
    bool is_found = false;
    int index = 0;
    if (node_obj["current_min_param"].IsNull() == false)
    {
        current_min_param = (char*)node_obj["current_min_param"].GetString();
        for (int n = 0; n < IM_ARRAYSIZE(resources_nodes_filtering_params) && is_found == false; n++)
        {
            is_found = std::string(current_min_param) == std::string(resources_nodes_filtering_params[n]);
            index = n;
        }
    }
    if (is_found)
        current_min_param = (char*)resources_nodes_filtering_params[index];
    else
        current_min_param = (char*)resources_nodes_filtering_params[0];

    is_found = false;
    index = 0;
    if (node_obj["current_mag_param"].IsNull() == false)
    {
        current_mag_param = (char*)node_obj["current_mag_param"].GetString();
        for (int n = 0; n < IM_ARRAYSIZE(resources_nodes_filtering_params) && is_found == false; n++)
        {
            is_found = std::string(current_mag_param) == std::string(resources_nodes_filtering_params[n]);
            index = n;
        }
    }
    if (is_found)
        current_mag_param = (char*)resources_nodes_filtering_params[index];
    else
        current_mag_param = (char*)resources_nodes_filtering_params[0];

    is_found = false;
    index = 0;
    if (node_obj["current_wrap_s"].IsNull() == false)
    {
        current_wrap_s = (char*)node_obj["current_wrap_s"].GetString();
        for (int n = 0; n < IM_ARRAYSIZE(resources_nodes_warp_params) && is_found == false; n++)
        {
            is_found = std::string(current_wrap_s) == std::string(resources_nodes_warp_params[n]);
            index = n;
        }
    }
    if (is_found)
        current_wrap_s = (char*)resources_nodes_warp_params[index];
    else
        current_wrap_s = (char*)resources_nodes_warp_params[0];

    is_found = false;
    index = 0;
    if (node_obj["current_wrap_t"].IsNull() == false)
    {
        current_wrap_t = (char*)node_obj["current_wrap_t"].GetString();
        for (int n = 0; n < IM_ARRAYSIZE(resources_nodes_warp_params) && is_found == false; n++)
        {
            is_found = std::string(current_wrap_t) == std::string(resources_nodes_warp_params[n]);
            index = n;
        }
    }
    if (is_found)
        current_wrap_t = (char*)resources_nodes_warp_params[index];
    else
        current_wrap_t = (char*)resources_nodes_warp_params[0];

    if (filepath != "")
    {
        object_prefix = GetInputPinValue<std::string>(parent_node, "name");
        selected_filepath = filepath;
        ImportTexture();
        SetUpParams();
        selected_filepath = "";
    }
}

std::string texture2DResourceNodeName = "Texture2D Resource";
std::shared_ptr<Node> Texture2DResourceNode(std::vector<std::shared_ptr<Node>>& s_Nodes)
{
    s_Nodes.emplace_back(new Node(GetNextId(), texture2DResourceNodeName.c_str(), true));
    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<PinValue<std::string>>>("name", new PinValue<std::string>("name", 0, GetNextId(), "Name", PinType::String, "Texture2DResource_" + std::to_string(s_Nodes.back()->id.Get()))));

    s_Nodes.back()->node_funcs = std::make_shared<Texture2DResourceNode_Func>();
    std::dynamic_pointer_cast<Texture2DResourceNode_Func>(s_Nodes.back()->node_funcs)->parent_node = s_Nodes.back();

    s_Nodes.back()->node_funcs->Initialize();

    BuildNode(s_Nodes.back());

    return s_Nodes.back();
}





void ResourcesNodesSearchSetup(std::vector<SearchNodeObj>& search_nodes_vector)
{
    std::function<std::shared_ptr<Node>(std::vector<std::shared_ptr<Node>>&)> func_1 = Texture2DResourceNode;
    std::vector<std::string> keywords_1{ "Texture2D", "Resource" };
    search_nodes_vector.push_back(SearchNodeObj("Texture2D Resource", "Resources", keywords_1, func_1));
}

std::shared_ptr<Node> ResourcesNodesLoadSetup(std::vector<std::shared_ptr<Node>>& s_Nodes, std::string node_key)
{
    std::shared_ptr<Node> loaded_node = nullptr;
    if (loaded_node == nullptr && node_key.rfind(texture2DResourceNodeName, 0) == 0) {
        loaded_node = Texture2DResourceNode(s_Nodes);
    }
    return loaded_node;
}