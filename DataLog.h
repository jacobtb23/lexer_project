#ifndef CS236MAIN_DATALOG_H
#define CS236MAIN_DATALOG_H

#include <vector>
#include <iostream>
#include "Predicate.h"
#include "Rule.h"
#include "Parameter.h"

using namespace std;
//datalogProgram -> SCHEMES COLON scheme schemeList FACTS COLON factList RULES COLON ruleList QUERIES COLON query queryList EOF
class DataLog
{
private:
    vector<Predicate*> schemeVector;
    vector<Predicate*> factsVector;
    vector<Predicate*> queriesVector;
public:
    DataLog();
    ~DataLog();

    void toString();
};
#endif //CS236MAIN_DATALOG_H
