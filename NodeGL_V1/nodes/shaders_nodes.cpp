#include "shaders_nodes.h"

const char* shaders_types[] = { "Vertex Shader", "Fragment Shader" };
void CreateSahder_Func::Initialize()
{
    object_prefix = GetInputPinValue<std::string>(parent_node, "name");
    showShaderEditorWindow = false;
    showFileBrowserWindow = false;
    shader_obj = nullptr;
    editor.SetPalette(TextEditor::GetDarkPalette());
    current_shader_type = shaders_types[0];
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
    std::string shader_code_str = editor.GetText();
    char* shader_code_ptr = (char*)shader_code_str.c_str();
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
    auto config = InstanceConfig::instance();

    writer.Key("name");
    writer.String(std::dynamic_pointer_cast<PinValue < std::string >> (parent_node->inputs.at("name"))->default_value.c_str());
    writer.Key("current_shader_type");
    writer.String(current_shader_type);
    writer.Key("is_compiled");
    writer.Bool(is_compiled);

   /* std::string shader_path = config->project_name.substr(0, config->project_name.size() - 4) + "_ShaderObject_" + std::to_string(parent_node->id.Get()) + ".glsl";
    std::ofstream out(shader_path);
    out << editor.GetText().substr(0, editor.GetText().size() - 7).c_str();
    out.close();
    
    writer.String(shader_path.c_str());*/

    writer.Key("shader_source");
    writer.String(editor.GetText().c_str());
}

void CreateSahder_Func::LoadNodeData(rapidjson::Value& node_obj)
{
    std::dynamic_pointer_cast<PinValue<std::string>>(parent_node->inputs.at("name"))->default_value = std::string(node_obj["name"].GetString());
    current_shader_type = node_obj["current_shader_type"].GetString();

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

    /*std::string shader_path = std::string(node_obj["shader_source"].GetString());
    std::ifstream t(shader_path);
    std::string shader_source((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
    editor.SetText(shader_source.c_str());*/
    editor.SetText(node_obj["shader_source"].GetString());

    bool tmp_is_compiled = node_obj["is_compiled"].GetBool();
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
            CreateProgram(vertex_shader, fragment_shader);
        }
        else if (vertex_shader->object_id != program_obj->vs->object_id || fragment_shader->object_id != program_obj->fs->object_id)
        {
            CreateProgram(vertex_shader, fragment_shader);
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

void CreateProgram_Func::CreateProgram(std::shared_ptr<ShaderObject> vertex_shader, std::shared_ptr<ShaderObject> fragment_shader)
{
    DeleteProgram();

    int  link_result = 0;
    //create the program handle, attatch the shaders and link it
    GLuint program = glCreateProgram();
    glAttachShader(program, vertex_shader->object_id);
    glAttachShader(program, fragment_shader->object_id);

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





void BindProgram_Func::Run(std::string called_pin)
{
    auto config = InstanceConfig::instance();
    std::shared_ptr<ProgramObject> in_program = GetInputPinValue<std::shared_ptr<ProgramObject>>(parent_node, "program");
    if (in_program)
    {
        config->programs_stack.push(config->current_program);
        
        glUseProgram(in_program->object_id);
        RunNextNodeFunc(parent_node, "in_bind");
        in_program->current_texture = 0;

        GLuint prev_prog = config->programs_stack.top();
        config->programs_stack.pop();
        glUseProgram(prev_prog);
    }
    RunNextNodeFunc(parent_node, "complete");
}

void BindProgram_Func::Delete()
{
    parent_node = nullptr;
}

std::string bindProgramNodeName = "Bind Program";
std::shared_ptr<Node> BindProgramNode(std::vector<std::shared_ptr<Node>>& s_Nodes)
{
    s_Nodes.emplace_back(new Node(GetNextId(), bindProgramNodeName.c_str()));

    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<BasePin>>("enter", new BasePin("enter", 0, GetNextId(), "Enter", PinType::Flow)));
    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<PinValue<std::shared_ptr<ProgramObject>>>>("program", new PinValue<std::shared_ptr<ProgramObject>>("program", 1, GetNextId(), "Program", PinType::ProgramObject, nullptr)));
    
    s_Nodes.back()->outputs.insert(std::pair<std::string, std::shared_ptr<BasePin>>("in_bind", new BasePin("in_bind", 0, GetNextId(), "Bind Context", PinType::Flow)));
    s_Nodes.back()->outputs.insert(std::pair<std::string, std::shared_ptr<BasePin>>("complete", new BasePin("complete", 1, GetNextId(), "Complete Binding", PinType::Flow)));

    s_Nodes.back()->node_funcs = std::make_shared<BindProgram_Func>();
    std::dynamic_pointer_cast<BindProgram_Func>(s_Nodes.back()->node_funcs)->parent_node = s_Nodes.back();

    s_Nodes.back()->node_funcs->Initialize();

    BuildNode(s_Nodes.back());

    return s_Nodes.back();
}





