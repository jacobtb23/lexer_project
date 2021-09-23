#ifndef CS236PROJECT_AGAIN_RULE_H
#define CS236PROJECT_AGAIN_RULE_H
#include "Predicate.h"
#include "Parameter.h"

using namespace std;

class Rule {
private:
    string headPredicateID;
    Predicate* headPredicate;
    vector<Parameter*> headPredicateList;

    string predicateId;
    vector<Predicate*> predicateList;

public:
    Rule(){}
    ~Rule(){}
    void toString() {}
};

#endif //CS236PROJECT_AGAIN_RULE_H
