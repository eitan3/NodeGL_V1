#pragma once
#ifndef NODES_COLLECTION_H
#define NODES_COLLECTION_H

#include <rapidjson/document.h>
#include "gl_nodes_1.h"
#include "utils_nodes.h"
#include "shaders_nodes.h"
#include "flow_nodes.h"
#include "relational_logical_nodes.h"
#include "math_nodes.h"
#include "animations_nodes_1.h"
#include "vec3_nodes.h"
#include "vec4_nodes.h"
#include "matrices_nodes.h";

void CollectSearchNodes(std::vector<SearchNodeObj>& search_nodes_vector);

std::shared_ptr<Node> LoadNodeFromJSON(std::vector<std::shared_ptr<Node>>& s_Nodes, std::string node_key);

#endif