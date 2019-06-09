#pragma once

#include <iostream>
#include <vector>
#include <string>
#include "route_model.h"


class RoutePlanner {
  public:
    RoutePlanner(RouteModel &model, float start_x, float start_y, float end_x, float end_y);
    // Add public variables or methods declarations here.
    auto &GetDistance() const { return distance; }

  private:
    // Add private variables or methods declarations here.
    RouteModel &m_Model;
    RouteModel::Node* start_node;          // nodes closest to start/end points
    RouteModel::Node* end_node;
    float distance;                       // from start_node -> end_node

    // @return vector<RouteModel::Node>
    auto ConstructFinalPath(RouteModel::Node* current_node);
};