void BindProgramWithUniforms_Func::Run(std::string called_pin)
{
    auto config = InstanceConfig::instance();
    std::shared_ptr<ProgramObject> in_program = GetInputPinValue<std::shared_ptr<ProgramObject>>(parent_node, "program");
    if (in_program)
    {
        if (in_program->object_id != prev_program)
        {
            ProgramChanged();
        }

        config->programs_stack.push(config->current_program);

        glUseProgram(in_program->object_id);

        for (int n = 0; n < in_program->uniforms_arr.size(); n++)
        {
            std::string uniName = in_program->uniforms_arr.at(n).name;
            std::string pin_key = "uni_pin_" + std::to_string(n);
            if (parent_node->inputs.at(pin_key)->type == PinType::Bool)
            {
                bool uni_value = GetInputPinValue<bool>(parent_node, pin_key);
                glUniform1i(glGetUniformLocation(in_program->object_id, uniName.c_str()), uni_value);

                /*GLint get_values[1];
                glGetUniformiv(in_program->object_id, glGetUniformLocation(in_program->object_id, current_uniform.c_str()), get_values);
                std::cout << glGetError() << ", " << get_values[0] << std::endl;*/
            }
            else if (parent_node->inputs.at(pin_key)->type == PinType::Int)
            {
                int uni_value = GetInputPinValue<int>(parent_node, pin_key);
                glUniform1i(glGetUniformLocation(in_program->object_id, uniName.c_str()), uni_value);

                /*GLint get_values[1];
                glGetUniformiv(in_program->object_id, glGetUniformLocation(in_program->object_id, current_uniform.c_str()), get_values);
                std::cout << glGetError() << ", " << get_values[0] << std::endl;*/
            }
            else if (parent_node->inputs.at(pin_key)->type == PinType::Float)
            {
                float uni_value = GetInputPinValue<float>(parent_node, pin_key);
                glUniform1f(glGetUniformLocation(in_program->object_id, uniName.c_str()), uni_value);

                /*GLfloat get_values[1];
                glGetUniformfv(in_program->object_id, glGetUniformLocation(in_program->object_id, current_uniform.c_str()), get_values);
                std::cout << glGetError() << ", " << get_values[0] << std::endl;*/
            }
            else if (parent_node->inputs.at(pin_key)->type == PinType::Vector2)
            {
                glm::vec2 uni_value = GetInputPinValue<glm::vec2>(parent_node, pin_key);
                glUniform2fv(glGetUniformLocation(in_program->object_id, uniName.c_str()), 1, glm::value_ptr(uni_value));

                /*GLfloat get_values[2];
                glGetUniformfv(in_program->object_id, glGetUniformLocation(in_program->object_id, current_uniform.c_str()), get_values);
                std::cout << glGetError() << ", " << get_values[0] << ", " << get_values[1] << std::endl;*/
            }
            else if (parent_node->inputs.at(pin_key)->type == PinType::Vector3)
            {
                glm::vec3 uni_value = GetInputPinValue<glm::vec3>(parent_node, pin_key);
                glUniform3fv(glGetUniformLocation(in_program->object_id, uniName.c_str()), 1, glm::value_ptr(uni_value));

                /*GLfloat get_values[3];
                glGetUniformfv(in_program->object_id, glGetUniformLocation(in_program->object_id, current_uniform.c_str()), get_values);
                std::cout << glGetError() << ", " << get_values[0] << ", " << get_values[1] << ", " << get_values[2] << std::endl;*/
            }
            else if (parent_node->inputs.at(pin_key)->type == PinType::Vector4)
            {
                glm::vec4 uni_value = GetInputPinValue<glm::vec4>(parent_node, pin_key);
                glUniform4fv(glGetUniformLocation(in_program->object_id, uniName.c_str()), 1, glm::value_ptr(uni_value));

                //GLfloat get_values[4];
                //glGetUniformfv(in_program->object_id, glGetUniformLocation(in_program->object_id, current_uniform.c_str()), get_values);
                //std::cout << glGetError() << ", " << get_values[0] << ", " << get_values[1] << ", " << get_values[2] << ", " << get_values[3] << std::endl;
            }
            else if (parent_node->inputs.at(pin_key)->type == PinType::Matrix4x4)
            {
                glm::mat4 uni_value = GetInputPinValue<glm::mat4>(parent_node, pin_key);
                glUniformMatrix4fv(glGetUniformLocation(in_program->object_id, uniName.c_str()), 1, false, &uni_value[0][0]);

                /*GLfloat get_values[16];
                glGetUniformfv(in_program->object_id, glGetUniformLocation(in_program->object_id, current_uniform.c_str()), get_values);
                std::cout << glGetError();
                for (int i = 0; i < 16; i++)
                    std::cout << ", " << get_values[i];
                std::cout << std::endl;*/
            }
            else if (parent_node->inputs.at(pin_key)->type == PinType::TextureObject)
            {
                std::shared_ptr<TextureObject> uni_value = GetInputPinValue<std::shared_ptr<TextureObject>>(parent_node, pin_key);
                if (uni_value)
                {
                    glActiveTexture(GL_TEXTURE0 + in_program->current_texture);
                    glBindTexture(GL_TEXTURE_2D, uni_value->object_id);
                    glUniform1i(glGetUniformLocation(in_program->object_id, uniName.c_str()), in_program->current_texture);
                    in_program->current_texture++;
                }
            }
        }

        RunNextNodeFunc(parent_node, "in_bind");
        in_program->current_texture = 0;

        GLuint prev_prog = config->programs_stack.top();
        config->programs_stack.pop();
        glUseProgram(prev_prog);
    }
    RunNextNodeFunc(parent_node, "complete");
}

void BindProgramWithUniforms_Func::Delete()
{
    parent_node = nullptr;
    tmp_loaded_value.clear();
}

void BindProgramWithUniforms_Func::UpdateNodeUI()
{
    std::shared_ptr<ProgramObject> in_program = GetInputPinValue<std::shared_ptr<ProgramObject>>(parent_node, "program");
    if (in_program)
    {
        if (in_program->object_id != prev_program)
        {
            ProgramChanged();
        }
    }
    else
    {
        prev_program = 0;
        DeletePins();
    }
}

