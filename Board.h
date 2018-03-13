#include <stdlib.h>
#include <array>
using namespace std;

class Board {

private:
	array< array <char,7> ,6> tab;
	char lastMove;
	int value; 
public:
	Board();
	~Board();
	array < array<char,7>,6> getBoard();	
	void printBoard();
	char searchToken(int i, int j);
	void chooseDropPlace(int l, int player);
	void calcAssignPoints(string h[6][4], string v[7][4], string d1[7][4], string d2[7][4]);
};

//Escolhe a coluna onde se põe o token
void Board::chooseDropPlace(int l, int player) {
	for (int i = 5 ; i >= 0; i--) {
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
		} //falta fazer "exception" para nao deixar por numa coluna cheia
	}
}

//Construtor default (void) do board
Board::Board() {
	for (int i = 0 ; i < 6 ; i++)
		for (int j = 0 ; j < 7 ; j++)
			tab[i][j] = '-';
		value = 0;
}

//Getter do board
array < array<char,7>,6> Board::getBoard() {
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
	for (int i = 0 ; i < 6 ; i++) {
		cout << "| ";
		for (int j = 0 ; j < 7 ; j++)
			cout << tab[i][j] << " ";
		cout << " |" << endl; //o endl está fora do for de j's
	}
	cout << "+----------------+" << endl;
}

