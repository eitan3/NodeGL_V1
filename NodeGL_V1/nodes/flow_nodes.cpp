#include "flow_nodes.h"

void Sequence_Func::Initialize()
{

}

void Sequence_Func::Run(std::string called_pin)
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
                UtilsDeleteLinks(parent_node->outputs.at(id));
                parent_node->outputs.erase(id);
                BuildNode(parent_node);
            }
        }
        ImGui::EndHorizontal();
    }
}

void Sequence_Func::SaveNodeData(rapidjson::Writer<rapidjson::StringBuffer>& writer)
{
    writer.Key("num_outputs");
    writer.Uint(parent_node->outputs.size());
}

void Sequence_Func::LoadNodeData(rapidjson::Value& node_obj)
{
    int num_additional_nodes = node_obj["num_outputs"].GetUint();
    for (int i = 2; i < num_additional_nodes; i++)
    {
        std::string id = std::to_string(parent_node->outputs.size() + 1);
        parent_node->outputs.insert(std::pair<std::string, std::shared_ptr<BasePin>>(id, new BasePin(id, std::stoi(id), GetNextId(), ("Out " + id).c_str(), PinType::Flow)));
        BuildNode(parent_node);
    }
}

std::string sequenceNodeName = "Sequence";
std::shared_ptr<Node> SequenceNode(std::vector<std::shared_ptr<Node>>& s_Nodes)
{
    s_Nodes.emplace_back(new Node(GetNextId(), sequenceNodeName.c_str()));

    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<BasePin>>("enter", new BasePin("enter", 0, GetNextId(), "Enter", PinType::Flow)));
    s_Nodes.back()->outputs.insert(std::pair<std::string, std::shared_ptr<BasePin>>("1", new BasePin("1", 1, GetNextId(), "Out 1", PinType::Flow)));
    s_Nodes.back()->outputs.insert(std::pair<std::string, std::shared_ptr<BasePin>>("2", new BasePin("2", 2, GetNextId(), "Out 2", PinType::Flow)));

    s_Nodes.back()->node_funcs = std::make_shared<Sequence_Func>();
    std::dynamic_pointer_cast<Sequence_Func>(s_Nodes.back()->node_funcs)->parent_node = s_Nodes.back();

    s_Nodes.back()->node_funcs->Initialize();

    BuildNode(s_Nodes.back());

    return s_Nodes.back();
}






void Branch_Func::Run(std::string called_pin)
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

void Branch_Func::SaveNodeData(rapidjson::Writer<rapidjson::StringBuffer>& writer)
{
    writer.Key("condition");
    writer.Bool(std::dynamic_pointer_cast<PinValue<bool>>(parent_node->inputs.at("condition"))->default_value);
}

void Branch_Func::LoadNodeData(rapidjson::Value& node_obj)
{
    std::dynamic_pointer_cast<PinValue<bool>>(parent_node->inputs.at("condition"))->default_value = node_obj["condition"].GetBool();
}

