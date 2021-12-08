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
    std::map<int, bool> visitedMap;

    void createNodes(int size);
    void createAdjacencyList(std::vector<Rule*> rules);
    void createReverseAdjacencyList();

    void depthFirstSearch(int rule, std::vector<int> &postorder, std::vector<int> &tree);

    void markVisited(int rule);
    bool isVisited(int rule);
    void resetVisited();
    std::set<int> findAdjacencyList(int rule);
    bool searchSet(std::set<int> adjacencyList, int adjacencyIndex);
public:
    Graph(std::vector<Rule*> rules);
    void depthFirstSearchForest();
};


#endif //PROJECT_1_GRAPH_H
