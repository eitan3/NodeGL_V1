#include "shaders_nodes.h"

void CreateSahder_Func::Initialize()
{
    object_prefix = GetInputPinValue<std::string>(parent_node, "name");
    showShaderEditorWindow = false;
    showFileBrowserWindow = false;
    shader_obj = nullptr;
    editor.SetPalette(TextEditor::GetDarkPalette());
    is_compiled = false;
}

void CreateSahder_Func::Delete()
{
    DeleteShader();
    parent_node = nullptr;
}

void CreateSahder_Func::DeleteShader()
{
    if (shader_obj)
    {
        if (parent_node->outputs.size() > 0)
        {
            for (auto& output : parent_node->outputs)
            {
                for (int j = 0; j < output.second->links.size(); j++)
                {
                    ed::DeleteLink(output.second->links.at(j)->id);
                }
                output.second->node = nullptr;
                output.second->links.clear();
            }
        }
        parent_node->outputs.clear();
        shader_obj = nullptr;
        BuildNode(parent_node);
    }
}

void CreateSahder_Func::ShowFileBrowserWindow(bool* show)
{
    ImGui::OpenPopup("Open File");
    if (file_dialog.showFileDialog("Open File", imgui_addons::ImGuiFileBrowser::DialogMode::OPEN, ImVec2(700, 310), ".glsl,.txt"))
    {
        //std::cout << file_dialog.selected_fn << std::endl;      // The name of the selected file or directory in case of Select Directory dialog mode
        //std::cout << file_dialog.selected_path << std::endl;    // The absolute path to the selected file

        std::string shaderCode;
        std::ifstream file(file_dialog.selected_path, std::ios::in);

        if (!file.good()) {
            std::cout << "Can't read file " << file_dialog.selected_path.c_str() << std::endl;
            std::terminate();
        }

        file.seekg(0, std::ios::end);
        shaderCode.resize((unsigned int)file.tellg());
        file.seekg(0, std::ios::beg);
        file.read(&shaderCode[0], shaderCode.size());
        file.close();
        editor.SetText(shaderCode);
        showFileBrowserWindow = false;
    }
    else
    {
        if (file_dialog.is_cancel)
        {
            showFileBrowserWindow = false;
        }
    }
}

const char* shaders_types[] = { "Vertex Shader", "Fragment Shader" };
void CreateSahder_Func::ShowShaderEditorWindow(bool* show)
{
    if (!ImGui::Begin((std::string("Shader Editor - ") + parent_node->name + std::to_string(parent_node->id.Get())).c_str(), show))
    {
        ImGui::End();
        return;
    }
    std::string prefix = "##shader_editor_" + parent_node->name + std::to_string(parent_node->id.Get());
    std::remove_if(prefix.begin(), prefix.end(), isspace);
    ImGui::SetWindowSize(ImVec2(768, 512));
    auto paneWidth = ImGui::GetContentRegionAvailWidth();

    ImGui::BeginHorizontal((prefix + "_buttons_panel").c_str(), ImVec2(paneWidth, 0), 1.0f);
    if (ImGui::Button("Compile"))
    {
        CompileShader();
    }
    if (ImGui::Button("Load"))
    {
        showFileBrowserWindow = true;
    }
    if (ImGui::Button("Clean Errors"))
    {
        TextEditor::ErrorMarkers errors = TextEditor::ErrorMarkers();
        editor.SetErrorMarkers(errors);
    }
    ImGui::EndHorizontal();

    if (current_shader_type == NULL)
        current_shader_type = shaders_types[0];
    if (ImGui::BeginCombo("##combo", current_shader_type)) // The second parameter is the label previewed before opening the combo.
    {
        for (int n = 0; n < IM_ARRAYSIZE(shaders_types); n++)
        {
            bool is_selected = (current_shader_type == shaders_types[n]); // You can store your selection however you want, outside or inside your objects
            if (ImGui::Selectable(shaders_types[n], is_selected))
                current_shader_type = shaders_types[n];
                if (is_selected)
                    ImGui::SetItemDefaultFocus();   // You may set the initial focus when opening the combo (scrolling + for keyboard navigation support)
        }
        ImGui::EndCombo();
    }

    auto cpos = editor.GetCursorPosition();
    ImGui::Text("%6d/%-6d %6d lines  | %s | %s | %s ", cpos.mLine + 1, cpos.mColumn + 1, editor.GetTotalLines(),
        editor.IsOverwrite() ? "Ovr" : "Ins",
        editor.CanUndo() ? "*" : " ",
        editor.GetLanguageDefinition().mName.c_str());

    editor.Render("##TextEditor");

    ImGui::End();
}

