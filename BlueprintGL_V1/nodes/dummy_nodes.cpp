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

void DummyNode_Func::NoFlowUpdatePinsValues()
{

}

void DummyNode_Func::ChangePinType(PinKind kind, int index, PinType type)
{
}

std::shared_ptr<Node> DummyNode(std::vector<std::shared_ptr<Node>>& s_Nodes)
{
    s_Nodes.emplace_back(new Node(GetNextId(), "Dummy Node"));
    s_Nodes.back()->inputs.emplace_back(new BasePin(s_Nodes.back()->inputs.size(), GetNextId(), "Enter", PinType::Flow));
    s_Nodes.back()->outputs.emplace_back(new BasePin(s_Nodes.back()->outputs.size(), GetNextId(), "Next", PinType::Flow));

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

void DummySendFloat_Func::NoFlowUpdatePinsValues()
{

}

void DummySendFloat_Func::ChangePinType(PinKind kind, int index, PinType type)
{
}

std::shared_ptr<Node> DummySendFloat(std::vector<std::shared_ptr<Node>>& s_Nodes)
{
    s_Nodes.emplace_back(new Node(GetNextId(), "Dummy Send Float"));
    s_Nodes.back()->inputs.emplace_back(new BasePin(s_Nodes.back()->inputs.size(), GetNextId(), "Enter", PinType::Flow));
    s_Nodes.back()->outputs.emplace_back(new BasePin(s_Nodes.back()->outputs.size(), GetNextId(), "Next", PinType::Flow));
    s_Nodes.back()->outputs.emplace_back(new PinValue<float>(s_Nodes.back()->outputs.size(), GetNextId(), "Float Value", PinType::Float, 0));

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

void DummyRecvSendFloat_Func::NoFlowUpdatePinsValues()
{

}

void DummyRecvSendFloat_Func::ChangePinType(PinKind kind, int index, PinType type)
{
}

std::shared_ptr<Node> DummyRecvSendFloat(std::vector<std::shared_ptr<Node>>& s_Nodes)
{
    s_Nodes.emplace_back(new Node(GetNextId(), "Dummy Receive Send Float"));
    s_Nodes.back()->inputs.emplace_back(new BasePin(s_Nodes.back()->inputs.size(), GetNextId(), "Enter", PinType::Flow));
    s_Nodes.back()->inputs.emplace_back(new PinValue<float>(s_Nodes.back()->inputs.size(), GetNextId(), "Float Value", PinType::Float, 0));
    s_Nodes.back()->outputs.emplace_back(new BasePin(s_Nodes.back()->outputs.size(), GetNextId(), "Next", PinType::Flow));
    s_Nodes.back()->outputs.emplace_back(new PinValue<float>(s_Nodes.back()->outputs.size(), GetNextId(), "Float Value", PinType::Float, 0));

    s_Nodes.back()->node_funcs = std::make_shared<DummyRecvSendFloat_Func>();
    std::dynamic_pointer_cast<DummyRecvSendFloat_Func>(s_Nodes.back()->node_funcs)->parent_node = s_Nodes.back();

    s_Nodes.back()->node_funcs->Initialize();

    BuildNode(s_Nodes.back());

    return s_Nodes.back();
}





void DummySendInt_Func::Initialize()
{

}

void DummySendInt_Func::Run()
{
    // Update output pin value
    std::shared_ptr<PinValue<int>> output_pin = std::dynamic_pointer_cast<PinValue<int>>(parent_node->outputs.at(1));
    if (output_pin)
    {
        output_pin->value += 1;
    }

    RunNextNodeFunc(parent_node, 0);
}

void DummySendInt_Func::Delete()
{
    parent_node = nullptr;
}

void DummySendInt_Func::NoFlowUpdatePinsValues()
{

}

void DummySendInt_Func::ChangePinType(PinKind kind, int index, PinType type)
{
}

std::shared_ptr<Node> DummySendInt(std::vector<std::shared_ptr<Node>>& s_Nodes)
{
    s_Nodes.emplace_back(new Node(GetNextId(), "Dummy Send Integer"));
    s_Nodes.back()->inputs.emplace_back(new BasePin(s_Nodes.back()->inputs.size(), GetNextId(), "Enter", PinType::Flow));
    s_Nodes.back()->outputs.emplace_back(new BasePin(s_Nodes.back()->outputs.size(), GetNextId(), "Next", PinType::Flow));
    s_Nodes.back()->outputs.emplace_back(new PinValue<int>(s_Nodes.back()->outputs.size(), GetNextId(), "Int Value", PinType::Int, 0));

    s_Nodes.back()->node_funcs = std::make_shared<DummySendInt_Func>();
    std::dynamic_pointer_cast<DummySendInt_Func>(s_Nodes.back()->node_funcs)->parent_node = s_Nodes.back();

    s_Nodes.back()->node_funcs->Initialize();

    BuildNode(s_Nodes.back());

    return s_Nodes.back();
}





void DummyRecvSendInt_Func::Initialize()
{

}

void DummyRecvSendInt_Func::Run()
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

void DummyRecvSendInt_Func::Delete()
{
    parent_node = nullptr;
}

void DummyRecvSendInt_Func::NoFlowUpdatePinsValues()
{

}

void DummyRecvSendInt_Func::ChangePinType(PinKind kind, int index, PinType type)
{
}

std::shared_ptr<Node> DummyRecvSendInt(std::vector<std::shared_ptr<Node>>& s_Nodes)
{
    s_Nodes.emplace_back(new Node(GetNextId(), "Dummy Receive Send Integer"));
    s_Nodes.back()->inputs.emplace_back(new BasePin(s_Nodes.back()->inputs.size(), GetNextId(), "Enter", PinType::Flow));
    s_Nodes.back()->inputs.emplace_back(new PinValue<int>(s_Nodes.back()->inputs.size(), GetNextId(), "Int Value", PinType::Int, 0));
    s_Nodes.back()->outputs.emplace_back(new BasePin(s_Nodes.back()->outputs.size(), GetNextId(), "Next", PinType::Flow));
    s_Nodes.back()->outputs.emplace_back(new PinValue<int>(s_Nodes.back()->outputs.size(), GetNextId(), "Int Value", PinType::Int, 0));

    s_Nodes.back()->node_funcs = std::make_shared<DummyRecvSendInt_Func>();
    std::dynamic_pointer_cast<DummyRecvSendInt_Func>(s_Nodes.back()->node_funcs)->parent_node = s_Nodes.back();

    s_Nodes.back()->node_funcs->Initialize();

    BuildNode(s_Nodes.back());

    return s_Nodes.back();
}





void DummiesSearchSetup(std::vector<SearchNodeObj>& search_nodes_vector)
{
    std::function<std::shared_ptr<Node>(std::vector<std::shared_ptr<Node>>&)> func_1 = DummyNode;
    std::vector<std::string> keywords_1{ "Dummy" };
    search_nodes_vector.push_back(SearchNodeObj("Dummy Node", keywords_1, func_1, false));

    std::function<std::shared_ptr<Node>(std::vector<std::shared_ptr<Node>>&)> func_2 = DummySendFloat;
    std::vector<std::string> keywords_2{ "Dummy", "Send", "Float" };
    search_nodes_vector.push_back(SearchNodeObj("Dummy Send Float", keywords_2, func_2));

    std::function<std::shared_ptr<Node>(std::vector<std::shared_ptr<Node>>&)> func_3 = DummyRecvSendFloat;
    std::vector<std::string> keywords_3{ "Dummy", "Send", "Receive", "Float" };
    search_nodes_vector.push_back(SearchNodeObj("Dummy Receive Send Float", keywords_3, func_3, false));

    std::function<std::shared_ptr<Node>(std::vector<std::shared_ptr<Node>>&)> func_4 = DummySendInt;
    std::vector<std::string> keywords_4{ "Dummy", "Send", "Int" };
    search_nodes_vector.push_back(SearchNodeObj("Dummy Send Int", keywords_4, func_4));

    std::function<std::shared_ptr<Node>(std::vector<std::shared_ptr<Node>>&)> func_5 = DummyRecvSendInt;
    std::vector<std::string> keywords_5{ "Dummy", "Send", "Receive", "Int" };
    search_nodes_vector.push_back(SearchNodeObj("Dummy Receive Send Int", keywords_5, func_5, false));
}