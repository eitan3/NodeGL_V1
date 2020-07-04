#include "utils.h"

std::shared_ptr<Node> FindNode(ed::NodeId id, std::vector<std::shared_ptr<Node>>& s_Nodes)
{
    for (auto& node : s_Nodes)
        if (node->id == id)
            return node;

    return nullptr;
}

std::shared_ptr<Link> FindLink(ed::LinkId id, std::vector<std::shared_ptr<Link>>& s_Links)
{
    for (auto& link : s_Links)
        if (link->id == id)
            return link;

    return nullptr;
}

std::shared_ptr<BasePin> FindPin(ed::PinId id, std::vector<std::shared_ptr<Node>>& s_Nodes)
{
    if (!id)
        return nullptr;

    for (auto& node : s_Nodes)
    {
        for (auto& pin : node->inputs)
            if (pin.second->id == id)
                return pin.second;

        for (auto& pin : node->outputs)
            if (pin.second->id == id)
                return pin.second;
    }

    return nullptr;
}

bool IsPinLinked(ed::PinId id, std::vector<std::shared_ptr<Link>>& s_Links)
{
    if (!id)
        return false;

    for (auto& link : s_Links)
        if (link->startPinID == id || link->endPinID == id)
            return true;

    return false;
}

bool CanCreateLink(std::shared_ptr<BasePin>& a, std::shared_ptr<BasePin>& b)
{
    if (!a || !b || a == b || a->kind == b->kind || a->type != b->type || a->node == b->node || a->isArr != b->isArr)
        return false;

    return true;
}

void RunNextNodeFunc(std::shared_ptr<Node>& parent_node, std::string pin_key)
{
    if (parent_node->outputs.at(pin_key)->type == PinType::Flow)
    {
        if (parent_node->outputs.at(pin_key)->links.size() > 0)
        {
            if (parent_node->outputs.at(pin_key)->links.at(0))
            {
                if (parent_node->outputs.at(pin_key)->links.at(0)->endPin)
                {
                    if (parent_node->outputs.at(pin_key)->links.at(0)->endPin->node)
                    {
                        if (parent_node->outputs.at(pin_key)->links.at(0)->endPin->node->node_funcs)
                        {
                            std::string in_pin_key = parent_node->outputs.at(pin_key)->links.at(0)->endPin->pin_key;
                            parent_node->outputs.at(pin_key)->links.at(0)->endPin->node->node_funcs->Run(in_pin_key);
                        }
                    }
                }
            }
        }
    }
}

std::string PinTypeToString(PinType type)
{
    if (type == PinType::Bool)
        return "Bool";
    else if (type == PinType::Float)
        return "Float";
    else if (type == PinType::Int)
        return "Int";
    else if (type == PinType::String)
        return "String";
    else if (type == PinType::VectorI2)
        return "Int Vector 2";
    else if (type == PinType::VectorI3)
        return "Int Vector 3";
    else if (type == PinType::VectorI4)
        return "Int Vector 4";
    else if (type == PinType::Vector2)
        return "Vector 2";
    else if (type == PinType::Vector3)
        return "Vector 3";
    else if (type == PinType::Vector4)
        return "Vector 4";
    else if (type == PinType::Matrix4x4)
        return "Matrix 4x4";
    else if (type == PinType::ProgramObject)
        return "Program Object";
    else if (type == PinType::VertexShaderObject)
        return "Vertex Shader Object";
    else if (type == PinType::FragmentShaderObject)
        return "Fragment Shader Object";
    else if (type == PinType::TextureObject)
        return "Texture Object";
    else if (type == PinType::MeshObject)
        return "Mesh Object";
    std::cout << "Error!!! Cant find pin type" << std::endl;
    return "Unkown";
}

PinType StringToPinType(std::string str)
{
    if (str == "Bool")
        return PinType::Bool;
    else if (str == "Float")
        return PinType::Float;
    else if (str == "Int")
        return PinType::Int;
    else if (str == "String")
        return PinType::String;
    else if (str == "Int Vector 2")
        return PinType::VectorI2;
    else if (str == "Int Vector 3")
        return PinType::VectorI3;
    else if (str == "Int Vector 4")
        return PinType::VectorI4;
    else if (str == "Vector 2")
        return PinType::Vector2;
    else if (str == "Vector 3")
        return PinType::Vector3;
    else if (str == "Vector 4")
        return PinType::Vector4;
    else if (str == "Matrix 4x4")
        return PinType::Matrix4x4;
    else if (str == "Program Object")
        return PinType::ProgramObject;
    else if (str == "Vertex Shader Object")
        return PinType::VertexShaderObject;
    else if (str == "Fragment Shader Object")
        return PinType::FragmentShaderObject;
    else if (str == "Texture Object")
        return PinType::TextureObject;
    else if (str == "Mesh Object")
        return PinType::MeshObject;
    std::cout << "Error!!! Cant find pin type" << std::endl;
    return PinType::Unknown;
}

std::vector<std::string> SortPins(std::map<std::string, std::shared_ptr<BasePin>> pins)
{
    auto cmp = [](const std::pair<std::string, std::shared_ptr<BasePin>>& p1, const std::pair<std::string, std::shared_ptr<BasePin>>& p2)
    {
        return p1.second->order < p2.second->order;
    };

    std::set<std::pair<std::string, std::shared_ptr<BasePin>>, decltype(cmp)> s(pins.begin(), pins.end(), cmp);
    std::vector<std::string> ret;
    for (const auto& p : s)
        ret.push_back(p.first);
    return ret;
}

bool CanAddToInputsTab(std::shared_ptr<BasePin> pin)
{
    if (pin->isArr == false)
        if (pin->type == PinType::Bool || pin->type == PinType::Float || pin->type == PinType::Int || pin->type == PinType::String || 
            pin->type == PinType::VectorI2 || pin->type == PinType::VectorI3 || pin->type == PinType::VectorI4 ||
            pin->type == PinType::Vector2 || pin->type == PinType::Vector3 || pin->type == PinType::Vector4)
            return true;
    return false;
}