void BindProgramWithUniforms_Func::SaveNodeData(rapidjson::Writer<rapidjson::StringBuffer>& writer)
{
    std::shared_ptr<ProgramObject> in_program = GetInputPinValue<std::shared_ptr<ProgramObject>>(parent_node, "program");
    if (in_program)
    {
        writer.Key("uniforms");
        writer.StartArray();
        for (int n = 0; n < in_program->uniforms_arr.size(); n++)
        {
            std::string uniName = in_program->uniforms_arr.at(n).name;
            std::string pin_key = "uni_pin_" + std::to_string(n);
            writer.StartArray();
            writer.String(uniName.c_str());
            writer.String(PinTypeToString(in_program->uniforms_arr.at(n).type).c_str());

            if (parent_node->inputs.at(pin_key)->type == PinType::Bool)
            {
                bool uni_value = std::dynamic_pointer_cast<PinValue<bool>>(parent_node->inputs.at(pin_key))->default_value;
                writer.Bool(uni_value);
            }
            else if (parent_node->inputs.at(pin_key)->type == PinType::Int)
            {
                int uni_value = std::dynamic_pointer_cast<PinValue<int>>(parent_node->inputs.at(pin_key))->default_value;
                writer.Int(uni_value);
            }
            else if (parent_node->inputs.at(pin_key)->type == PinType::Float)
            {
                float uni_value = std::dynamic_pointer_cast<PinValue<float>>(parent_node->inputs.at(pin_key))->default_value;
                writer.Double(uni_value);
            }
            if (parent_node->inputs.at(pin_key)->type == PinType::Vector2)
            {
                glm::vec2 uni_value = std::dynamic_pointer_cast<PinValue<glm::vec2>>(parent_node->inputs.at(pin_key))->default_value;
                writer.StartArray();
                writer.Double(uni_value.x);
                writer.Double(uni_value.y);
                writer.EndArray();
            }
            else if (parent_node->inputs.at(pin_key)->type == PinType::Vector3)
            {
                glm::vec3 uni_value = std::dynamic_pointer_cast<PinValue<glm::vec3>>(parent_node->inputs.at(pin_key))->default_value;
                writer.StartArray();
                writer.Double(uni_value.x);
                writer.Double(uni_value.y);
                writer.Double(uni_value.z);
                writer.EndArray();
            }
            else if (parent_node->inputs.at(pin_key)->type == PinType::Vector4)
            {
                glm::vec4 uni_value = std::dynamic_pointer_cast<PinValue<glm::vec4>>(parent_node->inputs.at(pin_key))->default_value;
                writer.StartArray();
                writer.Double(uni_value.x);
                writer.Double(uni_value.y);
                writer.Double(uni_value.z);
                writer.Double(uni_value.w);
                writer.EndArray();
            }
            else if (parent_node->inputs.at(pin_key)->type == PinType::Matrix4x4)
            {
                glm::mat4 uni_value = std::dynamic_pointer_cast<PinValue<glm::mat4>>(parent_node->inputs.at(pin_key))->default_value;
                writer.StartArray();
                const float* pSource = (const float*)glm::value_ptr(uni_value);
                for (int i = 0; i < 16; ++i)
                    writer.Double(pSource[i]);
                writer.EndArray();
            }
            writer.EndArray();
        }
        writer.EndArray();
    }
}

void BindProgramWithUniforms_Func::LoadNodeData(rapidjson::Value& node_obj)
{
    for (int uni_i = 0; uni_i < node_obj["uniforms"].GetArray().Size(); uni_i++)
    {
        std::string uniform_name = node_obj["uniforms"].GetArray()[uni_i][0].GetString();
        PinType uniform_type = StringToPinType(node_obj["uniforms"].GetArray()[uni_i][1].GetString());
        
        if (uniform_type == PinType::Bool)
        {
            bool uni_value = node_obj["uniforms"].GetArray()[uni_i][2].GetBool();
            std::shared_ptr<PlaceholderValue<bool>> tmp_ph = std::make_shared<PlaceholderValue<bool>>("tmp", uniform_type, uni_value);
            tmp_loaded_value.insert(std::pair<std::string, std::shared_ptr<BasePlaceholder>>(uniform_name, tmp_ph));
        }
        else if (uniform_type == PinType::Int)
        {
            int uni_value = node_obj["uniforms"].GetArray()[uni_i][2].GetInt();
            std::shared_ptr<PlaceholderValue<int>> tmp_ph = std::make_shared<PlaceholderValue<int>>("tmp", uniform_type, uni_value);
            tmp_loaded_value.insert(std::pair<std::string, std::shared_ptr<BasePlaceholder>>(uniform_name, tmp_ph));
        }
        else if (uniform_type == PinType::Float)
        {
            float uni_value = node_obj["uniforms"].GetArray()[uni_i][2].GetFloat();
            std::shared_ptr<PlaceholderValue<float>> tmp_ph = std::make_shared<PlaceholderValue<float>>("tmp", uniform_type, uni_value);
            tmp_loaded_value.insert(std::pair<std::string, std::shared_ptr<BasePlaceholder>>(uniform_name, tmp_ph));
        }
        if (uniform_type == PinType::Vector2)
        {
            glm::vec2 uni_value;
            uni_value.x = node_obj["uniforms"].GetArray()[uni_i][2].GetArray()[0].GetFloat();
            uni_value.y = node_obj["uniforms"].GetArray()[uni_i][2].GetArray()[1].GetFloat();
            std::shared_ptr<PlaceholderValue<glm::vec2>> tmp_ph = std::make_shared<PlaceholderValue<glm::vec2>>("tmp", uniform_type, uni_value);
            tmp_loaded_value.insert(std::pair<std::string, std::shared_ptr<BasePlaceholder>>(uniform_name, tmp_ph));
        }
        else if (uniform_type == PinType::Vector3)
        {
            glm::vec3 uni_value;
            uni_value.x = node_obj["uniforms"].GetArray()[uni_i][2].GetArray()[0].GetFloat();
            uni_value.y = node_obj["uniforms"].GetArray()[uni_i][2].GetArray()[1].GetFloat();
            uni_value.z = node_obj["uniforms"].GetArray()[uni_i][2].GetArray()[2].GetFloat();
            std::shared_ptr<PlaceholderValue<glm::vec3>> tmp_ph = std::make_shared<PlaceholderValue<glm::vec3>>("tmp", uniform_type, uni_value);
            tmp_loaded_value.insert(std::pair<std::string, std::shared_ptr<BasePlaceholder>>(uniform_name, tmp_ph));
        }
        else if (uniform_type == PinType::Vector4)
        {
            glm::vec4 uni_value;
            uni_value.x = node_obj["uniforms"].GetArray()[uni_i][2].GetArray()[0].GetFloat();
            uni_value.y = node_obj["uniforms"].GetArray()[uni_i][2].GetArray()[1].GetFloat();
            uni_value.z = node_obj["uniforms"].GetArray()[uni_i][2].GetArray()[2].GetFloat();
            uni_value.w = node_obj["uniforms"].GetArray()[uni_i][2].GetArray()[3].GetFloat();
            std::shared_ptr<PlaceholderValue<glm::vec4>> tmp_ph = std::make_shared<PlaceholderValue<glm::vec4>>("tmp", uniform_type, uni_value);
            tmp_loaded_value.insert(std::pair<std::string, std::shared_ptr<BasePlaceholder>>(uniform_name, tmp_ph));
        }
        else if (uniform_type == PinType::Matrix4x4)
        {
            glm::mat4 uni_value;
            float* pSource = (float*)glm::value_ptr(uni_value);
            for (int i = 0; i < 16; ++i)
            {
                pSource[i] = node_obj["uniforms"].GetArray()[uni_i][2].GetArray()[i].GetFloat();
            }
            std::shared_ptr<PlaceholderValue<glm::mat4>> tmp_ph = std::make_shared<PlaceholderValue<glm::mat4>>("tmp", uniform_type, uni_value);
            tmp_loaded_value.insert(std::pair<std::string, std::shared_ptr<BasePlaceholder>>(uniform_name, tmp_ph));
        }
    }
    continue_loading = true;
}

