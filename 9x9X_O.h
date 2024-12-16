#ifndef _9X9X_O_H
#define _9X9X_O_H

#include "BoardGame_Classes.h"
#include <iostream>
#include <iomanip>
#include <cctype>
#include <cstdlib>
#include <ctime>

using namespace std;

template <typename T>
class UltimateTicTacToeBoard : public Board<T> {
public:
    UltimateTicTacToeBoard();
    bool update_board(int x, int y, T symbol);
    void display_board();
    bool is_win();
    bool is_draw();
    bool game_is_over();

private:
    UltimateTicTacToeBoard<T>* subboards[3][3];
    bool check_subboard_win(int mainRow, int mainCol);
};

template <typename T>
UltimateTicTacToeBoard<T>::UltimateTicTacToeBoard() {
    this->rows = this->columns = 3;
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = ' ';
            this->subboards[i][j] = nullptr;
        }
    }
    this->n_moves = 81;
}

template <typename T>
bool UltimateTicTacToeBoard<T>::update_board(int x, int y, T mark) {
    int mainRow = x / 3, mainCol = y / 3;
    int subRow = x % 3, subCol = y % 3;

    if (this->board[mainRow][mainCol] != ' ') {
        cout << "\nThis subboard is already completed. Choose a different move.\n";
        return false;
    }

    if (this->subboards[mainRow][mainCol] == nullptr) {
        this->subboards[mainRow][mainCol] = new UltimateTicTacToeBoard<T>();
    }

    if (this->subboards[mainRow][mainCol]->board[subRow][subCol] == ' ') {
        this->subboards[mainRow][mainCol]->board[subRow][subCol] = mark;
        this->subboards[mainRow][mainCol]->n_moves++;

        bool subboardFinished = this->check_subboard_win(mainRow, mainCol);

        if (subboardFinished) {
            this->board[mainRow][mainCol] = mark;
            this->n_moves -= 9;
        }

        return true;
    } else {
        cout << "\nCell is already occupied. Choose a different move.\n";
    }
    return false;
}

template <typename T>
bool UltimateTicTacToeBoard<T>::check_subboard_win(int mainRow, int mainCol) {
    UltimateTicTacToeBoard<T>* subboard = this->subboards[mainRow][mainCol];

    if (subboard == nullptr) {
        return false;
    }

    for (int i = 0; i < 3; i++) {
        if (subboard->board[i][0] == subboard->board[i][1] &&
            subboard->board[i][1] == subboard->board[i][2] &&
            subboard->board[i][0] != ' ') {
            this->board[mainRow][mainCol] = subboard->board[i][0];
            return true;
        }

        if (subboard->board[0][i] == subboard->board[1][i] &&
            subboard->board[1][i] == subboard->board[2][i] &&
            subboard->board[0][i] != ' ') {
            this->board[mainRow][mainCol] = subboard->board[0][i];
            return true;
        }
    }

    if (subboard->board[0][0] == subboard->board[1][1] &&
        subboard->board[1][1] == subboard->board[2][2] &&
        subboard->board[0][0] != ' ') {
        this->board[mainRow][mainCol] = subboard->board[0][0];
        return true;
    }

    if (subboard->board[0][2] == subboard->board[1][1] &&
        subboard->board[1][1] == subboard->board[2][0] &&
        subboard->board[0][2] != ' ') {
        this->board[mainRow][mainCol] = subboard->board[0][2];
        return true;
    }

    return false;
}

template <typename T>
void UltimateTicTacToeBoard<T>::display_board() {
    cout << "Main Board:\n";
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->columns; j++) {
            if (this->board[i][j] == ' ') {
                cout << "| (" << i * 3 << "," << j * 3 << ") ";
            } else {
                cout << "| " << this->board[i][j] << " ";
            }
        }
        cout << "|\n";
        if (i != 2) cout << "-------------\n";
    }

    cout << "\nSub-Boards:\n";
    for (int mainRow = 0; mainRow < 3; mainRow++) {
        for (int subRow = 0; subRow < 3; subRow++) {
            for (int mainCol = 0; mainCol < 3; mainCol++) {
                for (int subCol = 0; subCol < 3; subCol++) {
                    int x = mainRow * 3 + subRow;
                    int y = mainCol * 3 + subCol;

                    if (this->subboards[mainRow][mainCol] != nullptr && this->subboards[mainRow][mainCol]->board[subRow][subCol] != ' ') {
                        cout << "|     " << this->subboards[mainRow][mainCol]->board[subRow][subCol] << " ";
                    } else {
                        cout << "| (" << x << "," << y << ") ";
                    }
                }
                cout << " ";
            }
            cout << "\n";
        }
        cout << "----------------------------------------------------------------------------\n";
    }
}

template <typename T>
bool UltimateTicTacToeBoard<T>::is_win() {
    for (int i = 0; i < this->rows; i++) {
        if ((this->board[i][0] == this->board[i][1] && this->board[i][1] == this->board[i][2] && this->board[i][0] != ' ') ||
            (this->board[0][i] == this->board[1][i] && this->board[1][i] == this->board[2][i] && this->board[0][i] != ' ')) {
            return true;
        }
    }

    if ((this->board[0][0] == this->board[1][1] && this->board[1][1] == this->board[2][2] && this->board[0][0] != ' ') ||
        (this->board[0][2] == this->board[1][1] && this->board[1][1] == this->board[2][0] && this->board[0][2] != ' ')) {
        return true;
    }

    return false;
}

template <typename T>
bool UltimateTicTacToeBoard<T>::is_draw() {
    return (this->n_moves == 0 && !is_win());
}

template <typename T>
bool UltimateTicTacToeBoard<T>::game_is_over() {
    return is_win() || is_draw();
}

template <typename T>
class UltimateTicTacToePlayer : public Player<T> {
public:
    UltimateTicTacToePlayer(string name, T symbol);
    void getmove(int& x, int& y);
};

template <typename T>
UltimateTicTacToePlayer<T>::UltimateTicTacToePlayer(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void UltimateTicTacToePlayer<T>::getmove(int& x, int& y) {
    cout << "\nPlease enter your move x and y (0 to 8) separated by spaces: ";
    cin >> x >> y;
}

template <typename T>
class UltimateTicTacToeRandomPlayer : public RandomPlayer<T> {
public:
    UltimateTicTacToeRandomPlayer(T symbol);
    void getmove(int& x, int& y);
};

template <typename T>
UltimateTicTacToeRandomPlayer<T>::UltimateTicTacToeRandomPlayer(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 9;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));
}

template <typename T>
void UltimateTicTacToeRandomPlayer<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;
    y = rand() % this->dimension;
    cout << "\nRandom move selected: " << x << " " << y << endl;
}

#endif // _9X9X_O_H