std::string branchNodeName = "Branch";
std::shared_ptr<Node> BranchNode(std::vector<std::shared_ptr<Node>>& s_Nodes)
{
    s_Nodes.emplace_back(new Node(GetNextId(), branchNodeName.c_str()));

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






void WhileLoop_Func::Run(std::string called_pin)
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

void WhileLoop_Func::SaveNodeData(rapidjson::Writer<rapidjson::StringBuffer>& writer)
{
    writer.Key("condition");
    writer.Bool(std::dynamic_pointer_cast<PinValue<bool>>(parent_node->inputs.at("condition"))->default_value);
}

void WhileLoop_Func::LoadNodeData(rapidjson::Value& node_obj)
{
    std::dynamic_pointer_cast<PinValue<bool>>(parent_node->inputs.at("condition"))->default_value = node_obj["condition"].GetBool();
}

std::string whileLoopNodeName = "While Loop";
std::shared_ptr<Node> WhileLoopNode(std::vector<std::shared_ptr<Node>>& s_Nodes)
{
    s_Nodes.emplace_back(new Node(GetNextId(), whileLoopNodeName.c_str()));

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






void ForLoop_Func::Run(std::string called_pin)
{
    float start = GetInputPinValue<float>(parent_node, "start");
    float end = GetInputPinValue<float>(parent_node, "end");
    float inc = GetInputPinValue<float>(parent_node, "increase");
    std::shared_ptr<PinValue<float>> iter_pin = std::dynamic_pointer_cast<PinValue<float>>(parent_node->outputs.at("iter"));
    for (float i = start; i < end; i += inc)
    {
        if (iter_pin)
        {
            iter_pin->value = i;
        }
        RunNextNodeFunc(parent_node, "loop_body");
    }
    RunNextNodeFunc(parent_node, "complete");
}

void ForLoop_Func::Delete()
{
    parent_node = nullptr;
}

void ForLoop_Func::SaveNodeData(rapidjson::Writer<rapidjson::StringBuffer>& writer)
{
    writer.Key("start");
    writer.Double(std::dynamic_pointer_cast<PinValue<float>>(parent_node->inputs.at("start"))->default_value);
    writer.Key("end");
    writer.Double(std::dynamic_pointer_cast<PinValue<float>>(parent_node->inputs.at("end"))->default_value);
    writer.Key("increase");
    writer.Double(std::dynamic_pointer_cast<PinValue<float>>(parent_node->inputs.at("increase"))->default_value);
}

void ForLoop_Func::LoadNodeData(rapidjson::Value& node_obj)
{
    std::dynamic_pointer_cast<PinValue<float>>(parent_node->inputs.at("start"))->default_value = node_obj["start"].GetFloat();
    std::dynamic_pointer_cast<PinValue<float>>(parent_node->inputs.at("end"))->default_value = node_obj["end"].GetFloat();
    std::dynamic_pointer_cast<PinValue<float>>(parent_node->inputs.at("increase"))->default_value = node_obj["increase"].GetFloat();
}

std::string forLoopNodeName = "For Loop";
std::shared_ptr<Node> ForLoopNode(std::vector<std::shared_ptr<Node>>& s_Nodes)
{
    s_Nodes.emplace_back(new Node(GetNextId(), forLoopNodeName.c_str()));

    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<BasePin>>("enter", new BasePin("enter", 0, GetNextId(), "Enter", PinType::Flow)));
    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<PinValue<float>>>("start", new PinValue<float>("start", 1, GetNextId(), "Start Value", PinType::Float, 0)));
    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<PinValue<float>>>("end", new PinValue<float>("end", 2, GetNextId(), "End Value", PinType::Float, 1)));
    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<PinValue<float>>>("increase", new PinValue<float>("increase", 3, GetNextId(), "Increase By", PinType::Float, 1)));

    s_Nodes.back()->outputs.insert(std::pair<std::string, std::shared_ptr<BasePin>>("loop_body", new BasePin("loop_body", 0, GetNextId(), "Loop Body", PinType::Flow)));
    s_Nodes.back()->outputs.insert(std::pair<std::string, std::shared_ptr<BasePin>>("complete", new BasePin("complete", 1, GetNextId(), "Complete", PinType::Flow)));
    s_Nodes.back()->outputs.insert(std::pair<std::string, std::shared_ptr<PinValue<float>>>("iter", new PinValue<float>("iter", 2, GetNextId(), "Iterator Value", PinType::Float, 0)));

    s_Nodes.back()->node_funcs = std::make_shared<ForLoop_Func>();
    std::dynamic_pointer_cast<ForLoop_Func>(s_Nodes.back()->node_funcs)->parent_node = s_Nodes.back();

    s_Nodes.back()->node_funcs->Initialize();

    BuildNode(s_Nodes.back());

    return s_Nodes.back();
}






void RunEveryXSeconds_Func::Run(std::string called_pin)
{
    auto& io = ImGui::GetIO();
    float in_seconds = GetInputPinValue<float>(parent_node, "seconds");
    bool run_anim_end = false;

    if (prev_seconds != in_seconds || called_pin == "reset")
    {
        prev_seconds = in_seconds;
        timer = 0;
    }

    timer += io.DeltaTime;
    if (timer > in_seconds)
    {
        timer -= in_seconds;
        run_anim_end = true;
    }
    if (run_anim_end)
        RunNextNodeFunc(parent_node, "complete");
    RunNextNodeFunc(parent_node, "always");
}

void RunEveryXSeconds_Func::Delete()
{
    parent_node = nullptr;
}

void RunEveryXSeconds_Func::SaveNodeData(rapidjson::Writer<rapidjson::StringBuffer>& writer)
{
    writer.Key("seconds");
    writer.Double(std::dynamic_pointer_cast<PinValue<float>>(parent_node->inputs.at("seconds"))->default_value);
}

void RunEveryXSeconds_Func::LoadNodeData(rapidjson::Value& node_obj)
{
    std::dynamic_pointer_cast<PinValue<float>>(parent_node->inputs.at("seconds"))->default_value = node_obj["seconds"].GetFloat();
}

