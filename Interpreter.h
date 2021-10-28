//
// Created by jharw on 10/25/2021.
//

#ifndef PROJECT_1_INTERPRETER_H
#define PROJECT_1_INTERPRETER_H

#include "DatalogProgram.h"
#include "Database.h"
#include <string>
#include <vector>

class Interpreter {
private:
    DatalogProgram* datalogProgram;
    Database* database;

    void createRelations();
    void createTuples();
    Relation* evaluatePredicate(Predicate* predicate);

    Relation* findRelation(Predicate* p);
    bool setConstant(std::string parameterId);
    int findIndex(std::vector<std::string> parameterStrings, std::string parameterId, bool isDuplicate);
    int searchMap(std::map<int, std::string> saveVars, std::string var, int index);
    bool checkVector(std::vector<std::string> saveVars, std::string var);

    void toString(Predicate* query, Relation* relation);
public:
    Interpreter(DatalogProgram* datalogProgram, Database* database);

    void evaluateQueries();
};


#endif //PROJECT_1_INTERPRETER_H
