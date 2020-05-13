#include "Application.h"
#include <string>
#include <sstream>
#include <iostream>
#include <iterator>
#include <vector>
#include <map>
#include <algorithm>
#include <utility>
#include <imgui_node_editor.h>
#include <ax/Math2D.h>
#include <ax/Builders.h>
#include <ax/Widgets.h>

#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui_internal.h>
#include <memory>
#include <functional>

#include "InstanceConfig.h"
#include "EditorConfig.h"
#include "imgui_utils.h"
#include "project_enums.h"
#include "project_classes.h"
#include "utils.h"
#include "id_generator.h"
#include "nodes_builder.h"
#include "nodes/collect_search_nodes.h"

// To add GL Main Loop
#include "nodes/gl_nodes_1.h"

using namespace ax;
namespace ed = ax::NodeEditor;
namespace util = ax::NodeEditor::Utilities;
using ax::Widgets::IconType;


// Set main variables
ed::EditorContext* m_Editor = nullptr;

// Varialbes for editor
const int            s_PinIconSize = 24;
ImTextureID          s_HeaderBackground = nullptr;
ImTextureID          s_SaveIcon = nullptr;
ImTextureID          s_RestoreIcon = nullptr;

ed::NodeId selectedNode;
ed::NodeId contextNodeId = 0;
ed::LinkId contextLinkId = 0;
ed::PinId  contextPinId = 0;
bool createNewNode = false;
std::shared_ptr<BasePin> newNodeLinkPin = nullptr;
std::shared_ptr<BasePin> newLinkPin = nullptr;

// Boolean variables to indicate which window to open
bool showStyleEditor = false;
bool showNodeHierarchyWindow = false;
bool showTextureViewer = false;
bool showNodeInspector = false;

// Variables for 'Create Placeholder' Window
std::string create_placeholder_name;
std::string create_placeholder_type_combo;

// Variable for 'Select Placeholder' Window
std::string select_placeholder_combo;

// Variables for 'Rename Placeholder' Window
std::string rename_placeholder_name;
std::string rename_placeholder_original_combo;

// Variable for 'Delete Placeholder' Window
std::string delete_placeholder_combo;

// Variables for seraching nodes on right click
std::vector<SearchNodeObj> search_nodes_vector;
std::string search_node_str = "";
bool reset_search_node = false;

// String variable to indicate which pin type we selected with templates pin
std::string template_pin_type_selected_item;

std::string preview_texture;


// Set timer functions variables
struct NodeIdLess
{
    bool operator()(const ed::NodeId& lhs, const ed::NodeId& rhs) const
    {
        return lhs.AsPointer() < rhs.AsPointer();
    }
};
static const float          s_TouchTime = 1.0f;
static std::map<ed::NodeId, float, NodeIdLess> s_NodeTouchTime;

static void TouchNode(ed::NodeId id)
{
    s_NodeTouchTime[id] = s_TouchTime;
}

static float GetTouchProgress(ed::NodeId id)
{
    auto it = s_NodeTouchTime.find(id);
    if (it != s_NodeTouchTime.end() && it->second > 0.0f)
        return (s_TouchTime - it->second) / s_TouchTime;
    else
        return 0.0f;
}

static void UpdateTouch()
{
    const auto deltaTime = ImGui::GetIO().DeltaTime;
    for (auto& entry : s_NodeTouchTime)
    {
        if (entry.second > 0.0f)
            entry.second -= deltaTime;
    }
}


// Main App
const char* Application_GetName()
{
    return "NodeGL V1";
}

void Application_Initialize()
{
    auto config = InstanceConfig::instance();
    s_HeaderBackground = Application_LoadTexture("Data/BlueprintBackground.png");
    s_SaveIcon = Application_LoadTexture("Data/ic_save_white_24dp.png");
    s_RestoreIcon = Application_LoadTexture("Data/ic_restore_white_24dp.png");

    ed::Config ed_config;
    ed_config.SettingsFile = "NodeGL.json";
    ed_config.LoadNodeSettings = [](ed::NodeId nodeId, char* data, void* userPointer) -> size_t
    {
        auto config = InstanceConfig::instance();
        auto node = FindNode(nodeId, config->s_Nodes);
        if (!node)
            return 0;

        if (data != nullptr)
            memcpy(data, node->state.data(), node->state.size());
        size_t ret_size = node->state.size();
        node = nullptr;
        return ret_size;
    };
    ed_config.SaveNodeSettings = [](ed::NodeId nodeId, const char* data, size_t size, ed::SaveReasonFlags reason, void* userPointer) -> bool
    {
        auto config = InstanceConfig::instance();
        auto node = FindNode(nodeId, config->s_Nodes);
        if (!node)
            return false;

        node->state.assign(data, size);

        TouchNode(nodeId);
        node = nullptr;
        return true;
    };

    m_Editor = ed::CreateEditor(&ed_config);
    ed::SetCurrentEditor(m_Editor);

    std::shared_ptr<Node> node;
    node = GlMainLoop(config->s_Nodes);      ed::SetNodePosition(node->id, ImVec2(0, 0));

    BuildNodes(config->s_Nodes);
    ed::NavigateToContent();
    search_node_str.reserve(128);
    CollectSearchNodes(search_nodes_vector);
}

void Application_Finalize()
{
    auto releaseTexture = [](ImTextureID& id)
    {
        if (id)
        {
            Application_DestroyTexture(id);
            id = nullptr;
        }
    };

    releaseTexture(s_RestoreIcon);
    releaseTexture(s_SaveIcon);
    releaseTexture(s_HeaderBackground);

    if (m_Editor)
    {
        ed::DestroyEditor(m_Editor);
        m_Editor = nullptr;
    }
}

ImColor GetIconColor(PinType type)
{
    switch (type)
    {
    default:
    case PinType::Flow:     return ImColor(255, 255, 255);
    case PinType::Bool:     return ImColor(220, 48, 48);
    case PinType::Int:      return ImColor(68, 201, 156);
    case PinType::Float:    return ImColor(147, 226, 74);
    case PinType::String:   return ImColor(124, 21, 153);
    case PinType::Vector3:   return ImColor(1, 91, 60);
    case PinType::Vector4:   return ImColor(107, 32, 124);
    case PinType::Matrix4x4:   return ImColor(223, 234, 149);
    case PinType::ProgramObject:   return ImColor(89, 48, 156);
    case PinType::VertexShaderObject:   return ImColor(100, 149, 106);
    case PinType::FragmentShaderObject:   return ImColor(239, 194, 154);
    case PinType::TextureObject:   return ImColor(75, 116, 117);
    case PinType::MeshObject:   return ImColor(90, 176, 177);
    }
};

void DrawPinIcon(std::shared_ptr<BasePin> pin, bool connected, int alpha)
{
    IconType iconType;
    ImColor  color = GetIconColor(pin->type);
    color.Value.w = alpha / 255.0f;
    if (pin->isTemplate == false)
    {
        switch (pin->type)
        {
        case PinType::Flow:     iconType = IconType::Flow;   break;
        case PinType::Bool:     iconType = IconType::Circle; break;
        case PinType::Int:      iconType = IconType::Circle; break;
        case PinType::Float:    iconType = IconType::Circle; break;
        case PinType::String:   iconType = IconType::Circle; break;
        case PinType::Vector3:   iconType = IconType::Circle; break;
        case PinType::Vector4:   iconType = IconType::Circle; break;
        case PinType::Matrix4x4:   iconType = IconType::Circle; break;
        case PinType::ProgramObject:   iconType = IconType::Circle; break;
        case PinType::VertexShaderObject:   iconType = IconType::Circle; break;
        case PinType::FragmentShaderObject:   iconType = IconType::Circle; break;
        case PinType::TextureObject:   iconType = IconType::Circle; break;
        case PinType::MeshObject:   iconType = IconType::Circle; break;
        default:
            return;
        }
    }
    else
    {
        iconType = IconType::Diamond;
    }

    ax::Widgets::Icon(ImVec2(s_PinIconSize, s_PinIconSize), iconType, connected, color, ImColor(32, 32, 32, alpha));
};

