#include "node_search_popup.h"
#ifndef IMGUI_DEFINE_MATH_OPERATORS
#define IMGUI_DEFINE_MATH_OPERATORS
#endif
#include <imgui_internal.h>

namespace imgui_addons
{
    NodeSearchPopup::NodeSearchPopup()
    {
        col_width = 280.0f;
        filter_dirty = true;
        close_window = true;
        current_node_int = -1;
        current_category_int = 0;
        current_category_str = "All";
    }

    NodeSearchPopup::~NodeSearchPopup()
    {
        filter_dirty = true;
        close_window = true;
        current_node_int = -1;
        current_category_int = 0;
        current_category_str = "All";
        filter.Clear();
        filter_nodes.clear();
        search_nodes_map.clear();
    }

    void NodeSearchPopup::BuildNodeMap(std::vector<SearchNodeObj>& search_nodes_vector)
    {
        search_nodes_map.insert(std::pair<std::string, std::vector<SearchNodeObj>>("All", std::vector<SearchNodeObj>()));
        for (int i = 0; i < search_nodes_vector.size(); i++)
        {
            if (search_nodes_map.count(search_nodes_vector.at(i).category) == 0)
            {
                std::vector<SearchNodeObj> tmp_vec;
                search_nodes_map.insert(std::pair<std::string, std::vector<SearchNodeObj>>(search_nodes_vector.at(i).category, tmp_vec));
            }
            search_nodes_map.at("All").push_back(search_nodes_vector.at(i));
            search_nodes_map.at(search_nodes_vector.at(i).category).push_back(search_nodes_vector.at(i));
        }
    }

    void NodeSearchPopup::closeDialog()
    {
        filter_dirty = true;
        close_window = true;
        current_node_int = -1;
        current_category_int = 0;
        current_category_str = "All";
        filter.Clear();
        filter_nodes.clear();
        ImGui::CloseCurrentPopup();
    }

    bool NodeSearchPopup::showSearchDialog(const std::string& label, const ImVec2& sz_xy)
    {
        ImGuiIO& io = ImGui::GetIO();
        max_size.x = io.DisplaySize.x;
        max_size.y = io.DisplaySize.y;
        ImGui::SetNextWindowSizeConstraints(min_size, max_size);
        ImVec2 center = ImVec2(io.DisplaySize.x * 0.5f, io.DisplaySize.y * 0.5f);
        ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
        ImGui::SetNextWindowSize(ImVec2(std::max(sz_xy.x, min_size.x), std::max(sz_xy.y, min_size.y)), ImGuiCond_Appearing);
        if (ImGui::BeginPopupModal(label.c_str(), nullptr, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse))
        {
            if (close_window)
            {
                close_window = false;
                selected_node_obj = SearchNodeObj("Not Selected", "Not Selected", std::vector<std::string>(), nullptr);
            }

            bool press_select = false;
            press_select = renderSelectedAndSearchBarRegion();
            renderCategoriesList();
            ImGui::SameLine();
            press_select = renderNodesListRegion();

            if (ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_Escape)))
            {
                closeDialog();
            }

