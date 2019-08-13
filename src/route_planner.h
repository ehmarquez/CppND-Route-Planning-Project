#pragma once

#include <iostream>
#include <vector>
#include <string>
#include "route_model.h"

using std::vector;

class RoutePlanner {
  public:
    RoutePlanner(RouteModel &model, float start_x, float start_y, float end_x, float end_y);

    // Add public variables or methods declarations here.
    auto &GetDistance() const { return distance; }
    void AStarSearch();

  private:
    // Private variables
    RouteModel &m_Model;
    RouteModel::Node* start_node;          // nodes closest to start/end points
    RouteModel::Node* end_node;
    float distance;                       // from start_node -> end_node
    vector<RouteModel::Node*> open_list;

    // Private method declarations 
    // @return vector<RouteModel::Node>
    auto ConstructFinalPath(RouteModel::Node* current_node);
    float CalculateHValue(RouteModel::Node* node);
    RouteModel::Node* NextNode();
    void AddNeighbors(RouteModel::Node* node);
};
