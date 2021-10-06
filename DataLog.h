#ifndef CS236PROJECT_AGAIN_DATALOG_H
#define CS236PROJECT_AGAIN_DATALOG_H
#include "Parser.h"
#include "Rule.h"
#include "Predicate.h"

using namespace std;

class DataLog {
private:
    vector<Predicate*> schemeVector;
    vector<Predicate*> factsVector;
    vector<Predicate*> queriesVector;
    vector<Rule*> rulesVector;
    set<string> domainSet;
public:
    DataLog();
    ~DataLog();

    DataLog(vector<Predicate*> schemeVector,vector<Predicate*> factsVector, vector<Predicate*> queriesVector, vector<Rule*> rulesVector, set<string> domainSet) {
        this->schemeVector = schemeVector;
        this->factsVector = factsVector;
        this->queriesVector = queriesVector;
        this->rulesVector = rulesVector;
        this->domainSet = domainSet;
    }
};
#endif //CS236PROJECT_AGAIN_DATALOG_H