void ShowStyleEditor(bool* show = nullptr)
{
    if (!ImGui::Begin("Style", show))
    {
        ImGui::End();
        return;
    }

    auto paneWidth = ImGui::GetContentRegionAvailWidth();

    auto& editorStyle = ed::GetStyle();
    ImGui::BeginHorizontal("Style buttons", ImVec2(paneWidth, 0), 1.0f);
    ImGui::TextUnformatted("Values");
    ImGui::Spring();
    if (ImGui::Button("Reset to defaults"))
        editorStyle = ed::Style();
    ImGui::EndHorizontal();
    ImGui::Spacing();
    ImGui::DragFloat4("Node Padding", &editorStyle.NodePadding.x, 0.1f, 0.0f, 40.0f);
    ImGui::DragFloat("Node Rounding", &editorStyle.NodeRounding, 0.1f, 0.0f, 40.0f);
    ImGui::DragFloat("Node Border Width", &editorStyle.NodeBorderWidth, 0.1f, 0.0f, 15.0f);
    ImGui::DragFloat("Hovered Node Border Width", &editorStyle.HoveredNodeBorderWidth, 0.1f, 0.0f, 15.0f);
    ImGui::DragFloat("Selected Node Border Width", &editorStyle.SelectedNodeBorderWidth, 0.1f, 0.0f, 15.0f);
    ImGui::DragFloat("Pin Rounding", &editorStyle.PinRounding, 0.1f, 0.0f, 40.0f);
    ImGui::DragFloat("Pin Border Width", &editorStyle.PinBorderWidth, 0.1f, 0.0f, 15.0f);
    ImGui::DragFloat("Link Strength", &editorStyle.LinkStrength, 1.0f, 0.0f, 500.0f);
    //ImVec2  SourceDirection;
    //ImVec2  TargetDirection;
    ImGui::DragFloat("Scroll Duration", &editorStyle.ScrollDuration, 0.001f, 0.0f, 2.0f);
    ImGui::DragFloat("Flow Marker Distance", &editorStyle.FlowMarkerDistance, 1.0f, 1.0f, 200.0f);
    ImGui::DragFloat("Flow Speed", &editorStyle.FlowSpeed, 1.0f, 1.0f, 2000.0f);
    ImGui::DragFloat("Flow Duration", &editorStyle.FlowDuration, 0.001f, 0.0f, 5.0f);
    //ImVec2  PivotAlignment;
    //ImVec2  PivotSize;
    //ImVec2  PivotScale;
    //float   PinCorners;
    //float   PinRadius;
    //float   PinArrowSize;
    //float   PinArrowWidth;
    ImGui::DragFloat("Group Rounding", &editorStyle.GroupRounding, 0.1f, 0.0f, 40.0f);
    ImGui::DragFloat("Group Border Width", &editorStyle.GroupBorderWidth, 0.1f, 0.0f, 15.0f);

    ImGui::Separator();

    static ImGuiColorEditFlags edit_mode = ImGuiColorEditFlags_RGB;
    ImGui::BeginHorizontal("Color Mode", ImVec2(paneWidth, 0), 1.0f);
    ImGui::TextUnformatted("Filter Colors");
    ImGui::Spring();
    ImGui::RadioButton("RGB", &edit_mode, ImGuiColorEditFlags_RGB);
    ImGui::Spring(0);
    ImGui::RadioButton("HSV", &edit_mode, ImGuiColorEditFlags_HSV);
    ImGui::Spring(0);
    ImGui::RadioButton("HEX", &edit_mode, ImGuiColorEditFlags_HEX);
    ImGui::EndHorizontal();

    static ImGuiTextFilter filter;
    filter.Draw("", paneWidth);

    ImGui::Spacing();

    ImGui::PushItemWidth(-160);
    for (int i = 0; i < ed::StyleColor_Count; ++i)
    {
        auto name = ed::GetStyleColorName((ed::StyleColor)i);
        if (!filter.PassFilter(name))
            continue;

        ImGui::ColorEdit4(name, &editorStyle.Colors[i].x, edit_mode);
    }
    ImGui::PopItemWidth();

    ImGui::End();
}

void ShowNodeHierarchyWindow(bool* show = nullptr)
{
    if (!ImGui::Begin("Node Hierarchy Window", show, ImGuiWindowFlags_AlwaysVerticalScrollbar | ImGuiWindowFlags_NoResize))
    {
        ImGui::End();
        return;
    }

    auto config = InstanceConfig::instance();
    auto& io = ImGui::GetIO();
    ImGui::SetWindowSize(ImVec2(350, 512));

    auto paneWidth = ImGui::GetContentRegionAvailWidth();
    paneWidth = ImGui::GetContentRegionAvailWidth();

    std::vector<ed::NodeId> selectedNodes;
    std::vector<ed::LinkId> selectedLinks;
    selectedNodes.resize(ed::GetSelectedObjectCount());
    selectedLinks.resize(ed::GetSelectedObjectCount());

    int nodeCount = ed::GetSelectedNodes(selectedNodes.data(), static_cast<int>(selectedNodes.size()));
    int linkCount = ed::GetSelectedLinks(selectedLinks.data(), static_cast<int>(selectedLinks.size()));

    selectedNodes.resize(nodeCount);
    selectedLinks.resize(linkCount);

    int saveIconWidth = Application_GetTextureWidth(s_SaveIcon);
    int saveIconHeight = Application_GetTextureWidth(s_SaveIcon);
    int restoreIconWidth = Application_GetTextureWidth(s_RestoreIcon);
    int restoreIconHeight = Application_GetTextureWidth(s_RestoreIcon);

    ImGui::GetWindowDrawList()->AddRectFilled(
        ImGui::GetCursorScreenPos(),
        ImGui::GetCursorScreenPos() + ImVec2(paneWidth, ImGui::GetTextLineHeight()),
        ImColor(ImGui::GetStyle().Colors[ImGuiCol_HeaderActive]), ImGui::GetTextLineHeight() * 0.25f);
    ImGui::Spacing(); ImGui::SameLine();
    ImGui::TextUnformatted("Nodes");
    ImGui::Indent();
    for (auto& node : config->s_Nodes)
    {
        ImGui::PushID(node->id.AsPointer());
        auto start = ImGui::GetCursorScreenPos();

        if (const auto progress = GetTouchProgress(node->id))
        {
            ImGui::GetWindowDrawList()->AddLine(
                start + ImVec2(-8, 0),
                start + ImVec2(-8, ImGui::GetTextLineHeight()),
                IM_COL32(255, 0, 0, 255 - (int)(255 * progress)), 4.0f);
        }

        bool isSelected = std::find(selectedNodes.begin(), selectedNodes.end(), node->id) != selectedNodes.end();
        if (ImGui::Selectable((node->name + "##" + std::to_string(reinterpret_cast<uintptr_t>(node->id.AsPointer()))).c_str(), &isSelected))
        {
            if (io.KeyCtrl)
            {
                if (isSelected)
                    ed::SelectNode(node->id, true);
                else
                    ed::DeselectNode(node->id);
            }
            else
                ed::SelectNode(node->id, false);

            ed::NavigateToSelection();
        }
        if (ImGui::IsItemHovered() && !node->state.empty())
            ImGui::SetTooltip("State: %s", node->state.c_str());

        auto id = std::string("(") + std::to_string(reinterpret_cast<uintptr_t>(node->id.AsPointer())) + ")";
        auto textSize = ImGui::CalcTextSize(id.c_str(), nullptr);
        auto iconPanelPos = start + ImVec2(
            paneWidth - ImGui::GetStyle().FramePadding.x - ImGui::GetStyle().IndentSpacing - saveIconWidth - restoreIconWidth - ImGui::GetStyle().ItemInnerSpacing.x * 1,
            (ImGui::GetTextLineHeight() - saveIconHeight) / 2);
        ImGui::GetWindowDrawList()->AddText(
            ImVec2(iconPanelPos.x - textSize.x - ImGui::GetStyle().ItemInnerSpacing.x, start.y),
            IM_COL32(255, 255, 255, 255), id.c_str(), nullptr);

        auto drawList = ImGui::GetWindowDrawList();
        ImGui::SetCursorScreenPos(iconPanelPos);
        ImGui::SetItemAllowOverlap();
        if (node->savedState.empty())
        {
            if (ImGui::InvisibleButton("save", ImVec2((float)saveIconWidth, (float)saveIconHeight)))
                node->savedState = node->state;

            if (ImGui::IsItemActive())
                drawList->AddImage(s_SaveIcon, ImGui::GetItemRectMin(), ImGui::GetItemRectMax(), ImVec2(0, 0), ImVec2(1, 1), IM_COL32(255, 255, 255, 96));
            else if (ImGui::IsItemHovered())
                drawList->AddImage(s_SaveIcon, ImGui::GetItemRectMin(), ImGui::GetItemRectMax(), ImVec2(0, 0), ImVec2(1, 1), IM_COL32(255, 255, 255, 255));
            else
                drawList->AddImage(s_SaveIcon, ImGui::GetItemRectMin(), ImGui::GetItemRectMax(), ImVec2(0, 0), ImVec2(1, 1), IM_COL32(255, 255, 255, 160));
        }
        else
        {
            ImGui::Dummy(ImVec2((float)saveIconWidth, (float)saveIconHeight));
            drawList->AddImage(s_SaveIcon, ImGui::GetItemRectMin(), ImGui::GetItemRectMax(), ImVec2(0, 0), ImVec2(1, 1), IM_COL32(255, 255, 255, 32));
        }

        ImGui::SameLine(0, ImGui::GetStyle().ItemInnerSpacing.x);
        ImGui::SetItemAllowOverlap();
        if (!node->savedState.empty())
        {
            if (ImGui::InvisibleButton("restore", ImVec2((float)restoreIconWidth, (float)restoreIconHeight)))
            {
                node->state = node->savedState;
                ed::RestoreNodeState(node->id);
                node->savedState.clear();
            }

            if (ImGui::IsItemActive())
                drawList->AddImage(s_RestoreIcon, ImGui::GetItemRectMin(), ImGui::GetItemRectMax(), ImVec2(0, 0), ImVec2(1, 1), IM_COL32(255, 255, 255, 96));
            else if (ImGui::IsItemHovered())
                drawList->AddImage(s_RestoreIcon, ImGui::GetItemRectMin(), ImGui::GetItemRectMax(), ImVec2(0, 0), ImVec2(1, 1), IM_COL32(255, 255, 255, 255));
            else
                drawList->AddImage(s_RestoreIcon, ImGui::GetItemRectMin(), ImGui::GetItemRectMax(), ImVec2(0, 0), ImVec2(1, 1), IM_COL32(255, 255, 255, 160));
        }
        else
        {
            ImGui::Dummy(ImVec2((float)restoreIconWidth, (float)restoreIconHeight));
            drawList->AddImage(s_RestoreIcon, ImGui::GetItemRectMin(), ImGui::GetItemRectMax(), ImVec2(0, 0), ImVec2(1, 1), IM_COL32(255, 255, 255, 32));
        }

        ImGui::SameLine(0, 0);
        ImGui::SetItemAllowOverlap();
        ImGui::Dummy(ImVec2(0, (float)restoreIconHeight));

        ImGui::PopID();
    }
    ImGui::Unindent();

    static int changeCount = 0;

    ImGui::GetWindowDrawList()->AddRectFilled(
        ImGui::GetCursorScreenPos(),
        ImGui::GetCursorScreenPos() + ImVec2(paneWidth, ImGui::GetTextLineHeight()),
        ImColor(ImGui::GetStyle().Colors[ImGuiCol_HeaderActive]), ImGui::GetTextLineHeight() * 0.25f);
    ImGui::Spacing(); ImGui::SameLine();
    ImGui::TextUnformatted("Selection");

    ImGui::BeginHorizontal("Selection Stats", ImVec2(paneWidth, 0));
    ImGui::Text("Changed %d time%s", changeCount, changeCount > 1 ? "s" : "");
    ImGui::Spring();
    if (ImGui::Button("Deselect All"))
        ed::ClearSelection();
    ImGui::EndHorizontal();
    ImGui::Indent();
    for (int i = 0; i < nodeCount; ++i) ImGui::Text("Node (%p)", selectedNodes[i].AsPointer());
    for (int i = 0; i < linkCount; ++i) ImGui::Text("Link (%p)", selectedLinks[i].AsPointer());
    ImGui::Unindent();

    if (ed::HasSelectionChanged())
        ++changeCount;

    ImGui::End();
}

