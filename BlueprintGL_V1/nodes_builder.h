#pragma once
#include "bp_structs.h"
#include "nodes_utils.h"
#include "id_generator.h"

void BuildNode(std::shared_ptr<Node>& node);

/*
Node* SpawnInputActionNode(std::vector<Node>& s_Nodes);
Node* SpawnBranchNode(std::vector<Node>& s_Nodes);
Node* SpawnDoNNode(std::vector<Node>& s_Nodes);
Node* SpawnOutputActionNode(std::vector<Node>& s_Nodes);
Node* SpawnPrintStringNode(std::vector<Node>& s_Nodes);
Node* SpawnMessageNode(std::vector<Node>& s_Nodes);
Node* SpawnSetTimerNode(std::vector<Node>& s_Nodes);
Node* SpawnLessNode(std::vector<Node>& s_Nodes);
Node* SpawnWeirdNode(std::vector<Node>& s_Nodes);
Node* SpawnTraceByChannelNode(std::vector<Node>& s_Nodes);
Node* SpawnComment(std::vector<Node>& s_Nodes);
*/

void BuildNodes(std::vector<std::shared_ptr<Node>>& s_Nodes);