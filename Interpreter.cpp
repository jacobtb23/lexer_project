#include <vector>
#include "DataLog.h"
#include "Database.h"
#include "Relation.h"
#include "Tuple.h"
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

        databaseObject.addRelation(relationName, newRelation);
    }

    //add tuples to each relation where schemes and fact name matches.
    for (unsigned int i = 0; i < dataLogObject->getFacts().size(); i++) {
        string factName;
        vector<string> parameterVector;
        //Tuple newTuple;

        factName = dataLogObject->getFacts().at(i)->returnPredicateID();

        for(unsigned int j = 0; j < dataLogObject->getFacts().at(i)->returnParameterVector().size(); j++) {
            parameterVector.push_back(dataLogObject->getFacts().at(i)->returnParameterVector().at(j)->getStringOrID());
        }

        Tuple newTuple = Tuple(parameterVector);
        databaseObject.addTupleToRelation(factName, newTuple);
    }
    databaseObject.toString();
}
//Relation* Interpreter::evaluatePredicate(const Predicate& p) --> Strongly recommended.


