#include <iostream>
#include "Board.h"
#include "Minimax.h"
#include "Alphabeta.h"

using namespace std;

int main() {
    int column, moves=0, gameOver=0, maxDistanceDepth, generatedNodes, visitedNodes;
    char firstPlayer, pcPiece, humanPiece, algorithm;

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

    cout << endl << "Profundidade máxima a usar na pesquisa: ";

    cin >> maxDistanceDepth;
    if(maxDistanceDepth <=0){
        cout << "Erro! Profundidade máxima inválida" << endl;
        return 1;
    }



    //O primeiro jogador joga com o 'x'
    cout << endl << "Primeiro jogador a jogar:" << endl;
    cout << "\tH - Humano" << endl;
    cout << "\tC - Computador" << endl << endl;
    cout << "Opção: ";

    cin >> firstPlayer;

    if(firstPlayer!='H' && firstPlayer!='C' && firstPlayer!='c' && firstPlayer!='h'){
        cout << "Erro! Opção não encontrada" << endl;
        return 1;
    }

    if(firstPlayer=='C' || firstPlayer == 'c'){
        pcPiece = 'X';
        humanPiece = 'O';
    }
    else{
        pcPiece = 'O';
        humanPiece = 'X';
    }



    //initialNode para depois podermos fazer delete à arvore toda
    Node* initialNode = new Node(firstPlayer);
    Node* actualNode = initialNode;

    actualNode->getBoard().display();
    
    while (!gameOver){
        //If it's the computer's turn
        if((moves%2==0 && (firstPlayer=='C' || firstPlayer=='c')) || (moves%2!=0 && (firstPlayer!='C' && firstPlayer!='c') )){

            //Run the choosen algorithm to calculate the best move for the Computer
            generatedNodes = visitedNodes = 0;
            clock1 = clock();
            if(algorithm == 'M' || algorithm == 'm')
                column = minimaxDecision(actualNode, maxDistanceDepth, pcPiece, generatedNodes, visitedNodes);
            else
                column = alphabetaDecision(actualNode, maxDistanceDepth, pcPiece, generatedNodes, visitedNodes);
            clock2 = clock();

            cout << endl << "   Nós gerados nesta procura: " << generatedNodes << endl;
            cout << "   Nós visitados nesta procura: " << visitedNodes << endl;
            cout << "   Tempo de execução do algoritmo: " << ((float)clock2-clock1)/CLOCKS_PER_SEC << " segundos" << endl << endl;

            cout << "O Computador decidiu jogar na coluna: " << column << endl;
            actualNode = actualNode->chooseDropPlace(column);
        }
        else{

            generatedNodes = visitedNodes = 0;
            clock1 = clock();
            if(algorithm == 'M' || algorithm == 'm')
                column = minimaxDecision(actualNode, maxDistanceDepth, humanPiece, generatedNodes, visitedNodes);
            else
                column = alphabetaDecision(actualNode, maxDistanceDepth, humanPiece, generatedNodes, visitedNodes);
            clock2 = clock();

            cout << endl << "   Nós gerados nesta procura: " << generatedNodes << endl;
            cout << "   Nós visitados nesta procura: " << visitedNodes << endl;
            cout << "   Tempo de execução do algoritmo: " << ((float)clock2-clock1)/CLOCKS_PER_SEC << " segundos" << endl << endl;

            cout << "Melhor coluna para jogar: " << column << endl;
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

            cout << endl << endl << endl << endl << endl << endl;
        }

        cout << endl << endl << endl;
        actualNode->getBoard().display();

        gameOver = actualNode->checkGameOver();
        moves++;

        actualNode->destroyBrothers();
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