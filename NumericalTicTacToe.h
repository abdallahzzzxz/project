#ifndef _NUMERICAL_TIC_TAC_TOE_H
#define _NUMERICAL_TIC_TAC_TOE_H

#include "BoardGame_Classes.h"

template <typename T>
class NumericalTicTacToeBoard : public Board<T> {
public:
    NumericalTicTacToeBoard();
    bool update_board(int x, int y, T symbol);
    void display_board();
    bool is_win();
    bool is_draw();
    bool game_is_over();
};

template <typename T>
class NumericalTicTacToePlayer : public Player<T> {
public:
    NumericalTicTacToePlayer(string name, T symbol);
    void getmove(int& x, int& y);
};

template <typename T>
class NumericalTicTacToeRandomPlayer : public RandomPlayer<T> {
public:
    NumericalTicTacToeRandomPlayer(T symbol);
    void getmove(int& x, int& y);
};

//--------------------------------------- IMPLEMENTATION

#include <iostream>
#include <iomanip>
#include <cctype>
#include <cstdlib>
#include <ctime>

using namespace std;

template <typename T>
NumericalTicTacToeBoard<T>::NumericalTicTacToeBoard() {
    this->rows = this->columns = 3;
    this->board = new int*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new int[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;
        }
    }
    this->n_moves = 0;
}

template <typename T>
bool NumericalTicTacToeBoard<T>::update_board(int x, int y, T mark) {
    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns)) {
        if (mark == 0) {
            this->n_moves--;
            this->board[x][y] = 0;
        } else {
            for (int i = 0; i < this->rows; i++) {
                for (int j = 0; j < this->columns; j++) {
                    if (this->board[i][j] == mark) {
                        return false;
                    }
                }
            }

            if (this->board[x][y] != 0) {
                return false;
            }

            this->n_moves++;
            this->board[x][y] = mark;
        }

        return true;
    }
    return false;
}

template <typename T>
void NumericalTicTacToeBoard<T>::display_board() {
    for (int i = 0; i < this->rows; i++) {
        cout << "\n| ";
        for (int j = 0; j < this->columns; j++) {
            cout << "(" << i << "," << j << ")";
            cout << setw(2) << this->board[i][j] << " |";
        }
        cout << "\n-----------------------------";
    }
    cout << endl;
}

template <typename T>
bool NumericalTicTacToeBoard<T>::is_win() {
    for (int i = 0; i < this->rows; i++) {
        if (((this->board[i][0] + this->board[i][1] + this->board[i][2] == 15) && this->board[i][0] != 0 && this->board[i][1] != 0 && this->board[i][2] != 0) ||
            ((this->board[0][i] + this->board[1][i] + this->board[2][i] == 15) && this->board[0][i] != 0 && this->board[1][i] != 0 && this->board[2][i] != 0)) {
            return true;
        }
    }

    if ((this->board[0][0] + this->board[1][1] + this->board[2][2] == 15) ||
        (this->board[0][2] + this->board[1][1] + this->board[2][0] == 15)) {
        return true;
    }

    return false;
}

template <typename T>
bool NumericalTicTacToeBoard<T>::is_draw() {
    return (this->n_moves == 9 && !is_win());
}

template <typename T>
bool NumericalTicTacToeBoard<T>::game_is_over() {
    return is_win() || is_draw();
}

//--------------------------------------

template <typename T>
NumericalTicTacToePlayer<T>::NumericalTicTacToePlayer(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void NumericalTicTacToePlayer<T>::getmove(int& x, int& y) {
    cout << "\nPlease enter your move (x, y) and number (1, 3, 5, 7, 9 for Player 1 or 2, 4, 6, 8 for Player 2): ";
    cin >> x >> y;
    T number;
    cin >> number;
    while (!((number % 2 == 1 && this->symbol % 2 == 1) || (number % 2 == 0 && this->symbol % 2 == 0)) || (number > 9 || number < 1)) {
        cout << "Please enter your move (x, y) and number (1, 3, 5, 7, 9 for Player 1 or 2, 4, 6, 8 for Player 2): ";
        cin >> x >> y >> number;
    }
    this->symbol = number;
}

template <typename T>
NumericalTicTacToeRandomPlayer<T>::NumericalTicTacToeRandomPlayer(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));
}

template <typename T>
void NumericalTicTacToeRandomPlayer<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;
    y = rand() % this->dimension;
    T number;
    number = rand() % 10;
    while (!((number % 2 == 1 && this->symbol % 2 == 1) || (number % 2 == 0 && this->symbol % 2 == 0)) || (number > 9 || number < 1)) {
        number = rand() % 10;
    }
    this->symbol = number;
}

#endif //_NUMERICAL_TIC_TAC_TOE_H