void ShowTextureViewer(bool* show = nullptr)
{
    if (!ImGui::Begin("Texture Viewer", show))
    {
        ImGui::End();
        return;
    }

    auto config = InstanceConfig::instance();
    std::vector<std::string> textures_keys = config->GetTextureMapKeys();

    if (textures_keys.size() > 0)
    {
        if (preview_texture == "" || std::find(textures_keys.begin(), textures_keys.end(), preview_texture) == textures_keys.end())
            preview_texture = textures_keys.at(0);
        if (ImGui::BeginCombo("##texture_combo", preview_texture.data())) // The second parameter is the label previewed before opening the combo.
        {
            for (int n = 0; n < textures_keys.size(); n++)
            {
                bool is_selected = (preview_texture == textures_keys.at(n));
                if (ImGui::Selectable(textures_keys.at(n).c_str(), is_selected))
                {
                    preview_texture = textures_keys.at(n);
                }
                if (is_selected)
                    ImGui::SetItemDefaultFocus();   // You may set the initial focus when opening the combo (scrolling + for keyboard navigation support)
            }
            ImGui::EndCombo();
        }
        ImGui::Image((void*)(intptr_t)config->GetTexture(preview_texture)->object_id, ImVec2(256, 256));
    }

    ImGui::End();
}

void ShowNodeInspector(bool* show = nullptr, std::shared_ptr<Node> node = nullptr)
{
    ImVec2 win_size = ImGui::GetWindowSize();
    if (!ImGui::Begin("Node Inspector", show, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_HorizontalScrollbar))
    {
        ImGui::End();
        return;
    }

    auto config = InstanceConfig::instance();
    auto& io = ImGui::GetIO();
    ImGui::GetCurrentWindow()->BeginOrderWithinParent = 1;
    ImGui::SetWindowPos(ImVec2(10, win_size.y - 350 - 25));
    ImGui::SetWindowSize(ImVec2(256, 350));

    ImGui::Text(((std::string)("Node: " + node->name)).c_str());
    if (ImGui::BeginTabBar("TabBar 0", 0))
    {
        AddInputPinsTab(node);
        node->node_funcs->UpdateNodeInspector();
        ImGui::EndTabBar();
    }

    ImGui::End();
}

void ShowCreatePlaceholderWindow(bool* show = nullptr)
{
    if (!ImGui::Begin("Create Placeholder", show))
    {
        ImGui::End();
        return;
    }
    ImGui::SetWindowSize(ImVec2(256, 0));
    auto editor_config = EditorConfig::instance();
    auto config = InstanceConfig::instance();
    auto paneWidth = ImGui::GetContentRegionAvailWidth();

    ImGui::BeginHorizontal("##placeholder_name", ImVec2(paneWidth, 0), 1.0f);
    ImGui::TextUnformatted("Placeholder Name");
    ImGui::InputText("##placeholder_name_input", (char*)create_placeholder_name.data(), create_placeholder_name.capacity() + 1.0);
    create_placeholder_name = std::string(create_placeholder_name.data());
    create_placeholder_name.reserve(create_placeholder_name.capacity() + 1.0);
    ImGui::EndHorizontal();

    ImGui::BeginHorizontal("##placeholder_type", ImVec2(paneWidth, 0), 1.0f);
    ImGui::TextUnformatted("Placeholder Type");
    std::string items[] = { PinTypeToString(PinType::String), PinTypeToString(PinType::Bool), PinTypeToString(PinType::Float), PinTypeToString(PinType::Int), 
        PinTypeToString(PinType::Vector3), PinTypeToString(PinType::Vector4), PinTypeToString(PinType::Matrix4x4), PinTypeToString(PinType::TextureObject), 
        PinTypeToString(PinType::ProgramObject), PinTypeToString(PinType::VertexShaderObject), PinTypeToString(PinType::FragmentShaderObject), 
        PinTypeToString(PinType::MeshObject) };
    if (create_placeholder_type_combo == "")
        create_placeholder_type_combo = items[0];
    if (ImGui::BeginCombo("##placeholder_type_combo", create_placeholder_type_combo.data())) // The second parameter is the label previewed before opening the combo.
    {
        for (int n = 0; n < ARRAYSIZE(items); n++)
        {
            bool is_selected = (create_placeholder_type_combo == items[n]);
            if (ImGui::Selectable(items[n].c_str(), is_selected))
            {
                create_placeholder_type_combo = items[n];
            }
            if (is_selected)
                ImGui::SetItemDefaultFocus();   // You may set the initial focus when opening the combo (scrolling + for keyboard navigation support)
        }
        ImGui::EndCombo();
    }
    ImGui::EndHorizontal();

    ImGui::BeginHorizontal("##placeholder_buttons", ImVec2(paneWidth, 0), 1.0f);
    if (ImGui::Button("Create"))
    {
        if (config->IsPlaceholderNameUsed(create_placeholder_name) == false)
        {
            PinType pinType = StringToPinType(create_placeholder_type_combo);
            if (pinType == PinType::String)
            {
                std::shared_ptr<PlaceholderValue<std::string>> ph = std::make_shared< PlaceholderValue<std::string>>(create_placeholder_name, pinType, "");;
                config->InsertNewPlaceholder(create_placeholder_name, ph);
                editor_config->showCreatePlaceholderWindow = false;
            }
            else if (pinType == PinType::Bool)
            {
                std::shared_ptr<PlaceholderValue<bool>> ph = std::make_shared< PlaceholderValue<bool>>(create_placeholder_name, pinType, false);;
                config->InsertNewPlaceholder(create_placeholder_name, ph);
                editor_config->showCreatePlaceholderWindow = false;
            }
            else if (pinType == PinType::Float)
            {
                std::shared_ptr<PlaceholderValue<float>> ph = std::make_shared< PlaceholderValue<float>>(create_placeholder_name, pinType, 0);;
                config->InsertNewPlaceholder(create_placeholder_name, ph);
                editor_config->showCreatePlaceholderWindow = false;
            }
            else if (pinType == PinType::Int)
            {
                std::shared_ptr<PlaceholderValue<int>> ph = std::make_shared< PlaceholderValue<int>>(create_placeholder_name, pinType, 0);;
                config->InsertNewPlaceholder(create_placeholder_name, ph);
                editor_config->showCreatePlaceholderWindow = false;
            }
            else if (pinType == PinType::Vector3)
            {
                std::shared_ptr<PlaceholderValue<glm::vec3>> ph = std::make_shared< PlaceholderValue<glm::vec3>>(create_placeholder_name, pinType, glm::vec3(0.0));;
                config->InsertNewPlaceholder(create_placeholder_name, ph);
                editor_config->showCreatePlaceholderWindow = false;
            }
            else if (pinType == PinType::Vector4)
            {
                std::shared_ptr<PlaceholderValue<glm::vec4>> ph = std::make_shared< PlaceholderValue<glm::vec4>>(create_placeholder_name, pinType, glm::vec4(0.0));;
                config->InsertNewPlaceholder(create_placeholder_name, ph);
                editor_config->showCreatePlaceholderWindow = false;
            }
            else if (pinType == PinType::Matrix4x4)
            {
                std::shared_ptr<PlaceholderValue<glm::mat4>> ph = std::make_shared< PlaceholderValue<glm::mat4>>(create_placeholder_name, pinType, glm::mat4(1.0));;
                config->InsertNewPlaceholder(create_placeholder_name, ph);
                editor_config->showCreatePlaceholderWindow = false;
            }
            else if (pinType == PinType::TextureObject)
            {
                std::shared_ptr<PlaceholderValue<std::shared_ptr<TextureObject>>> ph = std::make_shared< PlaceholderValue<std::shared_ptr<TextureObject>>>(create_placeholder_name, pinType, nullptr);;
                config->InsertNewPlaceholder(create_placeholder_name, ph);
                editor_config->showCreatePlaceholderWindow = false;
            }
            else if (pinType == PinType::ProgramObject)
            {
                std::shared_ptr<PlaceholderValue<std::shared_ptr<ProgramObject>>> ph = std::make_shared< PlaceholderValue<std::shared_ptr<ProgramObject>>>(create_placeholder_name, pinType, nullptr);;
                config->InsertNewPlaceholder(create_placeholder_name, ph);
                editor_config->showCreatePlaceholderWindow = false;
            }
            else if (pinType == PinType::VertexShaderObject)
            {
                std::shared_ptr<PlaceholderValue<std::shared_ptr<ShaderObject>>> ph = std::make_shared< PlaceholderValue<std::shared_ptr<ShaderObject>>>(create_placeholder_name, pinType, nullptr);;
                config->InsertNewPlaceholder(create_placeholder_name, ph);
                editor_config->showCreatePlaceholderWindow = false;
            }
            else if (pinType == PinType::FragmentShaderObject)
            {
                std::shared_ptr<PlaceholderValue<std::shared_ptr<ShaderObject>>> ph = std::make_shared< PlaceholderValue<std::shared_ptr<ShaderObject>>>(create_placeholder_name, pinType, nullptr);;
                config->InsertNewPlaceholder(create_placeholder_name, ph);
                editor_config->showCreatePlaceholderWindow = false;
            }
            else if (pinType == PinType::MeshObject)
            {
                std::shared_ptr<PlaceholderValue<std::shared_ptr<MeshObject>>> ph = std::make_shared< PlaceholderValue<std::shared_ptr<MeshObject>>>(create_placeholder_name, pinType, nullptr);;
                config->InsertNewPlaceholder(create_placeholder_name, ph);
                editor_config->showCreatePlaceholderWindow = false;
            }
        }
    }
    if (ImGui::Button("Cancel"))
    {
        editor_config->showCreatePlaceholderWindow = false;
    }

    ImGui::EndHorizontal();
    ImGui::End();
}