void CreateSahder_Func::CompileShader()
{
    DeleteShader();
    TextEditor::ErrorMarkers errors = TextEditor::ErrorMarkers();
    editor.SetErrorMarkers(errors);

    int compile_result = 0;
    GLuint shader_id = 0;
    if (current_shader_type == shaders_types[0])
        shader_id = glCreateShader(GL_VERTEX_SHADER);
    if (current_shader_type == shaders_types[1])
        shader_id = glCreateShader(GL_FRAGMENT_SHADER);
    char* shader_code_ptr = (char*)editor.GetText().c_str();
    int   shader_code_size = editor.GetText().size();

    glShaderSource(shader_id, 1, &shader_code_ptr, &shader_code_size);
    glCompileShader(shader_id);
    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &compile_result);

    //daca exista erori output la consola
    if (compile_result == GL_FALSE)
    {
        int info_log_length = 0;
        glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &info_log_length);
        std::vector<char> shader_log(info_log_length);
        glGetShaderInfoLog(shader_id, info_log_length, NULL, &shader_log[0]);
        std::string log_error(shader_log.begin(), shader_log.end());
        TextEditor::ErrorMarkers errors = TextEditor::ErrorMarkers();
        for (int line_i = 0; line_i < editor.GetTotalLines(); line_i++)
            errors.insert(std::pair<int, std::string>(line_i + 1, log_error));
        editor.SetErrorMarkers(errors);
        glDeleteShader(shader_id);
        is_compiled = false;
    }
    else
    {
        if (current_shader_type == shaders_types[0])
        {
            std::shared_ptr<ShaderObject> new_obj = std::make_shared<ShaderObject>(object_prefix, shader_id, editor.GetText(), PinType::VertexShaderObject);
            parent_node->outputs.insert(std::pair<std::string, std::shared_ptr<PinValue<std::shared_ptr<ShaderObject>>>>("shader_out", new PinValue<std::shared_ptr<ShaderObject>>("shader_out", 0, GetNextId(), "Vertex Shader Object", PinType::VertexShaderObject, new_obj)));
            shader_obj = new_obj;
        }
        else if (current_shader_type == shaders_types[1])
        {
            std::shared_ptr<ShaderObject> new_obj = std::make_shared<ShaderObject>(object_prefix, shader_id, editor.GetText(), PinType::FragmentShaderObject);
            parent_node->outputs.insert(std::pair<std::string, std::shared_ptr<PinValue<std::shared_ptr<ShaderObject>>>>("shader_out", new PinValue<std::shared_ptr<ShaderObject>>("shader_out", 0, GetNextId(), "Fragment Shader Object", PinType::FragmentShaderObject, new_obj)));
            shader_obj = new_obj;
        }
        is_compiled = true;
        BuildNode(parent_node);
    }
}

void CreateSahder_Func::UpdateNodeUI()
{
    if (showFileBrowserWindow)
    {
        ShowFileBrowserWindow(&showFileBrowserWindow);
    }
    else if (showShaderEditorWindow)
    {
        ShowShaderEditorWindow(&showShaderEditorWindow);
    }

    std::string new_object_prefix = GetInputPinValue<std::string>(parent_node, "name");
    if (object_prefix != new_object_prefix)
    {
        object_prefix = new_object_prefix;
        if (shader_obj)
            shader_obj->object_name = object_prefix;
    }
}

void CreateSahder_Func::UpdateNodeInspector()
{
    if (ImGui::BeginTabItem("Shader Configs"))
    {
        if (ImGui::Button("Shader Editor"))
        {
            showShaderEditorWindow = true;
        }
    }
}

