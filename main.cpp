#include <iostream>
#include <stdlib.h>
#include "Board.h"
#include "Algorithm.h"
using namespace std;
/*Vais metendo os tokens com o numero da coluna e enter e para sair fazes 7+Enter*/
int main(void) {
	Board *x = new Board();
	int inp = 0;
	int player = 0;
	x->printBoard();
	while (1)
	{
		cout << "Introduza a linha a inserir:" << endl;
		cin >> inp;
		system("clear");
		x->chooseDropPlace(inp,player);
		x->printBoard();
		if (player == 0) player = 1; else player = 0;
		if (inp == 7) break;
	}
	avaliateBoard(x);
	return 0;

}