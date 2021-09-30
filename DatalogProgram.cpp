//
// Created by jharw on 9/27/2021.
//

#include "DatalogProgram.h"

void DatalogProgram::toString() {
    unsigned int i;
    //schemas
    std::cout << "Schemes(" << schemes.size() << "):\n  ";
    for (i = 0; i < schemes.size(); i++) {
        if (i != (schemes.size() - 1))
            std::cout << schemes.at(i)->toString() << "\n  ";
        else
            std::cout << schemes.at(i)->toString() << "\n\n";
    }
    //facts
    std::cout << "Facts(" << facts.size() << "):\n  ";
    for (i = 0; i < facts.size(); i++) {
        if (i != (facts.size() - 1))
            std::cout << facts.at(i)->toString() << ".\n  ";
        else
            std::cout << facts.at(i)->toString() << ".\n\n";
    }
    //rules
    std::cout << "Rules(" << rules.size() << "):\n  ";
    std::cout << rules.at(0)->toString() << std::endl;
    //queries
    std::cout << "Queries(" << queries.size() << "):\n  ";
    for (i = 0; i < queries.size(); i++) {
        if (i != (queries.size() - 1))
            std::cout << queries.at(i)->toString() << "?\n  ";
        else
            std::cout << queries.at(i)->toString() << "?\n\n";
    }
}