bool isEditDefaultActive = false;
void AddInputPinsTab(std::shared_ptr<Node> node)
{
    bool g_hasValuePins = false;
    bool g_hasTemplate = false;
    for (auto& input : node->inputs)
    {
        if (CanAddToInputsTab(input.second))
            g_hasValuePins = true;
        if (input.second->isTemplate)
            g_hasTemplate = true;
    }
    for (auto& output : node->outputs)
    {
        if (output.second->isTemplate)
            g_hasTemplate = true;
    }

    if (g_hasValuePins || g_hasTemplate)
    {
        auto paneWidth = ImGui::GetContentRegionAvailWidth();
        if (ImGui::BeginTabItem("Inputs"))
        {
            if (g_hasValuePins)
            {
                if (ImGui::CollapsingHeader("Inputs Default Values", ImGuiTreeNodeFlags_AllowItemOverlap))
                {
                    std::vector<std::string> sort_pins = SortPins(node->inputs);
                    for (int pi = 0; pi < sort_pins.size(); pi++)
                    {
                        std::shared_ptr<BasePin> input = node->inputs.at(sort_pins.at(pi));
                        if (CanAddToInputsTab(input))
                        {
                            ImGui::BeginHorizontal(("##horizontal_panel" + input->name).c_str(), ImVec2(paneWidth, 0), 1.0f);
                            if (input->always_expose)
                            {
                                ImGui::PushItemFlag(ImGuiItemFlags_Disabled, true);
                                ImGui::PushStyleVar(ImGuiStyleVar_Alpha, ImGui::GetStyle().Alpha * 0.5f);
                                input->exposed = true;
                                ImGui::Checkbox(("##checkbox_" + input->name).c_str(), &input->exposed);
                                ImGui::PopItemFlag();
                                ImGui::PopStyleVar();
                            }
                            else
                            {
                                ImGui::Checkbox(("##checkbox_" + input->name).c_str(), &input->exposed);
                            }
                            ImGui::TextUnformatted(input->name.c_str());

                            if (input->type == PinType::String)
                            {
                                ImGui::PushItemWidth(100.0f);
                                std::shared_ptr<PinValue<std::string>> input_pin_value = std::dynamic_pointer_cast<PinValue<std::string>>(input);

                                ImGui::InputText("##edit", (char*)input_pin_value->default_value.data(), input_pin_value->default_value.capacity() + 1.0);
                                input_pin_value->default_value = std::string(input_pin_value->default_value.data());

                                ImGui::PopItemWidth();
                                if (ImGui::IsItemActive() && !isEditDefaultActive)
                                {
                                    ed::EnableShortcuts(false);
                                    isEditDefaultActive = true;
                                }
                                else if (!ImGui::IsItemActive() && isEditDefaultActive)
                                {
                                    ed::EnableShortcuts(true);
                                    isEditDefaultActive = false;
                                }
                            }
                            else if (input->type == PinType::Bool)
                            {
                                std::shared_ptr<PinValue<bool>> input_pin_value = std::dynamic_pointer_cast<PinValue<bool>>(input);
                                ImGui::PushItemWidth(100.0f);
                                
                                ImGui::Checkbox("##edit", &input_pin_value->default_value);

                                ImGui::PopItemWidth();
                                if (ImGui::IsItemActive() && !isEditDefaultActive)
                                {
                                    ed::EnableShortcuts(false);
                                    isEditDefaultActive = true;
                                }
                                else if (!ImGui::IsItemActive() && isEditDefaultActive)
                                {
                                    ed::EnableShortcuts(true);
                                    isEditDefaultActive = false;
                                }
                            }
                            else if (input->type == PinType::Float)
                            {
                                std::shared_ptr<PinValue<float>> input_pin_value = std::dynamic_pointer_cast<PinValue<float>>(input);
                                ImGui::PushItemWidth(100.0f);

                                ImGui::InputFloat("##edit", &input_pin_value->default_value, 0.0, 0.0, "%.6f", 0);

                                ImGui::PopItemWidth();
                                if (ImGui::IsItemActive() && !isEditDefaultActive)
                                {
                                    ed::EnableShortcuts(false);
                                    isEditDefaultActive = true;
                                }
                                else if (!ImGui::IsItemActive() && isEditDefaultActive)
                                {
                                    ed::EnableShortcuts(true);
                                    isEditDefaultActive = false;
                                }
                            }
                            else if (input->type == PinType::Int)
                            {
                                std::shared_ptr<PinValue<int>> input_pin_value = std::dynamic_pointer_cast<PinValue<int>>(input);
                                ImGui::PushItemWidth(100.0f);

                                ImGui::InputInt("##edit", &input_pin_value->default_value, 0, 0, 0);

                                ImGui::PopItemWidth();
                                if (ImGui::IsItemActive() && !isEditDefaultActive)
                                {
                                    ed::EnableShortcuts(false);
                                    isEditDefaultActive = true;
                                }
                                else if (!ImGui::IsItemActive() && isEditDefaultActive)
                                {
                                    ed::EnableShortcuts(true);
                                    isEditDefaultActive = false;
                                }
                            }
                            else if (input->type == PinType::Vector2)
                            {
                                std::shared_ptr<PinValue<glm::vec2>> input_pin_value = std::dynamic_pointer_cast<PinValue<glm::vec2>>(input);
                                ImGui::PushItemWidth(150.0f);

                                float float2[2] = { input_pin_value->default_value.x, input_pin_value->default_value.y };
                                ImGui::InputFloat2("##edit", float2);
                                input_pin_value->default_value = glm::vec2(float2[0], float2[1]);

                                ImGui::PopItemWidth();
                                if (ImGui::IsItemActive() && !isEditDefaultActive)
                                {
                                    ed::EnableShortcuts(false);
                                    isEditDefaultActive = true;
                                }
                                else if (!ImGui::IsItemActive() && isEditDefaultActive)
                                {
                                    ed::EnableShortcuts(true);
                                    isEditDefaultActive = false;
                                }
                            }
                            else if (input->type == PinType::Vector3)
                            {
                                std::shared_ptr<PinValue<glm::vec3>> input_pin_value = std::dynamic_pointer_cast<PinValue<glm::vec3>>(input);
                                ImGui::PushItemWidth(150.0f);

                                //ImGui::InputFloat("##edit", &input_pin_value->default_value, 0.0, 0.0, "%.6f", 0);
                                float float3[3] = { input_pin_value->default_value.x, input_pin_value->default_value.y, input_pin_value->default_value.z };
                                ImGui::InputFloat3("##edit", float3);
                                input_pin_value->default_value = glm::vec3(float3[0], float3[1], float3[2]);

                                ImGui::PopItemWidth();
                                if (ImGui::IsItemActive() && !isEditDefaultActive)
                                {
                                    ed::EnableShortcuts(false);
                                    isEditDefaultActive = true;
                                }
                                else if (!ImGui::IsItemActive() && isEditDefaultActive)
                                {
                                    ed::EnableShortcuts(true);
                                    isEditDefaultActive = false;
                                }
                            }
                            else if (input->type == PinType::Vector4)
                            {
                                std::shared_ptr<PinValue<glm::vec4>> input_pin_value = std::dynamic_pointer_cast<PinValue<glm::vec4>>(input);
                                ImGui::PushItemWidth(150.0f);

                                //ImGui::InputFloat("##edit", &input_pin_value->default_value, 0.0, 0.0, "%.6f", 0);
                                float float4[4] = { input_pin_value->default_value.x, input_pin_value->default_value.y, input_pin_value->default_value.z, input_pin_value->default_value.w };
                                ImGui::InputFloat4("##edit", float4);
                                input_pin_value->default_value = glm::vec4(float4[0], float4[1], float4[2], float4[3]);

                                ImGui::PopItemWidth();
                                if (ImGui::IsItemActive() && !isEditDefaultActive)
                                {
                                    ed::EnableShortcuts(false);
                                    isEditDefaultActive = true;
                                }
                                else if (!ImGui::IsItemActive() && isEditDefaultActive)
                                {
                                    ed::EnableShortcuts(true);
                                    isEditDefaultActive = false;
                                }
                            }
                            else if (input->type == PinType::VectorI2)
                            {
                                std::shared_ptr<PinValue<glm::ivec2>> input_pin_value = std::dynamic_pointer_cast<PinValue<glm::ivec2>>(input);
                                ImGui::PushItemWidth(150.0f);

                                int float2[2] = { input_pin_value->default_value.x, input_pin_value->default_value.y };
                                ImGui::InputInt2("##edit", float2);
                                input_pin_value->default_value = glm::ivec2(float2[0], float2[1]);

                                ImGui::PopItemWidth();
                                if (ImGui::IsItemActive() && !isEditDefaultActive)
                                {
                                    ed::EnableShortcuts(false);
                                    isEditDefaultActive = true;
                                }
                                else if (!ImGui::IsItemActive() && isEditDefaultActive)
                                {
                                    ed::EnableShortcuts(true);
                                    isEditDefaultActive = false;
                                }
                            }
                            else if (input->type == PinType::VectorI3)
                            {
                                std::shared_ptr<PinValue<glm::ivec3>> input_pin_value = std::dynamic_pointer_cast<PinValue<glm::ivec3>>(input);
                                ImGui::PushItemWidth(150.0f);

                                //ImGui::InputFloat("##edit", &input_pin_value->default_value, 0.0, 0.0, "%.6f", 0);
                                int float3[3] = { input_pin_value->default_value.x, input_pin_value->default_value.y, input_pin_value->default_value.z };
                                ImGui::InputInt3("##edit", float3);
                                input_pin_value->default_value = glm::ivec3(float3[0], float3[1], float3[2]);

                                ImGui::PopItemWidth();
                                if (ImGui::IsItemActive() && !isEditDefaultActive)
                                {
                                    ed::EnableShortcuts(false);
                                    isEditDefaultActive = true;
                                }
                                else if (!ImGui::IsItemActive() && isEditDefaultActive)
                                {
                                    ed::EnableShortcuts(true);
                                    isEditDefaultActive = false;
                                }
                            }
                            else if (input->type == PinType::VectorI4)
                            {
                                std::shared_ptr<PinValue<glm::ivec4>> input_pin_value = std::dynamic_pointer_cast<PinValue<glm::ivec4>>(input);
                                ImGui::PushItemWidth(150.0f);

                                //ImGui::InputFloat("##edit", &input_pin_value->default_value, 0.0, 0.0, "%.6f", 0);
                                int float4[4] = { input_pin_value->default_value.x, input_pin_value->default_value.y, input_pin_value->default_value.z, input_pin_value->default_value.w };
                                ImGui::InputInt4("##edit", float4);
                                input_pin_value->default_value = glm::ivec4(float4[0], float4[1], float4[2], float4[3]);

                                ImGui::PopItemWidth();
                                if (ImGui::IsItemActive() && !isEditDefaultActive)
                                {
                                    ed::EnableShortcuts(false);
                                    isEditDefaultActive = true;
                                }
                                else if (!ImGui::IsItemActive() && isEditDefaultActive)
                                {
                                    ed::EnableShortcuts(true);
                                    isEditDefaultActive = false;
                                }
                            }

                            ImGui::EndHorizontal();
                        }
                    }
                }
            }

            if (g_hasTemplate)
            {
                if (ImGui::CollapsingHeader("Inputs Type", ImGuiTreeNodeFlags_AllowItemOverlap))
                {
                    std::vector<std::string> sort_pins = SortPins(node->inputs);
                    for (int pi = 0; pi < sort_pins.size(); pi++)
                    {
                        std::shared_ptr<BasePin> input = node->inputs.at(sort_pins.at(pi));
                        if (input->isTemplate)
                        {
                            std::string template_pin_type_selected_item = PinTypeToString(input->type);
                            if (ImGui::BeginCombo(input->name.c_str(), template_pin_type_selected_item.data()))
                            {
                                for (int n = 0; n < input->template_allowed_types.size(); n++)
                                {
                                    bool is_selected = (template_pin_type_selected_item == PinTypeToString(input->template_allowed_types[n]));
                                    if (ImGui::Selectable(PinTypeToString(input->template_allowed_types[n]).c_str(), is_selected))
                                    {
                                        template_pin_type_selected_item = PinTypeToString(input->template_allowed_types[n]);
                                        UtilsChangePinType(input->node, input->kind, input->pin_key, input->template_allowed_types[n], input->isArr);
                                    }
                                    if (is_selected)
                                        ImGui::SetItemDefaultFocus();   // You may set the initial focus when opening the combo (scrolling + for keyboard navigation support)
                                }
                                ImGui::EndCombo();
                            }
                        }
                    }
                    
                    sort_pins = SortPins(node->outputs);
                    for (int pi = 0; pi < sort_pins.size(); pi++)
                    {
                        std::shared_ptr<BasePin> output = node->outputs.at(sort_pins.at(pi));
                        if (output->isTemplate)
                        {
                            std::string template_pin_type_selected_item = PinTypeToString(output->type);
                            if (ImGui::BeginCombo(output->name.c_str(), template_pin_type_selected_item.data()))
                            {
                                for (int n = 0; n < output->template_allowed_types.size(); n++)
                                {
                                    bool is_selected = (template_pin_type_selected_item == PinTypeToString(output->template_allowed_types[n]));
                                    if (ImGui::Selectable(PinTypeToString(output->template_allowed_types[n]).c_str(), is_selected))
                                    {
                                        template_pin_type_selected_item = PinTypeToString(output->template_allowed_types[n]);
                                        UtilsChangePinType(output->node, output->kind, output->pin_key, output->template_allowed_types[n], output->isArr);
                                    }
                                    if (is_selected)
                                        ImGui::SetItemDefaultFocus();   // You may set the initial focus when opening the combo (scrolling + for keyboard navigation support)
                                }
                                ImGui::EndCombo();
                            }
                        }
                    }
                }
            }

            ImGui::EndTabItem();
        }
    }
}

