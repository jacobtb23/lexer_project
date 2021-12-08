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
#include "graph.h"

//add two graph objects. One for the forward graph and one for the reverse graph. Where does this happen? Is seems like I will have to redo the last lab to do this?
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
    int continueLoop = 1;
    unsigned int count = 0;

    while(continueLoop > 0) {
        continueLoop = 0;
        count++;
        //Evaluate RHS predicates
        for (unsigned int i = 0; i < dataLogObject->getRules().size(); i++) {
            dataLogObject->getRules().at(i)->RulesToString();//Print out rule
            cout << ".";
            cout << endl;
            rightHandSidePredicates.clear();

            //Evaluate RHS Queries and push onto vector
            for (Predicate *it: dataLogObject->getRules().at(i)->returnRightSidePredicates()) {
                rightHandSidePredicates.push_back(evaluateRules(it));
            }

            //Join Evaluated RHS queries.
            Relation *joinedPredicate;
            joinedPredicate = rightHandSidePredicates.at(0);
            if (rightHandSidePredicates.size() > 1) { //If more than 1 RHS predicate exists
                for (unsigned int j = 0; j < rightHandSidePredicates.size() - 1; j++) { //check this...
                    joinedPredicate = joinedPredicate->join(rightHandSidePredicates.at(j + 1)); //
                }
            } else { joinedPredicate = rightHandSidePredicates.at(0); } //use single RHS predicate as result.

            //Project columns according to LHS rule head predicate.
            vector<int> indices;
            for (Parameter *it: dataLogObject->getRules().at(i)->returnHeadPredicate()->returnParameterVector()) {
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
            continueLoop += databaseObject.findMatch(dataLogObject->getRules().at(i)->returnHeadPredicate()->returnPredicateID())->unionOperator(joinedPredicate);
        }
    }
    cout << endl << "Schemes populated after ";
    cout << count << " passes through the Rules." << endl; //eventually take out the first endl.
}

void Interpreter::evaluateSCCs(vector<set<int>> SCCs) { //are we adding rules to the database object?
    cout << "Rule Evaluation" << endl;

    unsigned int count = 0;

    for (unsigned int i = 0; i < SCCs.size(); i++) {
        count = 0;
        cout << "SCC: ";
        string output = "";
        for(int rule : SCCs.at(i)) {
            output = output + "R" + to_string(rule) + ",";
        }
        output.pop_back();
        cout << output;
        cout << endl;

        if(SCCs.at(i).size() == 1 && forwardGraph.returnNode(SCCs.at(i)).returnSelfLoopBool() == false) {
            evaluateSingleRule(dataLogObject->getRules().at(*SCCs.at(i).begin()));
            count = 1;
        }
        else {
            vector<Relation*>rightHandSidePredicates;
            int continueLoop = 1;
            while(continueLoop > 0) {
                continueLoop = 0;
                count++;
                for (int dependency : SCCs.at(i)) {
                    continueLoop += evaluateSingleRule(dataLogObject->getRules().at(dependency));
                }
            }
        }

        cout << count << " passes: ";
        output = "";
        for(int rule : SCCs.at(i)) {
            output = output + "R" + to_string(rule) + ",";
        }
        output.pop_back();
        cout << output;
        cout << endl;
    }

}

int Interpreter::evaluateSingleRule (Rule* currentRule) {
    vector<Relation *> rightHandSidePredicates;
    currentRule->RulesToString();//Print out rule
    cout << ".";
    cout << endl;
    rightHandSidePredicates.clear();

    //Evaluate RHS Queries and push onto vector
    for (Predicate *it: currentRule->returnRightSidePredicates()) {
        rightHandSidePredicates.push_back(evaluateRules(it));
    }

    //Join Evaluated RHS queries.
    Relation *joinedPredicate;
    joinedPredicate = rightHandSidePredicates.at(0);
    if (rightHandSidePredicates.size() > 1) { //If more than 1 RHS predicate exists
        for (unsigned int j = 0; j < rightHandSidePredicates.size() - 1; j++) { //check this...
            joinedPredicate = joinedPredicate->join(rightHandSidePredicates.at(j + 1)); //
        }
    } else { joinedPredicate = rightHandSidePredicates.at(0); } //use single RHS predicate as result.

    //Project columns according to LHS rule head predicate.
    vector<int> indices;
    for (Parameter *it: currentRule->returnHeadPredicate()->returnParameterVector()) {
        for (unsigned int k = 0; k < joinedPredicate->returnHeader()->returnAttributes().size(); k++) {
            if (it->getStringOrID() == joinedPredicate->returnHeader()->returnAttributes().at(k)) {
                indices.push_back(k);
            }
        }
    }
    joinedPredicate = joinedPredicate->project(indices);

    //Rename according to head predicate header
    joinedPredicate = joinedPredicate->rename(currentRule->returnHeadPredicate()->returnVectorOfStrings());

    //populate schemes with new facts via union.
    return databaseObject.findMatch(currentRule->returnHeadPredicate()->returnPredicateID())->unionOperator(joinedPredicate);
}

void Interpreter::evaluateRulesOptimized(vector<Rule*> rulesVector) {
    //create dependency graphs
    createDependencyGraphs(rulesVector);
    reversedGraph.DFSForrestReverse(reversedGraph); //?? return type?
    //reversedGraph.postOrderToString();
    forwardGraph.DFSForrestForward(reversedGraph); //?? return type?
    evaluateSCCs(forwardGraph.returnSCCs());
}

void Interpreter::createDependencyGraphs(vector<Rule*> rulesVector) {
    //loop through and create a node for rules then add to them
        forwardGraph = graph();
        reversedGraph = graph();

    for (unsigned int i = 0; i < rulesVector.size(); i++) {
        Node newNode(i);
        forwardGraph.createNodes(i, newNode);
        reversedGraph.createNodes(i, newNode);
    }

    for (unsigned int i = 0; i < rulesVector.size(); i++) {
        for (unsigned int j = 0; j < rulesVector.size(); j++) {
            for (unsigned int k = 0; k < rulesVector.at(j)->returnRightSidePredicates().size(); k++) {
                if (rulesVector.at(i)->returnHeadPredicate()->returnPredicateID() == rulesVector.at(j)->returnRightSidePredicates().at(k)->returnPredicateID()) {
                    if (j == i) {
                        forwardGraph.addNodeDependency(j,i,true);
                        reversedGraph.addNodeDependency(i,j, true);
                    }
                    else {
                        forwardGraph.addNodeDependency(j,i,false);
                        reversedGraph.addNodeDependency(i,j, false);
                    }
                }
            }
        }
    }
    forwardGraph.dependencyGraphToString();
}

void Interpreter::runInterpreter() {
    addSchemes();
    addFacts();
    evaluateRulesOptimized(dataLogObject->getRules()); //fixed point algorithm function that takes in a vector rules --> SCC. for all scc evaluate via fixed point
    //databaseobject.toString?



    //addRulesToDB();
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



