#ifndef CS236PROJECT_AGAIN_TUPLE_H
#define CS236PROJECT_AGAIN_TUPLE_H
#include <vector>
using namespace std;

class Tuple {
private:
    vector<string> values; //Pointers?

public:
    Tuple(){}
    ~Tuple(){}

    bool operator< (const Tuple & secondTuple) const {
        //Compare this-> tuple to other secondTuple
        return values < secondTuple.values; //
    }
};
#endif //CS236PROJECT_AGAIN_TUPLE_H
