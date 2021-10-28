//
// Created by jharw on 10/25/2021.
//

#include "Database.h"

void Database::addToMap(Relation* relation) {
    dataMap.insert({relation->getName(), relation});
}