void CreateSahder_Func::SaveNodeData(rapidjson::Writer<rapidjson::StringBuffer>& writer)
{
    writer.Key("name");
    writer.String(std::dynamic_pointer_cast<PinValue < std::string >> (parent_node->inputs.at("name"))->default_value.c_str());
    writer.Key("current_shader_type");
    writer.String(current_shader_type);
    writer.Key("shader_source");
    writer.String(editor.GetText().c_str());
    writer.Key("is_compiled");
    writer.Bool(is_compiled);
}

void CreateSahder_Func::LoadNodeData(rapidjson::Value& node_obj)
{
    std::dynamic_pointer_cast<PinValue<std::string>>(parent_node->inputs.at("name"))->default_value = std::string(node_obj["name"].GetString());
    current_shader_type = node_obj["current_shader_type"].GetString();
    editor.SetText(std::string(node_obj["shader_source"].GetString()));
    bool tmp_is_compiled = node_obj["is_compiled"].GetBool();

    bool is_found = false;
    int index = 0;
    for (int n = 0; n < IM_ARRAYSIZE(shaders_types) && is_found == false; n++)
    {
        is_found = std::string(current_shader_type) == std::string(shaders_types[n]);
        index = n;
    }
    if (is_found)
        current_shader_type = (char*)shaders_types[index];
    else
        current_shader_type = (char*)shaders_types[0];

    if (tmp_is_compiled)
    {
        CompileShader();
    }
}

std::string createSahderName = "Create Shader";
std::shared_ptr<Node> CreateSahder(std::vector<std::shared_ptr<Node>>& s_Nodes)
{
    s_Nodes.emplace_back(new Node(GetNextId(), createSahderName.c_str(), true));
    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<PinValue<std::string>>>("name", new PinValue<std::string>("name", 0, GetNextId(), "Shader Name", PinType::String, "ShaderObject_" + std::to_string(s_Nodes.back()->id.Get()))));
    s_Nodes.back()->inputs.at("name")->always_expose = false;

    s_Nodes.back()->node_funcs = std::make_shared<CreateSahder_Func>();
    std::dynamic_pointer_cast<CreateSahder_Func>(s_Nodes.back()->node_funcs)->parent_node = s_Nodes.back();

    s_Nodes.back()->node_funcs->Initialize();

    BuildNode(s_Nodes.back());

    return s_Nodes.back();
}





void CreateProgram_Func::Initialize()
{
    object_prefix = GetInputPinValue<std::string>(parent_node, "name");
    program_obj = nullptr;
}

void CreateProgram_Func::Delete()
{
    DeleteProgram();
    parent_node = nullptr;
}

void CreateProgram_Func::DeleteProgram()
{
    if (program_obj)
    {
        if (parent_node->outputs.size() > 0)
        {
            for (auto& output : parent_node->outputs)
            {
                for (int j = 0; j < output.second->links.size(); j++)
                {
                    ed::DeleteLink(output.second->links.at(j)->id);
                }
                output.second->node = nullptr;
                output.second->links.clear();
            }
        }
        parent_node->outputs.clear();
        program_obj = nullptr;
        BuildNode(parent_node);
    }
}

void CreateProgram_Func::NoFlowUpdatePinsValues()
{
}

void CreateProgram_Func::UpdateNodeUI()
{
    std::shared_ptr<ShaderObject> vertex_shader = GetInputPinValue<std::shared_ptr<ShaderObject>>(parent_node, "vs");
    std::shared_ptr<ShaderObject> fragment_shader = GetInputPinValue<std::shared_ptr<ShaderObject>>(parent_node, "fs");

    if (vertex_shader && fragment_shader)
    {
        if (program_obj == nullptr)
        {
            CreateProgram(vertex_shader->object_id, fragment_shader->object_id);
        }
        else if (vertex_shader->object_id != program_obj->vertex_shader || fragment_shader->object_id != program_obj->fragment_shader)
        {
            CreateProgram(vertex_shader->object_id, fragment_shader->object_id);
        }
    }
    else
    {
        DeleteProgram();
    }

    std::string new_object_prefix = GetInputPinValue<std::string>(parent_node, "name");
    if (object_prefix != new_object_prefix)
    {
        object_prefix = new_object_prefix;
        if (program_obj)
            program_obj->object_name = object_prefix;
    }
}

void CreateProgram_Func::SaveNodeData(rapidjson::Writer<rapidjson::StringBuffer>& writer)
{
    writer.Key("name");
    writer.String(std::dynamic_pointer_cast<PinValue < std::string >> (parent_node->inputs.at("name"))->default_value.c_str());
}

