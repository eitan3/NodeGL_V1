#include "animations_nodes_1.h"


const char* ease_items[] = { "Linear", "Ease In Sine", "Ease Out Sine", "Ease In Out Sine", "Ease In Quad", "Ease Out Quad", "Ease In Out Quad",
        "Ease In Cubic", "Ease Out Cubic", "Ease In Out Cubic", "Ease In Quart", "Ease Out Quart", "Ease In Out Quart" };
void EaseAnimation_Func::Initialize()
{
    anim_time = 0;
    is_reverse = false;
    if (current_ease == NULL)
        current_ease = (char*)ease_items[0];
}

float linearFunc(float x)
{
    return x;
}

float easeInSine(float x){
    return 1 - cos((x * M_PI) / 2);
}

float easeOutSine(float x){
    return sin((x * M_PI) / 2);
}

float easeInOutSine(float x){
    return -(cos(M_PI * x) - 1) / 2;
}

float easeInQuad(float x){
    return x * x;
}

float easeOutQuad(float x){
    return 1 - (1 - x) * (1 - x);
}

float easeInOutQuad(float x){
    return x < 0.5 ? 2 * x * x : 1 - pow(-2 * x + 2, 2) / 2;
}

float easeInCubic(float x){
    return x * x * x;
}

float easeOutCubic(float x){
    return 1 - pow(1 - x, 3);
}

float easeInOutCubic(float x){
    return x < 0.5 ? 4 * x * x * x : 1 - pow(-2 * x + 2, 3) / 2;
}

float easeInQuart(float x){
    return x * x * x * x;
}

float easeOutQuart(float x){
    return 1 - pow(1 - x, 4);
}

float easeInOutQuart(float x){
    return x < 0.5 ? 8 * x * x * x * x : 1 - pow(-2 * x + 2, 4) / 2;
}

void EaseAnimation_Func::Run()
{
    auto& io = ImGui::GetIO();
    float new_min_val = GetInputPinValue<float>(parent_node, "min");
    float new_max_val = GetInputPinValue<float>(parent_node, "max");
    float new_duration_val = GetInputPinValue<float>(parent_node, "duration");
    bool reverse_val = GetInputPinValue<bool>(parent_node, "reverse");
    bool start_random_val = GetInputPinValue<bool>(parent_node, "start_random");

    if (new_min_val != min_val || new_max_val != max_val || new_duration_val != duration_val || reverse != reverse_val || start_random != start_random_val)
    {
        min_val = new_min_val;
        max_val = new_max_val;
        duration_val = new_duration_val;
        reverse = reverse_val;
        start_random = start_random_val;
        if (start_random)
        {
            std::random_device rd;  //Will be used to obtain a seed for the random number engine
            std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
            std::uniform_real_distribution<> dis(0.0, 1.0);
            float rand_start = dis(gen);
            anim_time = rand_start * new_duration_val;
            if (dis(gen) > 0.5)
                is_reverse = true;
            else
                is_reverse = false;
        }
        else
        {
            anim_time = 0;
            is_reverse = false;
        }
    }

    bool run_anim_end = false;
    if (reverse_val == false)
    {
        anim_time += io.DeltaTime;
        if (anim_time > new_duration_val)
        {
            anim_time -= new_duration_val;
            run_anim_end = true;
        }
    }
    else
    {
        if (is_reverse == false)
        {
            anim_time += io.DeltaTime;
            if (anim_time > new_duration_val)
            {
                is_reverse = true;
                run_anim_end = true;
            }
        }
        else
        {
            anim_time -= io.DeltaTime;
            if (anim_time < 0.0)
            {
                is_reverse = false;
                run_anim_end = true;
            }
        }
    }
    float norm_anim_time = anim_time / new_duration_val;
    float computed_ease = 0;

    if (current_ease == "Linear")
        computed_ease = linearFunc(norm_anim_time);
    else if (current_ease == "Ease In Sine")
        computed_ease = easeInSine(norm_anim_time);
    else if (current_ease == "Ease Out Sine")
        computed_ease = easeOutSine(norm_anim_time);
    else if (current_ease == "Ease In Out Sine")
        computed_ease = easeInOutSine(norm_anim_time);
    else if (current_ease == "Ease In Quad")
        computed_ease = easeInQuad(norm_anim_time);
    else if (current_ease == "Ease Out Quad")
        computed_ease = easeOutQuad(norm_anim_time);
    else if (current_ease == "Ease In Out Quad")
        computed_ease = easeInOutQuad(norm_anim_time);
    else if (current_ease == "Ease In Cubic")
        computed_ease = easeInCubic(norm_anim_time);
    else if (current_ease == "Ease Out Cubic")
        computed_ease = easeOutCubic(norm_anim_time);
    else if (current_ease == "Ease In Out Cubic")
        computed_ease = easeInOutCubic(norm_anim_time);
    else if (current_ease == "Ease In Quart")
        computed_ease = easeInQuart(norm_anim_time);
    else if (current_ease == "Ease Out Quart")
        computed_ease = easeOutQuart(norm_anim_time);
    else if (current_ease == "Ease In Out Quart")
        computed_ease = easeInOutQuart(norm_anim_time);

    std::shared_ptr<PinValue<float>> output_pin = std::dynamic_pointer_cast<PinValue<float>>(parent_node->outputs.at("value"));
    output_pin->value = computed_ease * (max_val - min_val) + min_val;
    
    if (run_anim_end)
        RunNextNodeFunc(parent_node, "animation_end");
    RunNextNodeFunc(parent_node, "next");
}