std::string runEveryXSecondsNodeName = "Run Every X Seconds";
std::shared_ptr<Node> RunEveryXSecondsNode(std::vector<std::shared_ptr<Node>>& s_Nodes)
{
    s_Nodes.emplace_back(new Node(GetNextId(), runEveryXSecondsNodeName.c_str()));

    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<BasePin>>("enter", new BasePin("enter", 0, GetNextId(), "Enter", PinType::Flow)));
    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<BasePin>>("reset", new BasePin("reset", 1, GetNextId(), "Reset", PinType::Flow)));
    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<PinValue<float>>>("seconds", new PinValue<float>("seconds", 2, GetNextId(), "Seconds", PinType::Float, 1)));
    
    s_Nodes.back()->outputs.insert(std::pair<std::string, std::shared_ptr<BasePin>>("complete", new BasePin("complete", 0, GetNextId(), "Every X Second", PinType::Flow)));
    s_Nodes.back()->outputs.insert(std::pair<std::string, std::shared_ptr<BasePin>>("always", new BasePin("always", 1, GetNextId(), "Always", PinType::Flow)));

    s_Nodes.back()->node_funcs = std::make_shared<RunEveryXSeconds_Func>();
    std::dynamic_pointer_cast<RunEveryXSeconds_Func>(s_Nodes.back()->node_funcs)->parent_node = s_Nodes.back();

    s_Nodes.back()->node_funcs->Initialize();

    BuildNode(s_Nodes.back());

    return s_Nodes.back();
}







void FlowNodesSearchSetup(std::vector<SearchNodeObj>& search_nodes_vector)
{
    std::function<std::shared_ptr<Node>(std::vector<std::shared_ptr<Node>>&)> func_1 = SequenceNode;
    std::vector<std::string> keywords_1{ "Flow", "Sequence" };
    search_nodes_vector.push_back(SearchNodeObj("Sequence", "Flow Nodes", keywords_1, func_1));

    std::function<std::shared_ptr<Node>(std::vector<std::shared_ptr<Node>>&)> func_2 = BranchNode;
    std::vector<std::string> keywords_2{ "Flow", "Branch", "If" };
    search_nodes_vector.push_back(SearchNodeObj("Branch", "Flow Nodes", keywords_2, func_2));

    std::function<std::shared_ptr<Node>(std::vector<std::shared_ptr<Node>>&)> func_3 = WhileLoopNode;
    std::vector<std::string> keywords_3{ "Flow", "While", "Loop" };
    search_nodes_vector.push_back(SearchNodeObj("While Loop", "Flow Nodes", keywords_3, func_3));

    std::function<std::shared_ptr<Node>(std::vector<std::shared_ptr<Node>>&)> func_4 = ForLoopNode;
    std::vector<std::string> keywords_4{ "Flow", "For", "Loop" };
    search_nodes_vector.push_back(SearchNodeObj("For Loop", "Flow Nodes", keywords_4, func_4));

    std::function<std::shared_ptr<Node>(std::vector<std::shared_ptr<Node>>&)> func_5 = RunEveryXSecondsNode;
    std::vector<std::string> keywords_5{ "Run", "Every", "Seconds" };
    search_nodes_vector.push_back(SearchNodeObj("Run Every X Seconds", "Flow Nodes", keywords_5, func_5));
}

std::shared_ptr<Node> FlowNodesLoadSetup(std::vector<std::shared_ptr<Node>>& s_Nodes, std::string node_key)
{
    std::shared_ptr<Node> loaded_node = nullptr;
    if (loaded_node == nullptr && node_key.rfind(sequenceNodeName, 0) == 0) {
        loaded_node = SequenceNode(s_Nodes);
    }
    else if (loaded_node == nullptr && node_key.rfind(branchNodeName, 0) == 0) {
        loaded_node = BranchNode(s_Nodes);
    }
    else if (loaded_node == nullptr && node_key.rfind(whileLoopNodeName, 0) == 0) {
        loaded_node = WhileLoopNode(s_Nodes);
    }
    else if (loaded_node == nullptr && node_key.rfind(forLoopNodeName, 0) == 0) {
        loaded_node = ForLoopNode(s_Nodes);
    }
    else if (loaded_node == nullptr && node_key.rfind(runEveryXSecondsNodeName, 0) == 0) {
        loaded_node = RunEveryXSecondsNode(s_Nodes);
    }
    return loaded_node;
}
