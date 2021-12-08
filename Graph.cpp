//
// Created by jharw on 12/7/2021.
//

#include "Graph.h"

Graph::Graph(std::vector<Rule*> rules) {
    createNodes(rules.size());
    createAdjacencyList(rules);
}

void Graph::createNodes(int size) {
    for (int i = 0; i < size; i++) {
        Node node = Node();
        node.index = i;
        node.visited = false;
        nodes.push_back(node);
    }
}

void Graph::createAdjacencyList(std::vector<Rule *> rules) {
    //nested for loops
    std::set<int> adjacencyList;
    std::string headPredicate;
    std::string bodyPredicate;
    //first runs through rules
    for (unsigned int i = 0; i < rules.size(); i++) {
        //second runs through body predicates

        //FIXME: for testing purposes
        std::string rule = rules.at(i)->getHeadPredicate()->getId();

        adjacencyList.clear();
        for (int j = 0; j < rules.at(i)->getBodyPredicateSize(); j++) {
            //third runs through head predicates to see if there is a match
            bodyPredicate = rules.at(i)->getBodyPredicate(j)->getId();
            for (unsigned int k = 0; k < rules.size(); k++) {
                //if match, add that rule to the adjacency list
                headPredicate = rules.at(k)->getHeadPredicate()->getId();
                if (headPredicate == bodyPredicate) {
                    adjacencyList.insert(k);
                }
            }
        }
        adjacencyListMap.insert({i, adjacencyList});
    }
}