#ifndef IA2_NODE_H
#define IA2_NODE_H

#include <array>

#include "Board.h"

using namespace std;

class Node{
private:
    Board board;
    Node* parent;
    char player;    //'C' = Computer, 'H' = Human | Whose turn is it
    char piece;     //Whose piece turn is it to play
    int move;       //In what column was the move that originated this node
    int depth;
    int score;      //Score of the board, depending on what piece turn is it to play and whose turn is it
    array<Node*, 7> children;

public:
    Node(char player_);
    Node(Node& node, int column);
    Node(Node& node, int column, int depth_);
    ~Node();

    inline Board getBoard();
    inline char getPlayer();
    inline char getPiece();
    inline int getMove();
    inline int getDepth();
    inline int getScore();
    inline array<Node*, 7> getChildren();

    void setScore(int score_);

    int checkGameOver();
    bool validMove(int column);
    array<Node*, 7> makeDescendants(int& generatedNodes);
    int utility(char myPiece);
    void deleteChild(Node* child);
};

Node::Node(char firstPlayer){
    board = Board();
    parent = NULL;
    player = firstPlayer;

    //Piece 'X' is the first piece to play
    piece = 'X';
    move = -1;
    depth = 0;
    score = 0;
    children = {};
}

Node::Node(Node& node, int column){
    board = node.getBoard();

    if(node.getPiece() == 'X'){
        board.insertPiece(column, 'X');
        piece = 'O';
    }
    else{
        board.insertPiece(column, 'O');
        piece = 'X';
    }
    
    parent = &node;
    
    if(node.getPlayer() == 'C')
        player = 'H';
    else
        player = 'C';

    move = column;
    depth = node.getDepth() + 1;
    score = 0;
    children = {};
}

Node::Node(Node& node, int column, int depth_){
    board = node.getBoard();

    if(node.getPiece() == 'X'){
        board.insertPiece(column, 'X');
        piece = 'O';
    }
    else{
        board.insertPiece(column, 'O');
        piece = 'X';
    }
    
    parent = &node;
    
    if(node.getPlayer() == 'C')
        player = 'H';
    else
        player = 'C';

    move = column;
    depth = depth_;
    score = 0;
    children = {};
}

Node::~Node(){
    if(parent!=NULL)
        parent->deleteChild(this);

    for(unsigned int i=0; i<7; i++){
        if(children[i]!=NULL){
            delete children[i];
        }
    }
}



inline Board Node::getBoard(){
    return board;
}

inline char Node::getPlayer(){
    return player;
}

inline char Node::getPiece(){
    return piece;
}

inline int Node::getMove(){
    return move;
}

inline int Node::getDepth(){
    return depth;
}

inline int Node::getScore(){
    return score;
}

inline array<Node*, 7> Node::getChildren(){
    return children;
}



inline void Node::setScore(int score_){
    score = score_;
}



int Node::checkGameOver(){
    return board.checkGameOver();
}

bool Node::validMove(int column){
    return board.validMove(column);
}

array<Node*, 7> Node::makeDescendants(int& generatedNodes){
    array<int, 7> moves = board.possibleMoves();
    array<Node*, 7> l = {};
    unsigned int index = 0;

    for(unsigned int i=0; i<7 && moves[i]!=-1; i++){
        Node *node = new Node(*this, moves[i]);

        for(unsigned int i=0; i<7; i++){
            if(children[i]==NULL){
                children[i] = node;
                break;
            }
        }

        generatedNodes++;
        l[index] = node;
        index++;
    }

    return l;
}

int Node::utility(char myPiece){
    return board.utility(myPiece, piece);
}

void Node::deleteChild(Node* child){
    for(unsigned int i=0; i<7; i++){
        if(children[i]==child){
            children[i] = NULL;
            break;
        }
    }
}

#endif