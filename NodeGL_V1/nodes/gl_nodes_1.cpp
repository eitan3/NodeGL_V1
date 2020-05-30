#include "gl_nodes_1.h"

const char* filtering_params[] = { "GL_LINEAR", "GL_NEAREST" };
const char* warp_params[] = { "GL_CLAMP_TO_EDGE", "GL_REPEAT", "GL_MIRRORED_REPEAT", "GL_CLAMP_TO_BORDER" };

void GlMainLoop_Func::Initialize()
{
    object_prefix = GetInputPinValue<std::string>(parent_node, "name");
    output_width = GetInputPinValue<int>(parent_node, "width");
    output_height = GetInputPinValue<int>(parent_node, "height");
    current_min_param = (char*)filtering_params[0];
    current_mag_param = (char*)filtering_params[0];
    current_wrap_s = (char*)warp_params[0];
    current_wrap_t = (char*)warp_params[0];
    prev_current_min_param = (char*)filtering_params[0];
    prev_current_mag_param = (char*)filtering_params[0];
    prev_current_wrap_s = (char*)warp_params[0];
    prev_current_wrap_t = (char*)warp_params[0];
    SetupFrameBuffer();
}

void GlMainLoop_Func::Run(std::string called_pin)
{
    if (parent_node->error == "")
    {
        auto config = InstanceConfig::instance();
        int new_width = GetInputPinValue<int>(parent_node, "width");
        int new_height = GetInputPinValue<int>(parent_node, "height");
        if (new_width != output_width || new_height != output_height || current_min_param != prev_current_min_param || 
            current_mag_param != prev_current_mag_param || current_wrap_s != prev_current_wrap_s || current_wrap_t != prev_current_wrap_t)
        {
            output_width = new_width;
            output_height = new_height;
            prev_current_min_param = current_min_param;
            prev_current_mag_param = current_mag_param;
            prev_current_wrap_s = current_wrap_s;
            prev_current_wrap_t = current_wrap_t;
            DeleteFrameBuffer();
            SetupFrameBuffer();
        }

        std::string new_prefix = GetInputPinValue<std::string>(parent_node, "name");
        if (new_prefix != object_prefix)
        {
            config->RenameTextureKey(object_prefix + "_color", new_prefix + "_color");
            config->RenameTextureKey(object_prefix + "_depth", new_prefix + "_depth");
            config->RenameFrameBufferKey(object_prefix, new_prefix);
            object_prefix = new_prefix;
        }

        std::shared_ptr<PinValue<std::shared_ptr<TextureObject>>> output_pin = std::dynamic_pointer_cast<PinValue<std::shared_ptr<TextureObject>>>(parent_node->outputs.at("texture_out"));
        output_pin->value = config->GetTexture(object_prefix + "_color");
        std::shared_ptr<PinValue<std::shared_ptr<TextureObject>>> output_pin2 = std::dynamic_pointer_cast<PinValue<std::shared_ptr<TextureObject>>>(parent_node->outputs.at("depth_texture"));
        output_pin2->value = config->GetTexture(object_prefix + "_depth");

        // Get previous viewport and set new viewport
        GLint prev_viewport[4];
        glGetIntegerv(GL_VIEWPORT, prev_viewport);
        glViewport(0, 0, output_width, output_height);

        // Bind framebuffer
        config->current_framebuffer = object_prefix;
        GLuint new_framebuffer_id = config->GetFrameBuffer(config->current_framebuffer)->object_id;
        glBindFramebuffer(GL_FRAMEBUFFER, new_framebuffer_id);

        // Run next node
        RunNextNodeFunc(parent_node, "next");

        // Unbind frambebuffer and return to previous viewport
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glViewport(0, 0, prev_viewport[2], prev_viewport[3]);
        parent_node->info = "Texture name: '" + object_prefix + "'";
    }
    else
    {
        parent_node->info = "";
    }
}

void GlMainLoop_Func::Delete()
{
    DeleteFrameBuffer();
    parent_node = nullptr;
}

