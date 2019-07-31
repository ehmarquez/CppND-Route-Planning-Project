#include "route_planner.h"
#include <algorithm>

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