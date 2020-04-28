#include "nodes_builder.h"

void BuildNode(std::shared_ptr<Node>& node)
{
    for (auto& input : node->inputs)
    {
        input->node = node;
        input->kind = PinKind::Input;
    }

    for (auto& output : node->outputs)
    {
        output->node = node;
        output->kind = PinKind::Output;
    }
}

/*
Node* SpawnBranchNode(std::vector<Node>& s_Nodes)
{
    s_Nodes.emplace_back(GetNextId(), "Branch");
    s_Nodes.back().Inputs.emplace_back(GetNextId(), "", PinType::Flow);
    s_Nodes.back().Inputs.emplace_back(GetNextId(), "Condition", PinType::Bool);
    s_Nodes.back().Outputs.emplace_back(GetNextId(), "True", PinType::Flow);
    s_Nodes.back().Outputs.emplace_back(GetNextId(), "False", PinType::Flow);

    BuildNode(&s_Nodes.back());

    return &s_Nodes.back();
}

Node* SpawnComment(std::vector<Node>& s_Nodes)
{
    s_Nodes.emplace_back(GetNextId(), "Test Comment");
    s_Nodes.back().Type = NodeType::Comment;
    s_Nodes.back().Size = ImVec2(300, 200);

    return &s_Nodes.back();
}
*/

void BuildNodes(std::vector<std::shared_ptr<Node>>& s_Nodes)
{
    for (auto& node : s_Nodes)
        BuildNode(node);
}