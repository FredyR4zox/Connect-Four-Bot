#include <iostream>
using namespace std;

int min(int a, int b);
int min(int a, int b, int c);
int max(int a, int b);
void avaliateBoard(Board* current);

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
//Por como parte da classe Board
void avaliateBoard(Board* current) {
	
	//Verificação Horizontal
	string str[6]; //Guarda cada linha horizontal (sao 6)
	string substrh[6][4]; //Guarda as substrings de cada linhas			

	//Cria as linhas
	for (int i = 0; i < 6; i++) //Para cada linha
		for (int j = 0 ; j < 7 ; j++) //Para cada char da linha
			str[i] += current->getBoard()[i][j];
	
	//Gera todas as substrings de cada linha
	for (int m = 0 ; m < 6 ; m++) //Para cada linha
		for (int l = 0 ; l <= 3; l++) //Para cada substring
			substrh[m][l] = str[m].substr(l,4);
	
	//Teste Horizontal
	/*
		cout << endl << "Combinações Horizontais" << endl;
		for (int i = 0 ; i < 7 ; i++)
			for (int j = 0 ; j < 4 ; j++)
				if (!substrh[i][j].empty())
					cout << substrh[i][j] << endl;
				else break;
*/
	


	//Verificação Vertical

	string str2[7]; //Guarda cada linha
	string substrv[7][4]; //Guarda as substrings de cada linha

	//Cria as linhas
	for (int i = 0; i < 7; i++) //Para cada linha (sao 7)
		for (int j = 0 ; j < 6 ; j++) //Para cada char da linha
			str2[i] += current->getBoard()[j][i];
	
	//Gera todas as substrings de cada linha
	for (int m = 0 ; m < 6 ; m++) //Para cada linha
		for (int l = 0 ; l < 3; l++) //Para cada substring (em linhas de 6, ha 3 possiveis substrings)
			substrv[m][l] = str2[m].substr(l,4);

		/*//Teste Vertical
		cout << endl << "Combinações Verticais" << endl;
		for (int i = 0 ; i < 7 ; i++)
			for (int j = 0 ; j < 4 ; j++)
				if (!substrv[i][j].empty())
					cout << substrv[i][j] << endl;
				else break;*/
	



	//Verificação diagonal -> Lower left to upper right  (sao 7 diagonais para cada lado)
	
	string str3[7];
	string substrd1[7][4]; //Guarda as substrings de cada linha
    
    //Existem (7+7-1) linhas no output
	int conta = 0;
    for (int line = 1; line <= (7+6-1); line++)
    {
        /* Get column index of the first element in this line of output.
           The index is 0 for first ROW lines and line - ROW for remaining
           lines  */
        int start_col = max(0, line-6);
 
        /* Get count of elements in this line. The count of elements is
           equal to minimum of line number, COL-start_col and ROW */
         int count = min(line, (7-start_col), 6);
 
        /* Print elements of this line */
        if (count > 3) {
        	for (int j = 0; j < count; j++) {
            	str3[conta] += current->getBoard()[min(6, line)-j-1][start_col+j];
        	} 
        	conta++;
        }       		
    }

    for (int i = 0; i < 6 ; i++) { //Para cada linha
		if (str3[i].length() == 6) //se tiver tamanho 5, só existe 2 substrings
			for (int l = 0 ; l < 3; l++) //Para cada substring
				substrd1[i][l] = str3[i].substr(l,4);
		else if (str3[i].length() == 5) //se tiver tamanho 4, existem 1 substrings
			for (int l = 0 ; l < 2 ; l++)	
				substrd1[i][l] = str3[i].substr(l,4);
		else //length 4
			{	substrd1[i][0] = str3[i].substr(0,4);}
		}
	
		//Teste Diagonal 1 
		/*cout << endl << "Combinações Diagonais Lower Left 2 Upper Right" << endl;
		for (int i = 0 ; i < 7 ; i++)
			for (int j = 0 ; j < 4 ; j++)
				if (!substrd1[i][j].empty())
					cout << substrd1[i][j] << endl;
				else break;
		*/
	//Verificação diagonal -> Upper left to lower right  (sao 6 diagonais para cada lado)
	
	string str4[7];
	string substrd2[7][4]; //Guarda as substrings de cada linha
  	int n = 4;
  	int j = 0;
    while (j < n) {
	    for (int col = 0; col < 6; col++)	
	    {
	    	for (int line = 0 ; line < 7; line++) {
	   	 		if (col == line-j) //col representa linhas e line representa cols mas wtv
					str4[j] += current->getBoard()[col][line];  			
	    	} 			
		}
		j++;
	}
	n = 3;
	j = 1;
	while (j < n) {
	    for (int col = 1; col < 7; col++)	
	    {
	    		for (int line = 0 ; line < 6; line++) {
	   	 			if (col-j == line) //Problema na Condição; col representa linhas e line representa cols mas wtv
						str4[j-1+4] += current->getBoard()[col][line];  			
	    		} 
		}
		j++;
	}				

    for (int i = 0; i < 6 ; i++) { //Para cada linha
		if (str4[i].length() == 6) {//se tiver tamanho 5, só existe 2 substrings
			for (int l = 0 ; l < 3; l++) //Para cada substring
				substrd2[i][l] = str4[i].substr(l,4); }
		else if (str4[i].length() == 5) {//se tiver tamanho 4, existem 1 substrings
			for (int l = 0 ; l < 2 ; l++)	
				substrd2[i][l] = str4[i].substr(l,4);}
		else //length 4
				{substrd2[i][0] = str4[i].substr(0,4);}
		}
	
	current->calcAssignPoints(substrh[6][4], substrv[7][4], substrd1[7][4],substrd2[7][4]);
}