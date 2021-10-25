//
// Created by jharw on 10/25/2021.
//

#include "Database.h"

void Database::addToMap(Relation* relation) {
    database.insert({relation->getName(), relation});
}