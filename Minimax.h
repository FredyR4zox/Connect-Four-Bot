#include <limits>

#include "Node.h"

using namespace std;

int minimaxDecision(Node& node, int maxDistanceDepth, char myPiece);
int maxValue(Node& node, int maxDistanceDepth, char myPiece);
int minValue(Node& node, int maxDistanceDepth, char myPiece);

int minimaxDecision(Node& node, int maxDistanceDepth, char myPiece){
	int v = maxValue(node, maxDistanceDepth, myPiece);
	array<Node*, 7> children = node.getChildren();
	for(int i=0; i<7 && children[i]!=NULL; i++)
		if(v == children[i]->getScore())
			return children[i]->getMove();

	return children[0]->getMove();
}

int maxValue(Node& node, int maxDistanceDepth, char myPiece){
	if(node.checkGameOver() || maxDistanceDepth<=0)
		return node.utility(myPiece);

	int v = numeric_limits<int>::min();

	array<Node*, 7> descendants;
	if(node.getChildren()[0] != NULL)
		descendants = node.getChildren();
	else
		descendants = node.makeDescendants();

	maxDistanceDepth--;
	for(int i=0; i<7 && descendants[i]!=NULL; i++)
		v = max(v, minValue(*descendants[i], maxDistanceDepth, myPiece));

	node.setScore(v);

	return v;
}

int minValue(Node& node, int maxDistanceDepth, char myPiece){
	if(node.checkGameOver() || maxDistanceDepth<=0)
		return node.utility(myPiece);

	int v = numeric_limits<int>::max();

	array<Node*, 7> descendants;
	if(node.getChildren()[0] != NULL)
		descendants = node.getChildren();
	else
		descendants = node.makeDescendants();

	maxDistanceDepth--;
	for(int i=0; i<7 && descendants[i]!=NULL; i++)
		v = min(v, maxValue(*descendants[i], maxDistanceDepth, myPiece));

	node.setScore(v);

	return v;
}