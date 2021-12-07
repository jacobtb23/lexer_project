#ifndef CS236PROJECT_AGAIN_NODE_H
#define CS236PROJECT_AGAIN_NODE_H
#include <set>
#include <string>
using namespace std;

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
    void toString() {
        string output = "";
        for (int it : dependencies) {
            output = output + "R" + to_string(it) + ",";
        }
        output.pop_back();
        cout << output;
    }
    bool noDependencies() {
        return dependencies.empty();
    }
    void visit() {
        visited = true;
    }
    bool isVisited() {
        return visited;
    }
    int returnNodeId() {
        return nodeID;
    }
    set<int> returnDependencySet() {
        return dependencies;
    }
};
#endif //CS236PROJECT_AGAIN_NODE_H
