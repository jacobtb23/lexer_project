#ifndef CS236PROJECT_AGAIN_INTERPRETER_H
#define CS236PROJECT_AGAIN_INTERPRETER_H
#include <vector>
#include "DataLog.h"
#include "Database.h"
#include "Relation.h"
#include "Header.h"
#include <iostream>
#include "Predicate.h"

using namespace std;

class Interpreter{
private:
    DataLog* dataLogObject; //Pointers?
    Database databaseObject; // Is this where we put the relations and map them to names?

    vector<Header*> deleteHeaders;
    vector<Relation*> deleteRelations;

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

    void runInterpreter();
    Relation* evaluateQuery(Predicate* queryPredicate);
    void addRulesToDB();
    void addSchemes();
    void addFacts();

};

#endif //CS236PROJECT_AGAIN_INTERPRETER_H
