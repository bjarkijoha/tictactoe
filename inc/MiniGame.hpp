#include <iostream>
#include <functional>
#include "./GameBoard.hpp"
#include "EngineStates.hpp"

using namespace std;
class MiniGame{
    public:
        MiniGame();
        MiniGame(function<void(int)> _cb, int bWidth, int bHeight);
        ~MiniGame(){cout<<"MiniGame deconstructor"<<endl;cout<<"Closing "<<gameName<<endl;}
        void restartGame();
        virtual void playRound(){};
        void setEngineState(int newState){_setState(newState);}
        void setBoardSpace(int x, int y);
        char getBoardSpace(int x, int y);
        bool isValidCoordinates(int x, int y);
        bool findWinnerFrom(int x, int y, function<bool(boardVectors b)> _rule);
        char getChar(char xy);
        void printBoard();
        void switchCurrentPlayer();
        void endRound();
        bool boardFull();
        string gameName = "N/A";
        char winner = ' ';
        char currentPlayer = 'X';
    private:
        GameBoard* _gameBoard;
        function<void(int)> _setState;
        int _boardWidth;
        int _boardHeight;
};

MiniGame::MiniGame(function<void(int)> _cb, int bWidth, int bHeight){
    _setState = _cb;
    _boardWidth = bWidth;
    _boardHeight = bHeight;
    _gameBoard = new GameBoard(_boardHeight, _boardWidth);
}
char MiniGame::getChar(char xy){
    cout<<"Player "<<currentPlayer<<", enter "<<xy<<" coordinate value:"<<endl;
    char entry;
    cin.clear();
    cin>>entry;
    return entry;
}
void MiniGame::restartGame(){
    _gameBoard->resetBoard();
    winner = ' ';
    currentPlayer = 'X';
}
bool MiniGame::findWinnerFrom(int x, int y, function<bool(boardVectors b)> _rule){
    boardVectors foo = _gameBoard->getAllVectorsFrom(x, y);
    return _rule(foo);
}
bool MiniGame::isValidCoordinates(int x, int y){
    bool valid = true;
    if(x<0 || x>_boardWidth){
        valid = false;
    }
    if(y<0 || y>_boardHeight){
        valid = false;
    }
    return valid;
}
void MiniGame::setBoardSpace(int x, int y){
    _gameBoard->setBoardSpace(x, y, currentPlayer);
}
char MiniGame::getBoardSpace(int x, int y){
    return _gameBoard->getBoardSpace(x, y);
}
void MiniGame::printBoard(){
    _gameBoard->printGameBoard();
}
void MiniGame::switchCurrentPlayer(){
    currentPlayer = currentPlayer == 'X' ? 'O' : 'X';
}
void MiniGame::endRound(){
    if(boardFull()){
        setEngineState(GameOver);
        return;
    }
    switchCurrentPlayer();
}
bool MiniGame::boardFull(){
    return _gameBoard->boardFull();
}











//////////////////////TICTACTOE////////////////////////////////////////

class TicTacToe : public MiniGame{
    public:
        TicTacToe();
        TicTacToe(function<void(int)>, int, int);
        void playRound() override;
    private:
        bool checkForWinningVector(vector<char> foo);
        char checkDiagonally();
        char checkVertically();
        char checkHorizontally();
        char check();
        void checkWinner();
        function<bool(boardVectors)> getRule();
};

TicTacToe::TicTacToe(function<void(int)> _cb, int _bWidth, int _bHeight) : MiniGame(_cb, _bWidth, _bHeight){
    gameName = "Tic Tac Toe";
}
bool TicTacToe::checkForWinningVector(vector<char> foo){
    if(foo.size()<3){return false;}
    for(vector<char>::iterator i = foo.begin(); i<foo.end(); i++){
        if(*i!=currentPlayer){return false;}
    }
    return true;
}
function<bool(boardVectors)> TicTacToe::getRule(){
    return [this](boardVectors b)->bool{
        return checkForWinningVector(b.vert) ||
                checkForWinningVector(b.hor) ||
                checkForWinningVector(b.d1) ||
                checkForWinningVector(b.d2);
    };
}

void TicTacToe::playRound(){
    printBoard();
    char selectedX = getChar('X');
    if(selectedX == 'q'){
        setEngineState(InMenu);
        return;
    }
    int intX = selectedX - 48;
    char selectedY = getChar('Y');
    if(selectedY == 'q'){
        setEngineState(InMenu);
        return;
    }
    int intY = selectedY - 48;

    if(!isValidCoordinates(intX, intY)){
        cout<<"Entry ("<<selectedX<<","<<selectedY<<") not valid. Try again."<<endl;
        playRound();
        return;
    }
    else if(getBoardSpace(intX, intY) != '-'){
        cout<<"Space ("<<intX<<","<<intY<<") is occupied. Try again."<<endl;
        playRound();
        return;
    }
    else{
        setBoardSpace(intX, intY);
        if(findWinnerFrom(intX, intY, getRule())){
            winner = currentPlayer;
            setEngineState(GameOver);
            return;
        }
    }
    endRound();
}








//////////////////////TODO:FOURINAROW////////////////////////////////////////

class FourInARow : public MiniGame{
    public:
        FourInARow();
        FourInARow(function<void(int)>, int, int);
        void playRound() override;
    private:
};

FourInARow::FourInARow(function<void(int)> _cb, int _bWidth, int _bHeight) : MiniGame(_cb, _bWidth, _bHeight){
    gameName = "Four In A Row";
}

void FourInARow::playRound(){
    cout<<"Lazy developers"<<endl;
    setEngineState(InMenu);    
}