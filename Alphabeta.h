#ifndef IA2_ALPHABETA_H
#define IA2_ALPHABETA_H

#include <array>
#include <limits>

#include "Node.h"

using namespace std;

//Protótipos
int alphabetaDecision(Node* node, int maxDistanceDepth, char myPiece, int& generatedNodes, int& visitedNodes);
int ABmaxValue(Node* node, int maxDistanceDepth, char myPiece, int alpha, int beta, int& generatedNodes, int& visitedNodes);
int ABminValue(Node* node, int maxDistanceDepth, char myPiece, int alpha, int beta, int& generatedNodes, int& visitedNodes);

int alphabetaDecision(Node* node, int maxDistanceDepth, char myPiece, int& generatedNodes, int& visitedNodes){
    int alpha = numeric_limits<int>::min(), beta = numeric_limits<int>::max();
    int v = ABmaxValue(node, maxDistanceDepth, myPiece, alpha, beta, generatedNodes, visitedNodes);
    
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

int ABmaxValue(Node* node, int maxDistanceDepth, char myPiece, int alpha, int beta, int& generatedNodes, int& visitedNodes){
    visitedNodes++;

    if(node->checkGameOver() || node->getDepth()>=maxDistanceDepth){
        int util = node->utility(myPiece);

        if(node->getDepth() <= 1)
            node->setScore(util);
        else
            delete node;

        return util;
    }
    
    int v = numeric_limits<int>::min();
    
    array<Node*, 7> descendants = node->makeDescendants(generatedNodes);

    for (int i = 0 ; i<7 && descendants[i]!=NULL ; i++) {
        v = max(v,ABminValue(descendants[i], maxDistanceDepth, myPiece, alpha, beta, generatedNodes, visitedNodes));
        
        if (v >= beta){

            if(node->getDepth() <= 1)
                node->setScore(v);
            else
                delete node;

            return v;
        }
        
        alpha = max(alpha, v);
    }
    
    if(node->getDepth() <= 1)
        node->setScore(v);
    else
        delete node;

    return v;
}

int ABminValue(Node* node, int maxDistanceDepth, char myPiece, int alpha, int beta, int& generatedNodes, int& visitedNodes){
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

    for (int i = 0 ; i<7 && descendants[i]!= NULL ; i++) {
        v = min(v,ABmaxValue(descendants[i], maxDistanceDepth, myPiece, alpha, beta, generatedNodes, visitedNodes));
        
        if (v <= alpha){

            if(node->getDepth() <= 1)
                node->setScore(v);
            else
                delete node;

            return v;
        }
        
        beta = min(beta, v);
    }
    
    if(node->getDepth() <= 1)
        node->setScore(v);
    else
        delete node;

    return v;
}

#endif