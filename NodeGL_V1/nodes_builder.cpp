#include "nodes_builder.h"

void BuildNode(std::shared_ptr<Node>& node)
{
    for (auto& input : node->inputs)
    {
        input.second->node = node;
        input.second->kind = PinKind::Input;
    }

    for (auto& output : node->outputs)
    {
        output.second->node = node;
        output.second->kind = PinKind::Output;
    }
}

void BuildNodes(std::vector<std::shared_ptr<Node>>& s_Nodes)
{
    for (auto& node : s_Nodes)
        BuildNode(node);
}