//Também se pode por esta funçao como parte da board
void Board::calcAssignPoints(string h[6][4], string v[7][4], string d1[7][4], string d2[7][4]) {
	/*
		Pontuação:
		+512 para vitória para o 'x' 
		-512 para vitória prar o 'o'
		0 para o empate
		-50 para 3 'o' e nenhum 'x'
		-10 para 2 'o' e nenhum 'x'
		-1 para 1 'o' e nenhum 'x'
		0 para nenhum token ou 'x' e 'o' mistos
		1 para um 'x' e nenhum 'o'
		10 para dois 'x' e nenhum 'o'
		50 para tres 'x' e nenhum 'o'
	Aĺém disto soma-se um valor pré-definido dependendo do turno atual
	(+16 for X, -16 for O)
	*/

int total = 0;

	//Calcular pontos horizontais
	for (int i = 0 ; i < 7 ; i++) {
		for (int j = 0 ; j < 4 ; j++) {
			if (h[i][j] == "xxxx") {
				total += 512;
				continue;
			}
			else if (h[i][j] == "oooo") {
				total -= 512;
				continue;
			}
			else if (h[i][j] == "ooo-" || h[i][j] == "-ooo") {
				total -= 50;
				continue;
			}
			else if (h[i][j] == "oo--" || h[i][j] == "-oo-" || h[i][j] == "--oo") {
				total -= 10;
				continue;
			}
			else if (h[i][j] == "o---" || h[i][j] == "-o--" || h[i][j] == "--o-" || h[i][j] == "---o") {
				total -= 1;
				continue;
			}
			else if (h[i][j] == "----" || h[i][j] == "xoxo" || h[i][j] == "oxox") {
				continue;
			}
			else if (h[i][j] == "x---" || h[i][j] == "-x--" || h[i][j] == "--x-" || h[i][j] == "---x") {
				total += 1;
				continue;
			}
			else if (h[i][j] == "xx--" || h[i][j] == "-xx-" || h[i][j] == "--xx") {
				total += 10;
				continue;
			}
			else if (h[i][j] == "xxx-" || h[i][j] == "-xxx") {
				total += 50;
				continue;
			}
		}		

		//Calcular pontos verticais
		for (int i = 0 ; i < 7 ; i++) {
		for (int j = 0 ; j < 4 ; j++) {
			if (v[i][j] == "xxxx") {
				total += 512;
				continue;
			}
			else if (v[i][j] == "oooo") {
				total -= 512;
				continue;
			}
			else if (v[i][j] == "ooo-" || v[i][j] == "-ooo") {
				total -= 50;
				continue;
			}
			else if (v[i][j] == "oo--" || v[i][j] == "-oo-" || v[i][j] == "--oo") {
				total -= 10;
				continue;
			}
			else if (v[i][j] == "o---" || v[i][j] == "-o--" || v[i][j] == "--o-" || v[i][j] == "---o") {
				total -= 1;
				continue;
			}
			else if (v[i][j] == "----" || v[i][j] == "xoxo" || v[i][j] == "oxox") {
				continue;
			}
			else if (v[i][j] == "x---" || v[i][j] == "-x--" || v[i][j] == "--x-" || v[i][j] == "---x") {
				total += 1;
				continue;
			}
			else if (v[i][j] == "xx--" || v[i][j] == "-xx-" || v[i][j] == "--xx") {
				total += 10;
				continue;
			}
			else if (v[i][j] == "xxx-" || v[i][j] == "-xxx") {
				total += 50;
				continue;
			}
		}	

	//Calcular pontos diagonal1 (/)
	for (int i = 0 ; i < 7 ; i++) {
		for (int j = 0 ; j < 4 ; j++) {
			if (d1[i][j] == "xxxx") {
				total += 512;
				continue;
			}
			else if (d1[i][j] == "oooo") {
				total -= 512;
				continue;
			}
			else if (d1[i][j] == "ooo-" || d1[i][j] == "-ooo") {
				total -= 50;
				continue;
			}
			else if (d1[i][j] == "oo--" || d1[i][j] == "-oo-" || d1[i][j] == "--oo") {
				total -= 10;
				continue;
			}
			else if (d1[i][j] == "o---" || d1[i][j] == "-o--" || d1[i][j] == "--o-" || d1[i][j] == "---o") {
				total -= 1;
				continue;
			}
			else if (d1[i][j] == "----" || d1[i][j] == "xoxo" || d1[i][j] == "oxox") {
				continue;
			}
			else if (d1[i][j] == "x---" || d1[i][j] == "-x--" || d1[i][j] == "--x-" || d1[i][j] == "---x") {
				total += 1;
				continue;
			}
			else if (d1[i][j] == "xx--" || d1[i][j] == "-xx-" || d1[i][j] == "--xx") {
				total += 10;
				continue;
			}
			else if (d1[i][j] == "xxx-" || d1[i][j] == "-xxx") {
				total += 50;
				continue;
			}
		}	

		//Calcular pontos diagonal2 (\)
	for (int i = 0 ; i < 7 ; i++) {
		for (int j = 0 ; j < 4 ; j++) {
			if (d2[i][j] == "xxxx") {
				total += 512;
				continue;
			}
			else if (d2[i][j] == "oooo") {
				total -= 512;
				continue;
			}
			else if (d2[i][j] == "ooo-" || d2[i][j] == "-ooo") {
				total -= 50;
				continue;
			}
			else if (d2[i][j] == "oo--" || d2[i][j] == "-oo-" || d2[i][j] == "--oo") {
				total -= 10;
				continue;
			}
			else if (d2[i][j] == "o---" || d2[i][j] == "-o--" || d2[i][j] == "--o-" || d2[i][j] == "---o") {
				total -= 1;
				continue;
			}
			else if (d2[i][j] == "----" || d2[i][j] == "xoxo" || d2[i][j] == "oxox") {
				continue;
			}
			else if (d2[i][j] == "x---" || d2[i][j] == "-x--" || d2[i][j] == "--x-" || d2[i][j] == "---x") {
				total += 1;
				continue;
			}
			else if (d2[i][j] == "xx--" || d2[i][j] == "-xx-" || d2[i][j] == "--xx") {
				total += 10;
				continue;
			}
			else if (d2[i][j] == "xxx-" || d2[i][j] == "-xxx") {
				total += 50;
				continue;
			}
		}

		if (lastMove == 'x')
			total -= 16;
		else total += 16;

		value = total;
}