void CreateProgram_Func::LoadNodeData(rapidjson::Value& node_obj)
{
    std::dynamic_pointer_cast<PinValue<std::string>>(parent_node->inputs.at("name"))->default_value = std::string(node_obj["name"].GetString());
}

void CreateProgram_Func::CreateProgram(GLuint vertex_shader, GLuint fragment_shader)
{
    DeleteProgram();

    int  link_result = 0;
    //create the program handle, attatch the shaders and link it
    GLuint program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);

    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &link_result);

    if (link_result == GL_FALSE)
    {
        int info_log_length = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &info_log_length);
        std::vector<char> program_log(info_log_length);
        glGetProgramInfoLog(program, info_log_length, NULL, &program_log[0]);
        std::string str_error(program_log.begin(), program_log.end());
        parent_node->error = str_error;
    }
    else
    {
        std::shared_ptr<ProgramObject> new_obj = std::make_shared<ProgramObject>(object_prefix, program, vertex_shader, fragment_shader);
        parent_node->outputs.insert(std::pair<std::string, std::shared_ptr<PinValue<std::shared_ptr<ProgramObject>>>>("prog_out", new PinValue<std::shared_ptr<ProgramObject>>("prog_out", 0, GetNextId(), "Program Object", PinType::ProgramObject, new_obj)));
        program_obj = new_obj;
        BuildNode(parent_node);
        parent_node->error = "";
    }
}

std::string createProgramName = "Create Program";
std::shared_ptr<Node> CreateProgram(std::vector<std::shared_ptr<Node>>& s_Nodes)
{
    s_Nodes.emplace_back(new Node(GetNextId(), createProgramName.c_str(), true));
    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<PinValue<std::string>>>("name", new PinValue<std::string>("name", 0, GetNextId(), "Program Name", PinType::String, "ProgramObject_" + std::to_string(s_Nodes.back()->id.Get()))));
    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<PinValue<std::shared_ptr<ShaderObject>>>>("vs", new PinValue<std::shared_ptr<ShaderObject>>("vs", 1, GetNextId(), "Vertex Shader", PinType::VertexShaderObject, nullptr)));
    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<PinValue<std::shared_ptr<ShaderObject>>>>("fs", new PinValue<std::shared_ptr<ShaderObject>>("fs", 2, GetNextId(), "Fragment Shader", PinType::FragmentShaderObject, nullptr)));

    s_Nodes.back()->inputs.at("name")->always_expose = false;

    s_Nodes.back()->node_funcs = std::make_shared<CreateProgram_Func>();
    std::dynamic_pointer_cast<CreateProgram_Func>(s_Nodes.back()->node_funcs)->parent_node = s_Nodes.back();

    s_Nodes.back()->node_funcs->Initialize();

    BuildNode(s_Nodes.back());

    return s_Nodes.back();
}





void ShadersNodesSearchSetup(std::vector<SearchNodeObj>& search_nodes_vector)
{
    std::function<std::shared_ptr<Node>(std::vector<std::shared_ptr<Node>>&)> func_1 = CreateSahder;
    std::vector<std::string> keywords_1{ "Create", "Shader" };
    search_nodes_vector.push_back(SearchNodeObj("Create Shader", "Shaders Nodes", keywords_1, func_1));

    std::function<std::shared_ptr<Node>(std::vector<std::shared_ptr<Node>>&)> func_2 = CreateProgram;
    std::vector<std::string> keywords_2{ "Create", "Program" };
    search_nodes_vector.push_back(SearchNodeObj("Create Program", "Shaders Nodes", keywords_2, func_2));
}

std::shared_ptr<Node> ShadersNodesLoadSetup(std::vector<std::shared_ptr<Node>>& s_Nodes, std::string node_key)
{
    std::shared_ptr<Node> loaded_node = nullptr;
    if (loaded_node == nullptr && node_key.rfind(createProgramName, 0) == 0) {
        loaded_node = CreateProgram(s_Nodes);
    }
    else if (loaded_node == nullptr && node_key.rfind(createSahderName, 0) == 0) {
        loaded_node = CreateSahder(s_Nodes);
    }
    return loaded_node;
}
