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
        visitedMap.insert({i, false});
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

void Graph::depthFirstSearchForest() {
    /*
     * forest := empty
     * for each vertex v in G
     * clear the visit mark for v
     *
     * for each vertex v in G
     * if v is not marked
     * tree := DepthFirstSearch(v)
     * add tree to forest
     */
    forest.clear();
    resetVisited();

    std::vector<int> postorder;
    std::vector<int> tree;
    std::map<int, std::set<int>>::iterator itr;
    for (itr = reverseAdjacencyMap.begin(); itr != reverseAdjacencyMap.end(); itr++) {
        tree.clear();
        if (!isVisited(itr->first)) {
            depthFirstSearch(itr->first, tree);
            forest.insert(tree);
        }
    }
}

void Graph::depthFirstSearch(int rule, std::vector<int> &tree) {
    /*
     * mark v
     * for each vertex w adjacent from v
     * if w is not marked
     * DepthFirstSearch(w)
     * still need to add postorder
     */
    markVisited(rule);
    tree.push_back(rule);
    std::set<int> adjacencyList = findAdjacencyList(rule);
    for (int dependent : adjacencyList) {
        if (!isVisited(dependent))
            depthFirstSearch(dependent, tree);
    }
    postorder.push_back(rule);
}

void Graph::markVisited(int rule) {
    std::map<int, bool>::iterator itr;
    for (itr = visitedMap.begin(); itr != visitedMap.end(); itr++) {
        if (itr->first == rule) {
            itr->second = true;
            break;
        }
    }
}

bool Graph::isVisited(int rule) {
    std::map<int, bool>::iterator itr;
    for (itr = visitedMap.begin(); itr != visitedMap.end(); itr++) {
        if (itr->first == rule) {
            if (itr->second){
                return true;
            }
            else {
                return false;
            }
        }
    }
    return false;
}

void Graph::resetVisited() {
    std::map<int, bool>::iterator itr;
    for (itr = visitedMap.begin(); itr != visitedMap.end(); itr++) {
        itr->second = false;
    }
}

std::set<int> Graph::findAdjacencyList(int rule) {
    std::map<int, std::set<int>>::iterator itr;
    for (itr = reverseAdjacencyMap.begin(); itr != reverseAdjacencyMap.end(); itr++) {
        if (itr->first == rule) {
            return itr->second;
        }
    }
}

std::vector<int> Graph::getPostorder() {
    return postorder;
}

std::set<std::vector<int>> Graph::getForest() {
    return forest;
}

void Graph::toString() {
    std::map<int, std::set<int>>::iterator itr;
    int count;
    std::cout << "Dependency Graph\n";
    for (itr = adjacencyListMap.begin(); itr != adjacencyListMap.end(); itr++) {
        std::cout << "R" << itr->first << ":";
        count = 0;
        for (int adjacent : itr->second) {
            if (count == itr->second.size() - 1) {
                std::cout << "R" << adjacent;
            }
            else {
                std::cout << "R" << adjacent << ",";
            }
            count++;
        }
        std::cout << "\n";
    }
}