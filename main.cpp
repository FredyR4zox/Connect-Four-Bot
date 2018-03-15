#include <iostream>
#include <stdlib.h>
#include "Board.h"
#include "Algorithm.h"
using namespace std;
/*Vais metendo os tokens com o numero da coluna e enter e para sair fazes 7+Enter*/

int main() {
    Board board = Board();
    int move, moves = 0, firstPlayer, gameOver = 0;
    char piece;

    //O primeiro jogador joga com o 'x'
    cout << "Primeiro jogador a jogar:" << endl;
    cout << "\t1 - EU" << endl;
    cout << "\t2 - Computador" << endl << endl;
    cout << "Opção: ";

    cin >> firstPlayer;

    if(firstPlayer!= 1 && firstPlayer!=2){
        cout << "Erro! Opção não disponível" << endl;
        return 1;
    }

    board.display();
    
    while (!gameOver){
        //if((moves%2 == 0 && firstPlayer == 1) || (moves%2 != 0 && firstPlayer != 1)){
            cout << "Introduza a linha a inserir: ";
            cin >> move;
        //}

        if(move<0 || move>6){
            cout << endl << "Erro! Coluna não existente" << endl;
            continue;
        }

        //se o jogador a jogar for o primeiro
        if(moves%2 == 0)
            piece = 'x';
        else
            piece = 'o';

        if(!board.chooseDropPlace(move, piece)){
            cout << endl << "Erro! Não é possivel fazer uma jogada nessa coluna" << endl;
            continue;
        }

        cout << endl << endl << endl;
        board.display();

        gameOver = board.checkGameOver();

        moves++;
    }

    cout << endl;

    moves--;
    if(gameOver == 2)
        cout << "Empate!" << endl;
    else if(moves%2 == 0){
        if(firstPlayer==1)
            cout << "Ganhaste!" << endl;
        else
            cout << "O Computador ganhou." << endl;
    }
    else{
        if(firstPlayer==1)
            cout << "O Computador ganhou." << endl;
        else
            cout << "Ganhaste!" << endl;
    }

    return 0;
}