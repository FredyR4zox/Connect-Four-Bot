#include <limits>

#include "Node.h"

using namespace std;

int minimaxDecision(Node* node, int maxDistanceDepth, char myPiece, int& generatedNodes, int& visitedNodes);
int maxValue(Node* node, int maxDistanceDepth, char myPiece, int& generatedNodes, int& visitedNodes);
int minValue(Node* node, int maxDistanceDepth, char myPiece, int& generatedNodes, int& visitedNodes);

int minimaxDecision(Node* node, int maxDistanceDepth, char myPiece, int& generatedNodes, int& visitedNodes){
    int v = maxValue(node, maxDistanceDepth, myPiece, generatedNodes, visitedNodes);

    array<Node*, 7> children = node->getChildren();
    for(int i=0; i<7 && children[i]!=NULL; i++)
        if(v == children[i]->getScore())
            return children[i]->getMove();

    return children[0]->getMove();
}

int maxValue(Node* node, int maxDistanceDepth, char myPiece, int& generatedNodes, int& visitedNodes){
    visitedNodes++;

    if(node->checkGameOver() || maxDistanceDepth<=0){
        int util = node->utility(myPiece);
        node->setScore(util);
        return util;
    }

    int v = numeric_limits<int>::min();

    array<Node*, 7> descendants;
    if(node->getChildren()[0] != NULL)
        descendants = node->getChildren();
    else
        descendants = node->makeDescendants(generatedNodes);

    for(int i=0; i<7 && descendants[i]!=NULL; i++)
        v = max(v, minValue(descendants[i], maxDistanceDepth-1, myPiece, generatedNodes, visitedNodes));

    node->setScore(v);

    return v;
}

int minValue(Node* node, int maxDistanceDepth, char myPiece, int& generatedNodes, int& visitedNodes){
    visitedNodes++;

    if(node->checkGameOver() || maxDistanceDepth<=0){
        int util = node->utility(myPiece);
        node->setScore(util);
        return util;
    }

    int v = numeric_limits<int>::max();

    array<Node*, 7> descendants;
    if(node->getChildren()[0] != NULL)
        descendants = node->getChildren();
    else
        descendants = node->makeDescendants(generatedNodes);

    for(int i=0; i<7 && descendants[i]!=NULL; i++)
        v = min(v, maxValue(descendants[i], maxDistanceDepth-1, myPiece, generatedNodes, visitedNodes));

    node->setScore(v);

    return v;
}