void BindProgramWithUniforms_Func::ProgramChanged()
{
    DeletePins();
    std::shared_ptr<ProgramObject> in_program = GetInputPinValue<std::shared_ptr<ProgramObject>>(parent_node, "program");
    if (in_program)
    {
        prev_program = in_program->object_id;
        if (in_program->uniforms_arr.size() > 0)
        {
            for (int n = 0; n < in_program->uniforms_arr.size(); n++)
            {
                std::string uniName = in_program->uniforms_arr.at(n).name;
                parent_node->inputs.insert(std::pair<std::string, std::shared_ptr<PinValue<float>>>("uni_pin_" + std::to_string(n), new PinValue<float>("uni_pin_" + std::to_string(n), n + 2, GetNextId(), uniName.c_str(), PinType::Float, 0)));
                UtilsChangePinType(parent_node, PinKind::Input, "uni_pin_" + std::to_string(n), in_program->uniforms_arr.at(n).type);
            }
            BuildNode(parent_node);

            if (continue_loading && tmp_loaded_value.size() > 0)
            {
                for (int n = 0; n < in_program->uniforms_arr.size(); n++)
                {
                    std::string uniName = in_program->uniforms_arr.at(n).name;
                    std::string pin_key = "uni_pin_" + std::to_string(n);
                    PinType uniform_type = in_program->uniforms_arr.at(n).type;
                    if (uniform_type == PinType::Bool)
                    {
                        if (tmp_loaded_value.count(uniName) > 0)
                            std::dynamic_pointer_cast<PinValue<bool>>(parent_node->inputs.at(pin_key))->default_value = std::dynamic_pointer_cast<PlaceholderValue<bool>>(tmp_loaded_value.at(uniName))->value;
                    }
                    else if (uniform_type == PinType::Int)
                    {
                        if (tmp_loaded_value.count(uniName) > 0)
                            std::dynamic_pointer_cast<PinValue<int>>(parent_node->inputs.at(pin_key))->default_value = std::dynamic_pointer_cast<PlaceholderValue<int>>(tmp_loaded_value.at(uniName))->value;
                    }
                    else if (uniform_type == PinType::Float)
                    {
                        if (tmp_loaded_value.count(uniName) > 0)
                            std::dynamic_pointer_cast<PinValue<float>>(parent_node->inputs.at(pin_key))->default_value = std::dynamic_pointer_cast<PlaceholderValue<float>>(tmp_loaded_value.at(uniName))->value;
                    }
                    if (uniform_type == PinType::Vector2)
                    {
                        if (tmp_loaded_value.count(uniName) > 0)
                            std::dynamic_pointer_cast<PinValue<glm::vec2>>(parent_node->inputs.at(pin_key))->default_value = std::dynamic_pointer_cast<PlaceholderValue<glm::vec2>>(tmp_loaded_value.at(uniName))->value;
                    }
                    else if (uniform_type == PinType::Vector3)
                    {
                        if (tmp_loaded_value.count(uniName) > 0)
                            std::dynamic_pointer_cast<PinValue<glm::vec3>>(parent_node->inputs.at(pin_key))->default_value = std::dynamic_pointer_cast<PlaceholderValue<glm::vec3>>(tmp_loaded_value.at(uniName))->value;
                    }
                    else if (uniform_type == PinType::Vector4)
                    {
                        if (tmp_loaded_value.count(uniName) > 0)
                            std::dynamic_pointer_cast<PinValue<glm::vec4>>(parent_node->inputs.at(pin_key))->default_value = std::dynamic_pointer_cast<PlaceholderValue<glm::vec4>>(tmp_loaded_value.at(uniName))->value;
                    }
                    else if (uniform_type == PinType::Matrix4x4)
                    {
                        if (tmp_loaded_value.count(uniName) > 0)
                            std::dynamic_pointer_cast<PinValue<glm::mat4>>(parent_node->inputs.at(pin_key))->default_value = std::dynamic_pointer_cast<PlaceholderValue<glm::mat4>>(tmp_loaded_value.at(uniName))->value;
                    }
                }
                tmp_loaded_value.clear();
                continue_loading = false;
            }
        }
    }
}

