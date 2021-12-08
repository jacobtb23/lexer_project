#ifndef CS236PROJECT_AGAIN_GRAPH_H
#define CS236PROJECT_AGAIN_GRAPH_H
#include "DataLog.h"
#include "Node.h"
#include <set>
#include <map>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

class graph {
private:

    vector<int> postOrder;
    map<int, Node> nodeMap; //key = ruleIndex, which maps to all rules (set of ruleIndex ints) that the rule(represented by ruleIndex) is adjacent to. Shouldnt this be ordered?
    vector<set<int>> SCCVector;

public:

    graph() {};
    ~graph() {};

    Node returnNode(set<int>SCCs) {
        return nodeMap.at(*SCCs.begin());
    }

    vector<set<int>> returnSCCs() {
        return SCCVector;
    }

    void depthFirstSearchSCCsHelper(Node currentNode,set<int>&emptySet) {
        nodeMap.at(currentNode.returnNodeId()).visit();
        if (currentNode.returnDependencySet().empty()) {
            postOrder.push_back(currentNode.returnNodeId());
            emptySet.insert(currentNode.returnNodeId());
        }
        else {
            for (int it: currentNode.returnDependencySet()) {
                if (nodeMap.at(it).isVisited() == false) {
                    depthFirstSearchSCCsHelper(nodeMap.at(it),emptySet); //what happens with empty set?
                }
            }
            postOrder.push_back(currentNode.returnNodeId());
            emptySet.insert(currentNode.returnNodeId());
        }
    }

    set<int>depthFirstSearchSCCs(Node currentNode) {
        set<int>SCCset;
        nodeMap.at(currentNode.returnNodeId()).visit();
        if (currentNode.returnDependencySet().empty()) {
            postOrder.push_back(currentNode.returnNodeId());
            SCCset.insert(currentNode.returnNodeId());
        }
        else {
            for (int it: currentNode.returnDependencySet()) {
                if (nodeMap.at(it).isVisited() == false) {
                    depthFirstSearchSCCsHelper(nodeMap.at(it), SCCset);
                }
            }
            postOrder.push_back(currentNode.returnNodeId());
            SCCset.insert(currentNode.returnNodeId());
        }
        return SCCset;
    }

    void depthFirstSearch(Node currentNode) {
        nodeMap.at(currentNode.returnNodeId()).visit();
        if (currentNode.returnDependencySet().empty()) {
            postOrder.push_back(currentNode.returnNodeId());
        }
        else {
            for (int it: currentNode.returnDependencySet()) {
                if (nodeMap.at(it).isVisited() == false) {
                    depthFirstSearch(nodeMap.at(it));
                }
            }
            postOrder.push_back(currentNode.returnNodeId());
        }
    }

    void DFSForrestForward(graph& reversedGraph){ //depth first search (finding post-order)
        set<int> emptySet;
        for(unsigned int i = reversedGraph.postOrder.size(); i > 0; i--) {
            if(nodeMap.at(reversedGraph.postOrder.at(i-1)).isVisited() == false){
                SCCVector.push_back(depthFirstSearchSCCs(nodeMap.at(reversedGraph.postOrder.at(i-1))));
            }
        }
        cout << "";
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
        if (selfLoop) {nodeMap.at(key).setSelfLoopBool(selfLoop);}
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
