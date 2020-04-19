#include "gl_main_loop.h"

void GlMainLoop_Func::Initialize()
{
    std::cout << "Init GL Main Loop, Node ID: " << parent_node->id.AsPointer() << std::endl;
}

void GlMainLoop_Func::Run()
{
    std::cout << "Run GL Main Loop, Node ID: " << parent_node->id.AsPointer() << ", ";
    if (parent_node->outputs[0]->link)
        if (parent_node->outputs[0]->link->endPin)
            if (parent_node->outputs[0]->link->endPin->node)
                if (parent_node->outputs[0]->link->endPin->node->node_funcs)
                    parent_node->outputs[0]->link->endPin->node->node_funcs->Run();
}

void GlMainLoop_Func::Delete()
{
    std::cout << "Remove GL Main Loop, Node ID: " << parent_node->id.AsPointer() << std::endl;
    parent_node = nullptr;
}

std::shared_ptr<Node> GlMainLoop(std::vector<std::shared_ptr<Node>>& s_Nodes)
{
    s_Nodes.emplace_back(new Node(GetNextId(), "GL Main Loop", ImColor(255, 128, 128)));
    s_Nodes.back()->outputs.emplace_back(new Pin(GetNextId(), "Next", PinType::Flow));

    s_Nodes.back()->node_funcs = std::make_shared<GlMainLoop_Func>();
    std::dynamic_pointer_cast<GlMainLoop_Func>(s_Nodes.back()->node_funcs)->parent_node = s_Nodes.back();

    s_Nodes.back()->node_funcs->Initialize();

    BuildNode(s_Nodes.back());

    return s_Nodes.back();
}