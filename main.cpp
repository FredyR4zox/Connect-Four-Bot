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
    
    
    cout << "                                 _      __                 " << endl;
    cout << "                                | |    / _|                " << endl;
    cout << "  ___ ___  _ __  _ __   ___  ___| |_  | |_ ___  _   _ _ __ " << endl;
    cout << " / __\\ _ \\| '_ \\| '_ \\ / _ \\/ __| __| |  _/ _ \\| | | | '__|" << endl;
    cout << "| (_| (_) | | | | | | |  __/ (__| |_  | || (_) | |_| | |   " << endl;
    cout << " \\___\\___/|_| |_|_| |_|\\___|\\___|\\__| |_| \\___/ \\__,_|_|   " << endl << endl;
                                                                    
    cout << "Algorithm to use:" << endl;
    cout << "\tM - Minimax" << endl;
    cout << "\tA - Alpha-Beta Pruning" << endl << endl;
    cout << "Option: ";

    cin >> algorithm;
    if(algorithm!='M' && algorithm!='A' && algorithm!='a' && algorithm!='m'){
        cout << "Error! Algorithm not found" << endl;
        return 1;
    }
    algorithm = toupper(algorithm);

    //Depending on the algorithm the function pointer will point to different functions
    if(algorithm == 'M')
        searchFunction = &minimaxDecision;
    else
        searchFunction = &alphabetaDecision;



    cout << endl << "Maximum depth: ";

    cin >> maxDistanceDepth;
    if(maxDistanceDepth <=0){
        cout << "Error! Invalid maximum depth" << endl;
        return 1;
    }



    //First player plays with 'X'
    cout << endl << "First player:" << endl;
    cout << "\tH - Human" << endl;
    cout << "\tC - Computer" << endl << endl;
    cout << "Opção: ";

    cin >> firstPlayer;

    if(firstPlayer!='H' && firstPlayer!='C' && firstPlayer!='c' && firstPlayer!='h'){
        cout << "Error! Option not found" << endl;
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

            cout << endl << "   Generated nodes on this search: " << generatedNodes << endl;
            cout << "   Visited nodes on this search: " << visitedNodes << endl;
            cout << "   Execution time of the algorithm: " << ((float)clock2-clock1)/CLOCKS_PER_SEC << " seconds" << endl << endl;

            cout << "The computer decided to play on column: " << column << endl;
        }
        else{

            generatedNodes = visitedNodes = 0;
            clock1 = clock();
            column = searchFunction(&actualNode, maxDistanceDepth, humanPiece, generatedNodes, visitedNodes);
            clock2 = clock();

            cout << endl << "   Generated nodes on this search: " << generatedNodes << endl;
            cout << "   Visited nodes on this search: " << visitedNodes << endl;
            cout << "   Execution time of the algorithm: " << ((float)clock2-clock1)/CLOCKS_PER_SEC << " seconds" << endl << endl;

            cout << "Best column to play: " << column << endl;
            cout << "Insert on which column you want to play: ";

            //Comment this line so that the human is also a bot
            cin >> column;

            if(column<0 || column>6 || !actualNode.validMove(column)){
                cout << endl << "Error! Invalid column to play" << endl;
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
        cout << "Draw!" << endl;
    else if((moves%2==0 && firstPlayer=='H') || (moves%2!=0 && firstPlayer!='H'))
        cout << "You won!" << endl;
    else
        cout << "The computer won." << endl;

    return 0;
}
