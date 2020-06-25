#include "nodes_collection.h"

void CollectSearchNodes(std::vector<SearchNodeObj>& search_nodes_vector)
{
	FlowNodesSearchSetup(search_nodes_vector);
	NodesUtilsSearchSetup(search_nodes_vector);
	ArraysNodesSearchSetup(search_nodes_vector);
	GlNodes1_SearchSetup(search_nodes_vector);
	ShadersNodesSearchSetup(search_nodes_vector);
	AnimNodesSearchSetup(search_nodes_vector);
	RelLogNodesSearchSetup(search_nodes_vector);
	MathNodesSearchSetup(search_nodes_vector);
	Vec2NodesSearchSetup(search_nodes_vector);
	Vec3NodesSearchSetup(search_nodes_vector);
	Vec4NodesSearchSetup(search_nodes_vector);
	MatricesNodes_SearchSetup(search_nodes_vector);
	MeshesNodesSearchSetup(search_nodes_vector);
	ResourcesNodesSearchSetup(search_nodes_vector);
}

std::shared_ptr<Node> LoadNodeFromJSON(std::vector<std::shared_ptr<Node>>& s_Nodes, std::string node_key)
{
	std::shared_ptr<Node> loaded_node = nullptr;
	if (loaded_node == nullptr)
		loaded_node = AnimNodesLoadSetup(s_Nodes, node_key);
	if (loaded_node == nullptr)
		loaded_node = FlowNodesLoadSetup(s_Nodes, node_key);
	if (loaded_node == nullptr)
		loaded_node = RelLogNodesLoadSetup(s_Nodes, node_key);
	if (loaded_node == nullptr)
		loaded_node = GlNodes1_LoadSetup(s_Nodes, node_key);
	if (loaded_node == nullptr)
		loaded_node = MathNodesLoadSetup(s_Nodes, node_key);
	if (loaded_node == nullptr)
		loaded_node = ShadersNodesLoadSetup(s_Nodes, node_key);
	if (loaded_node == nullptr)
		loaded_node = NodesUtilsLoadSetup(s_Nodes, node_key);
	if (loaded_node == nullptr)
		loaded_node = ArraysNodesLoadSetup(s_Nodes, node_key);
	if (loaded_node == nullptr)
		loaded_node = Vec2NodesLoadSetup(s_Nodes, node_key);
	if (loaded_node == nullptr)
		loaded_node = Vec3NodesLoadSetup(s_Nodes, node_key);
	if (loaded_node == nullptr)
		loaded_node = Vec4NodesLoadSetup(s_Nodes, node_key);
	if (loaded_node == nullptr)
		loaded_node = MatricesNodes_LoadSetup(s_Nodes, node_key);
	if (loaded_node == nullptr)
		loaded_node = MeshesNodesLoadSetup(s_Nodes, node_key);
	if (loaded_node == nullptr)
		loaded_node = ResourcesNodesLoadSetup(s_Nodes, node_key);
	return loaded_node;
}