void EaseAnimation_Func::Delete()
{
    parent_node = nullptr;
}

void EaseAnimation_Func::UpdateNodeInspector()
{
    if (ImGui::BeginTabItem("Animation Settings"))
    {
        if (current_ease == NULL)
            current_ease = (char *)ease_items[0];

        auto paneWidth = ImGui::GetContentRegionAvailWidth();
        ImGui::TextUnformatted("Ease Type: ");
        ImGui::BeginHorizontal("##ease_anim_config_panel_1", ImVec2(paneWidth, 0), 1.0f);
        if (ImGui::BeginCombo("##combo", current_ease)) // The second parameter is the label previewed before opening the combo.
        {
            for (int n = 0; n < IM_ARRAYSIZE(ease_items); n++)
            {
                bool is_selected = std::string(current_ease) == std::string(ease_items[n]); // You can store your selection however you want, outside or inside your objects
                if (ImGui::Selectable(ease_items[n], is_selected))
                    current_ease = (char*)ease_items[n];
                    if (is_selected)
                        ImGui::SetItemDefaultFocus();   // You may set the initial focus when opening the combo (scrolling + for keyboard navigation support)
            }
            ImGui::EndCombo();
        }
        ImGui::EndHorizontal();
    }
}

void EaseAnimation_Func::SaveNodeData(rapidjson::Writer<rapidjson::StringBuffer>& writer)
{
    writer.Key("min");
    writer.Double(std::dynamic_pointer_cast<PinValue<float>>(parent_node->inputs.at("min"))->default_value);
    writer.Key("max");
    writer.Double(std::dynamic_pointer_cast<PinValue<float>>(parent_node->inputs.at("max"))->default_value);
    writer.Key("duration");
    writer.Double(std::dynamic_pointer_cast<PinValue<float>>(parent_node->inputs.at("duration"))->default_value);
    writer.Key("reverse");
    writer.Bool(std::dynamic_pointer_cast<PinValue<bool>>(parent_node->inputs.at("reverse"))->default_value);
    writer.Key("start_random");
    writer.Bool(std::dynamic_pointer_cast<PinValue<bool>>(parent_node->inputs.at("start_random"))->default_value);
    writer.Key("ease");
    writer.String(current_ease);
    //std::dynamic_pointer_cast<PinValue<std::string>>(parent_node->inputs.at(""))->default_value;
}