void UtilsChangePinType(std::shared_ptr<Node> parent_node, PinKind kind, std::string index, PinType type, bool isArr)
{
    if (kind == PinKind::Input)
        UtilsDeleteLinks(parent_node->inputs.at(index));
    else
        UtilsDeleteLinks(parent_node->outputs.at(index));
    if (isArr == false)
    {
        if (kind == PinKind::Input)
        {
            std::shared_ptr<Node> node = parent_node->inputs.at(index)->node;;
            bool isTemplate = parent_node->inputs.at(index)->isTemplate;
            std::vector<PinType> template_allowed_types = parent_node->inputs.at(index)->template_allowed_types;
            bool isGeneralArray = parent_node->inputs.at(index)->isGeneralArray;
            if (type == PinType::Bool)
            {
                std::shared_ptr<PinValue<bool>> new_node = std::make_shared<PinValue<bool>>(index, parent_node->inputs.at(index)->order, parent_node->inputs.at(index)->id.Get(), parent_node->inputs.at(index)->name.c_str(), type, false);
                parent_node->inputs.at(index) = new_node;
            }
            else if (type == PinType::Float)
            {
                std::shared_ptr<PinValue<float>> new_node = std::make_shared<PinValue<float>>(index, parent_node->inputs.at(index)->order, parent_node->inputs.at(index)->id.Get(), parent_node->inputs.at(index)->name.c_str(), type, 0);
                parent_node->inputs.at(index) = new_node;
            }
            else if (type == PinType::Int)
            {
                std::shared_ptr<PinValue<int>> new_node = std::make_shared<PinValue<int>>(index, parent_node->inputs.at(index)->order, parent_node->inputs.at(index)->id.Get(), parent_node->inputs.at(index)->name.c_str(), type, 0);
                parent_node->inputs.at(index) = new_node;
            }
            else if (type == PinType::String)
            {
                std::shared_ptr<PinValue<std::string>> new_node = std::make_shared<PinValue<std::string>>(index, parent_node->inputs.at(index)->order, parent_node->inputs.at(index)->id.Get(), parent_node->inputs.at(index)->name.c_str(), type, "");
                parent_node->inputs.at(index) = new_node;
            }
            else if (type == PinType::VectorI2)
            {
                std::shared_ptr<PinValue<glm::ivec2>> new_node = std::make_shared<PinValue<glm::ivec2>>(index, parent_node->inputs.at(index)->order, parent_node->inputs.at(index)->id.Get(), parent_node->inputs.at(index)->name.c_str(), type, glm::ivec2(0));
                parent_node->inputs.at(index) = new_node;
            }
            else if (type == PinType::VectorI3)
            {
                std::shared_ptr<PinValue<glm::ivec3>> new_node = std::make_shared<PinValue<glm::ivec3>>(index, parent_node->inputs.at(index)->order, parent_node->inputs.at(index)->id.Get(), parent_node->inputs.at(index)->name.c_str(), type, glm::ivec3(0));
                parent_node->inputs.at(index) = new_node;
            }
            else if (type == PinType::VectorI4)
            {
                std::shared_ptr<PinValue<glm::ivec4>> new_node = std::make_shared<PinValue<glm::ivec4>>(index, parent_node->inputs.at(index)->order, parent_node->inputs.at(index)->id.Get(), parent_node->inputs.at(index)->name.c_str(), type, glm::ivec4(0));
                parent_node->inputs.at(index) = new_node;
            }
            else if (type == PinType::Vector2)
            {
                std::shared_ptr<PinValue<glm::vec2>> new_node = std::make_shared<PinValue<glm::vec2>>(index, parent_node->inputs.at(index)->order, parent_node->inputs.at(index)->id.Get(), parent_node->inputs.at(index)->name.c_str(), type, glm::vec2(0));
                parent_node->inputs.at(index) = new_node;
            }
            else if (type == PinType::Vector3)
            {
                std::shared_ptr<PinValue<glm::vec3>> new_node = std::make_shared<PinValue<glm::vec3>>(index, parent_node->inputs.at(index)->order, parent_node->inputs.at(index)->id.Get(), parent_node->inputs.at(index)->name.c_str(), type, glm::vec3(0));
                parent_node->inputs.at(index) = new_node;
            }
            else if (type == PinType::Vector4)
            {
                std::shared_ptr<PinValue<glm::vec4>> new_node = std::make_shared<PinValue<glm::vec4>>(index, parent_node->inputs.at(index)->order, parent_node->inputs.at(index)->id.Get(), parent_node->inputs.at(index)->name.c_str(), type, glm::vec4(0));
                parent_node->inputs.at(index) = new_node;
            }
            else if (type == PinType::Matrix4x4)
            {
                std::shared_ptr<PinValue<glm::mat4>> new_node = std::make_shared<PinValue<glm::mat4>>(index, parent_node->inputs.at(index)->order, parent_node->inputs.at(index)->id.Get(), parent_node->inputs.at(index)->name.c_str(), type, glm::mat4(1.0));
                parent_node->inputs.at(index) = new_node;
            }
            else if (type == PinType::TextureObject)
            {
                std::shared_ptr<PinValue<std::shared_ptr<TextureObject>>> new_node = std::make_shared<PinValue<std::shared_ptr<TextureObject>>>(index, parent_node->inputs.at(index)->order, parent_node->inputs.at(index)->id.Get(), parent_node->inputs.at(index)->name.c_str(), type, nullptr);
                parent_node->inputs.at(index) = new_node;
            }
            else if (type == PinType::ProgramObject)
            {
                std::shared_ptr<PinValue<std::shared_ptr<ProgramObject>>> new_node = std::make_shared<PinValue<std::shared_ptr<ProgramObject>>>(index, parent_node->inputs.at(index)->order, parent_node->inputs.at(index)->id.Get(), parent_node->inputs.at(index)->name.c_str(), type, nullptr);
                parent_node->inputs.at(index) = new_node;
            }
            else if (type == PinType::VertexShaderObject)
            {
                std::shared_ptr<PinValue<std::shared_ptr<ShaderObject>>> new_node = std::make_shared<PinValue<std::shared_ptr<ShaderObject>>>(index, parent_node->inputs.at(index)->order, parent_node->inputs.at(index)->id.Get(), parent_node->inputs.at(index)->name.c_str(), type, nullptr);
                parent_node->inputs.at(index) = new_node;
            }
            else if (type == PinType::FragmentShaderObject)
            {
                std::shared_ptr<PinValue<std::shared_ptr<ShaderObject>>> new_node = std::make_shared<PinValue<std::shared_ptr<ShaderObject>>>(index, parent_node->inputs.at(index)->order, parent_node->inputs.at(index)->id.Get(), parent_node->inputs.at(index)->name.c_str(), type, nullptr);
                parent_node->inputs.at(index) = new_node;
            }
            else if (type == PinType::MeshObject)
            {
                std::shared_ptr<PinValue<std::shared_ptr<MeshObject>>> new_node = std::make_shared<PinValue<std::shared_ptr<MeshObject>>>(index, parent_node->inputs.at(index)->order, parent_node->inputs.at(index)->id.Get(), parent_node->inputs.at(index)->name.c_str(), type, nullptr);
                parent_node->inputs.at(index) = new_node;
            }
            parent_node->inputs.at(index)->node = node;
            parent_node->inputs.at(index)->isTemplate = isTemplate;
            parent_node->inputs.at(index)->template_allowed_types = template_allowed_types;
            parent_node->inputs.at(index)->isArr = isArr;
            parent_node->inputs.at(index)->isGeneralArray = isGeneralArray;
        }
        else if (kind == PinKind::Output)
        {
            std::shared_ptr<Node> node = parent_node->outputs.at(index)->node;;
            bool isTemplate = parent_node->outputs.at(index)->isTemplate;
            std::vector<PinType> template_allowed_types = parent_node->outputs.at(index)->template_allowed_types;
            bool isGeneralArray = parent_node->outputs.at(index)->isGeneralArray;
            if (type == PinType::Bool)
            {
                std::shared_ptr<PinValue<bool>> new_node = std::make_shared<PinValue<bool>>(index, parent_node->outputs.at(index)->order, parent_node->outputs.at(index)->id.Get(), parent_node->outputs.at(index)->name.c_str(), type, false);
                parent_node->outputs.at(index) = new_node;
            }
            else if (type == PinType::Float)
            {
                std::shared_ptr<PinValue<float>> new_node = std::make_shared<PinValue<float>>(index, parent_node->outputs.at(index)->order, parent_node->outputs.at(index)->id.Get(), parent_node->outputs.at(index)->name.c_str(), type, 0);
                parent_node->outputs.at(index) = new_node;
            }
            else if (type == PinType::Int)
            {
                std::shared_ptr<PinValue<int>> new_node = std::make_shared<PinValue<int>>(index, parent_node->outputs.at(index)->order, parent_node->outputs.at(index)->id.Get(), parent_node->outputs.at(index)->name.c_str(), type, 0);
                parent_node->outputs.at(index) = new_node;
            }
            else if (type == PinType::String)
            {
                std::shared_ptr<PinValue<std::string>> new_node = std::make_shared<PinValue<std::string>>(index, parent_node->outputs.at(index)->order, parent_node->outputs.at(index)->id.Get(), parent_node->outputs.at(index)->name.c_str(), type, "");
                parent_node->outputs.at(index) = new_node;
            }
            else if (type == PinType::VectorI2)
            {
                std::shared_ptr<PinValue<glm::ivec2>> new_node = std::make_shared<PinValue<glm::ivec2>>(index, parent_node->outputs.at(index)->order, parent_node->outputs.at(index)->id.Get(), parent_node->outputs.at(index)->name.c_str(), type, glm::ivec2(0));
                parent_node->outputs.at(index) = new_node;
            }
            else if (type == PinType::VectorI3)
            {
                std::shared_ptr<PinValue<glm::ivec3>> new_node = std::make_shared<PinValue<glm::ivec3>>(index, parent_node->outputs.at(index)->order, parent_node->outputs.at(index)->id.Get(), parent_node->outputs.at(index)->name.c_str(), type, glm::ivec3(0));
                parent_node->outputs.at(index) = new_node;
            }
            else if (type == PinType::VectorI4)
            {
                std::shared_ptr<PinValue<glm::ivec4>> new_node = std::make_shared<PinValue<glm::ivec4>>(index, parent_node->outputs.at(index)->order, parent_node->outputs.at(index)->id.Get(), parent_node->outputs.at(index)->name.c_str(), type, glm::ivec4(0));
                parent_node->outputs.at(index) = new_node;
            }
            else if (type == PinType::Vector2)
            {
                std::shared_ptr<PinValue<glm::vec2>> new_node = std::make_shared<PinValue<glm::vec2>>(index, parent_node->outputs.at(index)->order, parent_node->outputs.at(index)->id.Get(), parent_node->outputs.at(index)->name.c_str(), type, glm::vec2(0));
                parent_node->outputs.at(index) = new_node;
            }
            else if (type == PinType::Vector3)
            {
                std::shared_ptr<PinValue<glm::vec3>> new_node = std::make_shared<PinValue<glm::vec3>>(index, parent_node->outputs.at(index)->order, parent_node->outputs.at(index)->id.Get(), parent_node->outputs.at(index)->name.c_str(), type, glm::vec3(0));
                parent_node->outputs.at(index) = new_node;
            }
            else if (type == PinType::Vector4)
            {
                std::shared_ptr<PinValue<glm::vec4>> new_node = std::make_shared<PinValue<glm::vec4>>(index, parent_node->outputs.at(index)->order, parent_node->outputs.at(index)->id.Get(), parent_node->outputs.at(index)->name.c_str(), type, glm::vec4(0));
                parent_node->outputs.at(index) = new_node;
            }
            else if (type == PinType::Matrix4x4)
            {
                std::shared_ptr<PinValue<glm::mat4>> new_node = std::make_shared<PinValue<glm::mat4>>(index, parent_node->outputs.at(index)->order, parent_node->outputs.at(index)->id.Get(), parent_node->outputs.at(index)->name.c_str(), type, glm::mat4(1.0));
                parent_node->outputs.at(index) = new_node;
            }
            else if (type == PinType::TextureObject)
            {
                std::shared_ptr<PinValue<std::shared_ptr<TextureObject>>> new_node = std::make_shared<PinValue<std::shared_ptr<TextureObject>>>(index, parent_node->outputs.at(index)->order, parent_node->outputs.at(index)->id.Get(), parent_node->outputs.at(index)->name.c_str(), type, nullptr);
                parent_node->outputs.at(index) = new_node;
            }
            else if (type == PinType::ProgramObject)
            {
                std::shared_ptr<PinValue<std::shared_ptr<ProgramObject>>> new_node = std::make_shared<PinValue<std::shared_ptr<ProgramObject>>>(index, parent_node->outputs.at(index)->order, parent_node->outputs.at(index)->id.Get(), parent_node->outputs.at(index)->name.c_str(), type, nullptr);
                parent_node->outputs.at(index) = new_node;
            }
            else if (type == PinType::VertexShaderObject)
            {
                std::shared_ptr<PinValue<std::shared_ptr<ShaderObject>>> new_node = std::make_shared<PinValue<std::shared_ptr<ShaderObject>>>(index, parent_node->outputs.at(index)->order, parent_node->outputs.at(index)->id.Get(), parent_node->outputs.at(index)->name.c_str(), type, nullptr);
                parent_node->outputs.at(index) = new_node;
            }
            else if (type == PinType::FragmentShaderObject)
            {
                std::shared_ptr<PinValue<std::shared_ptr<ShaderObject>>> new_node = std::make_shared<PinValue<std::shared_ptr<ShaderObject>>>(index, parent_node->outputs.at(index)->order, parent_node->outputs.at(index)->id.Get(), parent_node->outputs.at(index)->name.c_str(), type, nullptr);
                parent_node->outputs.at(index) = new_node;
            }
            else if (type == PinType::MeshObject)
            {
                std::shared_ptr<PinValue<std::shared_ptr<MeshObject>>> new_node = std::make_shared<PinValue<std::shared_ptr<MeshObject>>>(index, parent_node->outputs.at(index)->order, parent_node->outputs.at(index)->id.Get(), parent_node->outputs.at(index)->name.c_str(), type, nullptr);
                parent_node->outputs.at(index) = new_node;
            }
            parent_node->outputs.at(index)->node = node;
            parent_node->outputs.at(index)->isTemplate = isTemplate;
            parent_node->outputs.at(index)->template_allowed_types = template_allowed_types;
            parent_node->outputs.at(index)->isArr = isArr;
            parent_node->outputs.at(index)->isGeneralArray = isGeneralArray;
        }
    }
    else
    {
        if (kind == PinKind::Input)
        {
            std::shared_ptr<Node> node = parent_node->inputs.at(index)->node;;
            bool isTemplate = parent_node->inputs.at(index)->isTemplate;
            std::vector<PinType> template_allowed_types = parent_node->inputs.at(index)->template_allowed_types;
            bool isGeneralArray = parent_node->inputs.at(index)->isGeneralArray;
            if (type == PinType::Bool)
            {
                std::shared_ptr<PinArrValue<bool>> new_node = std::make_shared<PinArrValue<bool>>(index, parent_node->inputs.at(index)->order, parent_node->inputs.at(index)->id.Get(), parent_node->inputs.at(index)->name.c_str(), type, std::make_shared<std::vector<bool>>());
                parent_node->inputs.at(index) = new_node;
            }
            else if (type == PinType::Float)
            {
                std::shared_ptr<PinArrValue<float>> new_node = std::make_shared<PinArrValue<float>>(index, parent_node->inputs.at(index)->order, parent_node->inputs.at(index)->id.Get(), parent_node->inputs.at(index)->name.c_str(), type, std::make_shared<std::vector<float>>());
                parent_node->inputs.at(index) = new_node;
            }
            else if (type == PinType::Int)
            {
                std::shared_ptr<PinArrValue<int>> new_node = std::make_shared<PinArrValue<int>>(index, parent_node->inputs.at(index)->order, parent_node->inputs.at(index)->id.Get(), parent_node->inputs.at(index)->name.c_str(), type, std::make_shared<std::vector<int>>());
                parent_node->inputs.at(index) = new_node;
            }
            else if (type == PinType::String)
            {
                std::shared_ptr<PinArrValue<std::string>> new_node = std::make_shared<PinArrValue<std::string>>(index, parent_node->inputs.at(index)->order, parent_node->inputs.at(index)->id.Get(), parent_node->inputs.at(index)->name.c_str(), type, std::make_shared<std::vector<std::string>>());
                parent_node->inputs.at(index) = new_node;
            }
            else if (type == PinType::VectorI2)
            {
                std::shared_ptr<PinArrValue<glm::ivec2>> new_node = std::make_shared<PinArrValue<glm::ivec2>>(index, parent_node->inputs.at(index)->order, parent_node->inputs.at(index)->id.Get(), parent_node->inputs.at(index)->name.c_str(), type, std::make_shared<std::vector<glm::ivec2>>());
                parent_node->inputs.at(index) = new_node;
            }
            else if (type == PinType::VectorI3)
            {
                std::shared_ptr<PinArrValue<glm::ivec3>> new_node = std::make_shared<PinArrValue<glm::ivec3>>(index, parent_node->inputs.at(index)->order, parent_node->inputs.at(index)->id.Get(), parent_node->inputs.at(index)->name.c_str(), type, std::make_shared<std::vector<glm::ivec3>>());
                parent_node->inputs.at(index) = new_node;
            }
            else if (type == PinType::VectorI4)
            {
                std::shared_ptr<PinArrValue<glm::ivec4>> new_node = std::make_shared<PinArrValue<glm::ivec4>>(index, parent_node->inputs.at(index)->order, parent_node->inputs.at(index)->id.Get(), parent_node->inputs.at(index)->name.c_str(), type, std::make_shared<std::vector<glm::ivec4>>());
                parent_node->inputs.at(index) = new_node;
            }
            else if (type == PinType::Vector2)
            {
                std::shared_ptr<PinArrValue<glm::vec2>> new_node = std::make_shared<PinArrValue<glm::vec2>>(index, parent_node->inputs.at(index)->order, parent_node->inputs.at(index)->id.Get(), parent_node->inputs.at(index)->name.c_str(), type, std::make_shared<std::vector<glm::vec2>>());
                parent_node->inputs.at(index) = new_node;
            }
            else if (type == PinType::Vector3)
            {
                std::shared_ptr<PinArrValue<glm::vec3>> new_node = std::make_shared<PinArrValue<glm::vec3>>(index, parent_node->inputs.at(index)->order, parent_node->inputs.at(index)->id.Get(), parent_node->inputs.at(index)->name.c_str(), type, std::make_shared<std::vector<glm::vec3>>());
                parent_node->inputs.at(index) = new_node;
            }
            else if (type == PinType::Vector4)
            {
                std::shared_ptr<PinArrValue<glm::vec4>> new_node = std::make_shared<PinArrValue<glm::vec4>>(index, parent_node->inputs.at(index)->order, parent_node->inputs.at(index)->id.Get(), parent_node->inputs.at(index)->name.c_str(), type, std::make_shared<std::vector<glm::vec4>>());
                parent_node->inputs.at(index) = new_node;
            }
            else if (type == PinType::Matrix4x4)
            {
                std::shared_ptr<PinArrValue<glm::mat4>> new_node = std::make_shared<PinArrValue<glm::mat4>>(index, parent_node->inputs.at(index)->order, parent_node->inputs.at(index)->id.Get(), parent_node->inputs.at(index)->name.c_str(), type, std::make_shared<std::vector<glm::mat4>>());
                parent_node->inputs.at(index) = new_node;
            }
            else if (type == PinType::TextureObject)
            {
                std::shared_ptr<PinArrValue<std::shared_ptr<TextureObject>>> new_node = std::make_shared<PinArrValue<std::shared_ptr<TextureObject>>>(index, parent_node->inputs.at(index)->order, parent_node->inputs.at(index)->id.Get(), parent_node->inputs.at(index)->name.c_str(), type, std::make_shared<std::vector<std::shared_ptr<TextureObject>>>());
                parent_node->inputs.at(index) = new_node;
            }
            else if (type == PinType::ProgramObject)
            {
                std::shared_ptr<PinArrValue<std::shared_ptr<ProgramObject>>> new_node = std::make_shared<PinArrValue<std::shared_ptr<ProgramObject>>>(index, parent_node->inputs.at(index)->order, parent_node->inputs.at(index)->id.Get(), parent_node->inputs.at(index)->name.c_str(), type, std::make_shared<std::vector<std::shared_ptr<ProgramObject>>>());
                parent_node->inputs.at(index) = new_node;
            }
            else if (type == PinType::VertexShaderObject)
            {
                std::shared_ptr<PinArrValue<std::shared_ptr<ShaderObject>>> new_node = std::make_shared<PinArrValue<std::shared_ptr<ShaderObject>>>(index, parent_node->inputs.at(index)->order, parent_node->inputs.at(index)->id.Get(), parent_node->inputs.at(index)->name.c_str(), type, std::make_shared<std::vector<std::shared_ptr<ShaderObject>>>());
                parent_node->inputs.at(index) = new_node;
            }
            else if (type == PinType::FragmentShaderObject)
            {
                std::shared_ptr<PinArrValue<std::shared_ptr<ShaderObject>>> new_node = std::make_shared<PinArrValue<std::shared_ptr<ShaderObject>>>(index, parent_node->inputs.at(index)->order, parent_node->inputs.at(index)->id.Get(), parent_node->inputs.at(index)->name.c_str(), type, std::make_shared<std::vector<std::shared_ptr<ShaderObject>>>());
                parent_node->inputs.at(index) = new_node;
            }
            else if (type == PinType::MeshObject)
            {
                std::shared_ptr<PinArrValue<std::shared_ptr<MeshObject>>> new_node = std::make_shared<PinArrValue<std::shared_ptr<MeshObject>>>(index, parent_node->inputs.at(index)->order, parent_node->inputs.at(index)->id.Get(), parent_node->inputs.at(index)->name.c_str(), type, std::make_shared<std::vector<std::shared_ptr<MeshObject>>>());
                parent_node->inputs.at(index) = new_node;
            }
            parent_node->inputs.at(index)->node = node;
            parent_node->inputs.at(index)->isTemplate = isTemplate;
            parent_node->inputs.at(index)->template_allowed_types = template_allowed_types;
            parent_node->inputs.at(index)->isArr = isArr;
            parent_node->inputs.at(index)->isGeneralArray = isGeneralArray;
        }
        else if (kind == PinKind::Output)
        {
            std::shared_ptr<Node> node = parent_node->outputs.at(index)->node;;
            bool isTemplate = parent_node->outputs.at(index)->isTemplate;
            std::vector<PinType> template_allowed_types = parent_node->outputs.at(index)->template_allowed_types;
            bool isGeneralArray = parent_node->outputs.at(index)->isGeneralArray;
            if (type == PinType::Bool)
            {
                std::shared_ptr<PinArrValue<bool>> new_node = std::make_shared<PinArrValue<bool>>(index, parent_node->outputs.at(index)->order, parent_node->outputs.at(index)->id.Get(), parent_node->outputs.at(index)->name.c_str(), type, std::make_shared<std::vector<bool>>());
                parent_node->outputs.at(index) = new_node;
            }
            else if (type == PinType::Float)
            {
                std::shared_ptr<PinArrValue<float>> new_node = std::make_shared<PinArrValue<float>>(index, parent_node->outputs.at(index)->order, parent_node->outputs.at(index)->id.Get(), parent_node->outputs.at(index)->name.c_str(), type, std::make_shared<std::vector<float>>());
                parent_node->outputs.at(index) = new_node;
            }
            else if (type == PinType::Int)
            {
                std::shared_ptr<PinArrValue<int>> new_node = std::make_shared<PinArrValue<int>>(index, parent_node->outputs.at(index)->order, parent_node->outputs.at(index)->id.Get(), parent_node->outputs.at(index)->name.c_str(), type, std::make_shared<std::vector<int>>());
                parent_node->outputs.at(index) = new_node;
            }
            else if (type == PinType::String)
            {
                std::shared_ptr<PinArrValue<std::string>> new_node = std::make_shared<PinArrValue<std::string>>(index, parent_node->outputs.at(index)->order, parent_node->outputs.at(index)->id.Get(), parent_node->outputs.at(index)->name.c_str(), type, std::make_shared<std::vector<std::string>>());
                parent_node->outputs.at(index) = new_node;
            }
            else if (type == PinType::VectorI2)
            {
                std::shared_ptr<PinArrValue<glm::ivec2>> new_node = std::make_shared<PinArrValue<glm::ivec2>>(index, parent_node->outputs.at(index)->order, parent_node->outputs.at(index)->id.Get(), parent_node->outputs.at(index)->name.c_str(), type, std::make_shared<std::vector<glm::ivec2>>());
                parent_node->outputs.at(index) = new_node;
            }
            else if (type == PinType::VectorI3)
            {
                std::shared_ptr<PinArrValue<glm::ivec3>> new_node = std::make_shared<PinArrValue<glm::ivec3>>(index, parent_node->outputs.at(index)->order, parent_node->outputs.at(index)->id.Get(), parent_node->outputs.at(index)->name.c_str(), type, std::make_shared<std::vector<glm::ivec3>>());
                parent_node->outputs.at(index) = new_node;
            }
            else if (type == PinType::VectorI4)
            {
                std::shared_ptr<PinArrValue<glm::ivec4>> new_node = std::make_shared<PinArrValue<glm::ivec4>>(index, parent_node->outputs.at(index)->order, parent_node->outputs.at(index)->id.Get(), parent_node->outputs.at(index)->name.c_str(), type, std::make_shared<std::vector<glm::ivec4>>());
                parent_node->outputs.at(index) = new_node;
            }
            else if (type == PinType::Vector2)
            {
                std::shared_ptr<PinArrValue<glm::vec2>> new_node = std::make_shared<PinArrValue<glm::vec2>>(index, parent_node->outputs.at(index)->order, parent_node->outputs.at(index)->id.Get(), parent_node->outputs.at(index)->name.c_str(), type, std::make_shared<std::vector<glm::vec2>>());
                parent_node->outputs.at(index) = new_node;
            }
            else if (type == PinType::Vector3)
            {
                std::shared_ptr<PinArrValue<glm::vec3>> new_node = std::make_shared<PinArrValue<glm::vec3>>(index, parent_node->outputs.at(index)->order, parent_node->outputs.at(index)->id.Get(), parent_node->outputs.at(index)->name.c_str(), type, std::make_shared<std::vector<glm::vec3>>());
                parent_node->outputs.at(index) = new_node;
            }
            else if (type == PinType::Vector4)
            {
                std::shared_ptr<PinArrValue<glm::vec4>> new_node = std::make_shared<PinArrValue<glm::vec4>>(index, parent_node->outputs.at(index)->order, parent_node->outputs.at(index)->id.Get(), parent_node->outputs.at(index)->name.c_str(), type, std::make_shared<std::vector<glm::vec4>>());
                parent_node->outputs.at(index) = new_node;
            }
            else if (type == PinType::Matrix4x4)
            {
                std::shared_ptr<PinArrValue<glm::mat4>> new_node = std::make_shared<PinArrValue<glm::mat4>>(index, parent_node->outputs.at(index)->order, parent_node->outputs.at(index)->id.Get(), parent_node->outputs.at(index)->name.c_str(), type, std::make_shared<std::vector<glm::mat4>>());
                parent_node->outputs.at(index) = new_node;
            }
            else if (type == PinType::TextureObject)
            {
                std::shared_ptr<PinArrValue<std::shared_ptr<TextureObject>>> new_node = std::make_shared<PinArrValue<std::shared_ptr<TextureObject>>>(index, parent_node->outputs.at(index)->order, parent_node->outputs.at(index)->id.Get(), parent_node->outputs.at(index)->name.c_str(), type, std::make_shared<std::vector<std::shared_ptr<TextureObject>>>());
                parent_node->outputs.at(index) = new_node;
            }
            else if (type == PinType::ProgramObject)
            {
                std::shared_ptr<PinArrValue<std::shared_ptr<ProgramObject>>> new_node = std::make_shared<PinArrValue<std::shared_ptr<ProgramObject>>>(index, parent_node->outputs.at(index)->order, parent_node->outputs.at(index)->id.Get(), parent_node->outputs.at(index)->name.c_str(), type, std::make_shared<std::vector<std::shared_ptr<ProgramObject>>>());
                parent_node->outputs.at(index) = new_node;
            }
            else if (type == PinType::VertexShaderObject)
            {
                std::shared_ptr<PinArrValue<std::shared_ptr<ShaderObject>>> new_node = std::make_shared<PinArrValue<std::shared_ptr<ShaderObject>>>(index, parent_node->outputs.at(index)->order, parent_node->outputs.at(index)->id.Get(), parent_node->outputs.at(index)->name.c_str(), type, std::make_shared<std::vector<std::shared_ptr<ShaderObject>>>());
                parent_node->outputs.at(index) = new_node;
            }
            else if (type == PinType::FragmentShaderObject)
            {
                std::shared_ptr<PinArrValue<std::shared_ptr<ShaderObject>>> new_node = std::make_shared<PinArrValue<std::shared_ptr<ShaderObject>>>(index, parent_node->outputs.at(index)->order, parent_node->outputs.at(index)->id.Get(), parent_node->outputs.at(index)->name.c_str(), type, std::make_shared<std::vector<std::shared_ptr<ShaderObject>>>());
                parent_node->outputs.at(index) = new_node;
            }
            else if (type == PinType::MeshObject)
            {
                std::shared_ptr<PinArrValue<std::shared_ptr<MeshObject>>> new_node = std::make_shared<PinArrValue<std::shared_ptr<MeshObject>>>(index, parent_node->outputs.at(index)->order, parent_node->outputs.at(index)->id.Get(), parent_node->outputs.at(index)->name.c_str(), type, std::make_shared<std::vector<std::shared_ptr<MeshObject>>>());
                parent_node->outputs.at(index) = new_node;
            }
            parent_node->outputs.at(index)->node = node;
            parent_node->outputs.at(index)->isTemplate = isTemplate;
            parent_node->outputs.at(index)->template_allowed_types = template_allowed_types;
            parent_node->outputs.at(index)->isArr = isArr;
            parent_node->outputs.at(index)->isGeneralArray = isGeneralArray;
        }
    }
    
    BuildNode(parent_node);
}

