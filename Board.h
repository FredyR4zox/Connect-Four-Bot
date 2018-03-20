#ifndef IA2_BOARD_H
#define IA2_BOARD_H

#include <iostream>
#include <array>

using namespace std;

//Auxiliary function
int calculateFourArrayScore(int nOfMyPieces, int nOfOponentPieces);

class Board {
private:
    array< array<char, 7>, 6> tab;

public:
    Board();

    array< array<char, 7>, 6> getBoard();

    void display();
    bool validMove(int column);
    array<int, 7> possibleMoves();
    bool insertPiece(int column, char piece);
    int checkGameOver();
    int utility(char myPiece, char playingPiece);
};

//Default constructor
Board::Board() {
    for (int i = 0 ; i < 6 ; i++)
        for (int j = 0 ; j < 7 ; j++)
            tab[i][j] = '-';
}

//Board getter
array< array<char, 7>, 6> Board::getBoard() {
    return tab;
}

void Board::display() {
    cout << "+---------------+" << endl;
    for (int i = 0 ; i < 6 ; i++) {
        cout << "  ";
        for (int j = 0 ; j < 7 ; j++)
            cout << tab[i][j] << " ";
        
        cout << endl;
    }
    cout << "+ 0 1 2 3 4 5 6 +" << endl;
    cout << "+---------------+" << endl;
}

bool Board::validMove(int column){
    if (tab[0][column] != '-')
        return false;

    return true;
}

array<int, 7> Board::possibleMoves(){
    array<int, 7> possibles = {};
    for(int i=0; i<7; i++)
        possibles[i] = -1;
    
    int index = 0;

    for(int i=0; i<7; i++){
        if(validMove(i)){
            possibles[index] = i;
            index++;
        }
    }

    return possibles;
}

//Inserts the piece on the desired column and returns true if it was possible
bool Board::insertPiece(int column, char piece){
    for (int i = 5 ; i >= 0; i--){
        if (tab[i][column] != '-')
            continue;
        
        tab[i][column] = piece;
        return true;
    }
    return false;
}

//Return 0 if the game isn't finished yet, 1 if someone wins and
//2 if all the positions on the board are filled and no one has won
int Board::checkGameOver(){
    int k;
    for(int i=0; i<6; i++){
        for(int j=0; j<7; j++){
            if(tab[i][j] != '-'){
                //Search to the right
                for(k=1; k<4 && j+k<7; k++){
                    if(tab[i][j+k] != tab[i][j])
                        break;
                }
                if(k>=4)
                    return 1;

                //Search down
                for(k=1; k<4 && i+k<6; k++){
                    if(tab[i+k][j] != tab[i][j])
                        break;
                }
                if(k>=4)
                    return 1;

                //Search diagonal right/down
                for(k=1; k<4 && i+k<6 && j+k<7; k++){
                    if(tab[i+k][j+k] != tab[i][j])
                        break;
                }
                if(k>=4)
                    return 1;

                //Search diagonal left/down
                for(k=1; k<4 && i+k<6 && j-k>=0; k++){
                    if(tab[i+k][j-k] != tab[i][j])
                        break;
                }
                if(k>=4)
                    return 1;
            }
        }
    }

    //Game not yet ended
    for(int i=0; i<6; i++)
        for(int j=0; j<7; j++)
            if(tab[i][j] == '-')
                return 0;

    //All positions filled in and no one has won
    return 2;
}

//Calculate board's score
//myPiece is our piece and playingPiece is the piece that has the turn to play
int Board::utility(char myPiece, char playingPiece){
    
    /*
    The rules for evaluating segments are as follows (if X is the computer move):
    -50 for three Os, no Xs,
    -10 for two Os, no Xs,
    -1 for one O, no Xs,
    0 for no tokens, or mixed Xs and Os,
    1 for one X, no Os,
    10 for two Xs, no Os,
    50 for three Xs, no Os.

    plus a move bonus depending on whose turn is to play
    (+16 for X, -16 for O).

    a win by X has a value of +512,
    a win by O has a value of -512,
    a draw has a value of 0.
    */

    int gameOver = this->checkGameOver();
    if(gameOver == 1){
        //Se a minha peça for igual à peça que supostamente vai jogar, quer dizer que eu perdi
        if(myPiece == playingPiece)
            return -512;
        else
            return 512;
    }
    else if(gameOver == 2)
        return 0;
    

    int total = 0;
    int nOfMyPieces, nOfOponentPieces;

    //Calcular pontos horizontais
    for(int i=0; i<6; i++){
        for(int j=0; j<4; j++){

            nOfMyPieces = nOfOponentPieces = 0;

            for(int k=0; k<4; k++){
                if(tab[i][j+k] == myPiece)
                    nOfMyPieces++;
                else if(tab[i][j+k] != '-')
                    nOfOponentPieces++;
            }

            total += calculateFourArrayScore(nOfMyPieces, nOfOponentPieces);
        }
    }

    //Calcular pontos verticais
    for(int i=0; i<3; i++){
        for(int j=0; j<7; j++){

            nOfMyPieces = nOfOponentPieces = 0;

            for(int k=0; k<4; k++){
                if(tab[i+k][j] == myPiece)
                    nOfMyPieces++;
                else if(tab[i+k][j] != '-')
                    nOfOponentPieces++;
            }

            total += calculateFourArrayScore(nOfMyPieces, nOfOponentPieces);
        }
    }

    //Calcular pontos diagonal direita/baixo
    for(int i=0; i<3; i++){
        for(int j=0; j<4; j++){

            nOfMyPieces = nOfOponentPieces = 0;

            for(int k=0; k<4; k++){
                if(tab[i+k][j+k] == myPiece)
                    nOfMyPieces++;
                else if(tab[i+k][j+k] != '-')
                    nOfOponentPieces++;
            }

            total += calculateFourArrayScore(nOfMyPieces, nOfOponentPieces);
        }
    }

    //Calcular pontos diagonal esquerda/baixo
    for(int i=0; i<3; i++){
        for(int j=6; j>2; j--){

            nOfMyPieces = nOfOponentPieces = 0;

            for(int k=0; k<4; k++){
                if(tab[i+k][j-k] == myPiece)
                    nOfMyPieces++;
                else if(tab[i+k][j-k] != '-')
                    nOfOponentPieces++;
            }

            total += calculateFourArrayScore(nOfMyPieces, nOfOponentPieces);
        }
    }

    //Bonus points if it's my turn to play
    if(myPiece == playingPiece)
        total += 16;
    else
        total -= 16;

    return total;
}



int calculateFourArrayScore(int nOfMyPieces, int nOfOponentPieces){
    if(nOfMyPieces == 4)
        return 512;
    else if(nOfOponentPieces == 4)
        return -512;
    else if(nOfMyPieces == 3 && nOfOponentPieces == 0)
        return 50;
    else if(nOfOponentPieces == 3 && nOfMyPieces == 0)
        return -50;
    else if(nOfMyPieces == 2 && nOfOponentPieces == 0)
        return 10;
    else if(nOfOponentPieces == 2 && nOfMyPieces == 0)
        return -10;
    else if(nOfMyPieces == 1 && nOfOponentPieces == 0)
        return 1;
    else if(nOfOponentPieces == 1 && nOfMyPieces == 0)
        return -1;
    else
        return 0;
}

#endif