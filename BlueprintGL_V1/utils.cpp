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
            if (pin->id == id)
                return pin;

        for (auto& pin : node->outputs)
            if (pin->id == id)
                return pin;
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
    if (!a || !b || a == b || a->kind == b->kind || a->type != b->type || a->node == b->node)
        return false;

    return true;
}

void RunNextNodeFunc(std::shared_ptr<Node>& parent_node, int pin_index)
{
    if (parent_node->outputs.at(pin_index)->type == PinType::Flow)
        if (parent_node->outputs.at(pin_index)->links.size() > 0)
            if (parent_node->outputs.at(pin_index)->links.at(0))
                if (parent_node->outputs.at(pin_index)->links.at(0)->endPin)
                    if (parent_node->outputs.at(pin_index)->links.at(0)->endPin->node)
                        if (parent_node->outputs.at(pin_index)->links.at(0)->endPin->node->node_funcs)
                            parent_node->outputs.at(pin_index)->links.at(0)->endPin->node->node_funcs->Run();
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
    else if (type == PinType::TextureObject)
        return "Texture Object";
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
    else if (str == "Texture Object")
        return PinType::TextureObject;
    std::cout << "Error!!! Cant find pin type" << std::endl;
    return PinType::Unknown;
}

void UtilsChangePinType(std::shared_ptr<Node> parent_node, PinKind kind, int index, PinType type)
{
    if (kind == PinKind::Input)
    {
        if (type == PinType::Bool)
        {
            std::shared_ptr<PinValue<bool>> new_node = std::make_shared<PinValue<bool>>(index, parent_node->inputs.at(index)->id.Get(), parent_node->inputs.at(index)->name.c_str(), PinType::Bool, false);
            new_node->node = parent_node->inputs.at(index)->node;
            new_node->isTemplate = parent_node->inputs.at(index)->isTemplate;
            new_node->template_allowed_types = parent_node->inputs.at(index)->template_allowed_types;
            parent_node->inputs.at(index) = new_node;
        }
        else if (type == PinType::Float)
        {
            std::shared_ptr<PinValue<float>> new_node = std::make_shared<PinValue<float>>(index, parent_node->inputs.at(index)->id.Get(), parent_node->inputs.at(index)->name.c_str(), PinType::Float, 0);
            new_node->node = parent_node->inputs.at(index)->node;
            new_node->isTemplate = parent_node->inputs.at(index)->isTemplate;
            new_node->template_allowed_types = parent_node->inputs.at(index)->template_allowed_types;
            parent_node->inputs.at(index) = new_node;
        }
        else if (type == PinType::Int)
        {
            std::shared_ptr<PinValue<int>> new_node = std::make_shared<PinValue<int>>(index, parent_node->inputs.at(index)->id.Get(), parent_node->inputs.at(index)->name.c_str(), PinType::Int, 0);
            new_node->node = parent_node->inputs.at(index)->node;
            new_node->isTemplate = parent_node->inputs.at(index)->isTemplate;
            new_node->template_allowed_types = parent_node->inputs.at(index)->template_allowed_types;
            parent_node->inputs.at(index) = new_node;
        }
        else if (type == PinType::String)
        {
            std::shared_ptr<PinValue<std::string>> new_node = std::make_shared<PinValue<std::string>>(index, parent_node->inputs.at(index)->id.Get(), parent_node->inputs.at(index)->name.c_str(), PinType::String, "");
            new_node->node = parent_node->inputs.at(index)->node;
            new_node->isTemplate = parent_node->inputs.at(index)->isTemplate;
            new_node->template_allowed_types = parent_node->inputs.at(index)->template_allowed_types;
            parent_node->inputs.at(index) = new_node;
        }
        else if (type == PinType::TextureObject)
        {
            std::shared_ptr<PinValue<std::shared_ptr<TextureObject>>> new_node = std::make_shared<PinValue<std::shared_ptr<TextureObject>>>(index, parent_node->inputs.at(index)->id.Get(), parent_node->inputs.at(index)->name.c_str(), PinType::TextureObject, nullptr);
            new_node->node = parent_node->inputs.at(index)->node;
            new_node->isTemplate = parent_node->inputs.at(index)->isTemplate;
            new_node->template_allowed_types = parent_node->inputs.at(index)->template_allowed_types;
            parent_node->inputs.at(index) = new_node;
        }
    }
    else if (kind == PinKind::Output)
    {
        if (type == PinType::Bool)
        {
            std::shared_ptr<PinValue<bool>> new_node = std::make_shared<PinValue<bool>>(index, parent_node->outputs.at(index)->id.Get(), parent_node->outputs.at(index)->name.c_str(), PinType::Bool, false);
            new_node->node = parent_node->outputs.at(index)->node;
            new_node->isTemplate = parent_node->outputs.at(index)->isTemplate;
            new_node->template_allowed_types = parent_node->outputs.at(index)->template_allowed_types;
            parent_node->outputs.at(index) = new_node;
        }
        else if (type == PinType::Float)
        {
            std::shared_ptr<PinValue<float>> new_node = std::make_shared<PinValue<float>>(index, parent_node->outputs.at(index)->id.Get(), parent_node->outputs.at(index)->name.c_str(), PinType::Float, 0);
            new_node->node = parent_node->outputs.at(index)->node;
            new_node->isTemplate = parent_node->outputs.at(index)->isTemplate;
            new_node->template_allowed_types = parent_node->outputs.at(index)->template_allowed_types;
            parent_node->outputs.at(index) = new_node;
        }
        else if (type == PinType::Int)
        {
            std::shared_ptr<PinValue<int>> new_node = std::make_shared<PinValue<int>>(index, parent_node->outputs.at(index)->id.Get(), parent_node->outputs.at(index)->name.c_str(), PinType::Int, 0);
            new_node->node = parent_node->outputs.at(index)->node;
            new_node->isTemplate = parent_node->outputs.at(index)->isTemplate;
            new_node->template_allowed_types = parent_node->outputs.at(index)->template_allowed_types;
            parent_node->outputs.at(index) = new_node;
        }
        else if (type == PinType::String)
        {
            std::shared_ptr<PinValue<std::string>> new_node = std::make_shared<PinValue<std::string>>(index, parent_node->outputs.at(index)->id.Get(), parent_node->outputs.at(index)->name.c_str(), PinType::String, "");
            new_node->node = parent_node->outputs.at(index)->node;
            new_node->isTemplate = parent_node->outputs.at(index)->isTemplate;
            new_node->template_allowed_types = parent_node->outputs.at(index)->template_allowed_types;
            parent_node->outputs.at(index) = new_node;
        }
        else if (type == PinType::TextureObject)
        {
            std::shared_ptr<PinValue<std::shared_ptr<TextureObject>>> new_node = std::make_shared<PinValue<std::shared_ptr<TextureObject>>>(index, parent_node->outputs.at(index)->id.Get(), parent_node->outputs.at(index)->name.c_str(), PinType::TextureObject, nullptr);
            new_node->node = parent_node->outputs.at(index)->node;
            new_node->isTemplate = parent_node->outputs.at(index)->isTemplate;
            new_node->template_allowed_types = parent_node->outputs.at(index)->template_allowed_types;
            parent_node->outputs.at(index) = new_node;
        }
    }
}