void UtilsDeleteLink(std::shared_ptr<Link> link)
{
    if (link->startPin)
    {
        link->startPin->links.erase(std::remove(link->startPin->links.begin(), link->startPin->links.end(), link), link->startPin->links.end());
        link->startPin = nullptr;
    }
    if (link->endPin)
    {
        link->endPin->links.erase(std::remove(link->endPin->links.begin(), link->endPin->links.end(), link), link->endPin->links.end());
        link->endPin = nullptr;
    }
    ed::DeleteLink(link->id);
}

void UtilsDeleteLinks(std::shared_ptr<BasePin> pin)
{
    while (pin->links.size() > 0)
    {
        UtilsDeleteLink(pin->links.at(0));
    }
    pin->links.clear();
}

template<typename T>
T GetInputPinValue(std::shared_ptr<Node>& parent_node, std::string pin_key)
{
    if (parent_node->inputs.at(pin_key)->links.size() > 0)
    {
        if (parent_node->inputs.at(pin_key)->links.at(0))
        {
            if (parent_node->inputs.at(pin_key)->links.at(0)->startPin)
            {
                std::shared_ptr<PinValue<T>> input_pin = std::dynamic_pointer_cast<PinValue<T>>(parent_node->inputs.at(pin_key)->links.at(0)->startPin);
                if (input_pin)
                {
                    if (input_pin->node)
                    {
                        input_pin->node->node_funcs->NoFlowUpdatePinsValues();
                        std::dynamic_pointer_cast<PinValue<T>>(parent_node->inputs.at(pin_key))->value = input_pin->GetValue();
                        return input_pin->GetValue();
                    }
                }
            }
        }
    }
    std::shared_ptr<PinValue<T>> input_pin = std::dynamic_pointer_cast<PinValue<T>>(parent_node->inputs.at(pin_key));
    input_pin->value = input_pin->default_value;
    return input_pin->GetValue();
}

