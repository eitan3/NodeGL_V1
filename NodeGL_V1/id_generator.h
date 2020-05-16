#pragma once
#include <imgui_node_editor.h>
#ifndef ID_GENERATOR_H
#define ID_GENERATOR_H

namespace ed = ax::NodeEditor;

static int s_NextId = 1;
int GetNextId();
ed::LinkId GetNextLinkId();
void ResetId();

#endif