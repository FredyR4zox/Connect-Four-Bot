#include <stdlib.h>
#include <array>
using namespace std;

class Board {

private:
	array< array <char,7> ,7> tab;
	char lastMove;
	int value; 
public:
	Board();
	~Board();
	array < array<char,7>,7> getBoard();	
	void printBoard();
	char searchToken(int i, int j);
	void chooseDropPlace(int l, int player);
};

//Escolhe a coluna onde se põe o token
void Board::chooseDropPlace(int l, int player) {
	for (int i = 6 ; i >= 0; i--) {
		if (tab[i][l] == 'x' || tab[i][l] == 'o')
			continue;
		else {
			else if (player == 0) {
				tab[i][l] = 'x'; 
				return;
			}
			else {			
				tab[i][l] = 'o'; 
				return;
			}
		} //falta fazer "exception" para nao deixar por numa coluna cheia
	}
}

//Construtor default (void) do board
Board::Board() {
	for (int i = 0 ; i < 7 ; i++)
		for (int j = 0 ; j < 7 ; j++)
			tab[i][j] = '-';
		evaluation = 0;
}

//Getter do board
array < array<char,7>,7> Board::getBoard() {
	return tab;
}

//Retorna o token na posição (i,j)
char Board::searchToken(int i, int j) {
	return tab[i][j];
}

//Imprime o tabuleiro (já formatado/pronto!)
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