            if (selected_node_obj.category == "Not Selected" || selected_node_obj.title == "Not Selected")
                press_select = false;
            ImGui::EndPopup();
            return press_select;
        }
        else
        {
            return false;
        }
    }

    bool NodeSearchPopup::renderSelectedAndSearchBarRegion()
    {
        ImGuiStyle& style = ImGui::GetStyle();
        bool show_error = false;
        float frame_height = ImGui::GetFrameHeight();

        ImVec2 pw_content_size = ImGui::GetWindowSize() - style.WindowPadding * 2.0;
        ImVec2 sw_size = ImVec2(ImGui::CalcTextSize("Random").x + 200, style.WindowPadding.y * 2.0 + frame_height);
        ImVec2 sw_content_size = sw_size - style.WindowPadding * 2.0;
        ImVec2 nw_size = ImVec2(pw_content_size.x - style.ItemSpacing.x - sw_size.x, sw_size.y);


        ImGui::BeginChild("##NavigationWindow", nw_size, true, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoScrollbar);

        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.882f, 0.745f, 0.078f, 1.0f));
        
        std::string window_title = "Select Node";
        if (selected_node_obj.category != "Not Selected" && selected_node_obj.title != "Not Selected")
            window_title = "Category: " + selected_node_obj.category + ", Node: " + selected_node_obj.title;
        ImGui::TextUnformatted(window_title.c_str());

        ImGui::PopStyleColor();
        ImGui::EndChild();

        ImGui::SameLine();
        ImGui::BeginChild("##SearchWindow", sw_size, true, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoScrollbar);

        bool press_select = false;
        if (ImGui::Button("Select"))
        {
            press_select = true;
            closeDialog();
        }
        ImGui::SameLine();
        if (ImGui::Button("Cancel"))
        {
            closeDialog();
        }

        //Render Search/Filter bar
        ImGui::SameLine();
        float marker_width = ImGui::CalcTextSize("(?)").x + style.ItemSpacing.x;
        if (filter.Draw("##SearchBar", sw_content_size.x - marker_width) || filter_dirty)
        {
            filter_dirty = false;
            filterNodes();
        }

        //If filter bar was focused clear selection
        if (ImGui::GetFocusID() == ImGui::GetID("##SearchBar"))
            current_node_int = -1;

        ImGui::EndChild();
        return press_select;
    }

    void NodeSearchPopup::renderCategoriesList()
    {
        ImGuiStyle& style = ImGui::GetStyle();
        bool show_error = false;

        float frame_height = ImGui::GetWindowHeight() - ImGui::GetCursorPosY();
        ImVec2 cat_size = ImVec2(150, frame_height - style.WindowPadding.y * 2.0);

        ImGui::BeginChild("##categoriesWindow", cat_size, true, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoScrollbar);

        std::vector<std::string> vs;
        for (std::map<std::string, std::vector<SearchNodeObj>>::iterator it = search_nodes_map.begin(); it != search_nodes_map.end(); ++it) {
            vs.push_back(it->first);
        }
        std::string prev_current_category_str = current_category_str;
        ListBox("##categoriesList", &current_category_int, vs, 12 );
        current_category_str = vs.at(current_category_int);
        if (current_category_str != prev_current_category_str)
        {
            current_node_int = -1;
            filterNodes();
        }

        ImGui::EndChild();
    }

    bool NodeSearchPopup::renderNodesListRegion()
    {
        ImGuiStyle& style = ImGui::GetStyle();
        ImVec2 pw_size = ImGui::GetWindowSize();
        float list_item_height = ImGui::CalcTextSize("").y + style.ItemSpacing.y;

        bool press_select = false;
        float frame_height = ImGui::GetWindowHeight() - ImGui::GetCursorPosY();
        float window_content_height = frame_height - style.WindowPadding.y * 2.0;
        float min_content_size = pw_size.x - 150 - style.WindowPadding.x * 4.0f;

        //Reinitialize the limit on number of selectables in one column based on height
        col_items_limit = std::max(1.0f, window_content_height / list_item_height);
        int num_cols = std::max(1.0f, std::ceil(static_cast<float>(filter_nodes.size()) / col_items_limit));

        //Limitation by ImGUI in 1.75. If columns are greater than 64 readjust the limit on items per column and recalculate number of columns
        if (num_cols > 64)
        {
            int exceed_items_amount = (num_cols - 64) * col_items_limit;
            col_items_limit += std::ceil(exceed_items_amount / 64.0);
            num_cols = std::max(1.0f, std::ceil(static_cast<float>(filter_nodes.size()) / col_items_limit));
        }

        float content_width = num_cols * col_width;
        if (content_width < min_content_size)
            content_width = 0;

        ImGui::SetNextWindowContentSize(ImVec2(content_width, 0));
        ImGui::BeginChild("##ScrollingRegion", ImVec2(0, frame_height), true, ImGuiWindowFlags_HorizontalScrollbar);
        ImGui::Columns(num_cols);

        int items = 0;
        for (int i = 0; i < filter_nodes.size(); i++)
        {
            items++;
            if (ImGui::Selectable(filter_nodes.at(i).title.c_str(), current_node_int == i, ImGuiSelectableFlags_SelectOnClick))
            {
                current_node_int = i;
                selected_node_obj = filter_nodes.at(i);
                if (ImGui::IsMouseDoubleClicked(0))
                {
                    press_select = true;
                    closeDialog();
                }
            }
            if ((items) % col_items_limit == 0)
                ImGui::NextColumn();
        }

        ImGui::Columns(1);
        ImGui::EndChild();
        return press_select;
    }

    void NodeSearchPopup::filterNodes()
    {
        filter_nodes.clear();
        for (size_t i = 0; i < search_nodes_map.at(current_category_str).size(); i++)
        {
            if (filter.PassFilter(search_nodes_map.at(current_category_str).at(i).title.c_str()))
                filter_nodes.push_back(search_nodes_map.at(current_category_str).at(i));
        }
    }







    bool Combo(const char* label, int* currIndex, std::vector<std::string>& values)
    {
        if (values.empty()) { return false; }
        return ImGui::Combo(label, currIndex, vector_getter, static_cast<void*>(&values), values.size());
    }

    bool ListBox(const char* label, int* currIndex, std::vector<std::string>& values, int height)
    {
        if (values.empty()) { return false; }
        return ImGui::ListBox(label, currIndex, vector_getter, static_cast<void*>(&values), values.size(), height);
    }

}