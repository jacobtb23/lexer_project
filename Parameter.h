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
};
#endif //CS236MAIN_PARAMETER_H