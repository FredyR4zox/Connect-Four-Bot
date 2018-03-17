#include <limits>

#include "Node.h"

using namespace std;

int minimaxDecision(Node& node, int maxDistanceDepth);
int maxValue(Node& node, int maxDistanceDepth);
int minValue(Node& node, int maxDistanceDepth);

int minimaxDecision(Node& node, int maxDistanceDepth){
	int v = maxValue(node, maxDistanceDepth);
	array<Node*, 7> children = node.getChildren();
	for(int i=0; i<7 && children[i]!=NULL; i++)
		if(v == children[i]->getScore())
			return children[i]->getMove();

	return children[0]->getMove();
}

int maxValue(Node& node, int maxDistanceDepth){
	if(node.checkGameOver() || maxDistanceDepth<=0)
		return 1;

	int v = numeric_limits<int>::min();

	array<Node*, 7> descendants;
	if(node.getChildren()[0] != NULL)
		descendants = node.getChildren();
	else
		descendants = node.makeDescendants();

	maxDistanceDepth--;
	for(int i=0; i<7 && descendants[i]!=NULL; i++)
		v = max(v, minValue(*descendants[i], maxDistanceDepth));

	return v;
}

int minValue(Node& node, int maxDistanceDepth){
	if(node.checkGameOver() || maxDistanceDepth<=0)
		return 1;

	int v = numeric_limits<int>::max();

	array<Node*, 7> descendants;
	if(node.getChildren()[0] != NULL)
		descendants = node.getChildren();
	else
		descendants = node.makeDescendants();

	maxDistanceDepth--;
	for(int i=0; i<7 && descendants[i]!=NULL; i++)
		v = min(v, maxValue(*descendants[i], maxDistanceDepth));

	return v;
}