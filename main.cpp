#include <iostream>
#include <stdlib.h>
#include "Board.h"
#include "Algorithm.h"
#include "Minimax.h"
using namespace std;
/*Vais metendo os tokens com o numero da coluna e enter e para sair fazes 7+Enter*/

int main() {
    int column, moves = 0, gameOver = 0;
    char firstPlayer, pcPiece;

    //O primeiro jogador joga com o 'x'
    cout << "Primeiro jogador a jogar:" << endl;
    cout << "\tH - Humano" << endl;
    cout << "\tC - Computador" << endl << endl;
    cout << "Opção: ";

    cin >> firstPlayer;

    if(firstPlayer!='H' && firstPlayer!='C'){
        cout << "Erro! Opção não disponível" << endl;
        return 1;
    }

    if(firstPlayer=='C')
        pcPiece = 'X';
    else
        pcPiece = 'O';

    //initialNode para depois podermos fazer delete à arvore toda
    Node* initialNode = new Node(firstPlayer);
    Node* actualNode = initialNode;

    actualNode->getBoard().display();

    //fazer minimax inicial para ele calcular os nos todos
    minimaxDecision(*actualNode, 5, 'X');
    
    while (!gameOver){
        if((moves%2==0 && firstPlayer=='C') || (moves%2!=0 && firstPlayer!='C')){
            column = minimaxDecision(*actualNode, 5, pcPiece);
            cout << "PC jogou na coluna: " << column << endl;
            actualNode = actualNode->chooseDropPlace(column);
        }
        else{
            cout << "Introduza a linha a inserir: ";
            cin >> column;

            if(column<0 || column>6){
                cout << endl << "Erro! Coluna não existente" << endl;
                continue;
            }

            if(!actualNode->chooseDropPlace(column)){
                cout << endl << "Erro! Não é possivel fazer uma jogada nessa coluna" << endl;
                continue;
            }
            actualNode = actualNode->chooseDropPlace(column);
        }

        cout << endl << endl << endl;
        actualNode->getBoard().display();

        gameOver = actualNode->checkGameOver();

        moves++;
    }

    cout << endl;

    moves--;
    if(gameOver == 2)
        cout << "Empate!" << endl;
    else if((moves%2==0 && firstPlayer=='H') || (moves%2!=0 && firstPlayer!='H'))
        cout << "Ganhaste!" << endl;
    else
        cout << "O Computador ganhou." << endl;

    delete initialNode;

    return 0;
}