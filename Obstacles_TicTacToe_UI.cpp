/**
 * @file Obstacles_TicTacToe_UI.cpp
 * @brief Implementation of Obstacles UI logic.
 */
#include "Obstacles_TicTacToe_UI.h"
#include <cstdlib> 
#include <ctime> 
#include <limits> 

// Constructor
Obstacles_TicTacToe_UI::Obstacles_TicTacToe_UI() : UI<char>("Welcome to Obstacles Tic-Tac-Toe!", 2) 
{
    srand(time(0));
}

//Create a new Player
Player<char>* Obstacles_TicTacToe_UI::create_player(string& name, char symbol, PlayerType type) 
{
    return new Player<char>(name, symbol, type);
}

//Get a move from a human player or generates one for an computer player
Move<char>* Obstacles_TicTacToe_UI::get_move(Player<char>* player) 
{
    int r, c;
    cout << "\nIt's " << player->get_name() << " (" << player->get_symbol() << ")'s turn.\n";

    if (player->get_type() == PlayerType::HUMAN) 
    {
        while (true) {
            cout << "Enter Row (0-5), Column (0-5): ";
            if (cin >> r >> c) 
            {
                return new Move<char>(r, c, player->get_symbol());
            }
            else 
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input format. Please enter two integers: Row Column.\n";
            }
        }
    }
    else 
    { 
        // Computer player
        cout << "Computer is making a move...\n";
        r = rand() % 6; 
        c = rand() % 6;
        cout << "Computer chose: " << r << " " << c << endl;
        return new Move<char>(r, c, player->get_symbol());
    }
}


void Obstacles_TicTacToe_UI::display_board_matrix(const vector<vector<char>>& matrix) const {

    cout << "\nBoard:\n";
    cout << "    ";
    for (int j = 0; j < (int)matrix[0].size(); ++j) 
    {
        cout << j << "   ";
    }
    cout << "\n";
    cout << "  ";
    for (int j = 0; j < (int)matrix[0].size(); ++j) 
    {
        cout << "----";
    }
    cout << "-\n";

    for (int i = 0; i < (int)matrix.size(); ++i) 
    {
        cout << i << " | ";
        for (int j = 0; j < (int)matrix[i].size(); ++j)
        {
            cout << matrix[i][j] << " | ";
        }
        cout << "\n"; 

        cout << "  ";
        for (int j = 0; j < (int)matrix[0].size(); ++j) 
        {
            cout << "----";
        }
        cout << "-\n";
    }
    cout << "\n";
}