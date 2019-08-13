#include "route_planner.h"
#include <algorithm>

using std::sort;

RoutePlanner::RoutePlanner(RouteModel &model, float start_x, float start_y, float end_x, float end_y): m_Model(model) {
  // Scale to percentage values
  start_x *= 0.01;
  start_y *= 0.01;
  end_x *= 0.01;
  end_y *= 0.01;

  // Find closest nodes to start and end points
  start_node = &model.FindClosestNode(start_x, start_y);
  end_node = &model.FindClosestNode(end_x, end_y);
}


// @return vector<RouteModel::Node>
auto RoutePlanner::ConstructFinalPath(RouteModel::Node* current_node) {

  vector<RouteModel::Node> path_found;        // Store nodes on the path here
  distance = 0.0f;                            // Total distance travelled
  RouteModel::Node parent;                    // Store parent of current node

  // Start at end node and iterate until start node is found
  while(current_node->parent != nullptr) {
    path_found.push_back(*current_node);
    parent = *(current_node->parent);
    distance += current_node->distance(parent);
    current_node = current_node->parent;
  }
  path_found.push_back(*current_node);        // Add start node as final node
  distance *= m_Model.MetricScale();
  return path_found;
}


// Find the path using A* search
void RoutePlanner::AStarSearch() {
  start_node->visited = true;
  open_list.push_back(start_node);
  RouteModel::Node* current_node = nullptr;

  // Iterate through open list of nodes until end goal reached
  while (open_list.size() > 0) {
    // Explore next node based on heuristic values
    current_node = NextNode();
    if (current_node->distance(*end_node) == 0) {
      m_Model.path = ConstructFinalPath(current_node);
      return;
    }
      AddNeighbors(current_node);
  }
}

float RoutePlanner::CalculateHValue(RouteModel::Node *node) {
  return node->distance(*end_node);
}


RouteModel::Node* RoutePlanner::NextNode() {
  // sort list of nodes in ascending order of sum of h_value & g_value
  sort(open_list.begin(), open_list.end(),
    [](const auto &_1st, const auto &_2nd) {
      return _1st->h_value + _1st->g_value < _2nd->h_value + _2nd->g_value;
  });

  // Return node with the lowest sum value
  RouteModel::Node* lowest_node = open_list.front();    //ptr to 1st element
  open_list.erase(open_list.begin());                   //iter at 1st element
  return lowest_node;
}


void RoutePlanner::AddNeighbors(RouteModel::Node* node) {
  node->FindNeighbors();
  for (auto neighbor : node->neighbors) {
    neighbor->parent = node;
    neighbor->g_value = node->g_value + node->distance(*neighbor);
    neighbor->h_value = CalculateHValue(neighbor);

    // Finally, add neighbor node to open list of nodes to check
    open_list.push_back(neighbor);
    neighbor->visited = true;
  }
}
