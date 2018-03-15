#include <stdlib.h>
#include <array>
using namespace std;

class Board {
private:
	array< array<char, 7>, 6> tab;
	char lastMove;
	int value; 

public:
	Board();

	array< array<char, 7>, 6> getBoard();	

	void display();
	int checkGameOver();
	char searchToken(int i, int j);
	bool chooseDropPlace(int column, char piece);
	void calcAssignPoints(string h[6][4], string v[7][4], string d1[7][4], string d2[7][4]);
};

//Construtor default (void) do board
Board::Board() {
	for (int i = 0 ; i < 6 ; i++)
		for (int j = 0 ; j < 7 ; j++)
			tab[i][j] = '-';
	
	value = 0;
}

//Getter do board
array< array<char, 7>, 6> Board::getBoard() {
	return tab;
}

//Imprime o tabuleiro (já formatado/pronto!)
void Board::display() {
	cout << "+---------------+" << endl;
	for (int i = 0 ; i < 6 ; i++) {
		cout << "  ";
		for (int j = 0 ; j < 7 ; j++)
			cout << tab[i][j] << " ";
		
		cout << endl;
	}
	cout << "+ 0 1 2 3 4 5 6 +" << endl;
	cout << "+---------------+" << endl;
}

//Retorna o token na posição (i,j)
char Board::searchToken(int i, int j) {
	return tab[i][j];
}

//Escolhe a coluna onde se põe o token
bool Board::chooseDropPlace(int column, char piece) {
	for (int i = 5 ; i >= 0; i--){
		if (tab[i][column] != '-')
			continue;
		
		tab[i][column] = piece;
		return true;
	}
	return false;
}

int Board::checkGameOver(){
	int k;
	for(int i=0; i<6; i++){
		for(int j=0; j<7; j++){
			if(tab[i][j] != '-'){
				//verificar direita
				for(k=1; k<4 && j+k<7; k++){
					if(tab[i][j+k] != tab[i][j])
						break;
				}
				if(k>=4)
					return 1;

				//verificar esquerda
				for(k=1; k<4 && j-k>=0; k++){
					if(tab[i][j-k] != tab[i][j])
						break;
				}
				if(k>=4)
					return 1;

				//verificar baixo
				for(k=1; k<4 && i+k<6; k++){
					if(tab[i+k][j] != tab[i][j])
						break;
				}
				if(k>=4)
					return 1;

				//verificar cima
				for(k=1; k<4 && i-k>=0; k++){
					if(tab[i-k][j] != tab[i][j])
						break;
				}
				if(k>=4)
					return 1;
			}
		}
	}

	for(int i=0; i<6; i++)
		for(int j=0; j<7; j++)
			if(tab[i][j] == '-')
				return 0;

	return 2;
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
}