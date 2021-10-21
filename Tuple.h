#ifndef CS236PROJECT_AGAIN_TUPLE_H
#define CS236PROJECT_AGAIN_TUPLE_H
#include <vector>
using namespace std;

class Tuple {
private:
    vector<string> values; //Pointers?

public:
    Tuple();
    ~Tuple(){}

    Tuple(vector<string> values) {
        for(unsigned int i = 0; i < values.size(); i++){
            this->values.push_back(values.at(i));
        }
    }

    void toString() {
        cout << "(";
        string output = "";
        for(string it : values) {
            output = output + it + ",";
        }
        output.pop_back();
        output = output + ")";
        cout << output << endl;
    }

    bool operator< (const Tuple & secondTuple) const {
        //Compare this-> tuple to other secondTuple
        return values < secondTuple.values; //
    }

    vector<string> returnValues () {
        return values;
    }
};
#endif //CS236PROJECT_AGAIN_TUPLE_H
