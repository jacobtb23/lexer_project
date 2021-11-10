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
    DataLog(){}
    ~DataLog(){}

    DataLog(vector<Predicate*> schemeVector,vector<Predicate*> factsVector, vector<Predicate*> queriesVector, vector<Rule*> rulesVector, set<string> domainSet) {
        this->schemeVector = schemeVector;
        this->factsVector = factsVector;
        this->queriesVector = queriesVector;
        this->rulesVector = rulesVector;
        this->domainSet = domainSet;
    }

    vector<Predicate*> getSchemes(){
        return schemeVector;
    }
    vector<Predicate*> getFacts(){
        return factsVector;
    }
    vector<Predicate*> getQueries(){
        return queriesVector;
    }
    set<string> getDomains(){
        return domainSet;
    }
    vector<Rule*> getRules() {
        return rulesVector;
    }

};
#endif //CS236PROJECT_AGAIN_DATALOG_H
