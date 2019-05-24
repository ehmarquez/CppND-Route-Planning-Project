#include "route_model.h"
#include <iostream>

RouteModel::RouteModel(const std::vector<std::byte> &xml) : Model(xml) {
  // Creating RouteModel Nodes
  int iter = 0;
  for(Model::Node node : this->Nodes()) {
    m_Nodes.push_back(Node(iter, this, node));
    iter++;
  }
}