template<typename T>
std::shared_ptr<std::vector<T>> GetInputPinArrValue(std::shared_ptr<Node>& parent_node, std::string pin_key)
{
    if (parent_node->inputs.at(pin_key)->links.size() > 0)
    {
        if (parent_node->inputs.at(pin_key)->links.at(0))
        {
            if (parent_node->inputs.at(pin_key)->links.at(0)->startPin)
            {
                std::shared_ptr<PinArrValue<T>> input_pin = std::dynamic_pointer_cast<PinArrValue<T>>(parent_node->inputs.at(pin_key)->links.at(0)->startPin);
                if (input_pin)
                {
                    if (input_pin->node)
                    {
                        input_pin->node->node_funcs->NoFlowUpdatePinsValues();
                        //std::dynamic_pointer_cast<PinArrValue<T>>(parent_node->inputs.at(pin_key))->value = input_pin->GetValue();
                        return input_pin->GetValue();
                    }
                }
            }
        }
    }
    std::shared_ptr<PinArrValue<T>> input_pin = std::dynamic_pointer_cast<PinArrValue<T>>(parent_node->inputs.at(pin_key));
    //input_pin->value = input_pin->default_value;
    return input_pin->GetValue();
}

template<typename T>
std::shared_ptr<std::vector<T>> GetInputPinArrDefaultValue(std::shared_ptr<Node>& parent_node, std::string pin_key)
{
    if (parent_node->inputs.at(pin_key)->links.size() > 0)
    {
        if (parent_node->inputs.at(pin_key)->links.at(0))
        {
            if (parent_node->inputs.at(pin_key)->links.at(0)->startPin)
            {
                std::shared_ptr<PinArrValue<T>> input_pin = std::dynamic_pointer_cast<PinArrValue<T>>(parent_node->inputs.at(pin_key)->links.at(0)->startPin);
                if (input_pin)
                {
                    if (input_pin->node)
                    {
                        input_pin->node->node_funcs->NoFlowUpdatePinsValues();
                        //std::dynamic_pointer_cast<PinArrValue<T>>(parent_node->inputs.at(pin_key))->value = input_pin->default_value;
                        return input_pin->default_value;
                    }
                }
            }
        }
    }
    std::shared_ptr<PinArrValue<T>> input_pin = std::dynamic_pointer_cast<PinArrValue<T>>(parent_node->inputs.at(pin_key));
    //input_pin->value = input_pin->default_value;
    return input_pin->GetValue();
}














