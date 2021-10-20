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

    //The methods select, project, rename all return a new Relation object.
    Relation selectII() {
        //relation columns to select on same values...
    }
    Relation selectIV() {
        //relation column and value to select...
    }
    Relation project(vector<int> columns) { //pass in a vector of column indices for reordering capability
        //the columns to keep...
        //Note that the list of indices given to project specifies the new order of the columns in the new relation it returns.
    }
    Relation rename(vector<string> names) {
        //defines the new header...
    }

};
#endif //CS236PROJECT_AGAIN_RELATION_H