void ShowSelectPlaceholderWindow(bool* show = nullptr)
{
    if (!ImGui::Begin("Select Placeholder", show))
    {
        ImGui::End();
        return;
    }
    ImGui::SetWindowSize(ImVec2(256, 0));
    auto editor_config = EditorConfig::instance();
    auto config = InstanceConfig::instance();
    auto paneWidth = ImGui::GetContentRegionAvailWidth();

    ImGui::BeginHorizontal("##placeholder_original", ImVec2(paneWidth, 0), 1.0f);
    ImGui::TextUnformatted("Select Placeholder");
    std::vector<std::string> all_placeholders = config->GetPlaceholdersMapKeys();
    if (select_placeholder_combo == "")
        select_placeholder_combo = all_placeholders[0];
    if (ImGui::BeginCombo("##placeholder_type_combo", select_placeholder_combo.data())) // The second parameter is the label previewed before opening the combo.
    {
        for (int n = 0; n < all_placeholders.size(); n++)
        {
            bool is_selected = (select_placeholder_combo == all_placeholders[n]);
            if (ImGui::Selectable(all_placeholders[n].c_str(), is_selected))
            {
                select_placeholder_combo = all_placeholders[n];
            }
            if (is_selected)
                ImGui::SetItemDefaultFocus();   // You may set the initial focus when opening the combo (scrolling + for keyboard navigation support)
        }
        ImGui::EndCombo();
    }
    ImGui::EndHorizontal();

    ImGui::BeginHorizontal("##placeholder_buttons", ImVec2(paneWidth, 0), 1.0f);
    if (ImGui::Button("Select"))
    {
        auto node = FindNode(selectedNode, config->s_Nodes);
        std::shared_ptr<BasePlaceholder> ph = config->GetPlaceholder(select_placeholder_combo);
        if (node->is_set_placeholder)
        {
            if (std::dynamic_pointer_cast<SetPlaceholder_Func>(node->node_funcs)->placeholder)
            {
                std::shared_ptr<BasePlaceholder> prev_ph = std::dynamic_pointer_cast<SetPlaceholder_Func>(node->node_funcs)->placeholder;
                prev_ph->nodesID_vec.erase(std::remove(prev_ph->nodesID_vec.begin(), prev_ph->nodesID_vec.end(), node->id), prev_ph->nodesID_vec.end());
                prev_ph = nullptr;
            }
            std::dynamic_pointer_cast<SetPlaceholder_Func>(node->node_funcs)->placeholder = ph;
            if (node->inputs.count("placeholder_pin") > 0)
            {
                for (int link_i = 0; link_i < node->inputs.at("placeholder_pin")->links.size(); link_i++)
                {
                    ed::DeleteLink(node->inputs.at("placeholder_pin")->links.at(link_i)->id);
                }
                node->inputs.at("placeholder_pin")->links.clear();
            }
            else
            {
                node->inputs.insert(std::pair<std::string, std::shared_ptr<PinValue<std::string>>>("placeholder_pin", new PinValue<std::string>("placeholder_pin", 1, GetNextId(), "Value", PinType::String, "")));
                BuildNode(node);
            }
            UtilsChangePinType(node, PinKind::Input, "placeholder_pin", ph->type);
        }
        else if (node->is_get_placeholder)
        {
            if (std::dynamic_pointer_cast<GetPlaceholder_Func>(node->node_funcs)->placeholder)
            {
                std::shared_ptr<BasePlaceholder> prev_ph = std::dynamic_pointer_cast<GetPlaceholder_Func>(node->node_funcs)->placeholder;
                prev_ph->nodesID_vec.erase(std::remove(prev_ph->nodesID_vec.begin(), prev_ph->nodesID_vec.end(), node->id), prev_ph->nodesID_vec.end());
                prev_ph = nullptr;
            }
            std::dynamic_pointer_cast<GetPlaceholder_Func>(node->node_funcs)->placeholder = ph;
            std::dynamic_pointer_cast<GetPlaceholder_Func>(node->node_funcs)->placeholder_type = ph->type;
            
            if (node->outputs.count("placeholder_pin") > 0)
            {
                for (int link_i = 0; link_i < node->outputs.at("placeholder_pin")->links.size(); link_i++)
                {
                    ed::DeleteLink(node->outputs.at("placeholder_pin")->links.at(link_i)->id);
                }
                node->outputs.at("placeholder_pin")->links.clear();
            }
            else
            {
                node->outputs.insert(std::pair<std::string, std::shared_ptr<PinValue<std::string>>>("placeholder_pin", new PinValue<std::string>("placeholder_pin", 0, GetNextId(), "Value", PinType::String, "")));
                BuildNode(node);
            }
            UtilsChangePinType(node, PinKind::Output, "placeholder_pin", ph->type);
        }
        ph->nodesID_vec.push_back(selectedNode);
        editor_config->showSelectPlaceholderWindow = false;
    }
    if (ImGui::Button("Cancel"))
    {
        editor_config->showSelectPlaceholderWindow = false;
    }

    ImGui::EndHorizontal();
    ImGui::End();
}

