#ifndef CS236PROJECT_AGAIN_NODE_H
#define CS236PROJECT_AGAIN_NODE_H
#include <set>
class Node {
private:
    bool visited = false;
    bool selfLoop = false;
    set<int> dependencies;
    int nodeID;
public:
    Node(int key){
        nodeID = key;
    }
    ~Node(){}
    void setSelfLoopBool(bool selfLoop) {
        this->selfLoop = selfLoop;
    }
    void addDependency(int dependency) {
        dependencies.insert(dependency);
    }
};
#endif //CS236PROJECT_AGAIN_NODE_H