template<typename T>
std::shared_ptr<PinValue<T>> GetLinkedInputPin(std::shared_ptr<Node>& parent_node, int pin_index)
{
    if (parent_node->inputs.at(pin_index)->links.size() > 0)
    {
        if (parent_node->inputs.at(pin_index)->links.at(0))
        {
            if (parent_node->inputs.at(pin_index)->links.at(0)->startPin)
            {
                std::shared_ptr<PinValue<T>> input_pin = std::dynamic_pointer_cast<PinValue<T>>(parent_node->inputs.at(pin_index)->links.at(0)->startPin);
                return input_pin;
            }
        }
    }
    return nullptr;
}

template<typename T>
T GetInputPinValue(std::shared_ptr<Node>& parent_node, int pin_index)
{
    if (parent_node->inputs.at(pin_index)->links.size() > 0)
    {
        if (parent_node->inputs.at(pin_index)->links.at(0))
        {
            if (parent_node->inputs.at(pin_index)->links.at(0)->startPin)
            {
                std::shared_ptr<PinValue<T>> input_pin = std::dynamic_pointer_cast<PinValue<T>>(parent_node->inputs.at(pin_index)->links.at(0)->startPin);
                input_pin->node->node_funcs->NoFlowUpdatePinsValues();
                std::dynamic_pointer_cast<PinValue<T>>(parent_node->inputs.at(pin_index))->value = input_pin->GetValue();
                return input_pin->GetValue();
            }
        }
    }
    std::shared_ptr<PinValue<T>> input_pin = std::dynamic_pointer_cast<PinValue<T>>(parent_node->inputs.at(pin_index));
    input_pin->value = input_pin->default_value;
    return input_pin->GetValue();
}













template std::shared_ptr<PinValue<bool>> GetLinkedInputPin(std::shared_ptr<Node>& parent_node, int pin_index);
template std::shared_ptr<PinValue<int>> GetLinkedInputPin(std::shared_ptr<Node>& parent_node, int pin_index);
template std::shared_ptr<PinValue<float>> GetLinkedInputPin(std::shared_ptr<Node>& parent_node, int pin_index);
template std::shared_ptr<PinValue<std::string>> GetLinkedInputPin(std::shared_ptr<Node>& parent_node, int pin_index);
template std::shared_ptr<PinValue<std::shared_ptr<TextureObject>>> GetLinkedInputPin(std::shared_ptr<Node>& parent_node, int pin_index);

template bool GetInputPinValue(std::shared_ptr<Node>& parent_node, int pin_index);
template int GetInputPinValue(std::shared_ptr<Node>& parent_node, int pin_index);
template float GetInputPinValue(std::shared_ptr<Node>& parent_node, int pin_index);
template std::string GetInputPinValue(std::shared_ptr<Node>& parent_node, int pin_index);
template std::shared_ptr<TextureObject> GetInputPinValue(std::shared_ptr<Node>& parent_node, int pin_index);