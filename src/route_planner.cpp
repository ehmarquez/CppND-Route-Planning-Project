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