void ShowRenamePlaceholderWindow(bool* show = nullptr)
{
    if (!ImGui::Begin("Rename Placeholder", show))
    {
        ImGui::End();
        return;
    }
    ImGui::SetWindowSize(ImVec2(256, 0));
    auto editor_config = EditorConfig::instance();
    auto config = InstanceConfig::instance();
    auto paneWidth = ImGui::GetContentRegionAvailWidth();

    ImGui::BeginHorizontal("##placeholder_original", ImVec2(paneWidth, 0), 1.0f);
    ImGui::TextUnformatted("Placeholder To Rename");
    std::vector<std::string> all_placeholders = config->GetPlaceholdersMapKeys();
    if (rename_placeholder_original_combo == "")
        rename_placeholder_original_combo = all_placeholders[0];
    if (ImGui::BeginCombo("##placeholder_type_combo", rename_placeholder_original_combo.data())) // The second parameter is the label previewed before opening the combo.
    {
        for (int n = 0; n < all_placeholders.size(); n++)
        {
            bool is_selected = (rename_placeholder_original_combo == all_placeholders[n]);
            if (ImGui::Selectable(all_placeholders[n].c_str(), is_selected))
            {
                rename_placeholder_original_combo = all_placeholders[n];
            }
            if (is_selected)
                ImGui::SetItemDefaultFocus();   // You may set the initial focus when opening the combo (scrolling + for keyboard navigation support)
        }
        ImGui::EndCombo();
    }
    ImGui::EndHorizontal();

    ImGui::BeginHorizontal("##placeholder_name", ImVec2(paneWidth, 0), 1.0f);
    ImGui::TextUnformatted("Placeholder Name");
    ImGui::InputText("##placeholder_name_input", (char*)rename_placeholder_name.data(), rename_placeholder_name.capacity() + 1.0);
    rename_placeholder_name = std::string(rename_placeholder_name.data());
    rename_placeholder_name.reserve(rename_placeholder_name.capacity() + 1.0);
    ImGui::EndHorizontal();

    ImGui::BeginHorizontal("##placeholder_buttons", ImVec2(paneWidth, 0), 1.0f);
    if (ImGui::Button("Rename"))
    {
        if (config->IsPlaceholderNameUsed(rename_placeholder_name) == false)
        {
            std::shared_ptr<BasePlaceholder> ph = config->GetPlaceholder(rename_placeholder_original_combo);
            ph->name = rename_placeholder_name;
            config->DeletePlaceholder(rename_placeholder_original_combo);
            config->InsertNewPlaceholder(rename_placeholder_name, ph);
            editor_config->showRenamePlaceholderWindow = false;
        }
    }
    if (ImGui::Button("Cancel"))
    {
        editor_config->showRenamePlaceholderWindow = false;
    }

    ImGui::EndHorizontal();
    ImGui::End();
}

void ShowDeletePlaceholderWindow(bool* show = nullptr)
{
    if (!ImGui::Begin("Delete Placeholder", show))
    {
        ImGui::End();
        return;
    }
    ImGui::SetWindowSize(ImVec2(256, 0));
    auto editor_config = EditorConfig::instance();
    auto config = InstanceConfig::instance();
    auto paneWidth = ImGui::GetContentRegionAvailWidth();

    ImGui::BeginHorizontal("##placeholder_original", ImVec2(paneWidth, 0), 1.0f);
    ImGui::TextUnformatted("Select Placeholder");
    std::vector<std::string> all_placeholders = config->GetPlaceholdersMapKeys();
    if (delete_placeholder_combo == "")
        delete_placeholder_combo = all_placeholders[0];
    if (ImGui::BeginCombo("##placeholder_type_combo", delete_placeholder_combo.data())) // The second parameter is the label previewed before opening the combo.
    {
        for (int n = 0; n < all_placeholders.size(); n++)
        {
            bool is_selected = (delete_placeholder_combo == all_placeholders[n]);
            if (ImGui::Selectable(all_placeholders[n].c_str(), is_selected))
            {
                delete_placeholder_combo = all_placeholders[n];
            }
            if (is_selected)
                ImGui::SetItemDefaultFocus();   // You may set the initial focus when opening the combo (scrolling + for keyboard navigation support)
        }
        ImGui::EndCombo();
    }
    ImGui::EndHorizontal();

    ImGui::BeginHorizontal("##placeholder_buttons", ImVec2(paneWidth, 0), 1.0f);
    if (ImGui::Button("Delete"))
    {
        std::shared_ptr<BasePlaceholder> ph = config->GetPlaceholder(delete_placeholder_combo);
        for (int ph_node_i = 0; ph_node_i < ph->nodesID_vec.size(); ph_node_i++)
        {
            ed::DeleteNode(ph->nodesID_vec.at(ph_node_i));
        }
        config->DeletePlaceholder(delete_placeholder_combo);
        editor_config->showDeletePlaceholderWindow = false;
    }
    if (ImGui::Button("Cancel"))
    {
        editor_config->showDeletePlaceholderWindow = false;
    }

    ImGui::EndHorizontal();
    ImGui::End();
}

void ShowWindows()
{
    auto editor_config = EditorConfig::instance();
    if (showStyleEditor)
        ShowStyleEditor(&showStyleEditor);

    if (showTextureViewer)
        ShowTextureViewer(&showTextureViewer);

    if (showNodeHierarchyWindow)
        ShowNodeHierarchyWindow(&showNodeHierarchyWindow);

    if (editor_config->showCreatePlaceholderWindow)
    {
        ShowCreatePlaceholderWindow(&editor_config->showCreatePlaceholderWindow);
    }
    else
    {
        create_placeholder_name = "";
        create_placeholder_type_combo = "";
    }

    if (editor_config->showSelectPlaceholderWindow)
    {
        ShowSelectPlaceholderWindow(&editor_config->showSelectPlaceholderWindow);
    }
    else
    {
        select_placeholder_combo = "";
    }

    if (editor_config->showRenamePlaceholderWindow)
    {
        ShowRenamePlaceholderWindow(&editor_config->showRenamePlaceholderWindow);
    }
    else
    {
        rename_placeholder_name = "";
        rename_placeholder_original_combo = "";
    }

    if (editor_config->showDeletePlaceholderWindow)
    {
        ShowDeletePlaceholderWindow(&editor_config->showDeletePlaceholderWindow);
    }
    else
    {
        delete_placeholder_combo = "";
    }
}

