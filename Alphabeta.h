#include <limits>


using namespace std;

//Protótipos
int alphabetaDecision(Node& node, int maxDistanceDepth, char myPiece, int alpha, int beta);
int ABmaxValue(Node& node, int maxDistanceDepth, char myPiece, int alpha, int beta);
int ABminValue(Node& node, int maxDistanceDepth, char myPiece, int alpha, int beta);

/*O alphabeta é a mesma cena que o minimax, só que o max e o min levam o alpha e o beta a passear com eles.
o alpha tem o valor máximo nos Nodes MAX e o beta tem o valor minimo dos Nodes MIN, assim consegue-se cortar sub arvores que nao interessam*/

//valores default para o alpha e beta = 0 porque esta funçao nao e recursiva e precisa das variaveis temporarias alpha e beta
//assim podes omitir o ,...,0,0) ao invocar a funçao
int alphabetaDecision(Node& node, int maxDistanceDepth, char myPiece, int alpha, int beta) {
	int v = ABmaxValue(node,maxDistanceDepth,myPiece, alpha, beta);
	
	array<Node*, 7> children = node.getChildren();
	for(int i=0; i<7 && children[i]!=NULL; i++)
		if(v == children[i]->getScore())
			return children[i]->getMove();

	return children[0]->getMove();	
}

int ABmaxValue(Node& node, int maxDistanceDepth, char myPiece, int alpha, int beta) {
	if (node.checkGameOver() || maxDistanceDepth <= 0)
			return node.utility(myPiece);
	
	int v = numeric_limits<int>::min();
	
	array<Node*, 7> descendants;
	if (node.getChildren()[0] != NULL)
		descendants = node.getChildren();
	else
		descendants = node.makeDescendants();

	maxDistanceDepth--;
	for (int i = 0 ; i<7 && descendants[i]!= NULL ; i++) {
		v = max(v,ABminValue(*descendants[i], maxDistanceDepth, myPiece, alpha, beta));
		if (v >= beta)
			return v;
		alpha = max(alpha,v);
	}
	node.setScore(v);
	return v;
}

int ABminValue(Node& node, int maxDistanceDepth, char myPiece, int alpha, int beta) {
	if (node.checkGameOver() || maxDistanceDepth<=0)
		return node.utility(myPiece);

	int v = numeric_limits<int>::max();

	array<Node*, 7> descendants;

	if (node.getChildren()[0] != NULL)
		descendants = node.getChildren();
	else
		descendants = node.makeDescendants();

	maxDistanceDepth--;
	
	for (int i = 0 ; i<7 && descendants[i]!= NULL ; i++) {
		v = min(v,ABmaxValue(*descendants[i], maxDistanceDepth, myPiece, alpha, beta));
		if (v <= alpha)
			return v;
		beta = min(beta,v);
	}
	node.setScore(v);
	return v;
}