//
// Created by jharw on 10/25/2021.
//

#ifndef PROJECT_1_HEADER_H
#define PROJECT_1_HEADER_H

#include <vector>
#include <string>

class Header {
private:
    std::vector<std::string> attributes;
public:
    int getSize();
    std::string getValue(int index);
};


#endif //PROJECT_1_HEADER_H
