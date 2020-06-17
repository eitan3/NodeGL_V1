#pragma once
#ifndef NODE_SEARCH_POPUP_H
#define NODE_SEARCH_POPUP_H

#include <imgui.h>
#include <string>
#include <vector>
#include <map>
#include "../project_classes.h"


namespace imgui_addons
{

	static auto vector_getter = [](void* vec, int idx, const char** out_text)
	{
		auto& vector = *static_cast<std::vector<std::string>*>(vec);
		if (idx < 0 || idx >= static_cast<int>(vector.size())) { return false; }
		*out_text = vector.at(idx).c_str();
		return true;
	};

	bool Combo(const char* label, int* currIndex, std::vector<std::string>& values);

	bool ListBox(const char* label, int* currIndex, std::vector<std::string>& values, int height);

	class NodeSearchPopup
	{
	public:
		NodeSearchPopup();
		~NodeSearchPopup();

		void BuildNodeMap(std::vector<SearchNodeObj>& search_nodes_vector);

		bool showSearchDialog(const std::string& label, const ImVec2& sz_xy = ImVec2(0, 0));

		bool close_window;
		SearchNodeObj selected_node_obj = SearchNodeObj("Not Selected", "Not Selected", std::vector<std::string>(), nullptr);

	private:
		void closeDialog();
		
		bool renderSelectedAndSearchBarRegion();
		void renderCategoriesList();
		bool renderNodesListRegion();

		void filterNodes();

		std::map<std::string, std::vector<SearchNodeObj>> search_nodes_map;
		std::vector<SearchNodeObj> filter_nodes;

		ImVec2 min_size, max_size;
		ImGuiTextFilter filter;
		bool filter_dirty;
		int current_node_int;
		int current_category_int;
		std::string current_category_str;

		float col_width;
		int col_items_limit;
	};
}


#endif