void GlMainLoop_Func::UpdateNodeInspector()
{
    if (ImGui::BeginTabItem("Texture Settings"))
    {
        auto paneWidth = ImGui::GetContentRegionAvailWidth();
        if (current_min_param == NULL)
            current_min_param = (char*)filtering_params[0];
        if (current_mag_param == NULL)
            current_mag_param = (char*)filtering_params[0];

        ImGui::TextUnformatted("Min Filter: ");
        ImGui::BeginHorizontal("##texture_min_filter_config_panel_1", ImVec2(paneWidth, 0), 1.0f);
        if (ImGui::BeginCombo("##min_filter_combo", current_min_param)) // The second parameter is the label previewed before opening the combo.
        {
            for (int n = 0; n < IM_ARRAYSIZE(filtering_params); n++)
            {
                bool is_selected = std::string(current_min_param) == std::string(filtering_params[n]); // You can store your selection however you want, outside or inside your objects
                if (ImGui::Selectable(filtering_params[n], is_selected))
                    current_min_param = (char*)filtering_params[n];
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
            for (int n = 0; n < IM_ARRAYSIZE(filtering_params); n++)
            {
                bool is_selected = std::string(current_mag_param) == std::string(filtering_params[n]); // You can store your selection however you want, outside or inside your objects
                if (ImGui::Selectable(filtering_params[n], is_selected))
                    current_mag_param = (char*)filtering_params[n];
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
            for (int n = 0; n < IM_ARRAYSIZE(warp_params); n++)
            {
                bool is_selected = std::string(current_wrap_s) == std::string(warp_params[n]); // You can store your selection however you want, outside or inside your objects
                if (ImGui::Selectable(warp_params[n], is_selected))
                    current_wrap_s = (char*)warp_params[n];
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
            for (int n = 0; n < IM_ARRAYSIZE(warp_params); n++)
            {
                bool is_selected = std::string(current_wrap_t) == std::string(warp_params[n]); // You can store your selection however you want, outside or inside your objects
                if (ImGui::Selectable(warp_params[n], is_selected))
                    current_wrap_t = (char*)warp_params[n];
                if (is_selected)
                    ImGui::SetItemDefaultFocus();   // You may set the initial focus when opening the combo (scrolling + for keyboard navigation support)
            }
            ImGui::EndCombo();
        }
        ImGui::EndHorizontal();
    }
}

void GlMainLoop_Func::SaveNodeData(rapidjson::Writer<rapidjson::StringBuffer>& writer)
{
    writer.Key("name");
    writer.String(std::dynamic_pointer_cast<PinValue<std::string>>(parent_node->inputs.at("name"))->default_value.c_str());
    writer.Key("width");
    writer.Uint(std::dynamic_pointer_cast<PinValue<int>>(parent_node->inputs.at("width"))->default_value);
    writer.Key("height");
    writer.Uint(std::dynamic_pointer_cast<PinValue<int>>(parent_node->inputs.at("height"))->default_value);
    writer.Key("current_min_param");
    writer.String(current_min_param);
    writer.Key("current_mag_param");
    writer.String(current_mag_param);
    writer.Key("current_wrap_s");
    writer.String(current_wrap_s);
    writer.Key("current_wrap_t");
    writer.String(current_wrap_t);
}

void GlMainLoop_Func::LoadNodeData(rapidjson::Value& node_obj)
{
    DeleteFrameBuffer();
    std::dynamic_pointer_cast<PinValue<std::string>>(parent_node->inputs.at("name"))->default_value = std::string(node_obj["name"].GetString());
    std::dynamic_pointer_cast<PinValue<int>>(parent_node->inputs.at("width"))->default_value = node_obj["width"].GetUint();
    std::dynamic_pointer_cast<PinValue<int>>(parent_node->inputs.at("height"))->default_value = node_obj["height"].GetUint();

    bool is_found = false;
    int index = 0;
    if (node_obj["current_min_param"].IsNull() == false)
    {
        current_min_param = (char*)node_obj["current_min_param"].GetString();
        for (int n = 0; n < IM_ARRAYSIZE(filtering_params) && is_found == false; n++)
        {
            is_found = std::string(current_min_param) == std::string(filtering_params[n]);
            index = n;
        }
    }
    if (is_found)
        current_min_param = (char*)filtering_params[index];
    else
        current_min_param = (char*)filtering_params[0];

    is_found = false;
    index = 0;
    if (node_obj["current_mag_param"].IsNull() == false)
    {
        current_mag_param = (char*)node_obj["current_mag_param"].GetString();
        for (int n = 0; n < IM_ARRAYSIZE(filtering_params) && is_found == false; n++)
        {
            is_found = std::string(current_mag_param) == std::string(filtering_params[n]);
            index = n;
        }
    }
    if (is_found)
        current_mag_param = (char*)filtering_params[index];
    else
        current_mag_param = (char*)filtering_params[0];

    is_found = false;
    index = 0;
    if (node_obj["current_wrap_s"].IsNull() == false)
    {
        current_wrap_s = (char*)node_obj["current_wrap_s"].GetString();
        for (int n = 0; n < IM_ARRAYSIZE(warp_params) && is_found == false; n++)
        {
            is_found = std::string(current_wrap_s) == std::string(warp_params[n]);
            index = n;
        }
    }
    if (is_found)
        current_wrap_s = (char*)warp_params[index];
    else
        current_wrap_s = (char*)warp_params[0];

    is_found = false;
    index = 0;
    if (node_obj["current_wrap_t"].IsNull() == false)
    {
        current_wrap_t = (char*)node_obj["current_wrap_t"].GetString();
        for (int n = 0; n < IM_ARRAYSIZE(warp_params) && is_found == false; n++)
        {
            is_found = std::string(current_wrap_t) == std::string(warp_params[n]);
            index = n;
        }
    }
    if (is_found)
        current_wrap_t = (char*)warp_params[index];
    else
        current_wrap_t = (char*)warp_params[0];

    SetupFrameBuffer();
}

void GlMainLoop_Func::SetupFrameBuffer()
{
    auto config = InstanceConfig::instance();
    GLuint framebuffer_id;
    GLuint renderedTexture;
    GLuint depthTexture;

    glGenFramebuffers(1, &framebuffer_id);
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer_id);

    glGenTextures(1, &renderedTexture);
    glBindTexture(GL_TEXTURE_2D, renderedTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, output_width, output_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
    glPixelStorei(GL_PACK_ALIGNMENT, 1);
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
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, renderedTexture, 0);
    glBindTexture(GL_TEXTURE_2D, 0);

    glGenTextures(1, &depthTexture);
    glBindTexture(GL_TEXTURE_2D, depthTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH32F_STENCIL8, output_width, output_height, 0, GL_DEPTH_STENCIL, GL_FLOAT_32_UNSIGNED_INT_24_8_REV, 0);
    glPixelStorei(GL_PACK_ALIGNMENT, 1);
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
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, depthTexture, 0);
    glBindTexture(GL_TEXTURE_2D, 0);
    
    // Set the list of draw buffers.
    GLenum DrawBuffers[2] = { GL_DEPTH_STENCIL_ATTACHMENT, GL_DEPTH_ATTACHMENT };
    glDrawBuffers(2, DrawBuffers);

    // Always check that our framebuffer is ok
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        parent_node->error = "Somehting went wrong with Gl Main Loop!!";
        parent_node->info = "";
        return;
    }

    config->InsertTexture(object_prefix + "_color", std::make_shared<TextureObject>(object_prefix + "_color", renderedTexture, output_width, output_height));
    config->InsertTexture(object_prefix + "_depth", std::make_shared<TextureObject>(object_prefix + "_depth", depthTexture, output_width, output_height));
    config->InsertFrameBuffer(object_prefix, std::make_shared<FrameBufferObject>(object_prefix, framebuffer_id));
    parent_node->error = "";
}

