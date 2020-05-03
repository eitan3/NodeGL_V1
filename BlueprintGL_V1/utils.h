#pragma once
#ifndef UTILS_H
#define UTILS_H

#include "bp_structs.h"
#include "objects/texture_object.h"
#include "objects/program_object.h"
#include "objects/shader_object.h"
#include <memory>

std::shared_ptr<Node> FindNode(ed::NodeId id, std::vector<std::shared_ptr<Node>>& s_Nodes);
std::shared_ptr<Link> FindLink(ed::LinkId id, std::vector<std::shared_ptr<Link>>& s_Links);
std::shared_ptr<BasePin> FindPin(ed::PinId id, std::vector<std::shared_ptr<Node>>& s_Nodes);
bool IsPinLinked(ed::PinId id, std::vector<std::shared_ptr<Link>>& s_Links);
bool CanCreateLink(std::shared_ptr<BasePin>& a, std::shared_ptr<BasePin>& b);
void RunNextNodeFunc(std::shared_ptr<Node>& parent_node, int pin_index);
std::string PinTypeToString(PinType type);
PinType StringToPinType(std::string str);
void UtilsChangePinType(std::shared_ptr<Node> parent_node, PinKind kind, int index, PinType type);

template<typename T>
std::shared_ptr<PinValue<T>> GetLinkedInputPin(std::shared_ptr<Node>& parent_node, int pin_index);

template<typename T>
T GetInputPinValue(std::shared_ptr<Node>& parent_node, int pin_index);

#endif