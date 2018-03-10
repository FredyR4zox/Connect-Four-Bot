#include <iostream>
using namespace std;

class Algorithm {
	private:

	public:
	int MINIMAX_DECISION();
	int ALPHA_BETA_SEARCH();
	int avaliateBoard();
}

Algorithm::MINIMAX_DECISION(Board atual) {
	int v = maxvalue(atual);


}

Algorithm::ALPHA_BETA_SEARCH() {}

/*Estruturas de dados pode ser fila
 512 - se houver 4 em linha
avaliaçao: 61 SEGMENTOS - horizontais, verticais e diagonais*/

void Algorithm::avaliateBoard(Board* current) {
	/*
		-50 para 3 'o' e nenhum 'x'
		-10 para 2 'o' e nenhum 'x'
		-1 para 1 'o' e nenhum 'x'
		0 para nenhum token ou 'x' e 'o' mistos
		1 para um 'x' ou nenhum 'o'
		10 para dois 'x' ou nenhum 'o'
		50 para tres 'x' ou nenhum 'o'
	*/
	//Verificação Horizontal
	int segfour = 0;
	string seg[4];
	for (int i = 0 ; i < 1 ; i++) //para cada linha cria 4 substrings usando aritmetica de apontadores e conversores para classe
		int j = 0, prevj = j, count = 1;
		for (int j; j < 7 ; j++) //percorre a linha
			seg[n] +=  current->board[i][j];
			count++; //aumenta o contador até 4
			if (count >= 4) {
				n++; //move o vetor
				j = prevj + 1;
				j = prevj;
				count = 1;
			} 
	cout << seg[0] << endl;
	cout << seg[1] << endl;
	cout << seg[2] << endl;
	cout << seg[3] << endl;


	//Verificação vertical

	//Verificação diagonal
}