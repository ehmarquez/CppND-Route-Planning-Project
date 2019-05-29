#include "route_model.h"
#include <iostream>

RouteModel::RouteModel(const std::vector<std::byte> &xml) : Model(xml) {
  // Creating RouteModel Nodes
  int iter = 0;
  for(Model::Node node : this->Nodes()) {
    m_Nodes.push_back(Node(iter, this, node));
    iter++;
  }
  CreateNodeToRoadHashmap();
}

/*
 *
 * 
 */
void RouteModel::CreateNodeToRoadHashmap() {
  /* const to ensure that the values do not get changed outside the function
   * auto $road is of type Model::Road
   * Loop over each road in Model::Roads that is not a footway
   * Each road has the index of the way it belongs to (see struct Road)
   * Ways() returns a vector<Way>
   * Each Way has a vector<int> nodes (see struct Way) 
   * Iterate through the node in each Way and find in our hashmap
   * If node is not in hashmap, create empty vector of Model::Road pointers 
   * Then add (key)node_idx and (value)Road* to hashmap
   * Access the vector of Road* using (key)node_idx and append &road
  */
  for(const auto &road : Roads()) {
    if (road.type != Model::Road::Type::Footway) {
      for (int node_idx : Ways()[road.way].nodes) {
        if (node_to_road.find(node_idx) == node_to_road.end()) {
          node_to_road[node_idx] = vector<const Model::Road*> ();
        }
        node_to_road[node_idx].push_back(&road);
      }
    }

  }
}