void BindProgramWithUniforms_Func::DeletePins()
{
    unsigned int started_size = parent_node->inputs.size();
    for (int i = 2; i < started_size; i++)
    {
        std::string pin_key = "uni_pin_" + std::to_string(i - 2);
        if (parent_node->inputs.count(pin_key) > 0)
        {
            for (int j = 0; j < parent_node->inputs.at(pin_key)->links.size(); j++)
            {
                ed::DeleteLink(parent_node->inputs.at(pin_key)->links.at(j)->id);
            }
            parent_node->inputs.at(pin_key)->node = nullptr;
            parent_node->inputs.at(pin_key)->links.clear();

            parent_node->inputs.erase(pin_key);
        }
    }
    if (started_size > 2)
        BuildNode(parent_node);
}

std::string bindProgramWithUniformsNodeName = "Bind Program With Uniforms";
std::shared_ptr<Node> BindProgramWithUniformsNode(std::vector<std::shared_ptr<Node>>& s_Nodes)
{
    s_Nodes.emplace_back(new Node(GetNextId(), bindProgramWithUniformsNodeName.c_str()));

    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<BasePin>>("enter", new BasePin("enter", 0, GetNextId(), "Enter", PinType::Flow)));
    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<PinValue<std::shared_ptr<ProgramObject>>>>("program", new PinValue<std::shared_ptr<ProgramObject>>("program", 1, GetNextId(), "Program", PinType::ProgramObject, nullptr)));

    s_Nodes.back()->outputs.insert(std::pair<std::string, std::shared_ptr<BasePin>>("in_bind", new BasePin("in_bind", 0, GetNextId(), "Bind Context", PinType::Flow)));
    s_Nodes.back()->outputs.insert(std::pair<std::string, std::shared_ptr<BasePin>>("complete", new BasePin("complete", 1, GetNextId(), "Complete Binding", PinType::Flow)));

    s_Nodes.back()->node_funcs = std::make_shared<BindProgramWithUniforms_Func>();
    std::dynamic_pointer_cast<BindProgramWithUniforms_Func>(s_Nodes.back()->node_funcs)->parent_node = s_Nodes.back();

    s_Nodes.back()->node_funcs->Initialize();

    BuildNode(s_Nodes.back());

    return s_Nodes.back();
}






void SetProgramUniformNode_Func::Run(std::string called_pin)
{
    std::shared_ptr<ProgramObject> in_program = GetInputPinValue<std::shared_ptr<ProgramObject>>(parent_node, "program");
    if (in_program)
    {
        if (in_program->object_id != prev_program)
        {
            ProgramChanged();
            continue_loading = false;
        }
        
        if (parent_node->inputs.count("uni_pin") > 0 && current_uniform != "")
        {
            if (parent_node->inputs.at("uni_pin")->type == PinType::Bool)
            {
                bool uni_value = GetInputPinValue<bool>(parent_node, "uni_pin");
                glUniform1i(glGetUniformLocation(in_program->object_id, current_uniform.c_str()), uni_value);

                /*GLint get_values[1];
                glGetUniformiv(in_program->object_id, glGetUniformLocation(in_program->object_id, current_uniform.c_str()), get_values);
                std::cout << glGetError() << ", " << get_values[0] << std::endl;*/
            }
            else if (parent_node->inputs.at("uni_pin")->type == PinType::Int)
            {
                int uni_value = GetInputPinValue<int>(parent_node, "uni_pin");
                glUniform1i(glGetUniformLocation(in_program->object_id, current_uniform.c_str()), uni_value);
                
                /*GLint get_values[1];
                glGetUniformiv(in_program->object_id, glGetUniformLocation(in_program->object_id, current_uniform.c_str()), get_values);
                std::cout << glGetError() << ", " << get_values[0] << std::endl;*/
            }
            else if (parent_node->inputs.at("uni_pin")->type == PinType::Float)
            {
                float uni_value = GetInputPinValue<float>(parent_node, "uni_pin");
                glUniform1f(glGetUniformLocation(in_program->object_id, current_uniform.c_str()), uni_value);

                /*GLfloat get_values[1];
                glGetUniformfv(in_program->object_id, glGetUniformLocation(in_program->object_id, current_uniform.c_str()), get_values);
                std::cout << glGetError() << ", " << get_values[0] << std::endl;*/
            }
            else if (parent_node->inputs.at("uni_pin")->type == PinType::Vector2)
            {
                glm::vec2 uni_value = GetInputPinValue<glm::vec2>(parent_node, "uni_pin");
                glUniform2fv(glGetUniformLocation(in_program->object_id, current_uniform.c_str()), 1, glm::value_ptr(uni_value));
                
                /*GLfloat get_values[2];
                glGetUniformfv(in_program->object_id, glGetUniformLocation(in_program->object_id, current_uniform.c_str()), get_values);
                std::cout << glGetError() << ", " << get_values[0] << ", " << get_values[1] << std::endl;*/
            }
            else if (parent_node->inputs.at("uni_pin")->type == PinType::Vector3)
            {
                glm::vec3 uni_value = GetInputPinValue<glm::vec3>(parent_node, "uni_pin");
                glUniform3fv(glGetUniformLocation(in_program->object_id, current_uniform.c_str()), 1, glm::value_ptr(uni_value));
                
                /*GLfloat get_values[3];
                glGetUniformfv(in_program->object_id, glGetUniformLocation(in_program->object_id, current_uniform.c_str()), get_values);
                std::cout << glGetError() << ", " << get_values[0] << ", " << get_values[1] << ", " << get_values[2] << std::endl;*/
            }
            else if (parent_node->inputs.at("uni_pin")->type == PinType::Vector4)
            {
                glm::vec4 uni_value = GetInputPinValue<glm::vec4>(parent_node, "uni_pin");
                glUniform4fv(glGetUniformLocation(in_program->object_id, current_uniform.c_str()), 1, glm::value_ptr(uni_value));

                //GLfloat get_values[4];
                //glGetUniformfv(in_program->object_id, glGetUniformLocation(in_program->object_id, current_uniform.c_str()), get_values);
                //std::cout << glGetError() << ", " << get_values[0] << ", " << get_values[1] << ", " << get_values[2] << ", " << get_values[3] << std::endl;
            }
            else if (parent_node->inputs.at("uni_pin")->type == PinType::Matrix4x4)
            {
                glm::mat4 uni_value = GetInputPinValue<glm::mat4>(parent_node, "uni_pin");
                glUniformMatrix4fv(glGetUniformLocation(in_program->object_id, current_uniform.c_str()), 1, false, &uni_value[0][0]);

                /*GLfloat get_values[16];
                glGetUniformfv(in_program->object_id, glGetUniformLocation(in_program->object_id, current_uniform.c_str()), get_values);
                std::cout << glGetError();
                for (int i = 0; i < 16; i++)
                    std::cout << ", " << get_values[i];
                std::cout << std::endl;*/
            }
            else if (parent_node->inputs.at("uni_pin")->type == PinType::TextureObject)
            {
                std::shared_ptr<TextureObject> uni_value = GetInputPinValue<std::shared_ptr<TextureObject>>(parent_node, "uni_pin");
                if (uni_value)
                {
                    glActiveTexture(GL_TEXTURE0 + in_program->current_texture);
                    glBindTexture(GL_TEXTURE_2D, uni_value->object_id);
                    glUniform1i(glGetUniformLocation(in_program->object_id, current_uniform.c_str()), in_program->current_texture);
                    in_program->current_texture++;
                }
            }
        }
    }
    RunNextNodeFunc(parent_node, "next");
}

