#include <limits>

using namespace std;

//Protótipos
int alphabetaDecision(Node* node, int maxDistanceDepth, char myPiece, int& generatedNodes, int& visitedNodes);
int ABmaxValue(Node* node, int maxDistanceDepth, char myPiece, int alpha, int beta, int& generatedNodes, int& visitedNodes);
int ABminValue(Node* node, int maxDistanceDepth, char myPiece, int alpha, int beta, int& generatedNodes, int& visitedNodes);

int alphabetaDecision(Node* node, int maxDistanceDepth, char myPiece, int& generatedNodes, int& visitedNodes){
    int alpha = numeric_limits<int>::min(), beta = numeric_limits<int>::max();
    int v = ABmaxValue(node, maxDistanceDepth, myPiece, alpha, beta, generatedNodes, visitedNodes);
    
    array<Node*, 7> children = node->getChildren();
    for(int i=0; i<7 && children[i]!=NULL; i++)
        if(v == children[i]->getScore())
            return children[i]->getMove();

    return children[0]->getMove();
}

int ABmaxValue(Node* node, int maxDistanceDepth, char myPiece, int alpha, int beta, int& generatedNodes, int& visitedNodes){
    visitedNodes++;

    if(node->checkGameOver() || maxDistanceDepth<=0){
        int util = node->utility(myPiece);
        node->setScore(util);
        return util;
    }
    
    int v = numeric_limits<int>::min();
    
    array<Node*, 7> descendants;
    if (node->getChildren()[0] != NULL)
        descendants = node->getChildren();
    else
        descendants = node->makeDescendants(generatedNodes);

    for (int i = 0 ; i<7 && descendants[i]!= NULL ; i++) {
        v = max(v,ABminValue(descendants[i], maxDistanceDepth-1, myPiece, alpha, beta, generatedNodes, visitedNodes));
        
        if (v >= beta){
            node->setScore(v);
            return v;
        }
        
        alpha = max(alpha, v);
    }
    
    node->setScore(v);
    
    return v;
}

int ABminValue(Node* node, int maxDistanceDepth, char myPiece, int alpha, int beta, int& generatedNodes, int& visitedNodes){
    visitedNodes++;

    if(node->checkGameOver() || maxDistanceDepth<=0){
        int util = node->utility(myPiece);
        node->setScore(util);
        return util;
    }

    int v = numeric_limits<int>::max();

    array<Node*, 7> descendants;
    if (node->getChildren()[0] != NULL)
        descendants = node->getChildren();
    else
        descendants = node->makeDescendants(generatedNodes);

    for (int i = 0 ; i<7 && descendants[i]!= NULL ; i++) {
        v = min(v,ABmaxValue(descendants[i], maxDistanceDepth-1, myPiece, alpha, beta, generatedNodes, visitedNodes));
        
        if (v <= alpha){
            node->setScore(v);
            return v;
        }
        
        beta = min(beta, v);
    }
    
    node->setScore(v);
    
    return v;
}