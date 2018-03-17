#include <iostream>

class Node{
private:
    Board board;
    Node* parent;
    char pcPiece;
    char player; //'C' = Computer, 'H' = Human
    char piece;
    int move; //Em que coluna o jogador meteu a peça
    int depth;
    int score;
    array<Node*, 7> children;

public:
    Node(char player_);
    Node(Node& node, int column);
    ~Node();

    inline Board getBoard();
    inline char getPlayer();
    inline char getPiece();
    inline int getMove();
    inline int getDepth();
    inline int getScore();
    inline int getPcPiece();
    inline array<Node*, 7> getChildren();

    inline void setScore(int score_);

    int checkGameOver();
    array<Node*, 7> makeDescendants();
    Node* chooseDropPlace(int column);
    int utility(char myPiece);
};

Node::Node(char firstPlayer){
    board = Board();
    parent = NULL;
    player = firstPlayer;

    //piece é 'O' porque o 1º jogador começa com X e isto está assim por causa do outro construtor
    piece = 'X';

    if(firstPlayer == 'C')
        pcPiece = 'X';
    else
        pcPiece = 'O';

    move = -1;
    depth = 0;
    score = 0;
    children = {};
}

Node::Node(Node& node, int column){
    board = node.getBoard();

    if(node.getPiece() == 'X'){
        board.chooseDropPlace(column, 'X');
        piece = 'O';
    }
    else{
        board.chooseDropPlace(column, 'O');
        piece = 'X';
    }
    
    parent = &node;
    
    if(node.getPlayer() == 'C')
        player = 'H';
    else
        player = 'C';
    
    pcPiece = node.getPcPiece();
    move = column;
    depth = node.getDepth() + 1;
    score = 0;
    children = {};
}

Node::~Node(){
    for(unsigned int i=0; i<7; i++)
        if(children[i]!=NULL)
            delete children[i];
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

inline int Node::getPcPiece(){
    return pcPiece;
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

array<Node*, 7> Node::makeDescendants(){
    array<int, 7> moves = board.possibleMoves();
    array<Node*, 7> l = {};
    unsigned int index = 0;

    for(unsigned int i=0; i<7 && moves[i]!=-1; i++){
        Node *node = new Node(*this, moves[i]);
        /*if(hashSet->insert(node->getConfig()).second == false){
            delete node;
            continue;
        }*/

        for(unsigned int i=0; i<7; i++){
            if(this->children[i]==NULL){
                this->children[i] = node;
                break;
            }
        }

        l[index] = node;
        index++;
    }

    return l;
}

Node* Node::chooseDropPlace(int column){
    for(int i=0; i<7 && children[i]!=NULL; i++)
        if(children[i]->getMove() == column)
            return children[i];
    
    return NULL;
}

int Node::utility(char myPiece){
    return board.utility(myPiece, piece);
}