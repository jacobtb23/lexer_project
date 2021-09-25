#ifndef CS236PROJECT_AGAIN_RULE_H
#define CS236PROJECT_AGAIN_RULE_H
#include "Predicate.h"
#include "Parameter.h"

using namespace std;

class Rule {
private:
    Predicate* headPredicate;
    vector<Predicate*> rulePredicates;

public:
    Rule(){}
    ~Rule(){}

    Rule(Predicate* headPredicate, vector<Predicate*>rulePredicates) {
        this->headPredicate = headPredicate;

        for(Predicate* i : rulePredicates) {
            this->rulePredicates.push_back(i);
        }
    }

    void toString() {

    }
};

#endif //CS236PROJECT_AGAIN_RULE_H