void SetProgramUniformNode_Func::Delete()
{
    parent_node = nullptr;
    tmp_loaded_value = nullptr;
}

void SetProgramUniformNode_Func::UpdateNodeUI()
{
    if (current_uniform != "")
        parent_node->info = current_uniform;
    else
        parent_node->info = "";

    std::shared_ptr<ProgramObject> in_program = GetInputPinValue<std::shared_ptr<ProgramObject>>(parent_node, "program");
    if (in_program)
    {
        if (in_program->object_id != prev_program)
        {
            ProgramChanged();
            continue_loading = false;
        }

        if (in_program->uniforms_arr.size() == 0)
        {
            DeletePin();
        }
        else
        {
            if (parent_node->inputs.count("uni_pin") == 0)
            {
                parent_node->inputs.insert(std::pair<std::string, std::shared_ptr<PinValue<float>>>("uni_pin", new PinValue<float>("uni_pin", 2, GetNextId(), "Uniform Data", PinType::Float, 0)));
                BuildNode(parent_node);
            }

            if (current_uniform == "")
            {
                current_uniform = in_program->uniforms_arr.at(0).name;
                uniform_type = in_program->uniforms_arr.at(0).type;
            }
            UniformChanged();
        }
    }
    else
    {
        prev_program = 0;
        DeletePin();
    }
}

void SetProgramUniformNode_Func::UpdateNodeInspector()
{
    if (ImGui::BeginTabItem("Uniform Info"))
    {
        std::shared_ptr<ProgramObject> in_program = GetInputPinValue<std::shared_ptr<ProgramObject>>(parent_node, "program");
        if (in_program)
        {
            if (in_program->object_id != prev_program)
                ProgramChanged();

            auto paneWidth = ImGui::GetContentRegionAvailWidth();
            if (in_program->uniforms_arr.size() > 0)
            {
                ImGui::BeginHorizontal("##set_uniform_panel_1", ImVec2(paneWidth, 0), 1.0f);
                ImGui::TextUnformatted("Unifom: ");
                if (ImGui::BeginCombo("##combo", current_uniform.c_str()))
                {
                    for (int n = 0; n < in_program->uniforms_arr.size(); n++)
                    {
                        bool is_selected = current_uniform == in_program->uniforms_arr.at(n).name;
                        if (ImGui::Selectable(in_program->uniforms_arr.at(n).name.c_str(), is_selected))
                        {
                            current_uniform = in_program->uniforms_arr.at(n).name;
                            uniform_type = in_program->uniforms_arr.at(n).type;
                            UniformChanged();
                        }
                        if (is_selected)
                            ImGui::SetItemDefaultFocus();
                    }
                    ImGui::EndCombo();
                }
                ImGui::EndHorizontal();
            }
            else
            {
                ImGui::TextUnformatted("Shader doesnt have any uniform");
            }
        }
        ImGui::EndTabItem();
    }
}

