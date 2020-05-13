#pragma once
#ifndef UTILS_H
#define UTILS_H

#include <imgui.h>
#include <imgui_internal.h>
#include "project_classes.h"
#include "nodes_builder.h"
#include "objects/texture_object.h"
#include "objects/program_object.h"
#include "objects/shader_object.h"
#include "objects/mesh_object.h"
#include <memory>
#include <set>

std::shared_ptr<Node> FindNode(ed::NodeId id, std::vector<std::shared_ptr<Node>>& s_Nodes);
std::shared_ptr<Link> FindLink(ed::LinkId id, std::vector<std::shared_ptr<Link>>& s_Links);
std::shared_ptr<BasePin> FindPin(ed::PinId id, std::vector<std::shared_ptr<Node>>& s_Nodes);
bool IsPinLinked(ed::PinId id, std::vector<std::shared_ptr<Link>>& s_Links);
bool CanCreateLink(std::shared_ptr<BasePin>& a, std::shared_ptr<BasePin>& b);
void RunNextNodeFunc(std::shared_ptr<Node>& parent_node, std::string pin_key);
std::string PinTypeToString(PinType type);
PinType StringToPinType(std::string str);
std::vector<std::string> SortPins(std::map<std::string, std::shared_ptr<BasePin>> pins);
void AddInputPinsTab(std::shared_ptr<Node> node);
void UtilsChangePinType(std::shared_ptr<Node> parent_node, PinKind kind, std::string index, PinType type);

template<typename T>
T GetInputPinValue(std::shared_ptr<Node>& parent_node, std::string pin_key);

#endif