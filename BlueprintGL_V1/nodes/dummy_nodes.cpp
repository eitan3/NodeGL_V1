#include "dummy_nodes.h"

void DummyNode_Func::Initialize()
{
    // std::cout << "Init Dummy Function, Node ID: " << parent_node->id.AsPointer() << std::endl;
}

void DummyNode_Func::Run()
{
    // std::cout << "Run Dummy Function, Node ID: " << parent_node->id.AsPointer() << ", ";
    RunNextNodeFunc(parent_node, 0);
}

void DummyNode_Func::Delete()
{
    // std::cout << "Remove Dummy Function, Node ID: " << parent_node->id.AsPointer() << std::endl;
    parent_node = nullptr;
}

std::shared_ptr<Node> DummyNode(std::vector<std::shared_ptr<Node>>& s_Nodes)
{
    s_Nodes.emplace_back(new Node(GetNextId(), "Dummy Node"));
    s_Nodes.back()->inputs.emplace_back(new BasePin(GetNextId(), "Enter", PinType::Flow));
    s_Nodes.back()->outputs.emplace_back(new BasePin(GetNextId(), "Next", PinType::Flow));

    s_Nodes.back()->node_funcs = std::make_shared<DummyNode_Func>();
    std::dynamic_pointer_cast<DummyNode_Func>(s_Nodes.back()->node_funcs)->parent_node = s_Nodes.back();

    s_Nodes.back()->node_funcs->Initialize();

    BuildNode(s_Nodes.back());

    return s_Nodes.back();
}




void DummySendFloat_Func::Initialize()
{

}

void DummySendFloat_Func::Run()
{
    // Update output pin value
    std::shared_ptr<PinValue<float>> output_pin = std::dynamic_pointer_cast<PinValue<float>>(parent_node->outputs.at(1));
    if (output_pin)
    {
        output_pin->value += 0.000001;
    }

    RunNextNodeFunc(parent_node, 0);
}

void DummySendFloat_Func::Delete()
{
    parent_node = nullptr;
}

std::shared_ptr<Node> DummySendFloat(std::vector<std::shared_ptr<Node>>& s_Nodes)
{
    s_Nodes.emplace_back(new Node(GetNextId(), "Dummy Send Float"));
    s_Nodes.back()->inputs.emplace_back(new BasePin(GetNextId(), "Enter", PinType::Flow));
    s_Nodes.back()->outputs.emplace_back(new BasePin(GetNextId(), "Next", PinType::Flow));
    s_Nodes.back()->outputs.emplace_back(new PinValue<float>(GetNextId(), "Float Value", PinType::Float, 0));

    s_Nodes.back()->node_funcs = std::make_shared<DummySendFloat_Func>();
    std::dynamic_pointer_cast<DummySendFloat_Func>(s_Nodes.back()->node_funcs)->parent_node = s_Nodes.back();

    s_Nodes.back()->node_funcs->Initialize();

    BuildNode(s_Nodes.back());

    return s_Nodes.back();
}




void DummyRecvSendFloat_Func::Initialize()
{

}

void DummyRecvSendFloat_Func::Run()
{
    // Update output pin value
    float input_value = GetInputPinValue<float>(parent_node, 1);
    std::shared_ptr<PinValue<float>> output_pin = std::dynamic_pointer_cast<PinValue<float>>(parent_node->outputs.at(1));
    if (output_pin)
    {
        output_pin->value = input_value;
    }

    RunNextNodeFunc(parent_node, 0);
}

void DummyRecvSendFloat_Func::Delete()
{
    parent_node = nullptr;
}

std::shared_ptr<Node> DummyRecvSendFloat(std::vector<std::shared_ptr<Node>>& s_Nodes)
{
    s_Nodes.emplace_back(new Node(GetNextId(), "Dummy Receive Send Float"));
    s_Nodes.back()->inputs.emplace_back(new BasePin(GetNextId(), "Enter", PinType::Flow));
    s_Nodes.back()->inputs.emplace_back(new PinValue<float>(GetNextId(), "Float Value", PinType::Float, 0));
    s_Nodes.back()->outputs.emplace_back(new BasePin(GetNextId(), "Next", PinType::Flow));
    s_Nodes.back()->outputs.emplace_back(new PinValue<float>(GetNextId(), "Float Value", PinType::Float, 0));

    s_Nodes.back()->node_funcs = std::make_shared<DummyRecvSendFloat_Func>();
    std::dynamic_pointer_cast<DummyRecvSendFloat_Func>(s_Nodes.back()->node_funcs)->parent_node = s_Nodes.back();

    s_Nodes.back()->node_funcs->Initialize();

    BuildNode(s_Nodes.back());

    return s_Nodes.back();
}




void DummyPrintFloat_Func::Initialize()
{

}

void DummyPrintFloat_Func::Run()
{
    // GetInputPinValue
    float input_value = GetInputPinValue<float>(parent_node, 1);
    std::cout << input_value << std::endl;

    RunNextNodeFunc(parent_node, 0);
}

void DummyPrintFloat_Func::Delete()
{
    parent_node = nullptr;
}

std::shared_ptr<Node> DummyPrintFloat(std::vector<std::shared_ptr<Node>>& s_Nodes)
{
    s_Nodes.emplace_back(new Node(GetNextId(), "Dummy Print Float"));
    s_Nodes.back()->inputs.emplace_back(new BasePin(GetNextId(), "Enter", PinType::Flow));
    s_Nodes.back()->inputs.emplace_back(new PinValue<float>(GetNextId(), "Float Value", PinType::Float, 0));
    s_Nodes.back()->outputs.emplace_back(new BasePin(GetNextId(), "Next", PinType::Flow));

    s_Nodes.back()->node_funcs = std::make_shared<DummyPrintFloat_Func>();
    std::dynamic_pointer_cast<DummyPrintFloat_Func>(s_Nodes.back()->node_funcs)->parent_node = s_Nodes.back();

    s_Nodes.back()->node_funcs->Initialize();

    BuildNode(s_Nodes.back());

    return s_Nodes.back();
}