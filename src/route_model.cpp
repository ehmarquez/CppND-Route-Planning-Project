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

/* Loops through node indices to find closest unvisited node.
 * 
 * @param node_indices - vector of neighbor nodes to iterate
 * @return - pointer to closest unvisited neighbor node
 */
RouteModel::Node* RouteModel::Node::FindNeighbor(vector<int> node_indices) {
  Node* closest_node = nullptr;
  Node node;
  for (auto node_index : node_indices) {
    node = parent_model->SNodes()[node_index]; 
    if (this->distance(node) && !node.visited) {
      if (closest_node == nullptr || (this->distance(node) < this->distance(*closest_node))){
        closest_node = &parent_model->SNodes()[node_index];
      }
    }
  }
  return closest_node;
}

/* Create a vector of neighbors for the current node
 *
 */
void RouteModel::Node::FindNeighbors() {
  for (auto &road : parent_model->node_to_road[this->index]) {
    RouteModel::Node* new_neighbor = this->FindNeighbor(parent_model->Ways()[road->way].nodes);
    if (new_neighbor) {
      this->neighbors.emplace_back(new_neighbor);
    }
  }
}