void GlMainLoop_Func::DeleteFrameBuffer()
{
    auto config = InstanceConfig::instance();
    config->DeleteTexture(object_prefix + "_color");
    config->DeleteTexture(object_prefix + "_depth");
    config->DeleteFrameBuffer(object_prefix);
}

std::string glMainLoopName = "GL Main Loop";
std::shared_ptr<Node> GlMainLoop(std::vector<std::shared_ptr<Node>>& s_Nodes)
{
    s_Nodes.emplace_back(new Node(GetNextId(), glMainLoopName.c_str(), ImColor(255, 128, 128)));

    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<PinValue<std::string>>>("name", new PinValue<std::string>("name", 0, GetNextId(), "Name", PinType::String, "glMainLoop_" + std::to_string(s_Nodes.back()->id.Get()))));
    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<PinValue<int>>>("width", new PinValue<int>("width", 1, GetNextId(), "Width", PinType::Int, 1920)));
    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<PinValue<int>>>("height", new PinValue<int>("height", 2, GetNextId(), "Height", PinType::Int, 1080)));
    s_Nodes.back()->outputs.insert(std::pair<std::string, std::shared_ptr<BasePin>>("next", new BasePin("next", 0, GetNextId(), "Next", PinType::Flow)));
    s_Nodes.back()->outputs.insert(std::pair<std::string, std::shared_ptr<PinValue<std::shared_ptr<TextureObject>>>>("texture_out", new PinValue<std::shared_ptr<TextureObject>>("texture_out", 1, GetNextId(), "Color Texture", PinType::TextureObject, nullptr)));
    s_Nodes.back()->outputs.insert(std::pair<std::string, std::shared_ptr<PinValue<std::shared_ptr<TextureObject>>>>("depth_texture", new PinValue<std::shared_ptr<TextureObject>>("depth_texture", 2, GetNextId(), "Depth Texture", PinType::TextureObject, nullptr)));

    s_Nodes.back()->node_funcs = std::make_shared<GlMainLoop_Func>();
    std::dynamic_pointer_cast<GlMainLoop_Func>(s_Nodes.back()->node_funcs)->parent_node = s_Nodes.back();

    s_Nodes.back()->node_funcs->Initialize();

    BuildNode(s_Nodes.back());

    return s_Nodes.back();
}





