#include <iostream>
#include <cctype>
#include <ctime>

#include "Node.h"
#include "Minimax.h"
#include "Alphabeta.h"

using namespace std;

int main() {
    int column, moves=0, gameOver=0, maxDistanceDepth, generatedNodes, visitedNodes;
    char firstPlayer, pcPiece, humanPiece, algorithm;


    //Function Pointer to make cleaner code
    int (*searchFunction)(Node*, int, char, int&, int&);

    //Clocks to count the time that the algorithm took
    clock_t clock1, clock2;

    cout << " _  _                                     __   _         _            " << endl;
    cout << "| || |           ___  _ __ ___           / /  (_) _ __  | |__    __ _ " << endl;
    cout << "| || |_  _____  / _ \\| '_ ` _ \\  _____  / /   | || '_ \\ | '_ \\  / _` |" << endl;
    cout << "|__   _||_____||  __/| | | | | ||_____|/ /___ | || | | || | | || (_| |" << endl;
    cout << "   |_|          \\___||_| |_| |_|       \\____/ |_||_| |_||_| |_| \\__,_|" << endl << endl;
                                                                    
    cout << "Algoritmo a usar:" << endl;
    cout << "\tM - Minimax" << endl;
    cout << "\tA - Alpha-Beta" << endl << endl;
    cout << "Opção: ";

    cin >> algorithm;
    if(algorithm!='M' && algorithm!='A' && algorithm!='a' && algorithm!='m'){
        cout << "Erro! Algoritmo não encontrado" << endl;
        return 1;
    }
    algorithm = toupper(algorithm);

    //Depending on the algorithm the function pointer will point to different functions
    if(algorithm == 'M')
        searchFunction = &minimaxDecision;
    else
        searchFunction = &alphabetaDecision;



    cout << endl << "Profundidade máxima a usar na pesquisa: ";

    cin >> maxDistanceDepth;
    if(maxDistanceDepth <=0){
        cout << "Erro! Profundidade máxima inválida" << endl;
        return 1;
    }



    //First player plays with 'X'
    cout << endl << "Primeiro jogador a jogar:" << endl;
    cout << "\tH - Humano" << endl;
    cout << "\tC - Computador" << endl << endl;
    cout << "Opção: ";

    cin >> firstPlayer;

    if(firstPlayer!='H' && firstPlayer!='C' && firstPlayer!='c' && firstPlayer!='h'){
        cout << "Erro! Opção não encontrada" << endl;
        return 1;
    }
    firstPlayer = toupper(firstPlayer);

    //Give the game pieces to the players
    if(firstPlayer=='C'){
        pcPiece = 'X';
        humanPiece = 'O';
    }
    else{
        pcPiece = 'O';
        humanPiece = 'X';
    }



    //What node are we ate the moment (actual board, who plays, piece who plays, etc)
    Node actualNode = Node(firstPlayer);

    actualNode.getBoard().display();
    
    while (!gameOver){
        //If it's the computer's turn
        if((moves%2==0 && (firstPlayer=='C' || firstPlayer=='c')) || (moves%2!=0 && (firstPlayer!='C' && firstPlayer!='c') )){

            //Run the choosen algorithm to calculate the best move for the Computer
            generatedNodes = visitedNodes = 0;
            clock1 = clock();
            column = searchFunction(&actualNode, maxDistanceDepth, pcPiece, generatedNodes, visitedNodes);
            clock2 = clock();

            cout << endl << "   Nós gerados nesta procura: " << generatedNodes << endl;
            cout << "   Nós visitados nesta procura: " << visitedNodes << endl;
            cout << "   Tempo de execução do algoritmo: " << ((float)clock2-clock1)/CLOCKS_PER_SEC << " segundos" << endl << endl;

            cout << "O Computador decidiu jogar na coluna: " << column << endl;
        }
        else{

            generatedNodes = visitedNodes = 0;
            clock1 = clock();
            column = searchFunction(&actualNode, maxDistanceDepth, humanPiece, generatedNodes, visitedNodes);
            clock2 = clock();

            cout << endl << "   Nós gerados nesta procura: " << generatedNodes << endl;
            cout << "   Nós visitados nesta procura: " << visitedNodes << endl;
            cout << "   Tempo de execução do algoritmo: " << ((float)clock2-clock1)/CLOCKS_PER_SEC << " segundos" << endl << endl;

            cout << "Melhor coluna para jogar: " << column << endl;
            cout << "Introduza em que coluna quer jogar: ";

            //Comment this line so that the human is also a bot
            cin >> column;

            if(column<0 || column>6){
                cout << endl << "Erro! Coluna não existente" << endl;
                continue;
            }

            if(!actualNode.validMove(column)){
                cout << endl << "Erro! Não é possivel fazer uma jogada nessa coluna" << endl;
                continue;
            }

            //Make the output pretty
            cout << endl << endl << endl << endl << endl << endl;
        }

        //Generate the node, giving the actual node and the move that we want to make
        //The 0 is to tell the constructor what depth we want the new node to have
        //It's 0 because we want to make a new tree starting from the new node
        actualNode = Node(actualNode, column, 0);

        cout << endl << endl << endl;
        actualNode.getBoard().display();

        gameOver = actualNode.checkGameOver();
        moves++;
    }

    cout << endl;

    //Decrement the move variable to see which player made the last move
    moves--;
    if(gameOver == 2)
        cout << "Empate!" << endl;
    else if((moves%2==0 && firstPlayer=='H') || (moves%2!=0 && firstPlayer!='H'))
        cout << "Ganhaste!" << endl;
    else
        cout << "O Computador ganhou." << endl;

    return 0;
}