#ifndef CS236PROJECT_AGAIN_GRAPH_H
#define CS236PROJECT_AGAIN_GRAPH_H
#include "DataLog.h"
#include "Node.h"
#include <set>
#include <map>
#include <vector>
#include <stack>

using namespace std;

class graph {
private:
    vector<int> postOrder;
    stack<int> reversedPostorder;
    map<int, Node> nodeMap; //key = ruleIndex, which maps to all rules (set of ruleIndex ints) that the rule(represented by ruleIndex) is adjacent to. Shouldnt this be ordered?
    vector<set<int>> SCCs;

public:

    graph() {};
    ~graph() {};
    void depthFirstSearch(){}
    void DFSForrestPO(){} //depth first search (finding post-order)
    void DFSForrestSCC(){} //depth first search (finding SCC's)
    void addNodeDependency(int key, int dependency, bool selfLoop) {
        nodeMap.at(key).addDependency(dependency);
        nodeMap.at(key).setSelfLoopBool(selfLoop);
    }
    void createNodes(int key, Node newNode) {
        nodeMap.insert(pair<int,Node> (key,newNode));
    }
};

//represents relations between rules
//make an edge going from vx to vy if rule #x depends on rule #y.
//you already have a vector of rules that gives the indexes as node numbers
//evaluate the SCC that doesn't depend on anything first.
//sink forward = source reverse (determined by post order, the node that finishes last must be in a source scc)
//So we do a DFS Forrest on the reversed graph
//The order in which we solve the SCC's depends on the postorder
//store indexes of SCC components within a set
#endif //CS236PROJECT_AGAIN_GRAPH_H