void GlClear_Func::Initialize()
{
}

void GlClear_Func::Run(std::string called_pin)
{
    float r = GetInputPinValue<float>(parent_node, "r");
    float g = GetInputPinValue<float>(parent_node, "g");
    float b = GetInputPinValue<float>(parent_node, "b");
    float a = GetInputPinValue<float>(parent_node, "a");
    if (r < 0)
        r = 0;
    if (r > 1)
        r = 1;
    if (g < 0)
        g = 0;
    if (g > 1)
        g = 1;
    if (b < 0)
        b = 0;
    if (b > 1)
        b = 1;
    if (a < 0)
        a = 0;
    if (a > 1)
        a = r;
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    RunNextNodeFunc(parent_node, "next");
}

void GlClear_Func::Delete()
{
    parent_node = nullptr;
}

void GlClear_Func::SaveNodeData(rapidjson::Writer<rapidjson::StringBuffer>& writer)
{
    writer.Key("r");
    writer.Double(std::dynamic_pointer_cast<PinValue<float>>(parent_node->inputs.at("r"))->default_value);
    writer.Key("g");
    writer.Double(std::dynamic_pointer_cast<PinValue<float>>(parent_node->inputs.at("g"))->default_value);
    writer.Key("b");
    writer.Double(std::dynamic_pointer_cast<PinValue<float>>(parent_node->inputs.at("b"))->default_value);
    writer.Key("a");
    writer.Double(std::dynamic_pointer_cast<PinValue<float>>(parent_node->inputs.at("a"))->default_value);
}

void GlClear_Func::LoadNodeData(rapidjson::Value& node_obj)
{
    std::dynamic_pointer_cast<PinValue<float>>(parent_node->inputs.at("r"))->default_value = node_obj["r"].GetFloat();
    std::dynamic_pointer_cast<PinValue<float>>(parent_node->inputs.at("g"))->default_value = node_obj["g"].GetFloat();
    std::dynamic_pointer_cast<PinValue<float>>(parent_node->inputs.at("b"))->default_value = node_obj["b"].GetFloat();
    std::dynamic_pointer_cast<PinValue<float>>(parent_node->inputs.at("a"))->default_value = node_obj["a"].GetFloat();
}

