#ifndef CS236PROJECT_AGAIN_INTERPRETER_H
#define CS236PROJECT_AGAIN_INTERPRETER_H
#include <vector>
#include "DataLog.h"
#include "Database.h"
#include "Relation.h"
#include "Header.h"
#include <iostream>
#include <set>
#include "Predicate.h"
#include "graph.h"

using namespace std;

class Interpreter{
private:
    DataLog* dataLogObject; //Pointers?
    Database databaseObject; // Is this where we put the relations and map them to names?

    vector<Header*> deleteHeaders;
    vector<Relation*> deleteRelations;
    graph forwardGraph;
    graph reversedGraph;

public:
    Interpreter();
    ~Interpreter() {
        //delete stuff
        //delete DB and headers and datalog object?
        for (Relation* it : deleteRelations){
            delete it;
        }
        deleteRelations.clear();

        for (Header* it : deleteHeaders){
            delete it;
        }
        deleteHeaders.clear();
    };

    Interpreter(DataLog* dataLogObject){
        this->dataLogObject = dataLogObject;
    }


    Relation* evaluateQuery(Predicate* queryPredicate);
    Relation* evaluateRules(Predicate* queryPredicate);
    void runInterpreter();
    void addSchemes();
    void addFacts();
    void addRulesToDB();
    void evaluateSCCs(vector<set<int>> SCCs);
    void evaluateRulesOptimized(vector<Rule*> Rules);
    void createDependencyGraphs(vector<Rule*> Rules);


    int evaluateSingleRule(Rule *currentRule);
};

#endif //CS236PROJECT_AGAIN_INTERPRETER_H
