//
// Created by jharw on 12/7/2021.
//

#ifndef PROJECT_1_GRAPH_H
#define PROJECT_1_GRAPH_H

#include <iostream>
#include <map>
#include <set>
#include <vector>
#include "Rule.h"

class Graph {
private:
    std::map<int, std::set<int>> adjacencyListMap;
    std::map<int, std::set<int>> reverseAdjacencyMap;
    struct Node {
        int index;
        bool visited;
    };
    std::vector<Node> nodes;

    void createNodes(int size);
    void createAdjacencyList(std::vector<Rule*> rules);
    void createReverseAdjacencyList(std::vector<Rule*> rules);
public:
    Graph(std::vector<Rule*> rules);
};


#endif //PROJECT_1_GRAPH_H
