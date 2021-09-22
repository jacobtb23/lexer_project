#ifndef CS236MAIN_PARAMETER_H
#define CS236MAIN_PARAMETER_H
#include <vector>
#include <iostream>
#include "DataLog.h"

using namespace std;

class Parameter
{
private:
    string stringOrId;
public:

    Parameter();
    ~Parameter();

    Parameter(string element) {
        this->stringOrId = element;
    }

    void toString();
};
#endif //CS236MAIN_PARAMETER_H
