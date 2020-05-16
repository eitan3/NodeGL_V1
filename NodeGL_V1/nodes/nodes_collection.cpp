#include "nodes_collection.h"

void CollectSearchNodes(std::vector<SearchNodeObj>& search_nodes_vector)
{
	GlNodes1_SearchSetup(search_nodes_vector);
	NodesUtilsSearchSetup(search_nodes_vector);
	ShadersNodesSearchSetup(search_nodes_vector);
	AnimNodesSearchSetup(search_nodes_vector);
	FlowNodesSearchSetup(search_nodes_vector);
	MathNodesSearchSetup(search_nodes_vector);
}

std::shared_ptr<Node> LoadNodeFromJSON(std::vector<std::shared_ptr<Node>>& s_Nodes, std::string node_key)
{
	std::shared_ptr<Node> loaded_node = nullptr;
	if (loaded_node == nullptr)
		loaded_node = AnimNodesLoadSetup(s_Nodes, node_key);
	if (loaded_node == nullptr)
		loaded_node = FlowNodesLoadSetup(s_Nodes, node_key);
	if (loaded_node == nullptr)
		loaded_node = GlNodes1_LoadSetup(s_Nodes, node_key);
	if (loaded_node == nullptr)
		loaded_node = MathNodesLoadSetup(s_Nodes, node_key);
	return loaded_node;
}
