#include <iostream>
using namespace std;
//	int MINIMAX_DECISION();
//	int ALPHA_BETA_SEARCH();
/*
MINIMAX_DECISION(Board atual) {
	int v = maxvalue(atual);


};

void ALPHA_BETA_SEARCH() {}
*/
/*Estruturas de dados pode ser fila
 512 - se houver 4 em linha
avaliaçao: 61 SEGMENTOS - horizontais, verticais e diagonais*/

void avaliateBoard(Board* current) {
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

	string str[7]; //Guarda cada linha
	string substrh[7][4]; //Guarda as substrings de cada linha

	//Cria as linhas
	for (int i = 0; i < 7; i++) //Para cada linha
		for (int j = 0 ; j < 7 ; j++) //Para cada char da linha
			str[i] += current->getBoard()[i][j];
	
	//Gera todas as substrings
	for (int m = 0 ; m < 7 ; m++) //Para cada linha
		for (int l = 0 ; l <= 3; l++) //Para cada substring
			substrh[m][l] = str[m].substr(l,4);
	
	//Verificação Vertical

	string str2[7]; //Guarda cada linha
	string substrv[7][4]; //Guarda as substrings de cada linha

	//Cria as linhas
	for (int i = 0; i < 7; i++) //Para cada linha
		for (int j = 0 ; j < 7 ; j++) //Para cada char da linha
			str2[i] += current->getBoard()[j][i];
	
	//Gera todas as substrings
	for (int m = 0 ; m < 7 ; m++) //Para cada linha
		for (int l = 0 ; l <= 3; l++) //Para cada substring
			substrv[m][l] = str2[m].substr(l,4);

	cout << "Vertical : " << endl;
	for (int a = 0 ; a < 4 ; a++)
		cout << substrv[0][a] << endl;

	//Verificação diagonal
	string str3[7];
	string substrd[7][4]; //Guarda as substrings de cada linha
	int z;
	int n = 7;
	int slice = 0;
	for (slice = 0 ; slice < 2*n -1 ; slice++)
		z = (slice < n) ? 0 : slice - n + 1;
		for (int j = z ; j <= slice - z ; j++)
			str3[slice] += current->getBoard()[j][slice-j];


	for (int a = 0 ; a < 4 ; a++)
		cout << str3[a] << endl;
	


	//Gera todas as substrings
	for (int m = 0 ; m < 7 ; m++) //Para cada linha
		for (int l = 0 ; l < str3[m].size() ; l++) //Para cada substring
			substrd[m][l] = str3[m].substr(l,4);

	}
