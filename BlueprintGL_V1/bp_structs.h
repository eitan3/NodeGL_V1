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


class BasePin
{
public:
    BasePin(int id, const char* name, PinType type) :
        id(id), node(), name(name), type(type), kind(PinKind::Input)
    {
    }

    virtual ~BasePin()
    {
        node = nullptr;
        links.clear();
    }

    ed::PinId   id;
    std::shared_ptr<::Node> node;
    std::vector<std::shared_ptr<::Link>> links;
    std::string name;
    PinType     type;
    PinKind     kind;
};


template<class T>
class PinValue : public BasePin {
public:
    //using BasePin::BasePin;
    PinValue(int id, const char* name, PinType type, T default_val) : BasePin(id, name, type)
    {
        default_value = default_val;
    }


    T GetValue()
    {
        return value;
    }

    void SetValue(T v)
    {
        value = v;
    }
    T value;
    T default_value;
};


class Node
{
public:
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

    ed::NodeId id;
    std::string name;
    std::vector<std::shared_ptr<BasePin>> inputs;
    std::vector<std::shared_ptr<BasePin>> outputs;
    ImColor color;
    NodeType type;
    ImVec2 size;
    std::string state;
    std::string savedState;

    std::shared_ptr<NodeFunctions> node_funcs;
};


class Link
{
public:
    Link(ed::LinkId id, ed::PinId startPinId, ed::PinId endPinId, std::shared_ptr<BasePin> start_pin, std::shared_ptr<BasePin> end_pin) :
        id(id), startPinID(startPinId), endPinID(endPinId), startPin(start_pin), endPin(end_pin), color(255, 255, 255)
    {
    }

    ~Link()
    {
        if (startPin)
            startPin->links.clear();
        if (endPin)
            endPin->links.clear();
        startPin = nullptr;
        endPin = nullptr;
    }

    ed::LinkId id;

    ed::PinId startPinID;
    ed::PinId endPinID;

    std::shared_ptr<BasePin> startPin;
    std::shared_ptr<BasePin> endPin;

    ImColor color;
};