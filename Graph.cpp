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

void Graph::depthFirstSearchForest() {
    // this one returns the tree?
    // this function is necessary for the nodes that you can't get anywhere from
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

    //this is the second part without the forest stuff
    std::set<int> postorder;
    std::map<int, std::set<int>>::iterator itr;
    for (itr = reverseAdjacencyMap.begin(); itr != reverseAdjacencyMap.end(); itr++) {
        if (!isVisited(itr->first)) {
            depthFirstSearch(itr->first, postorder);
        }
    }
}

void Graph::depthFirstSearch(int rule, std::set<int> &postorder) {
    // this one returns the postorder
    /*
     * mark v
     * for each vertex w adjacent from v
     * if w is not marked
     * DepthFirstSearch(w)
     * still need to add postorder
     */

    //so its not working super great, its adding in the wrong order because of the set and also its adding the wrong thing
    int done = 0;
    bool marked = markVisited(rule);
    //FIXME:
    if (!marked) {
        std::cout << "what seems to be the officer problem?\n";
    }

    std::set<int> adjacencyList = findAdjacencyList(rule);
    for (int dependent : adjacencyList) {
        if (!isVisited(dependent))
            depthFirstSearch(dependent, postorder);

        done++;
        if (done == adjacencyList.size()) {
            if (adjacencyList.size() == 1)
                postorder.insert(rule);
            else
                postorder.insert(dependent);
        }
    }
}

bool Graph::markVisited(int rule) {
    std::map<int, bool>::iterator itr;
    for (itr = visitedMap.begin(); itr != visitedMap.end(); itr++) {
        if (itr->first == rule) {
            itr->second = true;
            return true;
        }
    }
    return false;
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

std::set<int> Graph::findAdjacencyList(int rule) {
    std::map<int, std::set<int>>::iterator itr;
    for (itr = reverseAdjacencyMap.begin(); itr != reverseAdjacencyMap.end(); itr++) {
        if (itr->first == rule) {
            return itr->second;
        }
    }
}