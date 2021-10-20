#ifndef CS236PROJECT_AGAIN_DATABASE_H
#define CS236PROJECT_AGAIN_DATABASE_H
#include <map>
#include "Relation.h"
#include "Parameter.h"
#include "Tuple.h"
using namespace std;

class Database {
private:
    //map from name "string" to relation... We do this because we want to look up relations by name.
    map<string, Relation> DataBaseMap;
public:
    Database() {};
    ~Database() {};

    void addRelation(string relationName,Relation newRelation){
        this->DataBaseMap.insert({relationName, newRelation});
    }

    bool addTupleToRelation(string factName, Tuple newTuple){
        return DataBaseMap.at(factName).addTuple(newTuple);
    }

    void toString() {
        for(auto it = DataBaseMap.begin(); it != DataBaseMap.cend(); it++) {
            cout << it->first;
            it->second.printHeader();
            it->second.printRelationRows();
            cout << endl;
        }
    }


};
#endif //CS236PROJECT_AGAIN_DATABASE_H
