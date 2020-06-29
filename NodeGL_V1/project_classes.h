#pragma once
#ifndef PROJECT_CLASSES_H
#define PROJECT_CLASSES_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <imgui_node_editor.h>
#include <ax/Builders.h>
#include <memory>
#include <functional>
#include "project_enums.h"
#include "nodes/node_function_interface.h"

namespace ed = ax::NodeEditor;
namespace util = ax::NodeEditor::Utilities;

struct Node;
struct Link;


class BasePin
{
public:
    BasePin(std::string pin_key, int order, int id, const char* name, PinType type) :
        pin_key(pin_key), order(order), id(id), node(), name(name), type(type), kind(PinKind::Input), isTemplate(false), 
        exposed(true), always_expose(true), isArr(false), isGeneralArray(false)
    {
    }

    virtual ~BasePin()
    {
        node = nullptr;
        links.clear();
        template_allowed_types.clear();
    }

    std::string pin_key;
    int order;
    ed::PinId   id;
    std::shared_ptr<::Node> node;
    std::vector<std::shared_ptr<::Link>> links;
    std::string name;
    PinType     type;
    PinKind     kind;

    bool isTemplate;
    bool isGeneralArray;
    std::vector<PinType> template_allowed_types;

    bool exposed;
    bool always_expose;
    bool isArr;
};


template<class T>
class PinValue : public BasePin {
public:
    PinValue(std::string pin_key, int order, int id, const char* name, PinType type, T default_val) : BasePin(pin_key, order, id, name, type)
    {
        isArr = false;
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


template<class T>
class PinArrValue : public BasePin {
public:
    PinArrValue(std::string pin_key, int order, int id, const char* name, PinType type, std::shared_ptr<std::vector<T>> default_val) : BasePin(pin_key, order, id, name, type)
    {
        isArr = true;
        value = default_val;
        default_value = std::make_shared<std::vector<T>>();
        if (default_val)
        {
            for (int i = 0; i < default_val->size(); i++)
            {
                default_value->push_back(default_val->at(i));
            }
        }
    }

    ~PinArrValue()
    {
        node = nullptr;
        links.clear();
        template_allowed_types.clear();
        value = nullptr;
        default_value = nullptr;
    }

    std::shared_ptr<std::vector<T>> GetValue()
    {
        return value;
    }

    void SetValue(std::shared_ptr<std::vector<T>> v)
    {
        value = v;
    }
    std::shared_ptr<std::vector<T>> value;
    std::shared_ptr<std::vector<T>> default_value;
};


class Node
{
public:
    Node(int id, const char* name, ImColor color = ImColor(128, 128, 128)) :
        id(id), name(name), no_flow_node(false), color(color), type(NodeType::Blueprint), size(0, 0),
        is_set_placeholder(false), is_get_placeholder(false), is_get_array(false)
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
    bool is_get_array;
    std::map<std::string, std::shared_ptr<BasePin>> inputs;
    std::map<std::string, std::shared_ptr<BasePin>> outputs;
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
    SearchNodeObj(std::string title, std::string category, std::vector<std::string> keywords, std::function<std::shared_ptr<Node>(std::vector<std::shared_ptr<Node>>&)> func) :
        title(title), category(category), keywords(keywords), func(func), show_in_global_search(true)
    {
    }
    SearchNodeObj(std::string title, std::string category, std::vector<std::string> keywords, std::function<std::shared_ptr<Node>(std::vector<std::shared_ptr<Node>>&)> func, bool show_in_global_search) :
        title(title), category(category), keywords(keywords), func(func), show_in_global_search(show_in_global_search)
    {
    }

    std::string title;
    std::string category;
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


class BaseArray
{
public:
    BaseArray(std::string name, PinType type) :
        name(name), type(type)
    {

    }

    virtual ~BaseArray()
    {
        nodesID_vec.clear();
    }

    std::string name;
    PinType type;
    std::vector<ed::NodeId> nodesID_vec;
};


template<class T>
class ArrayValue : public BaseArray
{
public:
    ArrayValue(std::string name, PinType type, std::shared_ptr<std::vector<T>> value) :
        BaseArray(name, type)
    {
        this->value = value;
        this->default_value = std::make_shared<std::vector<T>>();
        if (value)
        {
            for (int i = 0; i < value->size(); i++)
            {
                this->default_value->push_back(value->at(i));
            }
        }
    }

    ~ArrayValue()
    {
        nodesID_vec.clear();
        if (value)
            value->clear();
        if (default_value)
            default_value->clear();
        value = nullptr;
        default_value = nullptr;
    }

    std::shared_ptr<std::vector<T>> value;
    std::shared_ptr<std::vector<T>> default_value;
};

#endif