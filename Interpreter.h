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
    //std::vector<Relation*> evaluateRightPredicates(Predicate* bodyPredicate);

    Relation* findRelation(Predicate* p);
    bool setConstant(std::string parameterId);
    int findIndex(std::vector<std::string> parameterStrings, std::string parameterId, int prevIndex);
    std::vector<int> createIndexList(Relation* joinedRelation, Predicate* headPredicate);
    int searchMap(std::map<int, std::string> saveVars, std::string var, int index);
    bool checkVector(std::vector<std::string> saveVars, std::string var);
    bool checkAllConst(Predicate* query);

    void toString(Predicate* query, Relation* relation);
    void toString(Rule* rule);
public:
    Interpreter(DatalogProgram* datalogProgram, Database* database);

    void evaluateQueries();
    void evaluateRules();
};


#endif //PROJECT_1_INTERPRETER_H
