#ifndef CS236MAIN_PARAMETER_H
#define CS236MAIN_PARAMETER_H
#include <vector>
#include <iostream>

using namespace std;

class Parameter
{
private:
    string stringOrId;
public:

    Parameter() {}
    ~Parameter() {}

    Parameter(string element) {
        this->stringOrId = element;
    }

    void ParameterToString() {
        cout << stringOrId;
    }

    string getStringOrID() {
        return stringOrId;
    }

    bool isString() { // This is used in the project 3 algorithm. Get further help.
        if(this->stringOrId.at(0) =='\'' ) {return true;}
        else {return false;}
    }
};
#endif //CS236MAIN_PARAMETER_H