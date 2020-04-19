#include "dummy_nodes.h"

void DummyNode_Func::Initialize()
{
    std::cout << "Init Dummy Function, Node ID: " << parent_node->id.AsPointer() << std::endl;
}

void DummyNode_Func::Run()
{
    std::cout << "Run Dummy Function, Node ID: " << parent_node->id.AsPointer() << ", ";
    if (parent_node->outputs[0]->link)
        if (parent_node->outputs[0]->link->endPin)
            if (parent_node->outputs[0]->link->endPin->node)
                if (parent_node->outputs[0]->link->endPin->node->node_funcs)
                    parent_node->outputs[0]->link->endPin->node->node_funcs->Run();
}

void DummyNode_Func::Delete()
{
    std::cout << "Remove Dummy Function, Node ID: " << parent_node->id.AsPointer() << std::endl;
    parent_node = nullptr;
}

std::shared_ptr<Node> DummyNode(std::vector<std::shared_ptr<Node>>& s_Nodes)
{
    s_Nodes.emplace_back(new Node(GetNextId(), "Dummy Node"));
    s_Nodes.back()->inputs.emplace_back(new Pin(GetNextId(), "Enter", PinType::Flow));
    s_Nodes.back()->outputs.emplace_back(new Pin(GetNextId(), "Next", PinType::Flow));

    s_Nodes.back()->node_funcs = std::make_shared<DummyNode_Func>();
    std::dynamic_pointer_cast<DummyNode_Func>(s_Nodes.back()->node_funcs)->parent_node = s_Nodes.back();

    s_Nodes.back()->node_funcs->Initialize();

    BuildNode(s_Nodes.back());

    return s_Nodes.back();
}