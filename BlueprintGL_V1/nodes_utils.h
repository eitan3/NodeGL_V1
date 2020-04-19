#pragma once
#include "bp_structs.h"
#include <memory>

std::shared_ptr<Node> FindNode(ed::NodeId id, std::vector<std::shared_ptr<Node>>& s_Nodes);
std::shared_ptr<Link> FindLink(ed::LinkId id, std::vector<std::shared_ptr<Link>>& s_Links);
std::shared_ptr<Pin> FindPin(ed::PinId id, std::vector<std::shared_ptr<Node>>& s_Nodes);
bool IsPinLinked(ed::PinId id, std::vector<std::shared_ptr<Link>>& s_Links);
bool CanCreateLink(std::shared_ptr<Pin> a, std::shared_ptr<Pin> b);