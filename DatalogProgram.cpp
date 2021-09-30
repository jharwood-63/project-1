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
            std::cout << schemes.at(i)->toString() << "\n";
    }
    //facts
    std::cout << "Facts(" << facts.size() << "):\n";
    if (facts.size() != 0) {
        std::cout << "  ";
        for (i = 0; i < facts.size(); i++) {
            if (i != (facts.size() - 1))
                std::cout << facts.at(i)->toString() << ".\n  ";
            else
                std::cout << facts.at(i)->toString() << ".\n";
        }
    }
    //rules
    std::cout << "Rules(" << rules.size() << "):\n";
    if (rules.size() != 0) {
        std::cout << "  ";
        for (i = 0; i < rules.size(); i++) {
            if (i != (rules.size() - 1))
                std::cout << rules.at(i)->toString() << "\n  ";
            else
                std::cout << rules.at(i)->toString() << "\n";
        }
    }
    //queries
    std::cout << "Queries(" << queries.size() << "):\n";
    if (queries.size() != 0) {
        std::cout << "  ";
        for (i = 0; i < queries.size(); i++) {
            if (i != (queries.size() - 1))
                std::cout << queries.at(i)->toString() << "?\n  ";
            else
                std::cout << queries.at(i)->toString() << "?\n";
        }
    }
    //Domain
    std::cout << "Domain(" << domain.size() << "):\n";
    if (domain.size() != 0) {
        std::cout << "  ";
        std::string domainStr = "";
        for (std::set<std::string>::iterator itr = domain.begin(); itr != domain.end(); itr++) {
            domainStr += *itr + "\n  ";
        }
        domainStr.pop_back();
        domainStr.pop_back();
        //domainStr.pop_back();
        std::cout << domainStr;
    }
}

void DatalogProgram::addDomain(std::string parameterId) {
    domain.insert(parameterId);
    /*
    bool isDuplicate = false;
    if (!domain.empty()) {
        Parameter* temp;
        for (unsigned int i = 0; i < domain.size(); i++) {
            temp = domain.at(i);
            if (temp->getP() == parameter->getP()) {
                isDuplicate = true;
                break;
            }
        }
    }
    if (!isDuplicate) {
        domain.push_back(parameter);
    }
     */
}