#ifndef CS236MAIN_RULE_H
#define CS236MAIN_RULE_H
#include <vector>
#include <iostream>
#include "Predicate.h"
#include "DataLog.h"

using namespace std;

class Rule
{
private:
   Predicate* headPredicateId;
   vector<string*> headPredicateList;
   vector<Predicate*> rulePredicateList;
public:
    Rule();
    ~Rule();

    void toString() {

    };
};

#endif //CS236MAIN_RULE_H