template bool GetInputPinValue(std::shared_ptr<Node>& parent_node, std::string pin_key);
template int GetInputPinValue(std::shared_ptr<Node>& parent_node, std::string pin_key);
template float GetInputPinValue(std::shared_ptr<Node>& parent_node, std::string pin_key);
template std::string GetInputPinValue(std::shared_ptr<Node>& parent_node, std::string pin_key);
template glm::ivec2 GetInputPinValue(std::shared_ptr<Node>& parent_node, std::string pin_key);
template glm::ivec3 GetInputPinValue(std::shared_ptr<Node>& parent_node, std::string pin_key);
template glm::ivec4 GetInputPinValue(std::shared_ptr<Node>& parent_node, std::string pin_key);
template glm::vec2 GetInputPinValue(std::shared_ptr<Node>& parent_node, std::string pin_key);
template glm::vec3 GetInputPinValue(std::shared_ptr<Node>& parent_node, std::string pin_key);
template glm::vec4 GetInputPinValue(std::shared_ptr<Node>& parent_node, std::string pin_key);
template glm::mat4 GetInputPinValue(std::shared_ptr<Node>& parent_node, std::string pin_key);
template std::shared_ptr<TextureObject> GetInputPinValue(std::shared_ptr<Node>& parent_node, std::string pin_key);
template std::shared_ptr<ProgramObject> GetInputPinValue(std::shared_ptr<Node>& parent_node, std::string pin_key);
template std::shared_ptr<ShaderObject> GetInputPinValue(std::shared_ptr<Node>& parent_node, std::string pin_key);
template std::shared_ptr<MeshObject> GetInputPinValue(std::shared_ptr<Node>& parent_node, std::string pin_key);



