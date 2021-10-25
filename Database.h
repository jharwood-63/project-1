//
// Created by jharw on 10/25/2021.
//

#ifndef PROJECT_1_DATABASE_H
#define PROJECT_1_DATABASE_H

#include <map>
#include <string>
#include "Relation.h"

class Database {
private:
    std::map<std::string, Relation*> database;
public:
    void addToMap(Relation* relation);
};


#endif //PROJECT_1_DATABASE_H
