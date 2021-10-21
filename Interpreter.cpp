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
        deleteHeaders.push_back(newHeader);
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

    //For each query, get the matching relation...
//    for (unsigned int i = 0; i < dataLogObject->getQueries().size(); i++) {
//        string queryName;
//        vector<string> parameterVector;
//
//        queryName = dataLogObject->getQueries().at(i)->returnPredicateID();
//
//        for(unsigned int j = 0; j < dataLogObject->getQueries().at(i)->returnParameterVector().size(); j++) {
//            parameterVector.push_back(dataLogObject->getQueries().at(i)->returnParameterVector().at(j)->getStringOrID());
//        }
//    }

    //Test Relation
    vector<Parameter*> attributes;

    vector<string> testValues;
    testValues.push_back("\'A\'");
    testValues.push_back("\'C\'");
    testValues.push_back("\'Z\'");


    vector<string> testValues1;
    testValues1.push_back("\'A\'");
    testValues1.push_back("\'A\'");
    testValues1.push_back("\'C\'");


    vector<string> testValues2;
    testValues2.push_back("\'A\'");
    testValues2.push_back("\'C\'");
    testValues2.push_back("\'P\'");


    Tuple testTuple = Tuple(testValues);
    Tuple testTuple1 = Tuple(testValues1);
    Tuple testTuple2 = Tuple(testValues2);
    set<Tuple> testRows;
    Header* testHeader;
    string testName = "csg";
    testHeader = new Header(dataLogObject->getSchemes().at(1)->returnParameterVector());
    Relation* testRelation;
    testRelation = new Relation(testName,testHeader);
    deleteRelations.push_back(testRelation);
    vector<int> indices;
    indices.push_back(2);
    indices.push_back(1);

    testRelation->addTuple(testTuple);
    testRelation->addTuple(testTuple1);
    testRelation->addTuple(testTuple2);

    cout << "This is the test relation:" << endl;
    testRelation->printRelationName();
    cout << endl;
    testRelation->printHeader();
    testRelation->printRelationRows();
    cout << endl << "This is the new relation:" << endl;
    testRelation = testRelation->project(indices);
    testRelation->printHeader();
    cout << endl;
    testRelation->printRelationRows();
    cout << endl << endl;
    vector<string> newHeaderNames;
    newHeaderNames.push_back("DO");
    newHeaderNames.push_back("ME");
    testRelation = testRelation->rename(newHeaderNames);
    testRelation->printHeader();
    testRelation->printRelationRows();






    //databaseObject.toString();
    //cout << endl << "***********************************************************";
}
//Relation* Interpreter::evaluatePredicate(const Predicate& p) --> Strongly recommended.


