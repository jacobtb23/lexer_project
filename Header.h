#ifndef CS236PROJECT_AGAIN_HEADER_H
#define CS236PROJECT_AGAIN_HEADER_H
#include <vector>
#include "Parameter.h"
using namespace std;

class Header {
private:
    vector<string> attributes; //Pointers?
public:
    Header(){}
    ~Header(){}
    
    Header(vector<Parameter*> attributes) {
        for (unsigned int i = 0; i < attributes.size(); i++) {
            this->attributes.push_back(attributes.at(i)->getStringOrID());
        }
    }

    void toString() {
        cout << "{";
        for(string it : attributes){
            cout << it;
        }
        cout << "}";
        cout << endl;
    }
};
#endif //CS236PROJECT_AGAIN_HEADER_H
