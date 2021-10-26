//
// Created by jharw on 10/25/2021.
//

#include "Database.h"

void Database::addToMap(Relation* relation) {
    dataMap.insert({relation->getName(), relation});
}
/*
std::vector<Relation*> Database::getRelations() {
    std::vector<Relation*> relations;
    for (std::map<std::string, Relation*>::iterator itr = database.begin(); itr != database.end(); itr++) {
        relations.push_back(itr->second);
    }
    return relations;
}
 */