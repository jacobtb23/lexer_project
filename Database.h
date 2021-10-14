#ifndef CS236PROJECT_AGAIN_DATABASE_H
#define CS236PROJECT_AGAIN_DATABASE_H
#include <map>
#include "Relation.h"
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
};
#endif //CS236PROJECT_AGAIN_DATABASE_H