std::string glClearNodeName = "glClrear";
std::shared_ptr<Node> GlClearNode(std::vector<std::shared_ptr<Node>>& s_Nodes)
{
    s_Nodes.emplace_back(new Node(GetNextId(), glClearNodeName.c_str()));

    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<BasePin>>("enter", new BasePin("enter", 0, GetNextId(), "Enter", PinType::Flow)));
    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<PinValue<float>>>("r", new PinValue<float>("r", 1, GetNextId(), "R", PinType::Float, 0)));
    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<PinValue<float>>>("g", new PinValue<float>("g", 2, GetNextId(), "G", PinType::Float, 0)));
    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<PinValue<float>>>("b", new PinValue<float>("b", 3, GetNextId(), "B", PinType::Float, 0)));
    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<PinValue<float>>>("a", new PinValue<float>("a", 4, GetNextId(), "A", PinType::Float, 0)));
    s_Nodes.back()->outputs.insert(std::pair<std::string, std::shared_ptr<BasePin>>("next", new BasePin("next", 0, GetNextId(), "Next", PinType::Flow)));

    s_Nodes.back()->inputs.at("r")->always_expose = false;
    s_Nodes.back()->inputs.at("g")->always_expose = false;
    s_Nodes.back()->inputs.at("b")->always_expose = false;
    s_Nodes.back()->inputs.at("a")->always_expose = false;

    s_Nodes.back()->node_funcs = std::make_shared<GlClear_Func>();
    std::dynamic_pointer_cast<GlClear_Func>(s_Nodes.back()->node_funcs)->parent_node = s_Nodes.back();

    s_Nodes.back()->node_funcs->Initialize();

    BuildNode(s_Nodes.back());

    return s_Nodes.back();
}





void GlRenderToTexture_Func::Initialize()
{
    object_prefix = GetInputPinValue<std::string>(parent_node, "name");
    output_width = GetInputPinValue<int>(parent_node, "width");
    output_height = GetInputPinValue<int>(parent_node, "height");
    current_min_param = (char*)filtering_params[0];
    current_mag_param = (char*)filtering_params[0];
    current_wrap_s = (char*)warp_params[0];
    current_wrap_t = (char*)warp_params[0];
    prev_current_min_param = (char*)filtering_params[0];
    prev_current_mag_param = (char*)filtering_params[0];
    prev_current_wrap_s = (char*)warp_params[0];
    prev_current_wrap_t = (char*)warp_params[0];
    SetupFrameBuffer();
}

void GlRenderToTexture_Func::Run(std::string called_pin)
{
    if (parent_node->error == "")
    {
        auto config = InstanceConfig::instance();
        int new_width = GetInputPinValue<int>(parent_node, "width");
        int new_height = GetInputPinValue<int>(parent_node, "height");
        if (new_width != output_width || new_height != output_height || current_min_param != prev_current_min_param ||
            current_mag_param != prev_current_mag_param || current_wrap_s != prev_current_wrap_s || current_wrap_t != prev_current_wrap_t)
        {
            output_width = new_width;
            output_height = new_height;
            prev_current_min_param = current_min_param;
            prev_current_mag_param = current_mag_param;
            prev_current_wrap_s = current_wrap_s;
            prev_current_wrap_t = current_wrap_t;
            DeleteFrameBuffer();
            SetupFrameBuffer();
        }

        std::string new_prefix = GetInputPinValue<std::string>(parent_node, "name");
        if (new_prefix != object_prefix)
        {
            config->RenameTextureKey(object_prefix + "_color", new_prefix + "_color");
            config->RenameTextureKey(object_prefix + "_depth", new_prefix + "_depth");
            config->RenameFrameBufferKey(object_prefix, new_prefix);
            object_prefix = new_prefix;
        }

        std::shared_ptr<PinValue<std::shared_ptr<TextureObject>>> output_pin = std::dynamic_pointer_cast<PinValue<std::shared_ptr<TextureObject>>>(parent_node->outputs.at("texture_out"));
        output_pin->value = config->GetTexture(object_prefix + "_color");
        std::shared_ptr<PinValue<std::shared_ptr<TextureObject>>> output_pin2 = std::dynamic_pointer_cast<PinValue<std::shared_ptr<TextureObject>>>(parent_node->outputs.at("depth_texture"));
        output_pin2->value = config->GetTexture(object_prefix + "_depth");

        // Get previous viewport and set new viewport
        GLint prev_viewport[4];
        glGetIntegerv(GL_VIEWPORT, prev_viewport);
        glViewport(0, 0, output_width, output_height);

        // Bind framebuffer
        config->framebuffer_stack.push(config->current_framebuffer);
        config->current_framebuffer = object_prefix;
        GLuint new_framebuffer_id = config->GetFrameBuffer(config->current_framebuffer)->object_id;
        glBindFramebuffer(GL_FRAMEBUFFER, new_framebuffer_id);

        // Run next node
        RunNextNodeFunc(parent_node, "render_body");

        // Return to previous viewport and framebuffer
        std::string prev_framebuffer = config->framebuffer_stack.top();
        config->current_framebuffer = prev_framebuffer;
        config->framebuffer_stack.pop();
        GLuint prev_framebuffer_id = config->GetFrameBuffer(prev_framebuffer)->object_id;
        glBindFramebuffer(GL_FRAMEBUFFER, prev_framebuffer_id);
        glViewport(0, 0, prev_viewport[2], prev_viewport[3]);

        // Run next node
        RunNextNodeFunc(parent_node, "next");
        parent_node->info = "Texture name: '" + object_prefix + "'";
    }
    else
    {
        parent_node->info = "";
    }
}