void SetProgramUniformNode_Func::SaveNodeData(rapidjson::Writer<rapidjson::StringBuffer>& writer)
{
    std::shared_ptr<ProgramObject> in_program = GetInputPinValue<std::shared_ptr<ProgramObject>>(parent_node, "program");
    if (in_program)
    {
        writer.Key("current_uniform");
        writer.String(current_uniform.c_str());
        writer.Key("uniform_type");
        writer.String(PinTypeToString(uniform_type).c_str());


        if (parent_node->inputs.at("uni_pin")->type == PinType::Bool)
        {
            bool uni_value = std::dynamic_pointer_cast<PinValue<bool>>(parent_node->inputs.at("uni_pin"))->default_value;
            writer.Key("uniform_value");
            writer.Bool(uni_value);
        }
        else if (parent_node->inputs.at("uni_pin")->type == PinType::Int)
        {
            int uni_value = std::dynamic_pointer_cast<PinValue<int>>(parent_node->inputs.at("uni_pin"))->default_value;
            writer.Key("uniform_value");
            writer.Int(uni_value);
        }
        else if (parent_node->inputs.at("uni_pin")->type == PinType::Float)
        {
            float uni_value = std::dynamic_pointer_cast<PinValue<float>>(parent_node->inputs.at("uni_pin"))->default_value;
            writer.Key("uniform_value");
            writer.Double(uni_value);
        }
        if (parent_node->inputs.at("uni_pin")->type == PinType::Vector2)
        {
            glm::vec2 uni_value = std::dynamic_pointer_cast<PinValue<glm::vec2>>(parent_node->inputs.at("uni_pin"))->default_value;
            writer.Key("uniform_value");
            writer.StartArray();
            writer.Double(uni_value.x);
            writer.Double(uni_value.y);
            writer.EndArray();
        }
        else if (parent_node->inputs.at("uni_pin")->type == PinType::Vector3)
        {
            glm::vec3 uni_value = std::dynamic_pointer_cast<PinValue<glm::vec3>>(parent_node->inputs.at("uni_pin"))->default_value;
            writer.Key("uniform_value");
            writer.StartArray();
            writer.Double(uni_value.x);
            writer.Double(uni_value.y);
            writer.Double(uni_value.z);
            writer.EndArray();
        }
        else if (parent_node->inputs.at("uni_pin")->type == PinType::Vector4)
        {
            glm::vec4 uni_value = std::dynamic_pointer_cast<PinValue<glm::vec4>>(parent_node->inputs.at("uni_pin"))->default_value;
            writer.Key("uniform_value");
            writer.StartArray();
            writer.Double(uni_value.x);
            writer.Double(uni_value.y);
            writer.Double(uni_value.z);
            writer.Double(uni_value.w);
            writer.EndArray();
        }
        else if (parent_node->inputs.at("uni_pin")->type == PinType::Matrix4x4)
        {
            glm::mat4 uni_value = std::dynamic_pointer_cast<PinValue<glm::mat4>>(parent_node->inputs.at("uni_pin"))->default_value;
            writer.Key("uniform_value");
            writer.StartArray();
            const float* pSource = (const float*)glm::value_ptr(uni_value);
            for (int i = 0; i < 16; ++i)
                writer.Double(pSource[i]);
            writer.EndArray();
        }
    }
}

void SetProgramUniformNode_Func::LoadNodeData(rapidjson::Value& node_obj)
{
    if (!node_obj["current_uniform"].IsNull())
    {
        current_uniform = std::string(node_obj["current_uniform"].GetString());
        continue_loading = true;
    }
    if (!node_obj["uniform_type"].IsNull())
    {
        uniform_type = StringToPinType(node_obj["uniform_type"].GetString());
        UpdateNodeUI();
        if (!node_obj["uniform_value"].IsNull())
        {
            if (uniform_type == PinType::Bool)
            {
                bool uni_value = node_obj["uniform_value"].GetBool();
                tmp_loaded_value = std::make_shared<PlaceholderValue<bool>>("tmp", uniform_type, uni_value);
            }
            else if (uniform_type == PinType::Int)
            {
                int uni_value = node_obj["uniform_value"].GetInt();
                tmp_loaded_value = std::make_shared<PlaceholderValue<int>>("tmp", uniform_type, uni_value);
            }
            else if (uniform_type == PinType::Float)
            {
                float uni_value = node_obj["uniform_value"].GetFloat();
                tmp_loaded_value = std::make_shared<PlaceholderValue<float>>("tmp", uniform_type, uni_value);
            }
            if (uniform_type == PinType::Vector2)
            {
                glm::vec2 uni_value;
                uni_value.x = node_obj["uniform_value"].GetArray()[0].GetFloat();
                uni_value.y = node_obj["uniform_value"].GetArray()[1].GetFloat();
                tmp_loaded_value = std::make_shared<PlaceholderValue<glm::vec2>>("tmp", uniform_type, uni_value);
            }
            else if (uniform_type == PinType::Vector3)
            {
                glm::vec3 uni_value;
                uni_value.x = node_obj["uniform_value"].GetArray()[0].GetFloat();
                uni_value.y = node_obj["uniform_value"].GetArray()[1].GetFloat();
                uni_value.z = node_obj["uniform_value"].GetArray()[2].GetFloat();
                tmp_loaded_value = std::make_shared<PlaceholderValue<glm::vec3>>("tmp", uniform_type, uni_value);
            }
            else if (uniform_type == PinType::Vector4)
            {
                glm::vec4 uni_value;
                uni_value.x = node_obj["uniform_value"].GetArray()[0].GetFloat();
                uni_value.y = node_obj["uniform_value"].GetArray()[1].GetFloat();
                uni_value.z = node_obj["uniform_value"].GetArray()[2].GetFloat();
                uni_value.w = node_obj["uniform_value"].GetArray()[3].GetFloat();
                tmp_loaded_value = std::make_shared<PlaceholderValue<glm::vec4>>("tmp", uniform_type, uni_value);
            }
            else if (uniform_type == PinType::Matrix4x4)
            {
                glm::mat4 uni_value;
                float* pSource = (float*)glm::value_ptr(uni_value);
                for (int i = 0; i < 16; ++i)
                {
                    pSource[i] = node_obj["uniform_value"].GetArray()[i].GetFloat();
                }
                tmp_loaded_value = std::make_shared<PlaceholderValue<glm::mat4>>("tmp", uniform_type, uni_value);
            }
        }
    }
}

void SetProgramUniformNode_Func::ProgramChanged()
{
    std::shared_ptr<ProgramObject> in_program = GetInputPinValue<std::shared_ptr<ProgramObject>>(parent_node, "program");
    if (in_program)
        prev_program = in_program->object_id;
    DeletePin();
}

