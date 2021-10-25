//
// Created by jharw on 10/25/2021.
//

#ifndef PROJECT_1_TUPLE_H
#define PROJECT_1_TUPLE_H

#include <vector>
#include <string>

class Tuple {
private:
    std::vector<std::string> values;
    bool operator< (const Tuple &rhs) const;
public:
    std::string getValue(int index);
};


#endif //PROJECT_1_TUPLE_H
