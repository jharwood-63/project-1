//
// Created by jharw on 9/27/2021.
//

#ifndef PROJECT_1_PARAMETER_H
#define PROJECT_1_PARAMETER_H

#include <string>

class Parameter {
public:
    Parameter(std::string p, bool isConstant);
    std::string toString();
    std::string getP();
    void setConstant(bool isConstant);
private:
    std::string p;
    bool isConstant;
};


#endif //PROJECT_1_PARAMETER_H