void GlRenderToTexture_Func::Delete()
{
    DeleteFrameBuffer();
    parent_node = nullptr;
}

void GlRenderToTexture_Func::UpdateNodeInspector()
{
    if (ImGui::BeginTabItem("Texture Settings"))
    {
        auto paneWidth = ImGui::GetContentRegionAvailWidth();
        if (current_min_param == NULL)
            current_min_param = (char*)filtering_params[0];
        if (current_mag_param == NULL)
            current_mag_param = (char*)filtering_params[0];

        ImGui::TextUnformatted("Min Filter: ");
        ImGui::BeginHorizontal("##texture_min_filter_config_panel_1", ImVec2(paneWidth, 0), 1.0f);
        if (ImGui::BeginCombo("##min_filter_combo", current_min_param)) // The second parameter is the label previewed before opening the combo.
        {
            for (int n = 0; n < IM_ARRAYSIZE(filtering_params); n++)
            {
                bool is_selected = std::string(current_min_param) == std::string(filtering_params[n]); // You can store your selection however you want, outside or inside your objects
                if (ImGui::Selectable(filtering_params[n], is_selected))
                    current_min_param = (char*)filtering_params[n];
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
            for (int n = 0; n < IM_ARRAYSIZE(filtering_params); n++)
            {
                bool is_selected = std::string(current_mag_param) == std::string(filtering_params[n]); // You can store your selection however you want, outside or inside your objects
                if (ImGui::Selectable(filtering_params[n], is_selected))
                    current_mag_param = (char*)filtering_params[n];
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
            for (int n = 0; n < IM_ARRAYSIZE(warp_params); n++)
            {
                bool is_selected = std::string(current_wrap_s) == std::string(warp_params[n]); // You can store your selection however you want, outside or inside your objects
                if (ImGui::Selectable(warp_params[n], is_selected))
                    current_wrap_s = (char*)warp_params[n];
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
            for (int n = 0; n < IM_ARRAYSIZE(warp_params); n++)
            {
                bool is_selected = std::string(current_wrap_t) == std::string(warp_params[n]); // You can store your selection however you want, outside or inside your objects
                if (ImGui::Selectable(warp_params[n], is_selected))
                    current_wrap_t = (char*)warp_params[n];
                if (is_selected)
                    ImGui::SetItemDefaultFocus();   // You may set the initial focus when opening the combo (scrolling + for keyboard navigation support)
            }
            ImGui::EndCombo();
        }
        ImGui::EndHorizontal();
    }
}

void GlRenderToTexture_Func::SaveNodeData(rapidjson::Writer<rapidjson::StringBuffer>& writer)
{
    writer.Key("name");
    writer.String(std::dynamic_pointer_cast<PinValue<std::string>>(parent_node->inputs.at("name"))->default_value.c_str());
    writer.Key("width");
    writer.Uint(std::dynamic_pointer_cast<PinValue<int>>(parent_node->inputs.at("width"))->default_value);
    writer.Key("height");
    writer.Uint(std::dynamic_pointer_cast<PinValue<int>>(parent_node->inputs.at("height"))->default_value);
    writer.Key("current_min_param");
    writer.String(current_min_param);
    writer.Key("current_mag_param");
    writer.String(current_mag_param);
    writer.Key("current_wrap_s");
    writer.String(current_wrap_s);
    writer.Key("current_wrap_t");
    writer.String(current_wrap_t);
}

void GlRenderToTexture_Func::LoadNodeData(rapidjson::Value& node_obj)
{
    DeleteFrameBuffer();
    std::dynamic_pointer_cast<PinValue<std::string>>(parent_node->inputs.at("name"))->default_value = std::string(node_obj["name"].GetString());
    std::dynamic_pointer_cast<PinValue<int>>(parent_node->inputs.at("width"))->default_value = node_obj["width"].GetUint();
    std::dynamic_pointer_cast<PinValue<int>>(parent_node->inputs.at("height"))->default_value = node_obj["height"].GetUint();


    bool is_found = false;
    int index = 0;
    if (node_obj["current_min_param"].IsNull() == false)
    {
        current_min_param = (char*)node_obj["current_min_param"].GetString();
        for (int n = 0; n < IM_ARRAYSIZE(filtering_params) && is_found == false; n++)
        {
            is_found = std::string(current_min_param) == std::string(filtering_params[n]);
            index = n;
        }
    }
    if (is_found)
        current_min_param = (char*)filtering_params[index];
    else
        current_min_param = (char*)filtering_params[0];

    is_found = false;
    index = 0;
    if (node_obj["current_mag_param"].IsNull() == false)
    {
        current_mag_param = (char*)node_obj["current_mag_param"].GetString();
        for (int n = 0; n < IM_ARRAYSIZE(filtering_params) && is_found == false; n++)
        {
            is_found = std::string(current_mag_param) == std::string(filtering_params[n]);
            index = n;
        }
    }
    if (is_found)
        current_mag_param = (char*)filtering_params[index];
    else
        current_mag_param = (char*)filtering_params[0];

    is_found = false;
    index = 0;
    if (node_obj["current_wrap_s"].IsNull() == false)
    {
        current_wrap_s = (char*)node_obj["current_wrap_s"].GetString();
        for (int n = 0; n < IM_ARRAYSIZE(warp_params) && is_found == false; n++)
        {
            is_found = std::string(current_wrap_s) == std::string(warp_params[n]);
            index = n;
        }
    }
    if (is_found)
        current_wrap_s = (char*)warp_params[index];
    else
        current_wrap_s = (char*)warp_params[0];

    is_found = false;
    index = 0;
    if (node_obj["current_wrap_t"].IsNull() == false)
    {
        current_wrap_t = (char*)node_obj["current_wrap_t"].GetString();
        for (int n = 0; n < IM_ARRAYSIZE(warp_params) && is_found == false; n++)
        {
            is_found = std::string(current_wrap_t) == std::string(warp_params[n]);
            index = n;
        }
    }
    if (is_found)
        current_wrap_t = (char*)warp_params[index];
    else
        current_wrap_t = (char*)warp_params[0];

    SetupFrameBuffer();
}

void GlRenderToTexture_Func::SetupFrameBuffer()
{
    auto config = InstanceConfig::instance();
    GLuint framebuffer_id;
    GLuint renderedTexture;
    GLuint depthTexture;

    glGenFramebuffers(1, &framebuffer_id);
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer_id);

    glGenTextures(1, &renderedTexture);
    glBindTexture(GL_TEXTURE_2D, renderedTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, output_width, output_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
    glPixelStorei(GL_PACK_ALIGNMENT, 1);
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
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, renderedTexture, 0);
    glBindTexture(GL_TEXTURE_2D, 0);

    glGenTextures(1, &depthTexture);
    glBindTexture(GL_TEXTURE_2D, depthTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH32F_STENCIL8, output_width, output_height, 0, GL_DEPTH_STENCIL, GL_FLOAT_32_UNSIGNED_INT_24_8_REV, 0);
    glPixelStorei(GL_PACK_ALIGNMENT, 1);
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
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, depthTexture, 0);
    glBindTexture(GL_TEXTURE_2D, 0);

    // Set the list of draw buffers.
    GLenum DrawBuffers[2] = { GL_DEPTH_STENCIL_ATTACHMENT, GL_DEPTH_ATTACHMENT };
    glDrawBuffers(2, DrawBuffers);

    // Always check that our framebuffer is ok
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        parent_node->error = "Somehting went wrong with Gl Redner To Texture!!";
        parent_node->info = "";
        return;
    }

    config->InsertTexture(object_prefix + "_color", std::make_shared<TextureObject>(object_prefix + "_color", renderedTexture, output_width, output_height));
    config->InsertTexture(object_prefix + "_depth", std::make_shared<TextureObject>(object_prefix + "_depth", depthTexture, output_width, output_height));
    config->InsertFrameBuffer(object_prefix, std::make_shared<FrameBufferObject>(object_prefix, framebuffer_id));
    parent_node->error = "";
}

