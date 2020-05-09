#pragma once
#ifndef DUMMY_NODES_H
#define DUMMY_NODES_H

#include "node_function_interface.h"
#include "../nodes_builder.h"
#include "../utils.h"

class DummyNode_Func : public NodeFunctions {
public:
    void Initialize() {};
    void Run();
    void Delete();
    void NoFlowUpdatePinsValues() {};
    void PressButton(PinKind, std::string pin_key) {};
    void UpdateUI() {};
};

std::shared_ptr<Node> DummyNode(std::vector<std::shared_ptr<Node>>& s_Nodes);



class DummySendFloat_Func : public NodeFunctions {
public:
    void Initialize();
    void Run();
    void Delete();
    void NoFlowUpdatePinsValues();
    void PressButton(PinKind, std::string pin_key);
    void UpdateUI() {};
};

std::shared_ptr<Node> DummySendFloat(std::vector<std::shared_ptr<Node>>& s_Nodes);



class DummyRecvSendFloat_Func : public NodeFunctions {
public:
    void Initialize();
    void Run();
    void Delete();
    void NoFlowUpdatePinsValues();
    void PressButton(PinKind, std::string pin_key);
    void UpdateUI() {};
};

std::shared_ptr<Node> DummyRecvSendFloat(std::vector<std::shared_ptr<Node>>& s_Nodes);



class DummySendInt_Func : public NodeFunctions {
public:
    void Initialize();
    void Run();
    void Delete();
    void NoFlowUpdatePinsValues();
    void PressButton(PinKind, std::string pin_key);
    void UpdateUI() {};
};

std::shared_ptr<Node> DummySendInt(std::vector<std::shared_ptr<Node>>& s_Nodes);



class DummyRecvSendInt_Func : public NodeFunctions {
public:
    void Initialize();
    void Run();
    void Delete();
    void NoFlowUpdatePinsValues();
    void PressButton(PinKind, std::string pin_key);
    void UpdateUI() {};
};

std::shared_ptr<Node> DummyRecvSendInt(std::vector<std::shared_ptr<Node>>& s_Nodes);


void DummiesSearchSetup(std::vector<SearchNodeObj>& search_nodes_vector);

#endif