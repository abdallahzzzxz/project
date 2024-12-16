#include <iostream>
#include "BoardGame_Classes.h"
#include "9x9X_O.h"
#include "FourInRow.h"
#include "NumericalTicTacToe.h"

#include "X_O_Game.h"

using namespace std;

void playTicTacToe();
void playFourInRow();
void playNumericalTicTacToe();
void playUltimateTicTacToe();


int main() {
    int gameChoice;

    cout << "Welcome to FCAI Multi-Game Platform!\n";
    cout << "Choose a game to play:\n";
    cout << "1. Tic-Tac-Toe (Classic X-O Game)\n";
    cout << "2. Four in a Row\n";
    cout << "3. Numerical Tic-Tac-Toe\n";
    cout << "4. Ultimate Tic-Tac-Toe\n";
    cout << "Enter your choice: ";
    cin >> gameChoice;

    switch (gameChoice) {
        case 1:
            playTicTacToe();
            break;
        case 2:
            playFourInRow();
            break;
        case 3:
            playNumericalTicTacToe();
            break;
        case 4:
            playUltimateTicTacToe();
            break;
        default:
            cout << "Invalid choice. Exiting the program.\n";
            return 1;
    }

    return 0;
}

void playTicTacToe() {
    int choice;
    Player<char>* players[2];
    X_O_Board<char>* B = new X_O_Board<char>(); // 3x3 board for Tic-Tac-Toe
    string player1Name, player2Name;

    cout << "\n--- Tic-Tac-Toe ---\n";
    cout << "Enter Player 1 name: ";
    cin >> player1Name;
    cout << "Choose Player 1 type:\n1. Human\n2. Random Computer\n";
    cin >> choice;

    switch (choice) {
        case 1:
            players[0] = new X_O_Player<char>(player1Name, 'X');
            break;
        case 2:
            players[0] = new X_O_Random_Player<char>('X');
            break;
        default:
            cout << "Invalid choice for Player 1. Exiting the game.\n";
            return;
    }

    cout << "Enter Player 2 name: ";
    cin >> player2Name;
    cout << "Choose Player 2 type:\n1. Human\n2. Random Computer\n";
    cin >> choice;

    switch (choice) {
        case 1:
            players[1] = new X_O_Player<char>(player2Name, 'O');
            break;
        case 2:
            players[1] = new X_O_Random_Player<char>('O');
            break;
        default:
            cout << "Invalid choice for Player 2. Exiting the game.\n";
            return;
    }

    GameManager<char> tic_tac_toe_game(B, players);
    tic_tac_toe_game.run();

    delete B;
    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }
}

void playFourInRow() {
    int choice;
    Player<char>* players[2];
    FourInRow_Board<char>* B = new FourInRow_Board<char>();
    string player1Name, player2Name;

    cout << "\n--- Four in a Row ---\n";
    cout << "Enter Player 1 name: ";
    cin >> player1Name;
    cout << "Choose Player 1 type:\n1. Human\n2. Random Computer\n";
    cin >> choice;

    switch (choice) {
        case 1:
            players[0] = new FourInRow_Player<char>(player1Name, 'X');
            break;
        case 2:
            players[0] = new FourInRow_Random_Player<char>('X');
            break;
        default:
            cout << "Invalid choice for Player 1. Exiting the game.\n";
            return;
    }

    cout << "Enter Player 2 name: ";
    cin >> player2Name;
    cout << "Choose Player 2 type:\n1. Human\n2. Random Computer\n";
    cin >> choice;

    switch (choice) {
        case 1:
            players[1] = new FourInRow_Player<char>(player2Name, 'O');
            break;
        case 2:
            players[1] = new FourInRow_Random_Player<char>('O');
            break;
        default:
            cout << "Invalid choice for Player 2. Exiting the game.\n";
            return;
    }

    GameManager<char> four_in_row_game(B, players);
    four_in_row_game.run();

    delete B;
    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }
}

void playNumericalTicTacToe() {
    int choice;
    Player<int>* players[2];
    NumericalTicTacToeBoard<int>* B = new NumericalTicTacToeBoard<int>(); // 3x3 board for Numerical Tic-Tac-Toe
    string player1Name, player2Name;

    cout << "\n--- Numerical Tic-Tac-Toe ---\n";
    cout << "Enter Player 1 name: ";
    cin >> player1Name;
    cout << "Choose Player 1 type:\n1. Human\n2. Random Computer\n";
    cin >> choice;

    switch (choice) {
        case 1:
            players[0] = new NumericalTicTacToePlayer<int>(player1Name, 1);
            break;
        case 2:
            players[0] = new NumericalTicTacToeRandomPlayer<int>(1);
            break;
        default:
            cout << "Invalid choice for Player 1. Exiting the game.\n";
            return;
    }

    cout << "Enter Player 2 name: ";
    cin >> player2Name;
    cout << "Choose Player 2 type:\n1. Human\n2. Random Computer\n";
    cin >> choice;

    switch (choice) {
        case 1:
            players[1] = new NumericalTicTacToePlayer<int>(player2Name, 2);
            break;
        case 2:
            players[1] = new NumericalTicTacToeRandomPlayer<int>(2);
            break;
        default:
            cout << "Invalid choice for Player 2. Exiting the game.\n";
            return;
    }

    GameManager<int> numerical_tic_tac_toe_game(B, players);
    numerical_tic_tac_toe_game.run();

    delete B;
    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }
}

void playUltimateTicTacToe() {
    int choice;
    Player<char>* players[2];
    UltimateTicTacToeBoard<char>* B = new UltimateTicTacToeBoard<char>();
    string player1Name, player2Name;

    cout << "\n--- Ultimate Tic-Tac-Toe ---\n";
    cout << "Enter Player 1 name: ";
    cin >> player1Name;
    cout << "Choose Player 1 type:\n1. Human\n2. Random Computer\n";
    cin >> choice;

    switch (choice) {
        case 1:
            players[0] = new UltimateTicTacToePlayer<char>(player1Name, 'X');
            break;
        case 2:
            players[0] = new UltimateTicTacToeRandomPlayer<char>('X');
            break;
        default:
            cout << "Invalid choice for Player 1. Exiting the game.\n";
            return;
    }

    cout << "Enter Player 2 name: ";
    cin >> player2Name;
    cout << "Choose Player 2 type:\n1. Human\n2. Random Computer\n";
    cin >> choice;

    switch (choice) {
        case 1:
            players[1] = new UltimateTicTacToePlayer<char>(player2Name, 'O');
            break;
        case 2:
            players[1] = new UltimateTicTacToeRandomPlayer<char>('O');
            break;
        default:
            cout << "Invalid choice for Player 2. Exiting the game.\n";
            return;
    }

    GameManager<char> ultimate_tic_tac_toe_game(B, players);
    ultimate_tic_tac_toe_game.run();

    delete B;
    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }
}



