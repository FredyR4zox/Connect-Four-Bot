#include <iostream>
#include <stdlib.h>
#include "Board.h"
#include "Algorithm.h"
#include "Minimax.h"
#include "Alphabeta.h"

using namespace std;
/*Vais metendo os tokens com o numero da coluna e enter e para sair fazes 7+Enter*/

int main() {
    int column, moves=0, gameOver=0, maxDistanceDepth;
    char firstPlayer, pcPiece, algorithm;

    cout << "Algoritmo a usar:" << endl;
    cout << "\tM - Minimax" << endl;
    cout << "\tA - Alpha-Beta" << endl << endl;
    cout << "Opção: ";

    cin >> algorithm;
    if(algorithm!='M' && algorithm!='A'){
        cout << "Erro! Algoritmo não encontrado" << endl;
        return 1;
    }



    cout << "Profundidade máxima a usar na pesquisa: ";

    cin >> maxDistanceDepth;
    if(maxDistanceDepth <=0){
        cout << "Erro! Profundidade máxima inválida" << endl;
        return 1;
    }



    //O primeiro jogador joga com o 'x'
    cout << "Primeiro jogador a jogar:" << endl;
    cout << "\tH - Humano" << endl;
    cout << "\tC - Computador" << endl << endl;
    cout << "Opção: ";

    cin >> firstPlayer;

    if(firstPlayer!='H' && firstPlayer!='C'){
        cout << "Erro! Opção não encontrada" << endl;
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
    if(algorithm == 'M')
        minimaxDecision(actualNode, maxDistanceDepth, pcPiece);
    else
        alphabetaDecision(actualNode, maxDistanceDepth, pcPiece);


    
    while (!gameOver){
        if((moves%2==0 && firstPlayer=='C') || (moves%2!=0 && firstPlayer!='C')){
            if(algorithm == 'M')
                column = minimaxDecision(actualNode, maxDistanceDepth, pcPiece);
            else
                column = alphabetaDecision(actualNode, maxDistanceDepth, pcPiece);

            cout << "PC jogou na coluna: " << column << endl;
            actualNode = actualNode->chooseDropPlace(column);
        }
        else{
            cout << "Introduza em que coluna quer jogar: ";
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