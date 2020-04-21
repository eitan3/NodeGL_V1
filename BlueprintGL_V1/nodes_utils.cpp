#include "nodes_utils.h"

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
    if (parent_node->outputs.at(pin_index)->links.size() > 0)
        if (parent_node->outputs.at(pin_index)->links.at(0))
            if (parent_node->outputs.at(pin_index)->links.at(0)->endPin)
                if (parent_node->outputs.at(pin_index)->links.at(0)->endPin->node)
                    if (parent_node->outputs.at(pin_index)->links.at(0)->endPin->node->node_funcs)
                        parent_node->outputs.at(pin_index)->links.at(0)->endPin->node->node_funcs->Run();
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
                std::dynamic_pointer_cast<PinValue<T>>(parent_node->inputs.at(pin_index))->value = input_pin->GetValue();
                return input_pin->GetValue();
            }
        }
    }
    std::shared_ptr<PinValue<T>> input_pin = std::dynamic_pointer_cast<PinValue<T>>(parent_node->inputs.at(pin_index));
    std::dynamic_pointer_cast<PinValue<T>>(parent_node->inputs.at(pin_index))->value = input_pin->default_value;
    return input_pin->default_value;
}













template std::shared_ptr<PinValue<bool>> GetLinkedInputPin(std::shared_ptr<Node>& parent_node, int pin_index);
template std::shared_ptr<PinValue<int>> GetLinkedInputPin(std::shared_ptr<Node>& parent_node, int pin_index);
template std::shared_ptr<PinValue<float>> GetLinkedInputPin(std::shared_ptr<Node>& parent_node, int pin_index);
template std::shared_ptr<PinValue<std::string>> GetLinkedInputPin(std::shared_ptr<Node>& parent_node, int pin_index);

template bool GetInputPinValue(std::shared_ptr<Node>& parent_node, int pin_index);
template int GetInputPinValue(std::shared_ptr<Node>& parent_node, int pin_index);
template float GetInputPinValue(std::shared_ptr<Node>& parent_node, int pin_index);
template std::string GetInputPinValue(std::shared_ptr<Node>& parent_node, int pin_index);