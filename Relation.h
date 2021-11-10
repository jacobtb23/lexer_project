#ifndef CS236PROJECT_AGAIN_RELATION_H
#define CS236PROJECT_AGAIN_RELATION_H
#include <set>
#include <vector>
#include "Tuple.h"
#include <iostream>
#include "Header.h"
using namespace std;

class Relation {
private:
    set<Tuple> rows;
    string relationName;
    Header* relationHeader;

public:
    Relation(){}
    ~Relation(){}

    Relation(string relationName, Header* relationHeader) {
        this->relationName = relationName;
        this->relationHeader = relationHeader;
    }

    bool addTuple(Tuple tupleToAdd) {
        return rows.insert(tupleToAdd).second;
    };

    void printRelationRows() {
        for (Tuple it : rows) {
            it.toString();
        }
    }

    void printHeader() {
        relationHeader->toString();
    }

    Header* returnHeader() {
        return relationHeader;
    }

    void printRelationName() {
        cout << relationName;
    }

    bool tuplesPresent() {
        return rows.empty();
    }

    void printSetSize() {
        cout << rows.size();
    }

    void printFinalRelation (){
        for (Tuple it : rows) {
            cout << "  ";
            for (unsigned int j = 0; j < it.returnValues().size(); j++) {
                cout << relationHeader->returnAttributes().at(j) << "=";
                if (j == it.returnValues().size() - 1){
                    cout << it.returnValues().at(j);
                }
                else {cout << it.returnValues().at(j) << ", ";}
            }
            cout << endl;
        }

    }

    //The methods select, project, rename all return a new Relation object.
    Relation* selectIV(int index, string value) {
        //relation column and value to select...
        Relation* newRelation = new Relation();
        set<Tuple> newRelationSet;
        newRelation->relationHeader = this->relationHeader;
        newRelation->relationName = this->relationName;

        for(Tuple it : rows) {
           if (it.returnValues().at(index) == value) {
               newRelation->addTuple(it);
           }
        }
        return newRelation;
    }

    Relation* selectII(int index1, int index2) {
        //relation columns to select on same values...
        Relation* newRelation = new Relation();
        set<Tuple> newRelationSet;
        newRelation->relationHeader = this->relationHeader;
        newRelation->relationName = this->relationName;

        for(Tuple it : rows) {
            if (it.returnValues().at(index1) == it.returnValues().at(index2)) {
                newRelation->addTuple(it);
            }
        }
        return newRelation;
    }

    Relation* project(vector<int> columns) { //pass in a vector of column indices for reordering capability

        Relation* newRelation = new Relation();
        newRelation->relationName = this->relationName;

        //Header change
        vector<Parameter*> newHeaderAttributes;
        Parameter* parameterToAdd;

        for (unsigned int i = 0; i < columns.size(); i++) {
            parameterToAdd = new Parameter(relationHeader->returnAttributes().at(columns.at(i)));
            newHeaderAttributes.push_back(parameterToAdd);
        }

        Header* newHeader = new Header(newHeaderAttributes);

        for (Tuple it : rows) {
            vector<string> values;

            for (unsigned int i = 0; i < columns.size(); i++) {
                values.push_back(it.returnValues().at(columns.at(i)));
            }

            Tuple newTuple = Tuple(values);
            newRelation->addTuple(newTuple);
        }

        newRelation->relationHeader = newHeader;
        return newRelation;
    }

    Relation* rename(vector<string> names) { //rename all?
        Relation* newRelation = new Relation();
        newRelation->relationName = relationName;
        newRelation->rows = rows;

        vector<Parameter*> newHeaderAttributes;
        Parameter* parameterToAdd;

        for (unsigned int i = 0; i < names.size(); i++) {
            parameterToAdd = new Parameter(names.at(i));
            newHeaderAttributes.push_back(parameterToAdd);
        }

        Header* newHeader = new Header(newHeaderAttributes);
        newRelation->relationHeader = newHeader;
        return newRelation;
    }

    Relation* unionOperator() {} //bool has changed? -> see help slides