void CreateMenuBar()
{
    auto editor_config = EditorConfig::instance();
    auto config = InstanceConfig::instance();
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("Exit"))
            {
                exit(0);
            }
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Editor"))
        {
            if (ImGui::MenuItem("Zoom to Content"))
            {
                ed::NavigateToContent();
            }
            if (ImGui::MenuItem("Show Flow"))
            {
                for (auto& link : config->s_Links)
                    ed::Flow(link->id);
            }
            if (ImGui::MenuItem("Edit Style"))
            {
                showStyleEditor = true;
            }
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Windows"))
        {
            if (ImGui::MenuItem("Nodes Hierarchy Window"))
            {
                showNodeHierarchyWindow = true;
            }
            if (ImGui::MenuItem("Textures Viewer"))
            {
                showTextureViewer = true;
            }
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Placeholders"))
        {
            if (ImGui::MenuItem("Create Placeholder"))
                editor_config->showCreatePlaceholderWindow = true;
            if (config->GetPlaceholdersMapKeys().size() > 0)
            {
                if (ImGui::MenuItem("Rename Placeholder"))
                    editor_config->showRenamePlaceholderWindow = true;
                if (ImGui::MenuItem("Delete Placeholder"))
                    editor_config->showDeletePlaceholderWindow = true;
            }
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
}

std::vector<std::string> split_string(std::string s_tmp, char splitter)
{
    std::vector<std::string> tokens;
    std::size_t start = 0, end = 0;
    while ((end = s_tmp.find(splitter, start)) != std::string::npos) {
        if (end != start) {
            tokens.push_back(s_tmp.substr(start, end - start));
        }
        start = end + 1;
    }
    if (end != start) {
        std::string last_one = s_tmp.substr(start);
        if (last_one != "" && last_one != " ")
            tokens.push_back(last_one);
    }
    return tokens;
}

auto showLabelOnMouse = [](const char* label, ImColor color)
{
    ImGui::SetCursorPosY(ImGui::GetCursorPosY() - ImGui::GetTextLineHeight());
    auto size = ImGui::CalcTextSize(label);

    auto padding = ImGui::GetStyle().FramePadding;
    auto spacing = ImGui::GetStyle().ItemSpacing;

    ImGui::SetCursorPos(ImGui::GetCursorPos() + ImVec2(spacing.x, -spacing.y));

    auto rectMin = ImGui::GetCursorScreenPos() - padding;
    auto rectMax = ImGui::GetCursorScreenPos() + size + padding;

    auto drawList = ImGui::GetWindowDrawList();
    drawList->AddRectFilled(rectMin, rectMax, color, size.y * 0.15f);
    ImGui::TextUnformatted(label);
};

void Application_GL_Frame()
{
    auto config = InstanceConfig::instance();
    std::shared_ptr<Node> node = config->s_Nodes.at(0);
    node->node_funcs->Run();
}

void Application_Frame()
{
    UpdateTouch();
    CreateMenuBar();
    ShowWindows();

    auto& io = ImGui::GetIO();
    auto config = InstanceConfig::instance();

    ImGui::Text("FPS: %.2f (%.2gms)", io.Framerate, io.Framerate ? 1000.0f / io.Framerate : 0.0f);

    ed::SetCurrentEditor(m_Editor);

    for (auto& node : config->s_Nodes)
    {
        node->node_funcs->UpdateNodeUI();
    }

    ed::Begin("Node editor");
    {
        auto cursorTopLeft = ImGui::GetCursorScreenPos();

        util::BlueprintNodeBuilder builder(s_HeaderBackground, Application_GetTextureWidth(s_HeaderBackground), Application_GetTextureHeight(s_HeaderBackground));

        // Blueprint and simple
        for (auto& node : config->s_Nodes)
        {
            if (node->type != NodeType::Blueprint && node->type != NodeType::Simple)
                continue;

            const auto isSimple = node->type == NodeType::Simple;

            builder.Begin(node->id);
            if (!isSimple)
            {
                builder.Header(node->color);
                ImGui::Spring(0);
                std::string name = node->name;
                if (node->info != "")
                    name += "\n" + node->info;
                if (node->error != "")
                    name += "\n" + node->error;
                ImGui::TextUnformatted(name.c_str());
                ImGui::Spring(1);
                ImGui::Dummy(ImVec2(0, 28));
                ImGui::Spring(0);
                builder.EndHeader();
            }

            std::vector<std::string> sort_pins = SortPins(node->inputs);
            for (int pi = 0; pi < sort_pins.size(); pi++)
            {
                std::shared_ptr<BasePin> input = node->inputs.at(sort_pins.at(pi));
                if (input->exposed == false)
                {
                    for (int li = 0; li < input->links.size(); li++)
                        ed::DeleteLink(input->links.at(li)->id);
                    continue;
                }
                auto alpha = ImGui::GetStyle().Alpha;
                if (newLinkPin && !CanCreateLink(newLinkPin, input) && input != newLinkPin)
                    alpha = alpha * (48.0f / 255.0f);

                builder.Input(input->id);
                ImGui::PushStyleVar(ImGuiStyleVar_Alpha, alpha);
                DrawPinIcon(input, IsPinLinked(input->id, config->s_Links), (int)(alpha * 255));
                ImGui::Spring(0);
                
                static bool wasActive = false;
                if (input->type == PinType::String)
                {
                    ImGui::PushItemWidth(100.0f);
                    std::shared_ptr<PinValue<std::string>> input_pin_value = std::dynamic_pointer_cast<PinValue<std::string>>(input);
                    if (input_pin_value->links.size() > 0)
                    {
                        ImGui::InputText("##edit", (char*)input_pin_value->value.data(), input_pin_value->value.capacity() + 1.0);
                        input_pin_value->value = std::string(input_pin_value->value.data());
                    }
                    else
                    {
                        ImGui::InputText("##edit", (char*)input_pin_value->default_value.data(), input_pin_value->default_value.capacity() + 1.0);
                        input_pin_value->default_value = std::string(input_pin_value->default_value.data());
                    }
                    ImGui::PopItemWidth();
                    if (ImGui::IsItemActive() && !wasActive)
                    {
                        ed::EnableShortcuts(false);
                        wasActive = true;
                    }
                    else if (!ImGui::IsItemActive() && wasActive)
                    {
                        ed::EnableShortcuts(true);
                        wasActive = false;
                    }
                    ImGui::Spring(0);
                }
                else if (input->type == PinType::Bool)
                {
                    std::shared_ptr<PinValue<bool>> input_pin_value = std::dynamic_pointer_cast<PinValue<bool>>(input);
                    ImGui::PushItemWidth(100.0f);
                    if (input_pin_value->links.size() > 0)
                        ImGui::Checkbox("##edit", &input_pin_value->value);
                    else
                        ImGui::Checkbox("##edit", &input_pin_value->default_value);
                    ImGui::PopItemWidth();
                    if (ImGui::IsItemActive() && !wasActive)
                    {
                        ed::EnableShortcuts(false);
                        wasActive = true;
                    }
                    else if (!ImGui::IsItemActive() && wasActive)
                    {
                        ed::EnableShortcuts(true);
                        wasActive = false;
                    }
                    ImGui::Spring(0);
                }
                else if (input->type == PinType::Float)
                {
                    std::shared_ptr<PinValue<float>> input_pin_value = std::dynamic_pointer_cast<PinValue<float>>(input);
                    ImGui::PushItemWidth(100.0f);
                    if (input_pin_value->links.size() > 0)
                        ImGui::InputFloat("##edit", &input_pin_value->value, 0.0, 0.0, "%.6f", 0);
                    else
                        ImGui::InputFloat("##edit", &input_pin_value->default_value, 0.0, 0.0, "%.6f", 0);
                    ImGui::PopItemWidth();
                    if (ImGui::IsItemActive() && !wasActive)
                    {
                        ed::EnableShortcuts(false);
                        wasActive = true;
                    }
                    else if (!ImGui::IsItemActive() && wasActive)
                    {
                        ed::EnableShortcuts(true);
                        wasActive = false;
                    }
                    ImGui::Spring(0);
                }
                else if (input->type == PinType::Vector3)
                {
                    std::shared_ptr<PinValue<glm::vec3>> input_pin_value = std::dynamic_pointer_cast<PinValue<glm::vec3>>(input);
                    ImGui::PushItemWidth(125.0f);
                    if (input_pin_value->links.size() > 0)
                    {
                        float float3[3] = { input_pin_value->value.x, input_pin_value->value.y, input_pin_value->value.z };
                        ImGui::InputFloat3("##edit", float3);
                        input_pin_value->value = glm::vec3(float3[0], float3[1], float3[2]);
                    }
                    else
                    {
                        float float3[3] = { input_pin_value->default_value.x, input_pin_value->default_value.y, input_pin_value->default_value.z };
                        ImGui::InputFloat3("##edit", float3);
                        input_pin_value->default_value = glm::vec3(float3[0], float3[1], float3[2]);
                    }
                    ImGui::PopItemWidth();
                    if (ImGui::IsItemActive() && !wasActive)
                    {
                        ed::EnableShortcuts(false);
                        wasActive = true;
                    }
                    else if (!ImGui::IsItemActive() && wasActive)
                    {
                        ed::EnableShortcuts(true);
                        wasActive = false;
                    }
                    ImGui::Spring(0);
                }
                else if (input->type == PinType::Vector4)
                {
                    std::shared_ptr<PinValue<glm::vec4>> input_pin_value = std::dynamic_pointer_cast<PinValue<glm::vec4>>(input);
                    ImGui::PushItemWidth(125.0f);
                    if (input_pin_value->links.size() > 0)
                    {
                        float float4[4] = { input_pin_value->value.x, input_pin_value->value.y, input_pin_value->value.z, input_pin_value->value.w };
                        ImGui::InputFloat4("##edit", float4);
                        input_pin_value->value = glm::vec4(float4[0], float4[1], float4[2], float4[3]);
                    }
                    else
                    {
                        float float4[4] = { input_pin_value->default_value.x, input_pin_value->default_value.y, input_pin_value->default_value.z, input_pin_value->default_value.w };
                        ImGui::InputFloat4("##edit", float4);
                        input_pin_value->default_value = glm::vec4(float4[0], float4[1], float4[2], float4[3]);
                    }
                    ImGui::PopItemWidth();
                    if (ImGui::IsItemActive() && !wasActive)
                    {
                        ed::EnableShortcuts(false);
                        wasActive = true;
                    }
                    else if (!ImGui::IsItemActive() && wasActive)
                    {
                        ed::EnableShortcuts(true);
                        wasActive = false;
                    }
                    ImGui::Spring(0);
                }
                else if (input->type == PinType::Int)
                {
                    std::shared_ptr<PinValue<int>> input_pin_value = std::dynamic_pointer_cast<PinValue<int>>(input);
                    ImGui::PushItemWidth(100.0f);
                    if (input_pin_value->links.size() > 0)
                        ImGui::InputInt("##edit", &input_pin_value->value, 0, 0, 0);
                    else
                        ImGui::InputInt("##edit", &input_pin_value->default_value, 0, 0, 0);
                    ImGui::PopItemWidth();
                    if (ImGui::IsItemActive() && !wasActive)
                    {
                        ed::EnableShortcuts(false);
                        wasActive = true;
                    }
                    else if (!ImGui::IsItemActive() && wasActive)
                    {
                        ed::EnableShortcuts(true);
                        wasActive = false;
                    }
                    ImGui::Spring(0);
                }
                
                if (!input->name.empty())
                {
                    ImGui::TextUnformatted(input->name.c_str());
                    ImGui::Spring(0);
                }
                
                ImGui::PopStyleVar();
                builder.EndInput();
            }

            if (isSimple)
            {
                builder.Middle();

                ImGui::Spring(1, 0);
                ImGui::TextUnformatted(node->name.c_str());
                ImGui::Spring(1, 0);
            }

            if (!isSimple && (node->is_set_placeholder || node->is_get_placeholder))
            {
                builder.Middle();

                ImGui::Spring(1, 0);
                if (node->is_set_placeholder)
                    if (std::dynamic_pointer_cast<SetPlaceholder_Func>(node->node_funcs)->placeholder)
                        ImGui::TextUnformatted(std::dynamic_pointer_cast<SetPlaceholder_Func>(node->node_funcs)->placeholder->name.c_str());
                if (node->is_get_placeholder)
                    if (std::dynamic_pointer_cast<GetPlaceholder_Func>(node->node_funcs)->placeholder)
                        ImGui::TextUnformatted(std::dynamic_pointer_cast<GetPlaceholder_Func>(node->node_funcs)->placeholder->name.c_str());
                ImGui::Spring(1, 0);
            }

            sort_pins = SortPins(node->outputs);
            for (int pi = 0; pi < sort_pins.size(); pi++)
            {
                std::shared_ptr<BasePin> output = node->outputs.at(sort_pins.at(pi));
                auto alpha = ImGui::GetStyle().Alpha;
                if (newLinkPin && !CanCreateLink(newLinkPin, output) && output != newLinkPin)
                    alpha = alpha * (48.0f / 255.0f);

                ImGui::PushStyleVar(ImGuiStyleVar_Alpha, alpha);
                builder.Output(output->id);
                if (!output->name.empty())
                {
                    ImGui::Spring(0);
                    ImGui::TextUnformatted(output->name.c_str());
                }
                ImGui::Spring(0);
                DrawPinIcon(output, IsPinLinked(output->id, config->s_Links), (int)(alpha * 255));
                ImGui::PopStyleVar();
                builder.EndOutput();
            }


            builder.End();
        }

        // Comment
        for (auto& node : config->s_Nodes)
        {
            if (node->type != NodeType::Comment)
                continue;

            const float commentAlpha = 0.75f;

            ImGui::PushStyleVar(ImGuiStyleVar_Alpha, commentAlpha);
            ed::PushStyleColor(ed::StyleColor_NodeBg, ImColor(255, 255, 255, 64));
            ed::PushStyleColor(ed::StyleColor_NodeBorder, ImColor(255, 255, 255, 64));
            ed::BeginNode(node->id);
            ImGui::PushID(node->id.AsPointer());
            ImGui::BeginVertical("content");
            ImGui::BeginHorizontal("horizontal");
            ImGui::Spring(1);
            ImGui::TextUnformatted(node->name.c_str());
            ImGui::Spring(1);
            ImGui::EndHorizontal();
            ed::Group(node->size);
            ImGui::EndVertical();
            ImGui::PopID();
            ed::EndNode();
            ed::PopStyleColor(2);
            ImGui::PopStyleVar();

            if (ed::BeginGroupHint(node->id))
            {
                auto bgAlpha = static_cast<int>(ImGui::GetStyle().Alpha * 255);

                auto min = ed::GetGroupMin();

                ImGui::SetCursorScreenPos(min - ImVec2(-8, ImGui::GetTextLineHeightWithSpacing() + 4));
                ImGui::BeginGroup();
                ImGui::TextUnformatted(node->name.c_str());
                ImGui::EndGroup();

                auto drawList = ed::GetHintBackgroundDrawList();

                auto hintBounds = ImGui_GetItemRect();
                auto hintFrameBounds = ImRect_Expanded(hintBounds, 8, 4);

                drawList->AddRectFilled(
                    hintFrameBounds.GetTL(),
                    hintFrameBounds.GetBR(),
                    IM_COL32(255, 255, 255, 64 * bgAlpha / 255), 4.0f);

                drawList->AddRect(
                    hintFrameBounds.GetTL(),
                    hintFrameBounds.GetBR(),
                    IM_COL32(255, 255, 255, 128 * bgAlpha / 255), 4.0f);
            }
            ed::EndGroupHint();
        }

        for (auto& link : config->s_Links)
            ed::Link(link->id, link->startPinID, link->endPinID, link->color, 2.0f);

        if (!createNewNode)
        {
            if (ed::BeginCreate(ImColor(255, 255, 255), 2.0f))
            {
                ed::PinId startPinId = 0, endPinId = 0;
                if (ed::QueryNewLink(&startPinId, &endPinId))
                {
                    auto startPin = FindPin(startPinId, config->s_Nodes);
                    auto endPin = FindPin(endPinId, config->s_Nodes);

                    newLinkPin = startPin ? startPin : endPin;

                    if (startPin->kind == PinKind::Input)
                    {
                        std::swap(startPin, endPin);
                        std::swap(startPinId, endPinId);
                    }

                    if (startPin && endPin)
                    {
                        if (endPin == startPin)
                        {
                            ed::RejectNewItem(ImColor(255, 0, 0), 2.0f);
                        }
                        else if (endPin->kind == startPin->kind)
                        {
                            showLabelOnMouse("x Incompatible Pin Kind", ImColor(45, 32, 32, 180));
                            ed::RejectNewItem(ImColor(255, 0, 0), 2.0f);
                        }
                        else if (endPin->node->id == startPin->node->id)
                        {
                            showLabelOnMouse("x Cannot connect to self", ImColor(45, 32, 32, 180));
                            ed::RejectNewItem(ImColor(255, 0, 0), 1.0f);
                        }
                        else if (endPin->type != startPin->type)
                        {
                            showLabelOnMouse("x Incompatible Pin Type", ImColor(45, 32, 32, 180));
                            ed::RejectNewItem(ImColor(255, 128, 128), 1.0f);
                        }
                        else
                        {
                            showLabelOnMouse("+ Create Link", ImColor(32, 45, 32, 180));
                            if (ed::AcceptNewItem(ImColor(128, 255, 128), 4.0f))
                            {
                                for (int link_i = 0; link_i < config->s_Links.size(); link_i++)
                                {
                                    if (config->s_Links.at(link_i)->startPinID == startPinId && startPin->type == PinType::Flow)
                                    {
                                        config->s_Links.at(link_i)->endPin->links.erase(std::remove(config->s_Links.at(link_i)->endPin->links.begin(), config->s_Links.at(link_i)->endPin->links.end(), config->s_Links.at(link_i)), config->s_Links.at(link_i)->endPin->links.end());
                                        config->s_Links.at(link_i)->startPin->links.erase(std::remove(config->s_Links.at(link_i)->startPin->links.begin(), config->s_Links.at(link_i)->startPin->links.end(), config->s_Links.at(link_i)), config->s_Links.at(link_i)->startPin->links.end());
                                        config->s_Links.at(link_i)->startPin = nullptr;
                                        config->s_Links.at(link_i)->endPin = nullptr;
                                        ed::DeleteLink(config->s_Links.at(link_i)->id);
                                        link_i = config->s_Links.size();
                                    }
                                    else if (config->s_Links.at(link_i)->endPinID == endPinId && endPin->type != PinType::Flow && endPin->kind == PinKind::Input)
                                    {
                                        config->s_Links.at(link_i)->endPin->links.erase(std::remove(config->s_Links.at(link_i)->endPin->links.begin(), config->s_Links.at(link_i)->endPin->links.end(), config->s_Links.at(link_i)), config->s_Links.at(link_i)->endPin->links.end());
                                        config->s_Links.at(link_i)->startPin->links.erase(std::remove(config->s_Links.at(link_i)->startPin->links.begin(), config->s_Links.at(link_i)->startPin->links.end(), config->s_Links.at(link_i)), config->s_Links.at(link_i)->startPin->links.end());
                                        config->s_Links.at(link_i)->startPin = nullptr;
                                        config->s_Links.at(link_i)->endPin = nullptr;
                                        ed::DeleteLink(config->s_Links.at(link_i)->id);
                                        link_i = config->s_Links.size();
                                    }
                                }
                                config->s_Links.emplace_back(new Link(GetNextId(), startPinId, endPinId, startPin, endPin));
                                config->s_Links.back()->color = GetIconColor(startPin->type);
                                startPin->links.push_back(config->s_Links.back());
                                endPin->links.push_back(config->s_Links.back());
                            }
                        }
                    }
                }

                ed::PinId pinId = 0;
                if (ed::QueryNewNode(&pinId))
                {
                    newLinkPin = FindPin(pinId, config->s_Nodes);
                    if (newLinkPin)
                    {
                        showLabelOnMouse("+ Create Node", ImColor(32, 45, 32, 180));
                        if (ed::AcceptNewItem())
                        {
                            createNewNode = true;
                            newNodeLinkPin = FindPin(pinId, config->s_Nodes);
                            newLinkPin = nullptr;
                            ed::Suspend();
                            ImGui::OpenPopup("Create New Node");
                            reset_search_node = true;
                            ed::Resume();
                        }
                    }
                }
            }
            else
                newLinkPin = nullptr;

            ed::EndCreate();

            if (ed::BeginDelete())
            {
                ed::LinkId linkId = 0;
                while (ed::QueryDeletedLink(&linkId))
                {
                    if (ed::AcceptDeletedItem())
                    {
                        bool link_found = false;
                        int link_index = 0;
                        for (int link_i = 0; link_i < config->s_Links.size(); link_i++)
                        {
                            if (config->s_Links.at(link_i)->id == linkId)
                            {
                                link_found = true;
                                link_index = link_i;
                            }
                        }
                        if (link_found)
                        {
                            if (config->s_Links.at(link_index)->startPin)
                                config->s_Links.at(link_index)->startPin->links.clear();
                            if (config->s_Links.at(link_index)->endPin)
                                config->s_Links.at(link_index)->endPin->links.clear();
                            config->s_Links.at(link_index)->startPin = nullptr;
                            config->s_Links.at(link_index)->endPin = nullptr;
                            config->s_Links.erase(config->s_Links.begin() + link_index);
                        }
                    }
                }

                ed::NodeId nodeId = 0;
                while (ed::QueryDeletedNode(&nodeId))
                {
                    if (ed::AcceptDeletedItem())
                    {
                        bool node_found = false;
                        int node_index = 0;
                        for (int node_i = 0; node_i < config->s_Nodes.size(); node_i++)
                        {
                            if (config->s_Nodes.at(node_i)->id == nodeId && config->s_Nodes.at(node_i)->name != "GL Main Loop")
                            {
                                node_found = true;
                                node_index = node_i;
                            }
                        }
                        if (node_found)
                        {
                            config->s_Nodes.at(node_index)->node_funcs->Delete();
                            config->s_Nodes.at(node_index)->inputs.clear();
                            config->s_Nodes.at(node_index)->outputs.clear();
                            config->s_Nodes.at(node_index)->node_funcs = nullptr;
                            config->s_Nodes.erase(config->s_Nodes.begin() + node_index);
                        }
                    }
                }
            }
            ed::EndDelete();
        }

        ImGui::SetCursorScreenPos(cursorTopLeft);
    }


    auto openPopupPosition = ImGui::GetMousePos();
    ed::Suspend();
    if (ed::ShowNodeContextMenu(&contextNodeId))
        ImGui::OpenPopup("Node Context Menu");
    else if (ed::ShowPinContextMenu(&contextPinId))
        ImGui::OpenPopup("Pin Context Menu");
    else if (ed::ShowLinkContextMenu(&contextLinkId))
        ImGui::OpenPopup("Link Context Menu");
    else if (ed::ShowBackgroundContextMenu())
    {
        ImGui::OpenPopup("Create New Node");
        reset_search_node = true;
        newNodeLinkPin = nullptr;
    }
    ed::Resume();

    ed::Suspend();
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(8, 8));
    if (ImGui::BeginPopup("Node Context Menu"))
    {
        auto node = FindNode(contextNodeId, config->s_Nodes);

        ImGui::TextUnformatted("Node Context Menu");
        ImGui::Separator();
        if (node)
        {
            ImGui::Text("ID: %p", node->id.AsPointer());
            ImGui::Text("Type: %s", node->type == NodeType::Blueprint ? "Blueprint" : "Comment");
            ImGui::Text("Inputs: %d", (int)node->inputs.size());
            ImGui::Text("Outputs: %d", (int)node->outputs.size());
        }
        else
            ImGui::Text("Unknown node: %p", contextNodeId.AsPointer());
        
        if (node->name != "GL Main Loop")
        {
            ImGui::Separator();
            if (ImGui::MenuItem("Delete"))
                ed::DeleteNode(contextNodeId);
        }

        ImGui::EndPopup();
    }

    if (ImGui::BeginPopup("Pin Context Menu"))
    {
        auto pin = FindPin(contextPinId, config->s_Nodes);

        ImGui::TextUnformatted("Pin Context Menu");
        ImGui::Separator();
        if (pin)
        {
            ImGui::Text("ID: %p", pin->id.AsPointer());
            if (pin->node)
                ImGui::Text("Node: %p", pin->node->id.AsPointer());
            else
                ImGui::Text("Node: %s", "<none>");

            if (pin->isTemplate)
            {
                ImGui::Separator();
                ImGui::Text("Select Type:");

                template_pin_type_selected_item = PinTypeToString(pin->type);
                if (ImGui::BeginCombo("##combo", template_pin_type_selected_item.data())) // The second parameter is the label previewed before opening the combo.
                {
                    for (int n = 0; n < pin->template_allowed_types.size(); n++)
                    {
                        bool is_selected = (template_pin_type_selected_item == PinTypeToString(pin->template_allowed_types[n]));
                        if (ImGui::Selectable(PinTypeToString(pin->template_allowed_types[n]).c_str(), is_selected))
                        {
                            template_pin_type_selected_item = PinTypeToString(pin->template_allowed_types[n]);
                            for (int link_i = 0; link_i < pin->links.size(); link_i++)
                            {
                                ed::DeleteLink(pin->links.at(link_i)->id);
                            }
                            pin->links.clear();
                            UtilsChangePinType(pin->node, pin->kind, pin->pin_key, pin->template_allowed_types[n]);
                        }
                        if (is_selected)
                            ImGui::SetItemDefaultFocus();   // You may set the initial focus when opening the combo (scrolling + for keyboard navigation support)
                    }
                    ImGui::EndCombo();
                }
            }
        }
        else
            ImGui::Text("Unknown pin: %p", contextPinId.AsPointer());

        ImGui::EndPopup();
    }

    ImGui::SetNextWindowSize(ImVec2(0, 350));
    if (ImGui::BeginPopup("Create New Node", ImGuiWindowFlags_AlwaysVerticalScrollbar))
    {
        ImGui::PushItemWidth(100.0f);
        if (reset_search_node)
        {
            search_node_str = "";
            search_node_str.reserve(128);
        }
        reset_search_node = false;
        ImGui::InputText("##edit", (char*)search_node_str.data(), search_node_str.capacity() + 1);
        ImGui::PopItemWidth();

        search_node_str = std::string(search_node_str.c_str());
        search_node_str.reserve(128);
        std::string s_tmp = std::string(search_node_str.c_str());
        std::vector<std::string> search_input_split = split_string(s_tmp, ' ');

        std::shared_ptr<Node> node = nullptr;
        for (int node_i = 0; node_i < search_nodes_vector.size(); node_i++)
        {
            if (search_input_split.size() == 0)
            {
                if (search_nodes_vector.at(node_i).show_in_global_search)
                    if (ImGui::MenuItem(search_nodes_vector.at(node_i).title.c_str()))
                        node = search_nodes_vector.at(node_i).func(config->s_Nodes);
            }
            else if (search_nodes_vector.at(node_i).title.rfind(search_node_str, 0) == 0)
            {
                if (ImGui::MenuItem(search_nodes_vector.at(node_i).title.c_str()))
                    node = search_nodes_vector.at(node_i).func(config->s_Nodes);
            }
            else if (search_input_split.size() == 1)
            {
                bool added = false;
                if (search_nodes_vector.at(node_i).title.rfind(search_input_split.at(0), 0) == 0)
                {
                    added = true;
                    if (ImGui::MenuItem(search_nodes_vector.at(node_i).title.c_str()))
                        node = search_nodes_vector.at(node_i).func(config->s_Nodes);
                }
                if (added == false)
                {
                    for (int kw_i = 0; kw_i < search_nodes_vector.at(node_i).keywords.size() && added == false; kw_i++)
                    {
                        if (search_nodes_vector.at(node_i).keywords.at(kw_i).rfind(search_input_split.at(0), 0) == 0)
                        {
                            added = true;
                            if (ImGui::MenuItem(search_nodes_vector.at(node_i).title.c_str()))
                                node = search_nodes_vector.at(node_i).func(config->s_Nodes);
                        }
                    }
                }
            }
            else if (search_input_split.size() > 1)
            {
                bool match = true;
                for (int si_i = 0; si_i < search_input_split.size() - 1 && match; si_i++)
                {
                    if (std::find(search_nodes_vector.at(node_i).keywords.begin(), search_nodes_vector.at(node_i).keywords.end(), search_input_split.at(si_i)) != search_nodes_vector.at(node_i).keywords.end()) {
                        match = true;
                    }
                    else {
                        match = false;
                    }

                }
                if (match)
                {
                    bool added = false;
                    for (int kw_i = 0; kw_i < search_nodes_vector.at(node_i).keywords.size() && added == false; kw_i++)
                    {
                        if (search_nodes_vector.at(node_i).keywords.at(kw_i).rfind(search_input_split.at(search_input_split.size() - 1), 0) == 0)
                        {
                            added = true;
                            if (ImGui::MenuItem(search_nodes_vector.at(node_i).title.c_str()))
                                node = search_nodes_vector.at(node_i).func(config->s_Nodes);
                        }
                    }
                }
            }
        }
        
        ImGui::Separator();

        if (node)
        {
            createNewNode = false;
            ed::SetNodePosition(node->id, openPopupPosition);
        }
        ImGui::EndPopup();
    }
    else
        createNewNode = false;

    if (ImGui::BeginPopup("Link Context Menu"))
    {
        auto link = FindLink(contextLinkId, config->s_Links);

        ImGui::TextUnformatted("Link Context Menu");
        ImGui::Separator();
        if (link)
        {
            ImGui::Text("ID: %p", link->id.AsPointer());
            ImGui::Text("From: %p", link->startPinID.AsPointer());
            ImGui::Text("To: %p", link->endPinID.AsPointer());
        }
        else
            ImGui::Text("Unknown link: %p", contextLinkId.AsPointer());
        ImGui::Separator();
        if (ImGui::MenuItem("Delete"))
            ed::DeleteLink(contextLinkId);
        ImGui::EndPopup();
    }

    ImGui::PopStyleVar();
    ed::Resume();


    std::vector<ed::NodeId> selectedNodes;
    selectedNodes.resize(ed::GetSelectedObjectCount());
    int nodeCount = ed::GetSelectedNodes(selectedNodes.data(), static_cast<int>(selectedNodes.size()));
    selectedNodes.resize(nodeCount);

    if (nodeCount == 1)
    {
        ed::Suspend();
        selectedNode = selectedNodes.at(0);
        auto node = FindNode(selectedNode, config->s_Nodes);
        ShowNodeInspector(&showNodeInspector, node);
        ed::Resume();
    }
    else
    {
        selectedNode = ed::NodeId();
        showNodeInspector = false;
    }

    ed::End();
}

