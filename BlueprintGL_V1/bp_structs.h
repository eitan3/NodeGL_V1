#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <imgui_node_editor.h>
#include <ax/Builders.h>
#include <memory>
#include "bp_enums.h"
#include "nodes/node_function_interface.h"

namespace ed = ax::NodeEditor;
namespace util = ax::NodeEditor::Utilities;

struct Node;
struct Link;

struct Pin
{
    ed::PinId   id;
    std::shared_ptr<::Node> node;
    std::shared_ptr <::Link> link;
    std::string name;
    PinType     type;
    PinKind     kind;

    Pin(int id, const char* name, PinType type) :
        id(id), node(), link(), name(name), type(type), kind(PinKind::Input)
    {
    }

    ~Pin()
    {
        node = nullptr;
        link = nullptr;
    }
};

struct Node
{
    ed::NodeId id;
    std::string name;
    std::vector<std::shared_ptr<Pin>> inputs;
    std::vector<std::shared_ptr<Pin>> outputs;
    ImColor color;
    NodeType type;
    ImVec2 size;

    std::shared_ptr<NodeFunctions> node_funcs;

    std::string state;
    std::string savedState;

    Node(int id, const char* name, ImColor color = ImColor(255, 255, 255)) :
        id(id), name(name), color(color), type(NodeType::Blueprint), size(0, 0)
    {
    }

    ~Node()
    {
        inputs.clear();
        outputs.clear();
        node_funcs = nullptr;
    }
};

struct Link
{
    ed::LinkId id;

    ed::PinId startPinID;
    ed::PinId endPinID;

    std::shared_ptr<Pin> startPin;
    std::shared_ptr<Pin> endPin;

    ImColor color;

    Link(ed::LinkId id, ed::PinId startPinId, ed::PinId endPinId, std::shared_ptr<Pin> start_pin, std::shared_ptr<Pin> end_pin) :
        id(id), startPinID(startPinId), endPinID(endPinId), startPin(start_pin), endPin(end_pin), color(255, 255, 255)
    {
    }

    ~Link()
    {
        if (startPin)
            startPin->link = nullptr;
        if (endPin)
            endPin->link = nullptr;
        startPin = nullptr;
        endPin = nullptr;
    }
};