template std::shared_ptr<std::vector<bool>> GetInputPinArrValue(std::shared_ptr<Node>& parent_node, std::string pin_key);
template std::shared_ptr<std::vector<int>> GetInputPinArrValue(std::shared_ptr<Node>& parent_node, std::string pin_key);
template std::shared_ptr<std::vector<float>> GetInputPinArrValue(std::shared_ptr<Node>& parent_node, std::string pin_key);
template std::shared_ptr<std::vector<std::string>> GetInputPinArrValue(std::shared_ptr<Node>& parent_node, std::string pin_key);
template std::shared_ptr<std::vector<glm::ivec2>> GetInputPinArrValue(std::shared_ptr<Node>& parent_node, std::string pin_key);
template std::shared_ptr<std::vector<glm::ivec3>> GetInputPinArrValue(std::shared_ptr<Node>& parent_node, std::string pin_key);
template std::shared_ptr<std::vector<glm::ivec4>> GetInputPinArrValue(std::shared_ptr<Node>& parent_node, std::string pin_key);
template std::shared_ptr<std::vector<glm::vec2>> GetInputPinArrValue(std::shared_ptr<Node>& parent_node, std::string pin_key);
template std::shared_ptr<std::vector<glm::vec3>> GetInputPinArrValue(std::shared_ptr<Node>& parent_node, std::string pin_key);
template std::shared_ptr<std::vector<glm::vec4>> GetInputPinArrValue(std::shared_ptr<Node>& parent_node, std::string pin_key);
template std::shared_ptr<std::vector<glm::mat4>> GetInputPinArrValue(std::shared_ptr<Node>& parent_node, std::string pin_key);
template std::shared_ptr<std::vector<std::shared_ptr<TextureObject>>> GetInputPinArrValue(std::shared_ptr<Node>& parent_node, std::string pin_key);
template std::shared_ptr<std::vector<std::shared_ptr<ProgramObject>>> GetInputPinArrValue(std::shared_ptr<Node>& parent_node, std::string pin_key);
template std::shared_ptr<std::vector<std::shared_ptr<ShaderObject>>> GetInputPinArrValue(std::shared_ptr<Node>& parent_node, std::string pin_key);
template std::shared_ptr<std::vector<std::shared_ptr<MeshObject>>> GetInputPinArrValue(std::shared_ptr<Node>& parent_node, std::string pin_key);



