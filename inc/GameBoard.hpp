#include <iostream>
#include <vector>

using namespace std;
struct boardVectors{
    vector<char> hor;
    vector<char> vert;
    vector<char> d1;
    vector<char> d2;
    boardVectors(){}
    void printV(vector<char> a){
        for(vector<char>::iterator i=a.begin(); i<a.end();i++){
            cout<<*i;
            cout<<"\t";
        }
        cout<<endl;
    }
    void print(){
        cout<<"h:"<<endl;
        printV(hor);
        cout<<"v:"<<endl;
        printV(vert);
        cout<<"d1:"<<endl;
        printV(d1);
        cout<<"d2:"<<endl;
        printV(d2);
    }
};
class GameBoard{
    private:
        int _height;
        int _width;
        int* _board;
        void getHorizontalVector(vector<char> &foo, int y);
        void getVerticalVector(vector<char> &foo, int y);
        void getDiagonalVectors(vector<char> &foo, vector<char> &bar, int x, int y);
    public:
        GameBoard();
        GameBoard(int _height, int _width);
        ~GameBoard();
        bool boardFull();
        void resetBoard();
        void printGameBoard();
        void setBoardSpace(int x, int y, char val);
        char getBoardSpace(int x, int y);
        boardVectors getAllVectorsFrom(int x, int y);
};

GameBoard::GameBoard(){}
GameBoard::GameBoard(int height, int width){
    _height = height;
    _width = width;
    _board = new int[_height * _width];
    resetBoard();
    printGameBoard();
}
void GameBoard::resetBoard(){
    for(int y = 0; y<_height;y++){
        for(int x = 0; x<_width;x++){
            *(_board + x * _width + y) = int('-');
        }
    }
}
bool GameBoard::boardFull(){
    for(int y = 0; y<_height;y++){
        for(int x = 0; x<_width;x++){
            if(char(*(_board + x * _width + y)) == '-'){
                return false;
            }
        }
    }
    return true;
}
void GameBoard::printGameBoard(){
    cout<<"Current Game Board:\n";
    for(int y = 0; y<_height; y++){
        for(int x = 0; x<_width;x++){
            cout<<char(*(_board + x * _width + y));
            cout<<'\t';
        }
        cout<<endl;
    }
    cout<<endl;
}

void GameBoard::setBoardSpace(int x, int y, char val){
    x--;
    y--;
    *(_board + x * _width + y) = int(val);
}
char GameBoard::getBoardSpace(int x, int y){
    x--;
    y--;
    return char(*(_board + x * _width + y));
}
void GameBoard::getHorizontalVector(vector<char> &foo, int a){
    for(int i = 0; i<_width; i++) {
        foo.emplace_back(char(*(_board + i * _width + a)));
    }
}
void GameBoard::getVerticalVector(vector<char> &foo, int a){
    for(int i = 0; i<_height; i++){
        foo.emplace_back(char(*(_board + a * _height + i)));
    }
}
void GameBoard::getDiagonalVectors(vector<char> &foo, vector<char> &bar, int x, int y){
    int _x = x;
    int _y = y;
    while(_x>0 && _y>0){
        _x--;
        _y--;
    }
    do{
        foo.emplace_back(char(*(_board + _x * _width + _y)));
        _y++;
        _x++;
    }while(_x<_width && _y<_height);
    _x = x;
    _y = y;
    while(_x>0 && _y<_height){
        _x--;
        _y++;
    }
    do{
        bar.emplace_back(char(*(_board + _x * _width + _y)));
        _y--;
        _x++;
    }while(_x<_width && _y>=0);
}

boardVectors GameBoard::getAllVectorsFrom(int x, int y){
    x--;
    y--;
    boardVectors* foo = new boardVectors();
    getHorizontalVector(foo->hor, y);
    getVerticalVector(foo->vert, x);
    getDiagonalVectors(foo->d1, foo->d2, x, y);
    
    return *foo;
}