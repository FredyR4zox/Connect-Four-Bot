#ifndef IA2_MINIMAX_H
#define IA2_MINIMAX_H

#include <array>
#include <limits>

#include "Node.h"

using namespace std;

int minimaxDecision(Node* node, int maxDistanceDepth, char myPiece, int& generatedNodes, int& visitedNodes);
int maxValue(Node* node, int maxDistanceDepth, char myPiece, int& generatedNodes, int& visitedNodes);
int minValue(Node* node, int maxDistanceDepth, char myPiece, int& generatedNodes, int& visitedNodes);

int minimaxDecision(Node* node, int maxDistanceDepth, char myPiece, int& generatedNodes, int& visitedNodes){
    int v = maxValue(node, maxDistanceDepth, myPiece, generatedNodes, visitedNodes);
    int bestMove;

    array<Node*, 7> descendants = node->getChildren();
    for(int i=0; i<7 && descendants[i]!=NULL; i++){
        if(v == descendants[i]->getScore()){
            bestMove = descendants[i]->getMove();
            
            //Delete the descendants so that we dont have memory leaks
            for(int j=0; j<7 && descendants[j]!=NULL; j++)
                delete descendants[j];

            return bestMove;
        }
    }

    //In case a bug occurs (we dont find the v in any of the children's score)
    bestMove = descendants[0]->getMove();

    for(int i=0; i<7 && descendants[i]!=NULL; i++)
        delete descendants[i];


    return bestMove;
}

int maxValue(Node* node, int maxDistanceDepth, char myPiece, int& generatedNodes, int& visitedNodes){
    visitedNodes++;

    //If the game is over OR we reached maximum depth
    if(node->checkGameOver() || node->getDepth()>=maxDistanceDepth){
        int util = node->utility(myPiece);

        //If the node's depth is less or equal to one, we want want to delete it
        //because we don't want to delete the root node and we want it's children
        //not to get deleted because we will need to search thru them in the minimaxDecision
        //else we will not need that node anymore, so we delete it
        if(node->getDepth() <= 1)
            node->setScore(util);
        else
            delete node;

        return util;
    }

    int v = numeric_limits<int>::min();

    array<Node*, 7> descendants = node->makeDescendants(generatedNodes);

    for(int i=0; i<7 && descendants[i]!=NULL; i++)
        v = max(v, minValue(descendants[i], maxDistanceDepth, myPiece, generatedNodes, visitedNodes));

    if(node->getDepth() <= 1)
        node->setScore(v);
    else
        delete node;

    return v;
}

int minValue(Node* node, int maxDistanceDepth, char myPiece, int& generatedNodes, int& visitedNodes){
    visitedNodes++;

    if(node->checkGameOver() || node->getDepth()>=maxDistanceDepth){
        int util = node->utility(myPiece);

        if(node->getDepth() <= 1)
            node->setScore(util);
        else
            delete node;

        return util;
    }

    int v = numeric_limits<int>::max();

    array<Node*, 7> descendants = node->makeDescendants(generatedNodes);

    for(int i=0; i<7 && descendants[i]!=NULL; i++)
        v = min(v, maxValue(descendants[i], maxDistanceDepth, myPiece, generatedNodes, visitedNodes));

    if(node->getDepth() <= 1)
        node->setScore(v);
    else
        delete node;

    return v;
}

#endif