template std::shared_ptr<std::vector<bool>> GetInputPinArrDefaultValue(std::shared_ptr<Node>& parent_node, std::string pin_key);
template std::shared_ptr<std::vector<int>> GetInputPinArrDefaultValue(std::shared_ptr<Node>& parent_node, std::string pin_key);
template std::shared_ptr<std::vector<float>> GetInputPinArrDefaultValue(std::shared_ptr<Node>& parent_node, std::string pin_key);
template std::shared_ptr<std::vector<std::string>> GetInputPinArrDefaultValue(std::shared_ptr<Node>& parent_node, std::string pin_key);
template std::shared_ptr<std::vector<glm::ivec2>> GetInputPinArrDefaultValue(std::shared_ptr<Node>& parent_node, std::string pin_key);
template std::shared_ptr<std::vector<glm::ivec3>> GetInputPinArrDefaultValue(std::shared_ptr<Node>& parent_node, std::string pin_key);
template std::shared_ptr<std::vector<glm::ivec4>> GetInputPinArrDefaultValue(std::shared_ptr<Node>& parent_node, std::string pin_key);
template std::shared_ptr<std::vector<glm::vec2>> GetInputPinArrDefaultValue(std::shared_ptr<Node>& parent_node, std::string pin_key);
template std::shared_ptr<std::vector<glm::vec3>> GetInputPinArrDefaultValue(std::shared_ptr<Node>& parent_node, std::string pin_key);
template std::shared_ptr<std::vector<glm::vec4>> GetInputPinArrDefaultValue(std::shared_ptr<Node>& parent_node, std::string pin_key);
template std::shared_ptr<std::vector<glm::mat4>> GetInputPinArrDefaultValue(std::shared_ptr<Node>& parent_node, std::string pin_key);
template std::shared_ptr<std::vector<std::shared_ptr<TextureObject>>> GetInputPinArrDefaultValue(std::shared_ptr<Node>& parent_node, std::string pin_key);
template std::shared_ptr<std::vector<std::shared_ptr<ProgramObject>>> GetInputPinArrDefaultValue(std::shared_ptr<Node>& parent_node, std::string pin_key);
template std::shared_ptr<std::vector<std::shared_ptr<ShaderObject>>> GetInputPinArrDefaultValue(std::shared_ptr<Node>& parent_node, std::string pin_key);
template std::shared_ptr<std::vector<std::shared_ptr<MeshObject>>> GetInputPinArrDefaultValue(std::shared_ptr<Node>& parent_node, std::string pin_key);