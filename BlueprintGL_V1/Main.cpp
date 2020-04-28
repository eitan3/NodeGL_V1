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
#include "imgui_utils.h"
#include "bp_enums.h"
#include "bp_structs.h"
#include "utils.h"
#include "id_generator.h"
#include "nodes_builder.h"
#include "nodes/collect_search_nodes.h"

#include "nodes/gl_nodes_1.h"

namespace ed = ax::NodeEditor;
namespace util = ax::NodeEditor::Utilities;

using namespace ax;

using ax::Widgets::IconType;



// Set main variables
ed::EditorContext* m_Editor = nullptr;

const int            s_PinIconSize = 24;
ImTextureID          s_HeaderBackground = nullptr;
ImTextureID          s_SaveIcon = nullptr;
ImTextureID          s_RestoreIcon = nullptr;

std::vector<SearchNodeObj> search_nodes_vector;
std::string search_node_str = "";
bool reset_search_node = false;

std::string pin_type_selected_item;

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
    return "Blueprints";
}

void Application_Initialize()
{
    auto config = InstanceConfig::instance();
    s_HeaderBackground = Application_LoadTexture("Data/BlueprintBackground.png");
    s_SaveIcon = Application_LoadTexture("Data/ic_save_white_24dp.png");
    s_RestoreIcon = Application_LoadTexture("Data/ic_restore_white_24dp.png");

    ed::Config ed_config;
    ed_config.SettingsFile = "Blueprints.json";
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
    //s_Links.push_back(Link(GetNextLinkId(), s_Nodes[5].Outputs[0].id, s_Nodes[6].Inputs[0].id));

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

static bool Splitter(bool split_vertically, float thickness, float* size1, float* size2, float min_size1, float min_size2, float splitter_long_axis_size = -1.0f)
{
    using namespace ImGui;
    ImGuiContext& g = *GImGui;
    ImGuiWindow* window = g.CurrentWindow;
    ImGuiID id = window->GetID("##Splitter");
    ImRect bb;
    bb.Min = window->DC.CursorPos + (split_vertically ? ImVec2(*size1, 0.0f) : ImVec2(0.0f, *size1));
    bb.Max = bb.Min + CalcItemSize(split_vertically ? ImVec2(thickness, splitter_long_axis_size) : ImVec2(splitter_long_axis_size, thickness), 0.0f, 0.0f);
    return SplitterBehavior(bb, id, split_vertically ? ImGuiAxis_X : ImGuiAxis_Y, size1, size2, min_size1, min_size2, 0.0f);
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
    case PinType::Delegate: return ImColor(255, 48, 48);
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
        case PinType::Delegate: iconType = IconType::Square; break;
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
        ImGui::Image((void*)(intptr_t)config->GetTexture(preview_texture), ImVec2(256, 256));
    }

    ImGui::End();
}

