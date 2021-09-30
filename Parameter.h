//
// Created by jharw on 9/27/2021.
//

#ifndef PROJECT_1_PARAMETER_H
#define PROJECT_1_PARAMETER_H

#include <string>

class Parameter {
public:
    Parameter(std::string p);
    std::string toString();
private:
    std::string p;
};


#endif //PROJECT_1_PARAMETER_H
