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

    Predicate* returnHeadPredicate() {
        return headPredicate;
    }

    vector<Predicate*> returnRightSidePredicates() {
        return rulePredicates;
    }

    Rule(Predicate* headPredicate, vector<Predicate*>rulePredicates) {
        this->headPredicate = headPredicate;
        for(Predicate* i : rulePredicates) {
            this->rulePredicates.push_back(i);
        }
    }

    void RulesToString() {
       headPredicate->PredicateToString();
       cout << " :- ";
       for (unsigned int i = 0; i < rulePredicates.size(); i++) {
            rulePredicates.at(i)->PredicateToString();
            if(i != rulePredicates.size() - 1) {
                cout << ",";
            }
       }
    }
};

#endif //CS236PROJECT_AGAIN_RULE_H
