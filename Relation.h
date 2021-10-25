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

};
#endif //CS236PROJECT_AGAIN_RELATION_H
