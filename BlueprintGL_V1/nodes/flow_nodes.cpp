#include "flow_nodes.h"

void Sequence_Func::Initialize()
{

}

void Sequence_Func::Run()
{
    for (auto& output : parent_node->outputs)
    {
        RunNextNodeFunc(parent_node, output.first);
    }
}

void Sequence_Func::Delete()
{
    parent_node = nullptr;
}

void Sequence_Func::UpdateNodeInspector()
{
    if (ImGui::BeginTabItem("Sequence Configs"))
    {
        auto paneWidth = ImGui::GetContentRegionAvailWidth();
        ImGui::BeginHorizontal("##sequence_config_panel_1", ImVec2(paneWidth, 0), 1.0f);
        if (ImGui::Button("Add Output"))
        {
            std::string id = std::to_string(parent_node->outputs.size() + 1);
            parent_node->outputs.insert(std::pair<std::string, std::shared_ptr<BasePin>>(id, new BasePin(id, std::stoi(id), GetNextId(), ("Out " + id).c_str(), PinType::Flow)));
            BuildNode(parent_node);
        }
        if (parent_node->outputs.size() > 2)
        {
            if (ImGui::Button("Delete Output"))
            {
                std::string id = std::to_string(parent_node->outputs.size());
                for (int li = 0; li < parent_node->outputs.at(id)->links.size(); li++)
                {
                    ed::DeleteLink(parent_node->outputs.at(id)->links.at(li)->id);
                }
                parent_node->outputs.erase(id);
                BuildNode(parent_node);
            }
        }
        ImGui::EndHorizontal();
    }
}

std::shared_ptr<Node> SequenceNode(std::vector<std::shared_ptr<Node>>& s_Nodes)
{
    s_Nodes.emplace_back(new Node(GetNextId(), "Sequence"));

    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<BasePin>>("enter", new BasePin("enter", 0, GetNextId(), "Enter", PinType::Flow)));
    s_Nodes.back()->outputs.insert(std::pair<std::string, std::shared_ptr<BasePin>>("1", new BasePin("1", 1, GetNextId(), "Out 1", PinType::Flow)));
    s_Nodes.back()->outputs.insert(std::pair<std::string, std::shared_ptr<BasePin>>("2", new BasePin("2", 2, GetNextId(), "Out 2", PinType::Flow)));

    s_Nodes.back()->node_funcs = std::make_shared<Sequence_Func>();
    std::dynamic_pointer_cast<Sequence_Func>(s_Nodes.back()->node_funcs)->parent_node = s_Nodes.back();

    s_Nodes.back()->node_funcs->Initialize();

    BuildNode(s_Nodes.back());

    return s_Nodes.back();
}






void Branch_Func::Run()
{
    bool condition = GetInputPinValue<bool>(parent_node, "condition");
    if (condition)
    {
        RunNextNodeFunc(parent_node, "true");
    }
    else
    {
        RunNextNodeFunc(parent_node, "false");
    }
}

void Branch_Func::Delete()
{
    parent_node = nullptr;
}

std::shared_ptr<Node> BranchNode(std::vector<std::shared_ptr<Node>>& s_Nodes)
{
    s_Nodes.emplace_back(new Node(GetNextId(), "Branch"));

    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<BasePin>>("enter", new BasePin("enter", 0, GetNextId(), "Enter", PinType::Flow)));
    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<PinValue<bool>>>("condition", new PinValue<bool>("condition", 1, GetNextId(), "Condition", PinType::Bool, false)));
    s_Nodes.back()->outputs.insert(std::pair<std::string, std::shared_ptr<BasePin>>("true", new BasePin("true", 0, GetNextId(), "True", PinType::Flow)));
    s_Nodes.back()->outputs.insert(std::pair<std::string, std::shared_ptr<BasePin>>("false", new BasePin("false", 1, GetNextId(), "False", PinType::Flow)));

    s_Nodes.back()->node_funcs = std::make_shared<Branch_Func>();
    std::dynamic_pointer_cast<Branch_Func>(s_Nodes.back()->node_funcs)->parent_node = s_Nodes.back();

    s_Nodes.back()->node_funcs->Initialize();

    BuildNode(s_Nodes.back());

    return s_Nodes.back();
}






void WhileLoop_Func::Run()
{
    bool condition = GetInputPinValue<bool>(parent_node, "condition");
    while (condition)
    {
        RunNextNodeFunc(parent_node, "loop_body");
    }
    RunNextNodeFunc(parent_node, "complete");
}

void WhileLoop_Func::Delete()
{
    parent_node = nullptr;
}

std::shared_ptr<Node> WhileLoopNode(std::vector<std::shared_ptr<Node>>& s_Nodes)
{
    s_Nodes.emplace_back(new Node(GetNextId(), "While Loop"));

    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<BasePin>>("enter", new BasePin("enter", 0, GetNextId(), "Enter", PinType::Flow)));
    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<PinValue<bool>>>("condition", new PinValue<bool>("condition", 1, GetNextId(), "Condition", PinType::Bool, false)));
    s_Nodes.back()->outputs.insert(std::pair<std::string, std::shared_ptr<BasePin>>("loop_body", new BasePin("loop_body", 0, GetNextId(), "Loop Body", PinType::Flow)));
    s_Nodes.back()->outputs.insert(std::pair<std::string, std::shared_ptr<BasePin>>("complete", new BasePin("complete", 1, GetNextId(), "Complete", PinType::Flow)));

    s_Nodes.back()->node_funcs = std::make_shared<WhileLoop_Func>();
    std::dynamic_pointer_cast<WhileLoop_Func>(s_Nodes.back()->node_funcs)->parent_node = s_Nodes.back();

    s_Nodes.back()->node_funcs->Initialize();

    BuildNode(s_Nodes.back());

    return s_Nodes.back();
}







void FlowNodesSearchSetup(std::vector<SearchNodeObj>& search_nodes_vector)
{
    std::function<std::shared_ptr<Node>(std::vector<std::shared_ptr<Node>>&)> func_1 = SequenceNode;
    std::vector<std::string> keywords_1{ "Flow", "Sequence" };
    search_nodes_vector.push_back(SearchNodeObj("Sequence", keywords_1, func_1));

    std::function<std::shared_ptr<Node>(std::vector<std::shared_ptr<Node>>&)> func_2 = BranchNode;
    std::vector<std::string> keywords_2{ "Flow", "Branch", "If" };
    search_nodes_vector.push_back(SearchNodeObj("Branch", keywords_2, func_2));

    std::function<std::shared_ptr<Node>(std::vector<std::shared_ptr<Node>>&)> func_3 = WhileLoopNode;
    std::vector<std::string> keywords_3{ "Flow", "While", "Loop" };
    search_nodes_vector.push_back(SearchNodeObj("While Loop", keywords_3, func_3));
}
