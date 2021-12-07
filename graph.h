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
    vector<set<int>> SCCVector;
    set<int> SCCs;

public:

    graph() {};
    ~graph() {};

    void depthFirstSearch(Node currentNode) {
        SCCs.clear(); //scc's clearing?
        nodeMap.at(currentNode.returnNodeId()).visit();
        if (currentNode.returnDependencySet().empty()) {
            SCCs.insert(currentNode.returnNodeId());
            postOrder.push_back(currentNode.returnNodeId());
        }
        else {
            for (int it: currentNode.returnDependencySet()) {
                if (nodeMap.at(it).isVisited() == false) {
                    depthFirstSearch(nodeMap.at(it)); //aren't dependent on anything, then evaluate according to order
                }
            }

            SCCs.insert(currentNode.returnNodeId()); //Not working. Reverse postorder? Should I add in the same place as I do the postorder? //Should things already visited be included?
            postOrder.push_back(currentNode.returnNodeId()); //would this be messing up my postorder?
        }
    }

    void DFSForrestForward(graph& reversedGraph){ //depth first search (finding post-order)
        vector<int>::reverse_iterator it = reversedGraph.postOrder.rbegin();
        while(it != reversedGraph.postOrder.rend()) {
            if(nodeMap.at(*it).isVisited() == false){
                depthFirstSearch(nodeMap.at(*it)); //STD out of range on last iteration
            }
            it++;
            SCCVector.push_back(SCCs);
        }
    }

    void DFSForrestReverse(graph& reverseGraph) {
        for(auto it = nodeMap.begin(); it != nodeMap.cend(); it++) { //loop through it's children
            if(it->second.isVisited() == false){
                depthFirstSearch(it->second);
            }
        }
    }

    void addNodeDependency(int key, int dependency, bool selfLoop) {
        nodeMap.at(key).addDependency(dependency);
        nodeMap.at(key).setSelfLoopBool(selfLoop);
    }

    void createNodes(int key, Node newNode) {
        nodeMap.insert(pair<int,Node> (key,newNode));
    }

    void dependencyGraphToString() {
        cout << "Dependency Graph" << endl;
        for(auto it = nodeMap.begin(); it != nodeMap.cend(); it++) {
            cout << "R" << it->first << ":";
            if (it->second.noDependencies() == true) {
                cout << endl;
            }
            else {
                it->second.toString();
                cout << endl;
            }
        }
        cout << endl;
    }

    void postOrderToString() {
        for (int it : postOrder) {
            cout << it << endl;
        }
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
