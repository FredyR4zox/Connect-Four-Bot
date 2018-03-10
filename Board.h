#include <iostream>
#include <stdlib.h>
#include <array>
using namespace std;

class Board {

private:
	array< array <char,7> ,7> tab; //até fazermos um enum, 'x' e 'o' representam os jogadores e 'n' vazio
	int evaluation;
public:
	Board();
	~Board();
	array < array<char,7>,7> getBoard();	
	void printBoard();
	char searchToken(int i, int j);
	void chooseDropPlace(int l, int player);
};

void Board::chooseDropPlace(int l, int player) {
	for (int i = 6 ; i >= 0; i--) {
		if (tab[i][l] == 'x' || tab[i][l] == 'o')
			continue;
		else {
			if (player == 0) {
				tab[i][l] = 'x'; 
				return;
			}
			else {			
				tab[i][l] = 'o'; 
				return;
			}
		}
	//falta por uma exception:se uma coluna estiver cheia, não deixar por
	}
}
Board::Board() {
	for (int i = 0 ; i < 7 ; i++)
		for (int j = 0 ; j < 7 ; j++)
			tab[i][j] = '-';
		evaluation = 0;
}

array < array<char,7>,7> Board::getBoard() {
	return tab;
}

char Board::searchToken(int i, int j) {
	return tab[i][j];
}

void Board::printBoard() {
	cout << "+----------------+" << endl;
	cout << "+ 0 1 2 3 4 5 6  +" << endl;
	for (int i = 0 ; i < 7 ; i++) {
		cout << "| ";
		for (int j = 0 ; j < 7 ; j++)
			cout << tab[i][j] << " ";
			cout << " |" << endl; //o endl está fora do for de j's
	}
	cout << "+----------------+" << endl;
}
