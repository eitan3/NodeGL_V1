#include "collect_search_nodes.h"

void CollectSearchNodes(std::vector<SearchNodeObj>& search_nodes_vector)
{
	GlNodes1_SearchSetup(search_nodes_vector);
	DummiesSearchSetup(search_nodes_vector);
	NodesUtilsSearchSetup(search_nodes_vector);
	MathNodesSearchSetup(search_nodes_vector);
}