void GlRenderToTexture_Func::DeleteFrameBuffer()
{
    auto config = InstanceConfig::instance();
    config->DeleteTexture(object_prefix + "_color");
    config->DeleteTexture(object_prefix + "_depth");
    config->DeleteFrameBuffer(object_prefix);
}

std::string glRenderToTextureName = "GL Render To Texture";
std::shared_ptr<Node> GlRenderToTexture(std::vector<std::shared_ptr<Node>>& s_Nodes)
{
    s_Nodes.emplace_back(new Node(GetNextId(), glRenderToTextureName.c_str()));

    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<BasePin>>("enter", new BasePin("enter", 0, GetNextId(), "Enter", PinType::Flow)));
    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<PinValue<std::string>>>("name", new PinValue<std::string>("name", 1, GetNextId(), "Name", PinType::String, "glRenderToTexture_" + std::to_string(s_Nodes.back()->id.Get()))));
    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<PinValue<int>>>("width", new PinValue<int>("width", 2, GetNextId(), "Width", PinType::Int, 1920)));
    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<PinValue<int>>>("height", new PinValue<int>("height", 3, GetNextId(), "Height", PinType::Int, 1080)));

    s_Nodes.back()->outputs.insert(std::pair<std::string, std::shared_ptr<BasePin>>("render_body", new BasePin("render_body", 0, GetNextId(), "Render Body", PinType::Flow)));
    s_Nodes.back()->outputs.insert(std::pair<std::string, std::shared_ptr<BasePin>>("next", new BasePin("next", 1, GetNextId(), "After Rendering", PinType::Flow)));
    s_Nodes.back()->outputs.insert(std::pair<std::string, std::shared_ptr<PinValue<std::shared_ptr<TextureObject>>>>("texture_out", new PinValue<std::shared_ptr<TextureObject>>("texture_out", 2, GetNextId(), "Texture Object", PinType::TextureObject, nullptr)));
    s_Nodes.back()->outputs.insert(std::pair<std::string, std::shared_ptr<PinValue<std::shared_ptr<TextureObject>>>>("depth_texture", new PinValue<std::shared_ptr<TextureObject>>("depth_texture", 3, GetNextId(), "Depth Texture", PinType::TextureObject, nullptr)));

    s_Nodes.back()->node_funcs = std::make_shared<GlRenderToTexture_Func>();
    std::dynamic_pointer_cast<GlRenderToTexture_Func>(s_Nodes.back()->node_funcs)->parent_node = s_Nodes.back();

    s_Nodes.back()->node_funcs->Initialize();

    BuildNode(s_Nodes.back());

    return s_Nodes.back();
}



