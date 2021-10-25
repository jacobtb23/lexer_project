#include <vector>
#include "DataLog.h"
#include "Database.h"
#include "Relation.h"
#include "Tuple.h"
#include "Header.h"
#include <map>
#include <iostream>
#include "Predicate.h"
#include "Interpreter.h"
#include <stdexcept>

Relation* Interpreter::evaluateQuery(Predicate* queryPredicate) {
    string queryName;
    queryName = queryPredicate->returnPredicateID();
    Relation* matchedRelation = databaseObject.findMatch(queryName);
    map<string, int> variableIndexMap;
    vector<int> indices;
    vector<string> newNames;

    //print out query here
    queryPredicate->PredicateToString();
    cout  << "?";

    for(unsigned int i = 0; i < queryPredicate->returnParameterVector().size(); i++){
        if(queryPredicate->returnParameterVector().at(i)->isConstant()) {
            matchedRelation = matchedRelation->selectIV(i,queryPredicate->returnParameterVector().at(i)->getStringOrID());
            //matchedRelation->printRelationRows();
        }
        else {
            if(variableIndexMap.count(queryPredicate->returnParameterVector().at(i)->getStringOrID()) > 0) {
                //variableIndexMap.insert({queryPredicate->returnParameterVector().at(i)->getStringOrID(), i});
                matchedRelation = matchedRelation->selectII(i,variableIndexMap.at(queryPredicate->returnParameterVector().at(i)->getStringOrID()));
                //will there be more than 2 of the same variables?
            }
            else {
                variableIndexMap.insert({queryPredicate->returnParameterVector().at(i)->getStringOrID(), i});
                indices.push_back(i);
            }
        }
    }

    //project and rename
    for (unsigned int i = 0; i < indices.size(); i++) {
        newNames.push_back(queryPredicate->returnParameterVector().at(indices.at(i))->getStringOrID());
    }

    matchedRelation = matchedRelation->project(indices);
    matchedRelation = matchedRelation->rename(newNames);
    if (matchedRelation->tuplesPresent() == false) {
        cout << " Yes(";
        matchedRelation->printSetSize();
        cout << ")" << endl;
        if(matchedRelation->returnHeader()->returnAttributes().empty() == true) {
            //Do nothing
        }
        else {matchedRelation->printFinalRelation();}
     }
    else {cout << " No" << endl;}



    return matchedRelation;
}

void Interpreter::runInterpreter() {

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

    //databaseObject.toString();


    //Relation* Interpreter::evaluatePredicate(const Predicate& p) --> Strongly recommended.

    //Test Relation
//    vector<Parameter*> attributes;
//
//    vector<string> testValues;
//    testValues.push_back("\'A\'");
//    testValues.push_back("\'C\'");
//    testValues.push_back("\'Z\'");
//
//
//    vector<string> testValues1;
//    testValues1.push_back("\'A\'");
//    testValues1.push_back("\'A\'");
//    testValues1.push_back("\'C\'");
//
//
//    vector<string> testValues2;
//    testValues2.push_back("\'A\'");
//    testValues2.push_back("\'C\'");
//    testValues2.push_back("\'P\'");
//
//
//    Tuple testTuple = Tuple(testValues);
//    Tuple testTuple1 = Tuple(testValues1);
//    Tuple testTuple2 = Tuple(testValues2);
//    set<Tuple> testRows;
//    Header* testHeader;
//    string testName = "csg";
//    testHeader = new Header(dataLogObject->getSchemes().at(1)->returnParameterVector());
//    Relation* testRelation;
//    testRelation = new Relation(testName,testHeader);
//    deleteRelations.push_back(testRelation);
//    vector<int> indices;
//    indices.push_back(2);
//    indices.push_back(1);
//
//    testRelation->addTuple(testTuple);
//    testRelation->addTuple(testTuple1);
//    testRelation->addTuple(testTuple2);
//
//    cout << "This is the test relation:" << endl;
//    testRelation->printRelationName();
//    cout << endl;
//    testRelation->printHeader();
//    testRelation->printRelationRows();
//    cout << endl << "This is the new relation:" << endl;
//    testRelation = testRelation->project(indices);
//    testRelation->printHeader();
//    cout << endl;
//    testRelation->printRelationRows();
//    cout << endl << endl;
//    vector<string> newHeaderNames;
//    newHeaderNames.push_back("DONT");
//    newHeaderNames.push_back("BE");
//    testRelation = testRelation->rename(newHeaderNames);
//    testRelation->printHeader();
//    testRelation->printRelationRows();
//    testRelation = testRelation->selectIV(0,"\'P\'");
//    testRelation->printHeader();
//    testRelation->printRelationRows();
//    testRelation = testRelation->selectIV(0,"\'A\'");
//    testRelation->printHeader();
//    testRelation->printRelationRows();
    //cout << endl << "***********************************************************";
}



