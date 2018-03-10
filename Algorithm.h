#include <iostream>
using namespace std;

int min(int a, int b);
int min(int a, int b, int c);
int max(int a, int b);
void avaliateBoard(Board* current);
void CalcAssignPoints(Board* current, string h[][], string v[][], string d1[][], string d2[][]);

//Auxiliar para retornar o minimo de dois inteiros
int min(int a, int b)
{ return (a < b)? a: b; }
 
//Auxiliar recursiva para retornar o minimo de tres inteiros
int min(int a, int b, int c)
{ return min(min(a, b), c);}
 
//Auxiliar para retornar o maximo de dois inteiros
int max(int a, int b)
{ return (a > b)? a: b; }

//Função para dividir cada linha do tabuleiro em substrings de length 4.
//Mais tarde pode se por esta funçao como parte da classe Board.
void avaliateBoard(Board* current) {
	
	//Verificação Horizontal
	string str[7]; //Guarda cada linha
	string substrh[7][4]; //Guarda as substrings de cada linha

	//Cria as linhas
	for (int i = 0; i < 7; i++) //Para cada linha
		for (int j = 0 ; j < 7 ; j++) //Para cada char da linha
			str[i] += current->getBoard()[i][j];
	
	//Gera todas as substrings de cada linha
	for (int m = 0 ; m < 7 ; m++) //Para cada linha
		for (int l = 0 ; l <= 3; l++) //Para cada substring
			substrh[m][l] = str[m].substr(l,4);
	
	//Teste Horizontal
		cout << endl << "Combinações Horizontais" << endl;
		for (int i = 0 ; i < 7 ; i++)
			for (int j = 0 ; j < 4 ; j++)
				if (!substrh[i][j].empty())
					cout << substrh[i][j] << endl;
				else break;

	//
	//Verificação Vertical

	string str2[7]; //Guarda cada linha
	string substrv[7][4]; //Guarda as substrings de cada linha

	//Cria as linhas
	for (int i = 0; i < 7; i++) //Para cada linha
		for (int j = 0 ; j < 7 ; j++) //Para cada char da linha
			str2[i] += current->getBoard()[j][i];
	
	//Gera todas as substrings de cada linha
	for (int m = 0 ; m < 7 ; m++) //Para cada linha
		for (int l = 0 ; l <= 3; l++) //Para cada substring
			substrv[m][l] = str2[m].substr(l,4);

		//Teste Vertical
		cout << endl << "Combinações Verticais" << endl;
		for (int i = 0 ; i < 7 ; i++)
			for (int j = 0 ; j < 4 ; j++)
				if (!substrv[i][j].empty())
					cout << substrv[i][j] << endl;
				else break;
	//
	//Verificação diagonal -> Lower left to upper right  (sao 7 diagonais para cada lado)
	
	string str3[7];
	string substrd1[7][4]; //Guarda as substrings de cada linha
    
    //Existem (7+7-1) linhas no output

    for (int line = 1; line <= (7+7-1); line++)
    {
        /* Get column index of the first element in this line of output.
           The index is 0 for first ROW lines and line - ROW for remaining
           lines  */
        int start_col = max(0, line-7);
 
        /* Get count of elements in this line. The count of elements is
           equal to minimum of line number, COL-start_col and ROW */
         int count = min(line, (7-start_col), 7);
 
        /* Print elements of this line */
        if (count > 3) {
        	for (int j = 0; j < count; j++) {
            	str3[line - 4] += current->getBoard()[min(7, line)-j-1][start_col+j];
        	} 
        }       		
    }

    for (int i = 0; i < 7 ; i++) { //Para cada linha
		if (str3[i].length() == 4) //se tiver tamanho 4, só existe 1 substring
			for (int l = 0 ; l < 1; l++) //Para cada substring
				substrd1[i][l] = str3[i].substr(l,4);
		else if (str3[i].length() == 5) //se tiver tamanho 5, existem 2 substrings
			for (int l = 0 ; l < 2; l++) //Para cada substring
				substrd1[i][l] = str3[i].substr(l,4);
		else if (str3[i].length() == 6) //se tiver tamanho 6, existem 3 substrings
			for (int l = 0 ; l < 3; l++) //Para cada substring
				substrd1[i][l] = str3[i].substr(l,4);
		else //se tiver tamanho 7, existem 4 substrings
			for (int l = 0 ; l <= 3; l++) //Para cada substring
				substrd1[i][l] = str3[i].substr(l,4);
		}

		//Teste Diagonal 1
		cout << endl << "Combinações Diagonais Lower Left 2 Upper Right" << endl;
		for (int i = 0 ; i < 7 ; i++)
			for (int j = 0 ; j < 4 ; j++)
				if (!substrd1[i][j].empty())
					cout << substrd1[i][j] << endl;
				else break;
		//
	//Está tudo a funcionar. Falta fazer a 2a verificação diagonal
	//Verificação diagonal -> Upper left to lower right  (sao 7 diagonais para cada lado)
	//Usar algoritmo da outra diagonal com a Transposta da matriz ou trocar alguma variavel???
	
	CalcAssignPoints(current, substrh[][], substrv[][], substrd1[][],substrd2[][]);
}
//Também se pode por esta funçao como parte da board
void CalcAssignPoints(Board* current, string h[][], string v[][], string d1[][], string d2[][]) {
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

		if (current->lastMove == 'x')
			total -= 16;
		else total += 16;

		current->value = total;
}