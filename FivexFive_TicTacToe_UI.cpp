/**
 * @file FivexFive_TicTacToe_UI.cpp
 * @brief Implementation of 5x5 Tic-Tac-Toe UI functions.
 */
#include "FivexFive_TicTacToe_UI.h"
#include <cstdlib>
#include <ctime>

FivexFive_TicTacToe_UI::FivexFive_TicTacToe_UI(FivexFive_TicTacToe_Board* b)
    : UI<char>("5x5 Tic-Tac-Toe (Smart AI)", 2)
{
    boardPtr = b;
    srand(time(0));
}
Player<char>* FivexFive_TicTacToe_UI::create_player(string& name, char symbol, PlayerType type) 
{
    return new Player<char>(name, symbol, type);
}

Move<char>* FivexFive_TicTacToe_UI::get_move(Player<char>* player) 
{
    int r, c;
    cout << "\nIt's " << player->get_name() << " (" << player->get_symbol() << ")'s turn.\n";

    if (player->get_type() == PlayerType::HUMAN) 
    {
        while (true) 
        {
            cout << "Enter Row (0-4), Column (0-4): ";
            if (cin >> r >> c) 
            {
                return new Move<char>(r, c, player->get_symbol());
            }
            else 
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input format.\n";
            }
        }
    }
    else 
    { 
        cout << "Computer is thinking...\n";
        // Call the smart function from the board
        pair<int, int> bestMove = boardPtr->get_best_move(player->get_symbol());

        r = bestMove.first;
        c = bestMove.second;

        cout << "Computer chose: " << r << " " << c << endl;
        return new Move<char>(r, c, player->get_symbol());
    }
}
void FivexFive_TicTacToe_UI::display_board_matrix(const vector<vector<char>>& matrix) const {
    cout << "\nBoard:\n";
    cout << "    0   1   2   3   4\n";
    cout << "  ---------------------\n";
    for (int i = 0; i < 5; ++i) {
        cout << i << " | ";
        for (int j = 0; j < 5; ++j) {
            char cell = matrix[i][j];
            if (cell == ' ') cout << ".";
            else cout << cell;
            cout << " | ";
        }
        cout << "\n  ---------------------\n";
    }
    cout << "\n";
}