void EaseAnimation_Func::LoadNodeData(rapidjson::Value& node_obj)
{
    std::dynamic_pointer_cast<PinValue<float>>(parent_node->inputs.at("min"))->default_value = node_obj["min"].GetFloat();
    std::dynamic_pointer_cast<PinValue<float>>(parent_node->inputs.at("max"))->default_value = node_obj["max"].GetFloat();
    std::dynamic_pointer_cast<PinValue<float>>(parent_node->inputs.at("duration"))->default_value = node_obj["duration"].GetFloat();
    std::dynamic_pointer_cast<PinValue<bool>>(parent_node->inputs.at("reverse"))->default_value = node_obj["reverse"].GetBool();
    std::dynamic_pointer_cast<PinValue<bool>>(parent_node->inputs.at("start_random"))->default_value = node_obj["start_random"].GetBool();
    current_ease = (char *)node_obj["ease"].GetString();
    bool is_found = false;
    int index = 0;
    for (int n = 0; n < IM_ARRAYSIZE(ease_items) && is_found == false; n++)
    {
        is_found = std::string(current_ease) == std::string(ease_items[n]);
        index = n;
    }
    if (is_found)
        current_ease = (char*)ease_items[index];
    else
        current_ease = (char*)ease_items[0];
}

std::string easeAnimationhNodeName = "Ease Animation";
std::shared_ptr<Node> EaseAnimationhNode(std::vector<std::shared_ptr<Node>>& s_Nodes)
{
    s_Nodes.emplace_back(new Node(GetNextId(), easeAnimationhNodeName.c_str()));

    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<BasePin>>("enter", new BasePin("enter", 0, GetNextId(), "Enter", PinType::Flow)));
    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<PinValue<float>>>("min", new PinValue<float>("min", 1, GetNextId(), "Min", PinType::Float, 0)));
    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<PinValue<float>>>("max", new PinValue<float>("max", 2, GetNextId(), "Max", PinType::Float, 1)));
    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<PinValue<float>>>("duration", new PinValue<float>("duration", 3, GetNextId(), "Duration", PinType::Float, 1)));
    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<PinValue<bool>>>("reverse", new PinValue<bool>("reverse", 4, GetNextId(), "Reverse", PinType::Bool, true)));
    s_Nodes.back()->inputs.at("reverse")->always_expose = false;
    s_Nodes.back()->inputs.at("reverse")->exposed = false;
    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<PinValue<bool>>>("start_random", new PinValue<bool>("start_random", 5, GetNextId(), "Start Random", PinType::Bool, true)));
    s_Nodes.back()->inputs.at("start_random")->always_expose = false;
    s_Nodes.back()->inputs.at("start_random")->exposed = false;

    s_Nodes.back()->outputs.insert(std::pair<std::string, std::shared_ptr<BasePin>>("next", new BasePin("next", 0, GetNextId(), "next", PinType::Flow)));
    s_Nodes.back()->outputs.insert(std::pair<std::string, std::shared_ptr<BasePin>>("animation_end", new BasePin("animation_end", 1, GetNextId(), "Animation End", PinType::Flow)));
    s_Nodes.back()->outputs.insert(std::pair<std::string, std::shared_ptr<PinValue<float>>>("value", new PinValue<float>("value", 2, GetNextId(), "Animation Value", PinType::Float, 0)));

    s_Nodes.back()->node_funcs = std::make_shared<EaseAnimation_Func>();
    std::dynamic_pointer_cast<EaseAnimation_Func>(s_Nodes.back()->node_funcs)->parent_node = s_Nodes.back();

    s_Nodes.back()->node_funcs->Initialize();

    BuildNode(s_Nodes.back());

    return s_Nodes.back();
}







void AnimNodesSearchSetup(std::vector<SearchNodeObj>& search_nodes_vector)
{
    std::function<std::shared_ptr<Node>(std::vector<std::shared_ptr<Node>>&)> func_1 = EaseAnimationhNode;
    std::vector<std::string> keywords_1{ "Ease", "Animation" };
    search_nodes_vector.push_back(SearchNodeObj("Ease Animation", "Animations", keywords_1, func_1, true));
}

std::shared_ptr<Node> AnimNodesLoadSetup(std::vector<std::shared_ptr<Node>>& s_Nodes, std::string node_key)
{
    std::shared_ptr<Node> loaded_node = nullptr;
    if (loaded_node == nullptr && node_key.rfind(easeAnimationhNodeName, 0) == 0) {
        loaded_node = EaseAnimationhNode(s_Nodes);
    }
    return loaded_node;
}
