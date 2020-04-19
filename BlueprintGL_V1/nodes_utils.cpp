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

std::shared_ptr<Pin> FindPin(ed::PinId id, std::vector<std::shared_ptr<Node>>& s_Nodes)
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

bool CanCreateLink(std::shared_ptr<Pin> a, std::shared_ptr<Pin> b)
{
    if (!a || !b || a == b || a->kind == b->kind || a->type != b->type || a->node == b->node)
        return false;

    return true;
}