#pragma once
#include <imgui_node_editor.h>

namespace ed = ax::NodeEditor;

static int s_NextId = 1;
int GetNextId();
ed::LinkId GetNextLinkId();