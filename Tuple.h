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
public:
    std::string getValue(int index);
    void addValue(std::string value);
    bool operator< (const Tuple &rhs) const;
    Tuple projectTuple(std::vector<int> indices, bool reorder);
    int getSize();
    void switchTuple(int switchIndex, int next, std::vector<int> indices);
};


#endif //PROJECT_1_TUPLE_H
