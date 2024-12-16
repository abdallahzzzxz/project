#ifndef _X_O_GAME_H
#define _X_O_GAME_H

#include "BoardGame_Classes.h"
#include <iostream>
#include <iomanip>
#include <cctype>
#include <cstdlib>
#include <ctime>

using namespace std;

enum Direction { UP, DOWN, LEFT, RIGHT };
Direction direction;

template <typename T>
class X_O_Board: public Board<T> {
public:
    X_O_Board();
    bool update_board(int x, int y, T symbol);
    void display_board();
    bool is_win();
    bool is_draw();
    bool game_is_over();
};

template <typename T>
class X_O_Player : public Player<T> {
public:
    X_O_Player(string name, T symbol);
    void getmove(int& x, int& y);
};

template <typename T>
class X_O_Random_Player : public RandomPlayer<T> {
public:
    X_O_Random_Player(T symbol);
    void getmove(int& x, int& y);
};

//--------------------------------------- IMPLEMENTATION

template <typename T>
X_O_Board<T>::X_O_Board() {
    this->rows = this->columns = 4;
    this->board = new T*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new T[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = ' ';
        }
    }

    this->board[0][0] = this->board[0][2] = 'O';
    this->board[3][3] = this->board[3][1] = 'O';
    this->board[0][1] = this->board[0][3] = 'X';
    this->board[3][0] = this->board[3][2] = 'X';
    this->n_moves = 0;
}

template <typename T>
bool X_O_Board<T>::update_board(int x, int y, T mark) {
    int startX = x, startY = y;
    int endX = x, endY = y;

    switch (direction) {
        case UP:
            endX = max(0, startX - 1);
            break;
        case DOWN:
            endX = min(3, startX + 1);
            break;
        case LEFT:
            endY = max(0, startY - 1);
            break;
        case RIGHT:
            endY = min(3, startY + 1);
            break;
    }

    if (startX >= 0 && startX < this->rows && startY >= 0 && startY < this->columns &&
        endX >= 0 && endX < this->rows && endY >= 0 && endY < this->columns) {

        if (this->board[startX][startY] == mark && this->board[endX][endY] == ' ') {
            this->board[startX][startY] = ' ';
            this->board[endX][endY] = mark;
            this->n_moves++;
            display_board();
            return true;
        } else {
            cout << "Invalid move! You must move your own symbol." << endl;
        }
    }
    return false;
}

template <typename T>
void X_O_Board<T>::display_board() {
    for (int i = 0; i < this->rows; i++) {
        cout << "\n| ";
        for (int j = 0; j < this->columns; j++) {
            cout << "(" << i << "," << j << ")";
            cout << setw(2) << this->board[i][j] << " |";
        }
        cout << "\n---------------------------------";
    }
    cout << endl;
}

template <typename T>
bool X_O_Board<T>::is_win() {
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->columns - 2; j++) {
            if ((this->board[i][j] == this->board[i][j+1] && this->board[i][j+1] == this->board[i][j+2] && this->board[i][j] != ' ') ||
                (this->board[j][i] == this->board[j+1][i] && this->board[j+1][i] == this->board[j+2][i] && this->board[j][i] != ' ')) {
                return true;
            }
        }
    }

    for (int i = 0; i < this->rows - 2; i++) {
        for (int j = 0; j < this->columns - 2; j++) {
            if ((this->board[i][j] == this->board[i+1][j+1] && this->board[i+1][j+1] == this->board[i+2][j+2] && this->board[i][j] != ' ') ||
                (this->board[i][j+2] == this->board[i+1][j+1] && this->board[i+1][j+1] == this->board[i+2][j] && this->board[i][j+2] != ' ')) {
                return true;
            }
        }
    }

    return false;
}

template <typename T>
bool X_O_Board<T>::is_draw() {
    return false;
}

template <typename T>
bool X_O_Board<T>::game_is_over() {
    return is_win();
}

//--------------------------------------

template <typename T>
X_O_Player<T>::X_O_Player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void X_O_Player<T>::getmove(int& x, int& y) {
    int startX, startY;
    char dir;

    cout << "\nPlease enter the starting position (x, y): ";
    cin >> startX >> startY;

    while (true) {
        cout << "Please enter the direction (U for UP, D for DOWN, L for LEFT, R for RIGHT): ";
        cin >> dir;

        switch (toupper(dir)) {
            case 'U':
                direction = UP;
                break;
            case 'D':
                direction = DOWN;
                break;
            case 'L':
                direction = LEFT;
                break;
            case 'R':
                direction = RIGHT;
                break;
            default:
                cout << "Invalid direction! Please enter again." << endl;
                continue;
        }
        break;
    }

    x = startX;
    y = startY;
}

template <typename T>
X_O_Random_Player<T>::X_O_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 4;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));
}

template <typename T>
void X_O_Random_Player<T>::getmove(int& x, int& y) {
    int startX = rand() % this->dimension;
    int startY = rand() % this->dimension;
    char dir = "UDLR"[rand() % 4];

    cout << "Random starting position: (" << startX << ", " << startY << ")\n";
    cout << "Random direction: " << dir << "\n";

    switch (dir) {
        case 'U':
            direction = UP;
            break;
        case 'D':
            direction = DOWN;
            break;
        case 'L':
            direction = LEFT;
            break;
        case 'R':
            direction = RIGHT;
            break;
    }

    x = startX;
    y = startY;
}

#endif //_X_O_GAME_H
