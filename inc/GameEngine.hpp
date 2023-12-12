#include <iostream>
#include <vector>
#include "MiniGame.hpp"

using namespace std;

class GameEngine{
    private:
        //GameBoard board;
        enum GamesList{
            tictactoe,
            fourinarow
        };
        void inMenu();
        void inGame();
        void gameOver();
        MiniGame* currentGame = nullptr;
        function<void(int)> getStateSetter();
        int currentState;
        void checkForWinner();
        void displayMenu();
        void getMenuSelection();
        void startGame(MiniGame* _game);
    public:
        GameEngine();
        ~GameEngine();
};

GameEngine::GameEngine(){
    currentState = InMenu;
    do{
        switch(currentState){
            case InMenu:
                inMenu();
                break;
            case InGame:
                inGame();
                break;
            case GameOver:
                gameOver();
                break;
        }
    }while(currentState != ExitGame);
}


void GameEngine::inMenu(){
    displayMenu();
    getMenuSelection();
}
void GameEngine::inGame(){
    if (currentGame == nullptr){
        cout<<"No current game selected. Returning to menu."<<endl;
        currentState = InMenu;
        return;
    }
    currentGame->playRound();
}
void GameEngine::gameOver(){
    currentGame->printBoard();
    cout<<"Game Over!"<<endl;
    if(currentGame->winner != ' '){
        cout<<"Player "<<currentGame->winner<<" wins!"<<endl;
    }
    else if(currentGame->boardFull()){
        cout<<"Gameboard is full."<<endl;
    }
    cout<<"Do you want to restart [y/n]? ";
    cin.clear();
    char uIn;
    cin>>uIn;
    if(uIn == 'y'){
        currentGame->restartGame();
    }
    else{
        currentState = InMenu;
        delete currentGame;
        currentGame = nullptr;
        return;
    }
}
void GameEngine::displayMenu(){
    int disp = 0;
    char _tab = '\t';
    cout<<"Select a game:"<<endl;
    if(currentGame != nullptr){
        cout<<_tab<<"r: Resume "<<currentGame->gameName<<endl;
    }
    cout<<_tab<<"0: TicTacToe"<<endl;
    cout<<_tab<<"1: FourInARow"<<endl;
    cout<<_tab<<"q: Quit"<<endl;
}

void GameEngine::getMenuSelection(){
    char selection;
    cin.clear();
    cin>>selection;
    cout<<"Selected: "<<selection<<endl;
    switch(selection){
        case '0':
            startGame(new TicTacToe(getStateSetter(), 3, 3));
            break;
        case '1':
            startGame(new FourInARow(getStateSetter(), 7, 7));
            break;
        case 'q':
            currentState = ExitGame;
            break;
        case 'r':
            currentState = InGame;
            break;
        case 'h':
            cout<<"Help arriving shortly!"<<endl;
            break;
    }
}
function<void(int)> GameEngine::getStateSetter(){
    return [this](int newState)->void{
        this->currentState = newState;
    };
}

void GameEngine::startGame(MiniGame* _game){
    cout<<"Trying to start "<<_game->gameName;
    if(currentGame!=nullptr){
        delete(currentGame);
    }
    currentGame = _game;
    currentState = InGame;
}

GameEngine::~GameEngine(){
    delete currentGame;
}