#ifndef CS236PROJECT_AGAIN_RELATION_H
#define CS236PROJECT_AGAIN_RELATION_H
#include <set>
#include <vector>
#include "Tuple.h"
using namespace std;

class Relation {
private:
    set<Tuple*> associatedTuples;
public:
    Relation(){}
    ~Relation(){}

    //The methods select, project, rename all return a new Relation object.
    Relation selectII(){
        //relation columns to select on same values...
    }
    Relation selectIV(){
        //relation column and value to select...
    }
    Relation project(vector<int> columns){ //pass in a vector of columns for reordering capability
        //the columns to keep...
        //Note that the list of indices given to project specifies the new order of the columns in the new relation it returns.
    }
    Relation rename(){
        //defines the new header...
    }

};
#endif //CS236PROJECT_AGAIN_RELATION_H
