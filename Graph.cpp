//
// Created by jharw on 12/7/2021.
//

#include "Graph.h"

Graph::Graph(std::vector<Rule*> rules) {
    createNodes(rules.size());
    createAdjacencyList(rules);
    createReverseAdjacencyList();
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

void Graph::createReverseAdjacencyList() {
    //go through the adjacency list
    //for each RULE in the map, look for rules that are dependent on the RULE
    //add those rules to the reverse adjacency list
    std::map<int, std::set<int>>::iterator itr1;
    std::map<int, std::set<int>>::iterator itr2;
    std::set<int> reverseAdjacency;
    int index = 0;
    for (itr1 = adjacencyListMap.begin(); itr1 != adjacencyListMap.end(); itr1++) {
        reverseAdjacency.clear();
        // we want to look for itr1->first in all the other sets
        for (itr2 = adjacencyListMap.begin(); itr2 != adjacencyListMap.end(); itr2++) {
            if (searchSet(itr2->second, itr1->first)) {
                reverseAdjacency.insert(itr2->first);
            }
        }
        //after everything
        reverseAdjacencyMap.insert({index, reverseAdjacency});
        index++;
    }

}

bool Graph::searchSet(std::set<int> adjacencyList, int adjacencyIndex) {
    for(int dependent : adjacencyList) {
        if (dependent == adjacencyIndex) {
            return true;
        }
    }
    return false;
}