void ShowLeftPane(float paneWidth)
{
    auto config = InstanceConfig::instance();
    auto& io = ImGui::GetIO();

    ImGui::BeginChild("Selection", ImVec2(paneWidth, 0));

    paneWidth = ImGui::GetContentRegionAvailWidth();

    static bool showStyleEditor = false;
    static bool showTextureViewer = false;
    ImGui::BeginHorizontal("Style Editor", ImVec2(paneWidth, 0));
    ImGui::Spring(0.0f, 0.0f);
    if (ImGui::Button("Zoom to Content"))
        ed::NavigateToContent();
    ImGui::Spring(0.0f);
    if (ImGui::Button("Show Flow"))
    {
        for (auto& link : config->s_Links)
            ed::Flow(link->id);
    }
    ImGui::Spring();
    if (ImGui::Button("Edit Style"))
        showStyleEditor = true;
    if (ImGui::Button("Texture Viewer"))
        showTextureViewer = true;
    ImGui::EndHorizontal();

    if (showTextureViewer)
        ShowTextureViewer(&showTextureViewer);

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

    // Press Z to show the flow
    //if (ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_Z)))
    //    for (auto& link : s Links)
    //        ed::Flow(link.id);

    if (ed::HasSelectionChanged())
        ++changeCount;

    ImGui::EndChild();
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

void Application_GL_Frame()
{
    auto config = InstanceConfig::instance();
    std::shared_ptr<Node> node = config->s_Nodes.at(0);
    node->node_funcs->Run();
}

void Application_Frame()
{
    UpdateTouch();

    auto& io = ImGui::GetIO();
    auto config = InstanceConfig::instance();

    ImGui::Text("FPS: %.2f (%.2gms)", io.Framerate, io.Framerate ? 1000.0f / io.Framerate : 0.0f);

    ed::SetCurrentEditor(m_Editor);

    static ed::NodeId contextNodeId = 0;
    static ed::LinkId contextLinkId = 0;
    static ed::PinId  contextPinId = 0;
    static bool createNewNode = false;
    static std::shared_ptr<BasePin> newNodeLinkPin = nullptr;
    static std::shared_ptr<BasePin> newLinkPin = nullptr;

    static float leftPaneWidth = 400.0f;
    static float rightPaneWidth = 800.0f;
    Splitter(true, 4.0f, &leftPaneWidth, &rightPaneWidth, 50.0f, 50.0f);

    ShowLeftPane(leftPaneWidth - 4.0f);

    ImGui::SameLine(0.0f, 12.0f);

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

            bool hasOutputDelegates = false;
            for (auto& output : node->outputs)
                if (output->type == PinType::Delegate)
                    hasOutputDelegates = true;

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
                if (hasOutputDelegates)
                {
                    ImGui::BeginVertical("delegates", ImVec2(0, 28));
                    ImGui::Spring(1, 0);
                    for (auto& output : node->outputs)
                    {
                        if (output->type != PinType::Delegate)
                            continue;

                        auto alpha = ImGui::GetStyle().Alpha;
                        if (newLinkPin && !CanCreateLink(newLinkPin, output) && output != newLinkPin)
                            alpha = alpha * (48.0f / 255.0f);

                        ed::BeginPin(output->id, ed::PinKind::Output);
                        ed::PinPivotAlignment(ImVec2(1.0f, 0.5f));
                        ed::PinPivotSize(ImVec2(0, 0));
                        ImGui::BeginHorizontal(output->id.AsPointer());
                        ImGui::PushStyleVar(ImGuiStyleVar_Alpha, alpha);
                        if (!output->name.empty())
                        {
                            ImGui::TextUnformatted(output->name.c_str());
                            ImGui::Spring(0);
                        }
                        DrawPinIcon(output, IsPinLinked(output->id, config->s_Links), (int)(alpha * 255));
                        ImGui::Spring(0, ImGui::GetStyle().ItemSpacing.x / 2);
                        ImGui::EndHorizontal();
                        ImGui::PopStyleVar();
                        ed::EndPin();

                        //DrawItemRect(ImColor(255, 0, 0));
                    }
                    ImGui::Spring(1, 0);
                    ImGui::EndVertical();
                    ImGui::Spring(0, ImGui::GetStyle().ItemSpacing.x / 2);
                }
                else
                    ImGui::Spring(0);
                builder.EndHeader();
            }

            for (auto& input : node->inputs)
            {
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

            for (auto& output : node->outputs)
            {
                if (!isSimple && output->type == PinType::Delegate)
                    continue;

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
                //auto alpha   = static_cast<int>(commentAlpha * ImGui::GetStyle().Alpha * 255);
                auto bgAlpha = static_cast<int>(ImGui::GetStyle().Alpha * 255);

                //ImGui::PushStyleVar(ImGuiStyleVar_Alpha, commentAlpha * ImGui::GetStyle().Alpha);

                auto min = ed::GetGroupMin();
                //auto max = ed::GetGroupMax();

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

                //ImGui::PopStyleVar();
            }
            ed::EndGroupHint();
        }

        for (auto& link : config->s_Links)
            ed::Link(link->id, link->startPinID, link->endPinID, link->color, 2.0f);

        if (!createNewNode)
        {
            if (ed::BeginCreate(ImColor(255, 255, 255), 2.0f))
            {
                auto showLabel = [](const char* label, ImColor color)
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
                            showLabel("x Incompatible Pin Kind", ImColor(45, 32, 32, 180));
                            ed::RejectNewItem(ImColor(255, 0, 0), 2.0f);
                        }
                        else if (endPin->node->id == startPin->node->id)
                        {
                            showLabel("x Cannot connect to self", ImColor(45, 32, 32, 180));
                            ed::RejectNewItem(ImColor(255, 0, 0), 1.0f);
                        }
                        else if (endPin->type != startPin->type)
                        {
                            showLabel("x Incompatible Pin Type", ImColor(45, 32, 32, 180));
                            ed::RejectNewItem(ImColor(255, 128, 128), 1.0f);
                        }
                        else
                        {
                            showLabel("+ Create Link", ImColor(32, 45, 32, 180));
                            if (ed::AcceptNewItem(ImColor(128, 255, 128), 4.0f))
                            {
                                for (int link_i = 0; link_i < config->s_Links.size(); link_i++)
                                {
                                    if (config->s_Links.at(link_i)->startPinID == startPinId && startPin->type == PinType::Flow)
                                    {
                                        // s_Links.at(link_i)->endPin->link = nullptr;
                                        config->s_Links.at(link_i)->endPin->links.erase(std::remove(config->s_Links.at(link_i)->endPin->links.begin(), config->s_Links.at(link_i)->endPin->links.end(), config->s_Links.at(link_i)), config->s_Links.at(link_i)->endPin->links.end());
                                        config->s_Links.at(link_i)->startPin->links.erase(std::remove(config->s_Links.at(link_i)->startPin->links.begin(), config->s_Links.at(link_i)->startPin->links.end(), config->s_Links.at(link_i)), config->s_Links.at(link_i)->startPin->links.end());
                                        config->s_Links.at(link_i)->startPin = nullptr;
                                        config->s_Links.at(link_i)->endPin = nullptr;
                                        ed::DeleteLink(config->s_Links.at(link_i)->id);
                                        link_i = config->s_Links.size();
                                    }
                                    else if (config->s_Links.at(link_i)->endPinID == endPinId && endPin->type != PinType::Flow && endPin->kind == PinKind::Input)
                                    {
                                        //s_Links.at(link_i)->startPin->link = nullptr;
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
                        showLabel("+ Create Node", ImColor(32, 45, 32, 180));

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
            ImGui::Text("Type: %s", node->type == NodeType::Blueprint ? "Blueprint" : (node->type == NodeType::Tree ? "Tree" : "Comment"));
            ImGui::Text("Inputs: %d", (int)node->inputs.size());
            ImGui::Text("Outputs: %d", (int)node->outputs.size());
        }
        else
            ImGui::Text("Unknown node: %p", contextNodeId.AsPointer());
        ImGui::Separator();
        if (node->name != "GL Main Loop")
        {
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

                pin_type_selected_item = PinTypeToString(pin->type);
                if (ImGui::BeginCombo("##combo", pin_type_selected_item.data())) // The second parameter is the label previewed before opening the combo.
                {
                    for (int n = 0; n < pin->template_allowed_types.size(); n++)
                    {
                        bool is_selected = (pin_type_selected_item == PinTypeToString(pin->template_allowed_types[n]));
                        if (ImGui::Selectable(PinTypeToString(pin->template_allowed_types[n]).c_str(), is_selected))
                        {
                            pin_type_selected_item = PinTypeToString(pin->template_allowed_types[n]);
                            for (int link_i = 0; link_i < pin->links.size(); link_i++)
                            {
                                ed::DeleteLink(pin->links.at(link_i)->id);
                            }
                            pin->links.clear();
                            pin->node->node_funcs->ChangePinType(pin->kind, pin->index, StringToPinType(pin_type_selected_item));
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

    if (ImGui::BeginPopup("Create New Node"))
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
    ImGui::PopStyleVar();
    ed::Resume();

    ed::End();
}