void SetProgramUniformNode_Func::UniformChanged()
{
    if (parent_node->inputs.count("uni_pin") > 0 && current_uniform != "")
    {
        if (parent_node->inputs.at("uni_pin")->name != current_uniform)
        {
            parent_node->inputs.at("uni_pin")->name = current_uniform;
        }
        if (parent_node->inputs.at("uni_pin")->type != uniform_type)
        {
            for (int j = 0; j < parent_node->inputs.at("uni_pin")->links.size(); j++)
            {
                ed::DeleteLink(parent_node->inputs.at("uni_pin")->links.at(j)->id);
            }
            parent_node->inputs.at("uni_pin")->links.clear();
            UtilsChangePinType(parent_node, PinKind::Input, "uni_pin", uniform_type);

            if (tmp_loaded_value)
            {
                if (uniform_type == PinType::Bool)
                {
                    std::dynamic_pointer_cast<PinValue<bool>>(parent_node->inputs.at("uni_pin"))->default_value = std::dynamic_pointer_cast<PlaceholderValue<bool>>(tmp_loaded_value)->value;
                }
                else if (uniform_type == PinType::Int)
                {
                    std::dynamic_pointer_cast<PinValue<int>>(parent_node->inputs.at("uni_pin"))->default_value = std::dynamic_pointer_cast<PlaceholderValue<int>>(tmp_loaded_value)->value;
                }
                else if (uniform_type == PinType::Float)
                {
                    std::dynamic_pointer_cast<PinValue<float>>(parent_node->inputs.at("uni_pin"))->default_value = std::dynamic_pointer_cast<PlaceholderValue<float>>(tmp_loaded_value)->value;
                }
                if (uniform_type == PinType::Vector2)
                {
                    std::dynamic_pointer_cast<PinValue<glm::vec2>>(parent_node->inputs.at("uni_pin"))->default_value = std::dynamic_pointer_cast<PlaceholderValue<glm::vec2>>(tmp_loaded_value)->value;
                }
                else if (uniform_type == PinType::Vector3)
                {
                    std::dynamic_pointer_cast<PinValue<glm::vec3>>(parent_node->inputs.at("uni_pin"))->default_value = std::dynamic_pointer_cast<PlaceholderValue<glm::vec3>>(tmp_loaded_value)->value;
                }
                else if (uniform_type == PinType::Vector4)
                {
                    std::dynamic_pointer_cast<PinValue<glm::vec4>>(parent_node->inputs.at("uni_pin"))->default_value = std::dynamic_pointer_cast<PlaceholderValue<glm::vec4>>(tmp_loaded_value)->value;
                }
                else if (uniform_type == PinType::Matrix4x4)
                {
                    std::dynamic_pointer_cast<PinValue<glm::mat4>>(parent_node->inputs.at("uni_pin"))->default_value = std::dynamic_pointer_cast<PlaceholderValue<glm::mat4>>(tmp_loaded_value)->value;
                }
                tmp_loaded_value = nullptr;
            }
        }
    }
}

void SetProgramUniformNode_Func::DeletePin()
{
    std::string pin_key = "uni_pin";
    if (parent_node->inputs.count(pin_key) > 0)
    {
        for (int j = 0; j < parent_node->inputs.at(pin_key)->links.size(); j++)
        {
            ed::DeleteLink(parent_node->inputs.at(pin_key)->links.at(j)->id);
        }
        parent_node->inputs.at(pin_key)->node = nullptr;
        parent_node->inputs.at(pin_key)->links.clear();

        parent_node->inputs.erase(pin_key);
    }

    parent_node->info = "";
    if (continue_loading == false)
    {
        current_uniform = "";
        uniform_type = PinType::Float;
    }
}

std::string setProgramUniformNodeName = "Set Program Uniform";
std::shared_ptr<Node> SetProgramUniformNode(std::vector<std::shared_ptr<Node>>& s_Nodes)
{
    s_Nodes.emplace_back(new Node(GetNextId(), setProgramUniformNodeName.c_str()));

    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<BasePin>>("enter", new BasePin("enter", 0, GetNextId(), "Enter", PinType::Flow)));
    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<PinValue<std::shared_ptr<ProgramObject>>>>("program", new PinValue<std::shared_ptr<ProgramObject>>("program", 1, GetNextId(), "Program", PinType::ProgramObject, nullptr)));
    
    s_Nodes.back()->outputs.insert(std::pair<std::string, std::shared_ptr<BasePin>>("next", new BasePin("next", 0, GetNextId(), "Next", PinType::Flow)));

    s_Nodes.back()->node_funcs = std::make_shared<SetProgramUniformNode_Func>();
    std::dynamic_pointer_cast<SetProgramUniformNode_Func>(s_Nodes.back()->node_funcs)->parent_node = s_Nodes.back();

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

    std::function<std::shared_ptr<Node>(std::vector<std::shared_ptr<Node>>&)> func_3 = BindProgramNode;
    std::vector<std::string> keywords_3{ "Bind", "Program" };
    search_nodes_vector.push_back(SearchNodeObj("Bind Program", "Shaders Nodes", keywords_3, func_3));

    std::function<std::shared_ptr<Node>(std::vector<std::shared_ptr<Node>>&)> func_4 = BindProgramWithUniformsNode;
    std::vector<std::string> keywords_4{ "Bind", "Program", "Uniforms", "Shader" };
    search_nodes_vector.push_back(SearchNodeObj("Bind Program With Uniforms", "Shaders Nodes", keywords_4, func_4));

    std::function<std::shared_ptr<Node>(std::vector<std::shared_ptr<Node>>&)> func_5 = SetProgramUniformNode;
    std::vector<std::string> keywords_5{ "Set", "Program", "Uniform" };
    search_nodes_vector.push_back(SearchNodeObj("Set Program Uniform", "Shaders Nodes", keywords_5, func_5));
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
    else if (loaded_node == nullptr && node_key.rfind(bindProgramWithUniformsNodeName, 0) == 0) {
        loaded_node = BindProgramWithUniformsNode(s_Nodes);
    }
    else if (loaded_node == nullptr && node_key.rfind(bindProgramNodeName, 0) == 0) {
        loaded_node = BindProgramNode(s_Nodes);
    }
    else if (loaded_node == nullptr && node_key.rfind(setProgramUniformNodeName, 0) == 0) {
        loaded_node = SetProgramUniformNode(s_Nodes);
    }
    return loaded_node;
}