    Relation* join(Relation* relationToJoin) {
        //find unique columns vector<int>
        //find matching columns vector<pair of ints>
        Header* combinedHeader;
        vector<pair<int, int>> matchedHeaders;
        vector<string> uniqueHeaders;

        matchedHeaders = this->findMatchingHeaders(relationToJoin->returnHeader());
        uniqueHeaders = this->findUniqueHeaders(relationToJoin->returnHeader());
        combinedHeader = this->combineHeader(relationToJoin->returnHeader());
        Relation* joinedRelation = new Relation("joinedRelation",combinedHeader);

        for (Tuple it : this->rows) {
            for(Tuple it2 : relationToJoin->rows) {
                if(isJoinable(it,it2,matchedHeaders) == true) {
                    joinedRelation->addTuple(combineTuples(it, it2, combinedHeader, matchedHeaders));
                }
            }
        }
        return joinedRelation;
    }

    Header* combineHeader(Header* headerToJoin) {
        vector<Parameter*> attributes;
        Parameter* newParameter;

        vector<string> allHeaders = this->returnHeader()->returnAttributes();
        for (unsigned int i = 0; i < headerToJoin->returnAttributes().size(); i++) {
            allHeaders.push_back(headerToJoin->returnAttributes().at(i));
        }

        for (unsigned int i = 0; i < allHeaders.size(); i++) {
            for (unsigned int j = 0; j < allHeaders.size(); j++) {
                if (allHeaders.at(i) == allHeaders.at(j) && i != j) {
                    allHeaders.erase(allHeaders.begin() + j);
                }
            }
        }

        for (unsigned int i = 0; i < allHeaders.size(); i++) {
            newParameter = new Parameter(allHeaders.at(i));
            attributes.push_back(newParameter);
        }

        Header* newHeader = new Header(attributes);
        return newHeader;
    }

    bool isJoinable(Tuple Tuple1, Tuple Tuple2, vector<pair<int, int>> matchedHeaders) {
        bool isCombinable = true;
            for (pair<int,int> it : matchedHeaders) {
                if(Tuple1.returnValues().at(it.first) != Tuple2.returnValues().at(it.second)) {
                    isCombinable = false;
                }
            }
        return isCombinable;
    }

    Tuple combineTuples(Tuple Tuple1, Tuple Tuple2, Header* combinedHeader, vector<pair<int, int>> matchedHeaders) {
        vector<string> tupleVector;

        for(string it : Tuple1.returnValues()) {
            tupleVector.push_back(it);
        }

        if (matchedHeaders.size() == 0) {
            for (unsigned int i = 0; i < Tuple2.returnValues().size(); i++) {
                tupleVector.push_back(Tuple2.returnValues().at(i));
            }
        }
        else {
            for (unsigned int i = 0; i < Tuple2.returnValues().size(); i++) {
                for (unsigned int j = 0; j < matchedHeaders.size(); j++) {
                    if ( i != matchedHeaders.at(j).second) {
                        tupleVector.push_back(Tuple2.returnValues().at(i));
                    }
                }
            }
        }

        Tuple combinedTuple = Tuple(tupleVector);
        return combinedTuple;

    } //do this like you do the header.

    vector<string> findUniqueHeaders(Header* headerToCombine) {
        vector<string> uniqueHeaders;
        vector<string> allHeaders = this->returnHeader()->returnAttributes();
        for (unsigned int i = 0; i < headerToCombine->returnAttributes().size(); i++) {
            allHeaders.push_back(headerToCombine->returnAttributes().at(i));
        }

        for (unsigned int i = 0; i < allHeaders.size(); i++) {
            unsigned int count = 0;
            for (unsigned int j = 0; j < allHeaders.size(); j++) {
                if (allHeaders.at(i) == allHeaders.at(j)) {
                    count++;
                }
            }
            if (count == 1) {
                uniqueHeaders.push_back(allHeaders.at(i));
            }
        }
        return uniqueHeaders;
    }

    vector<pair<int, int>> findMatchingHeaders(Header* headerToCompare) {
        vector<pair<int, int>> matchedPairs;
        pair<int, int> matchingTuple;
        for (unsigned int i = 0; i < this->returnHeader()->returnAttributes().size(); i++) {
            for (unsigned int j = 0; j < headerToCompare->returnAttributes().size(); j++) {
                if (this->returnHeader()->returnAttributes().at(i) == headerToCompare->returnAttributes().at(j)) {
                    matchingTuple.first = i;
                    matchingTuple.second = j;
                    matchedPairs.push_back(matchingTuple);
                }
            }
        }
        return matchedPairs;
    }


};
#endif //CS236PROJECT_AGAIN_RELATION_H
