#ifndef CS236PROJECT_AGAIN_PREDICATE_H
#define CS236PROJECT_AGAIN_PREDICATE_H
#include "Parameter.h"
#include <vector>
using namespace std;

class Predicate
{
private:
    string PredicateId;
    vector<Parameter*> parameterVector;

public:
    Predicate() {}
    ~Predicate() {
        for (Parameter *deletePointer : parameterVector) {
            delete deletePointer;
        }
        parameterVector.clear();
    }

    Predicate(string PredicateId, vector<Parameter*> parameterVector) {
        this->PredicateId = PredicateId;

        for(Parameter* i : parameterVector) {
            this->parameterVector.push_back(i);
        }
    }

    void PredicateToString() {
        cout << PredicateId << "(";
        for (unsigned int i = 0; i < parameterVector.size(); i++) {
            parameterVector.at(i)->ParameterToString();
            if (i != parameterVector.size() - 1) {
                cout << ",";
            }
        }
        cout << ")";
    }
};
#endif //CS236PROJECT_AGAIN_PREDICATE_H
