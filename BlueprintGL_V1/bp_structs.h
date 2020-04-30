#pragma once
#ifndef BP_CLASSES_H
#define BP_CLASSES_H

#include <iostream>
#include <string>
#include <vector>
#include <imgui_node_editor.h>
#include <ax/Builders.h>
#include <memory>
#include <functional>
#include "bp_enums.h"
#include "nodes/node_function_interface.h"

namespace ed = ax::NodeEditor;
namespace util = ax::NodeEditor::Utilities;

struct Node;
struct Link;


class BasePin
{
public:
    BasePin(int index, int id, const char* name, PinType type) :
        index(index), id(id), node(), name(name), type(type), kind(PinKind::Input), isTemplate(false)
    {
    }

    virtual ~BasePin()
    {
        node = nullptr;
        links.clear();
        template_allowed_types.clear();
    }

    int index;
    ed::PinId   id;
    std::shared_ptr<::Node> node;
    std::vector<std::shared_ptr<::Link>> links;
    std::string name;
    PinType     type;
    PinKind     kind;

    bool isTemplate;
    std::vector<PinType> template_allowed_types;
};


template<class T>
class PinValue : public BasePin {
public:
    PinValue(int index, int id, const char* name, PinType type, T default_val) : BasePin(index, id, name, type)
    {
        value = default_val;
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
    Node(int id, const char* name, ImColor color = ImColor(128, 128, 128)) :
        id(id), name(name), no_flow_node(false), color(color), type(NodeType::Blueprint), size(0, 0),
        is_set_placeholder(false), is_get_placeholder(false)
    {
    }

    Node(int id, const char* name, bool no_flow_node, ImColor color = ImColor(128, 128, 128)) :
        id(id), name(name), no_flow_node(no_flow_node), color(color), type(NodeType::Blueprint), size(0, 0),
        is_set_placeholder(false), is_get_placeholder(false)
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
    bool no_flow_node;
    bool is_set_placeholder;
    bool is_get_placeholder;
    std::vector<std::shared_ptr<BasePin>> inputs;
    std::vector<std::shared_ptr<BasePin>> outputs;
    ImColor color;
    NodeType type;
    ImVec2 size;
    std::string state;
    std::string savedState;
    std::string info;
    std::string error;
    std::shared_ptr<NodeFunctions> node_funcs;
};


class SearchNodeObj
{
public:
    SearchNodeObj(std::string title, std::vector<std::string> keywords, std::function<std::shared_ptr<Node>(std::vector<std::shared_ptr<Node>>&)> func) :
        title(title), keywords(keywords), func(func), show_in_global_search(true)
    {
    }
    SearchNodeObj(std::string title, std::vector<std::string> keywords, std::function<std::shared_ptr<Node>(std::vector<std::shared_ptr<Node>>&)> func, bool show_in_global_search) :
        title(title), keywords(keywords), func(func), show_in_global_search(show_in_global_search)
    {
    }

    std::string title;
    std::vector<std::string> keywords;
    std::function<std::shared_ptr<Node>(std::vector<std::shared_ptr<Node>>&)> func;
    bool show_in_global_search;
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


class BasePlaceholder
{
public:
    BasePlaceholder(std::string name, PinType type) :
        name(name), type(type)
    {

    }

    virtual ~BasePlaceholder()
    {
        nodesID_vec.clear();
    }

    std::string name;
    PinType type;
    std::vector<ed::NodeId> nodesID_vec;
};


template<class T>
class PlaceholderValue : public BasePlaceholder
{
public:
    PlaceholderValue(std::string name, PinType type, T value) :
        BasePlaceholder(name, type)
    {
        this->value = value;
    }

    T value;
};

#endif