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

Relation* Interpreter::evaluateRules(Predicate* queryPredicate) {
    string queryName;
    queryName = queryPredicate->returnPredicateID();
    Relation* matchedRelation = databaseObject.findMatch(queryName);
    map<string, int> variableIndexMap;
    vector<int> indices;
    vector<string> newNames;

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

    return matchedRelation;
}

void Interpreter::addRulesToDB() {
    cout << "Rule Evaluation" << endl;
    vector<Relation*>rightHandSidePredicates;

    //Evaluate RHS predicates
    for (unsigned int i = 0; i < dataLogObject->getRules().size(); i++) {
        dataLogObject->getRules().at(i)->RulesToString();//Print out rule
        cout << endl;
        rightHandSidePredicates.clear();

        //Evaluate RHS Queries and push onto vector
        for (Predicate* it : dataLogObject->getRules().at(i)->returnRightSidePredicates()) {
            rightHandSidePredicates.push_back(evaluateRules(it));
        }

        //Join Evaluated RHS queries.
        Relation* joinedPredicate;
        joinedPredicate = rightHandSidePredicates.at(0);
        if (rightHandSidePredicates.size() > 1) { //If more than 1 RHS predicate exists
            for (unsigned int j = 0; j < rightHandSidePredicates.size() - 1; j++) { //check this...
                joinedPredicate = joinedPredicate->join(rightHandSidePredicates.at(j+1)); //
            }
        }
        else {joinedPredicate = rightHandSidePredicates.at(0);} //use single RHS predicate as result.

        //Project columns according to LHS rule head predicate.
        vector<int> indices;
        for (Parameter* it : dataLogObject->getRules().at(i)->returnHeadPredicate()->returnParameterVector()) {
            for (unsigned int k = 0; k < joinedPredicate->returnHeader()->returnAttributes().size(); k++) {
                if (it->getStringOrID() == joinedPredicate->returnHeader()->returnAttributes().at(k)) {
                    indices.push_back(k);
                }
            }
        }
        joinedPredicate = joinedPredicate->project(indices);

        //Rename according to head predicate header
        joinedPredicate = joinedPredicate->rename(dataLogObject->getRules().at(i)->returnHeadPredicate()->returnVectorOfStrings());

        //populate schemes with new facts via union.
        databaseObject.findMatch(dataLogObject->getRules().at(i)->returnHeadPredicate()->returnPredicateID())->unionOperator(joinedPredicate);
        cout << "";
    }
    cout << endl << "Schemes populated after ? passes through the Rules."  << endl;
}
void Interpreter::addSchemes() {
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
}
void Interpreter::addFacts() {
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
}
void Interpreter::runInterpreter() {
    addSchemes();
    addFacts();
    addRulesToDB();
    //databaseObject.toString();

    //Test Relation

//    vector<string> testValues;
//    testValues.push_back("\'12345\'");
//    testValues.push_back("\'C. Brown\'");
//    testValues.push_back("\'12 Apple St.\'");
//    testValues.push_back("\'555-1234\'");
//
//
//    vector<string> testValues1;
//    testValues1.push_back("\'67890\'");
//    testValues1.push_back("\'L.Van Pelt\'");
//    testValues1.push_back("\'34 Pear Ave.\'");
//    testValues1.push_back("\'555-5678\'");
//
//
//    vector<string> testValues2;
//    testValues2.push_back("\'33333\'");
//    testValues2.push_back("\'Snoopy\'");
//    testValues2.push_back("\'12 Apple St.\'");
//    testValues2.push_back("\'555-1234\'");


//    Tuple testTuple = Tuple(testValues);
//    Tuple testTuple1 = Tuple(testValues1);
//    Tuple testTuple2 = Tuple(testValues2);
//    set<Tuple> testRows;
//    Header* testHeader;
//    string testName = "snap";
//    testHeader = new Header(dataLogObject->getSchemes().at(0)->returnParameterVector());
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
//    ////////////////////////////////////////////
//
//    vector<string> moretestValues;
//    moretestValues.push_back("\'CS101\'");
//    moretestValues.push_back("\'67890\'");
//    moretestValues.push_back("\'A\'");
//
//
//    vector<string> moretestValues1;
//    moretestValues1.push_back("\'CS101\'");
//    moretestValues1.push_back("\'12345\'");
//    moretestValues1.push_back("\'B\'");
//
//
//    vector<string> moretestValues2;
//    moretestValues2.push_back("\'EE200\'");
//    moretestValues2.push_back("\'12345\'");
//    moretestValues2.push_back("\'C\'");
//
//
//    Tuple moretestTuple = Tuple(moretestValues);
//    Tuple moretestTuple1 = Tuple(moretestValues1);
//    Tuple moretestTuple2 = Tuple(moretestValues2);
//    set<Tuple> moretestRows;
//    Header* moretestHeader;
//    string moretestName = "csg";
//    moretestHeader = new Header(dataLogObject->getSchemes().at(1)->returnParameterVector());
//    Relation* testRelation2;
//    testRelation2 = new Relation(moretestName,moretestHeader);
//    deleteRelations.push_back(testRelation);
//    vector<int> moreindices;
//    indices.push_back(2);
//    indices.push_back(1);
//
//    testRelation2->addTuple(moretestTuple);
//    testRelation2->addTuple(moretestTuple1);
//    testRelation2->addTuple(moretestTuple2);
//
//    testRelation->join(testRelation2);

}



