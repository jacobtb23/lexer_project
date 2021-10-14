#include <vector>
#include "DataLog.h"
#include "Database.h"
#include "Relation.h"
#include "Header.h"
#include <iostream>
#include "Predicate.h"
#include "Interpreter.h"

void Interpreter::runInterpreter() {
    //do stuff...
    cout << endl;
    cout << "Testing Interpreter:" << endl;
    cout << "************************************************" << endl;

    //create relation for each scheme object in the schemeVector...
    for (unsigned int i = 0; i < dataLogObject->getSchemes().size(); i++) {
        Header* newHeader;
        Relation newRelation;
        string relationName;

        relationName = dataLogObject->getSchemes().at(i)->returnPredicateID();
        newHeader = new Header(dataLogObject->getSchemes().at(i)->returnParameterVector());
        newRelation = Relation(relationName, newHeader);
        cout << "";

        //add new relation to database map, then add tuples.
        //Should the DB be a pointer?
    }
}
//Relation* Interpreter::evaluatePredicate(const Predicate& p) --> Strongly recommended.
