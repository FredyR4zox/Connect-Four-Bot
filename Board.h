#include <iostream>
#include <stdlib.h>
#include <array>
using namespace std;

class Board {
private:
	array< array<char, 7>, 6> tab;

public:
	Board();

	array< array<char, 7>, 6> getBoard();

	array<int, 7> possibleMoves();

	void display();
	int checkGameOver();
	char searchToken(int i, int j);
	bool chooseDropPlace(int column, char piece);
	int utility(char myPiece, char playingPiece);
};

//Construtor default (void) do board
Board::Board() {
	for (int i = 0 ; i < 6 ; i++)
		for (int j = 0 ; j < 7 ; j++)
			tab[i][j] = '-';
}

//Getter do board
array< array<char, 7>, 6> Board::getBoard() {
	return tab;
}

array<int, 7> Board::possibleMoves(){
	array<int, 7> possibles = {-1};
	for(int i=0; i<7; i++)
		possibles[i] = -1;
	
	int index = 0;

	for(int i=0; i<7; i++){
		if(tab[0][i] == '-'){
			possibles[index] = i;
			index++;
		}
	}

	return possibles;
}


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
bool Board::chooseDropPlace(int column, char piece){
	for (int i = 5 ; i >= 0; i--){
		if (tab[i][column] != '-')
			continue;
		
		tab[i][column] = piece;
		return true;
	}
	return false;
}

//retorna 0 se o jogo ainda não tiver acabado, 1 se alguem ganhar e 2
//se nao houver mais posições onde se jogar e ninguem tiver ganho
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

				//verificar diagonal direita/cima
				for(k=1; k<4 && i-k>=0 && j+k<7; k++){
					if(tab[i-k][j+k] != tab[i][j])
						break;
				}
				if(k>=4)
					return 1;

				//verificar diagonal direita/baixo
				for(k=1; k<4 && i+k<6 && j+k<7; k++){
					if(tab[i+k][j+k] != tab[i][j])
						break;
				}
				if(k>=4)
					return 1;

				//verificar diagonal esquerda/cima
				for(k=1; k<4 && i-k>=0 && j-k>=0; k++){
					if(tab[i-k][j-k] != tab[i][j])
						break;
				}
				if(k>=4)
					return 1;

				//verificar diagonal esquerda/baixo
				for(k=1; k<4 && i+k<6 && j-k>=0; k++){
					if(tab[i+k][j-k] != tab[i][j])
						break;
				}
				if(k>=4)
					return 1;
			}
		}
	}

	//jogo ainda nao terminado
	for(int i=0; i<6; i++)
		for(int j=0; j<7; j++)
			if(tab[i][j] == '-')
				return 0;

	//jogo terminado sem vencedores
	return 2;
}

int calculateFourArrayScore(int nOfMyPieces, int nOfOponentPieces){
	if(nOfMyPieces == 4)
		return 512;
	else if(nOfOponentPieces == 4)
		return -512;
	else if(nOfMyPieces == 3 && nOfOponentPieces == 0)
		return 50;
	else if(nOfOponentPieces == 3 && nOfMyPieces == 0)
		return -50;
	else if(nOfMyPieces == 2 && nOfOponentPieces == 0)
		return 10;
	else if(nOfOponentPieces == 2 && nOfMyPieces == 0)
		return -10;
	else if(nOfMyPieces == 1 && nOfOponentPieces == 0)
		return 1;
	else if(nOfOponentPieces == 1 && nOfMyPieces == 0)
		return -1;
	else
		return 0;
}

//Calcular a pontuação do tabuleiro, sendo que piece é a nossa peça
int Board::utility(char myPiece, char playingPiece){
	
	/*
	The rules for evaluating segments are as follows (if X is the computer move):
	-50 for three Os, no Xs,
	-10 for two Os, no Xs,
	-1 for one O, no Xs,
	0 for no tokens, or mixed Xs and Os,
	1 for one X, no Os,
	10 for two Xs, no Os,
	50 for three Xs, no Os.

	a win by X has a value of +512,
	a win by O has a value of -512,
	a draw has a value of 0.
	*/

	if(this->checkGameOver() == 1){
		//Se a minha peça for igual à peça que supostamente vai jogar, quer dizer que eu perdi
		if(myPiece == playingPiece)
			return -512;
		else
			return 512;
	}
	else if(this->checkGameOver() == 2)
		return 0;
	

	int total = 0;
	int nOfMyPieces, nOfOponentPieces;

	//Calcular pontos horizontais
	for(int i=0; i<6; i++){
		for(int j=0; j<4; j++){

			nOfMyPieces = nOfOponentPieces = 0;

			for(int k=0; k<4; k++){
				if(tab[i][j+k] == myPiece)
					nOfMyPieces++;
				else if(tab[i][j+k] != '-')
					nOfOponentPieces++;
			}

			total += calculateFourArrayScore(nOfMyPieces, nOfOponentPieces);
		}
	}

	//Calcular pontos verticais
	for(int i=0; i<3; i++){
		for(int j=0; j<7; j++){

			nOfMyPieces = nOfOponentPieces = 0;

			for(int k=0; k<4; k++){
				if(tab[i+k][j] == myPiece)
					nOfMyPieces++;
				else if(tab[i+k][j] != '-')
					nOfOponentPieces++;
			}

			total += calculateFourArrayScore(nOfMyPieces, nOfOponentPieces);
		}
	}

	//Calcular pontos diagonal direita/baixo
	for(int i=0; i<3; i++){
		for(int j=0; j<4; j++){

			nOfMyPieces = nOfOponentPieces = 0;

			for(int k=0; k<4; k++){
				if(tab[i+k][j+k] == myPiece)
					nOfMyPieces++;
				else if(tab[i+k][j+k] != '-')
					nOfOponentPieces++;
			}

			total += calculateFourArrayScore(nOfMyPieces, nOfOponentPieces);
		}
	}

	//Calcular pontos diagonal esquerda/baixo
	for(int i=0; i<3; i++){
		for(int j=6; j>2; j--){

			nOfMyPieces = nOfOponentPieces = 0;

			for(int k=0; k<4; k++){
				if(tab[i+k][j-k] == myPiece)
					nOfMyPieces++;
				else if(tab[i+k][j-k] != '-')
					nOfOponentPieces++;
			}

			total += calculateFourArrayScore(nOfMyPieces, nOfOponentPieces);
		}
	}

	if(myPiece == playingPiece)
		total += 16;
	else
		total -= 16;

	return total;
}