void GlNodes1_SearchSetup(std::vector<SearchNodeObj>& search_nodes_vector)
{
    std::function<std::shared_ptr<Node>(std::vector<std::shared_ptr<Node>>&)> func_1 = GlClearNode;
    std::vector<std::string> keywords_1{ "glClear", "Gl", "gl", "Clear" };
    search_nodes_vector.push_back(SearchNodeObj("GL Clear", "OpenGL Nodes", keywords_1, func_1));

    std::function<std::shared_ptr<Node>(std::vector<std::shared_ptr<Node>>&)> func_2 = GlRenderToTexture;
    std::vector<std::string> keywords_2{ "glRenderToTexture", "Gl", "gl", "Render", "To", "Texture" };
    search_nodes_vector.push_back(SearchNodeObj("GL Render To Texture", "OpenGL Nodes", keywords_2, func_2));
}

std::shared_ptr<Node> GlNodes1_LoadSetup(std::vector<std::shared_ptr<Node>>& s_Nodes, std::string node_key)
{
    std::shared_ptr<Node> loaded_node = nullptr;
    if (loaded_node == nullptr && node_key.rfind(glClearNodeName, 0) == 0) {
        loaded_node = GlClearNode(s_Nodes);
    }
    else if (loaded_node == nullptr && node_key.rfind(glRenderToTextureName, 0) == 0) {
        loaded_node = GlRenderToTexture(s_Nodes);
    }
    return loaded_node;
}
