#pragma once

#include <limits>
#include <cmath>
#include <unordered_map>
#include "model.h"
#include <iostream>

using std::vector;
using std::sqrt;
using std::pow;
using std::unordered_map;

class RouteModel : public Model {

  public:
    class Node : public Model::Node {
      public:
        // Add public Node variables and methods here.
        
        Node(){}
        Node(int idx, RouteModel * search_model, Model::Node node) : Model::Node(node), parent_model(search_model), index(idx) {}
        Node* parent = nullptr;
        float h_value = std::numeric_limits<float>::max();
        float g_value = 0.0;
        bool visited = false;
        vector<Node*> neighbors;

        // Compare node other-x,y values with inherited Model::Node-x,y values
        float distance(Node other_node) const {
          return sqrt(pow(other_node.x - this->x, 2) + pow(other_node.y - this->y, 2));
        }
      
      private:
        // Add private Node variables and methods here.
        int index;
        RouteModel* parent_model = nullptr;
    };
    
    // Add public RouteModel variables and methods here.
    RouteModel(const vector<std::byte> &xml);  
    vector<Node> path; // This variable will eventually store the path that is found by the A* search.

    // Getter
    auto &SNodes() { return m_Nodes; }
    auto &GetNodeToRoadMap() { return node_to_road; }

  private:
    // Add private RouteModel variables and methods here.
    vector<Node> m_Nodes;

};
