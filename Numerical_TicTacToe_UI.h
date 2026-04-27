/**
 * @file Numerical_TicTacToe_UI.h
 * @brief Header file for Numerical Tic-Tac-Toe User Interface.
 */
#pragma once
#include "BoardGame_Classes.h"
#include <iostream>
#include <set>
#include <cstdlib>
#include <ctime>

using namespace std;

/**
 * @class Numerical_TicTacToe_UI
 * @brief Handles I/O for Numerical Tic-Tac-Toe.
 */
class Numerical_TicTacToe_UI : public UI<int> {
public:
    /**
     * @brief Constructor. Seeds random number generator.
     */
    Numerical_TicTacToe_UI() : UI<int>("Numerical Tic-Tac-Toe", 3)
    {
        // cell_width small because numbers
        srand(time(0));
    }
    /**
     * @brief Gets a move from the player (Human or Computer).
     * @param player Pointer to the player.
     * @return Pointer to the Move object.
     */
    Move<int>* get_move(Player<int>* player) override
    {
        int r, c, val;
        if (player->get_type() == PlayerType::HUMAN) 
        {
            while (true) 
            {
                cout << player->get_name() << " (";
                if (player->get_symbol() == 1) cout << "Odd";
                else cout << "Even";
                cout << ") - Enter (row, col, number): ";

                if (!(cin >> r >> c >> val)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid input. Please enter three integers: row col number\n";
                    continue;
                }
                // basic validation of indices and value
                if (r < 0 || r > 2 || c < 0 || c > 2) {
                    cout << "Row and column must be between 0 and 2.\n";
                    continue;
                }
                if (val < 1 || val > 9) {
                    cout << "Number must be between 1 and 9.\n";
                    continue;
                }

                // ensure parity of number matches player's allowed parity
                if (player->get_symbol() == 1 && val % 2 == 0) {
                    cout << "Player requires an odd number.\n";
                    continue;
                }
                if (player->get_symbol() == 2 && val % 2 != 0) {
                    cout << "Player requires an even number.\n";
                    continue;
                }

                return new Move<int>(r, c, val);
            }
        }
        else { //If player is COMPUTER
            cout << "Computer is making a move for " << player->get_name() << " (";
            if (player->get_symbol() == 1) cout << "Odd";
            else cout << "Even";
            cout << ")...\n";

            r = rand() % 3; 
            c = rand() % 3; 

            if (player->get_symbol() == 1) 
            {
                int odd_numbers[] = { 1, 3, 5, 7, 9 };
                val = odd_numbers[rand() % 5];
            }
            else
            {
                int even_numbers[] = { 2, 4, 6, 8 };
                val = even_numbers[rand() % 4];
            }

            cout << "Computer chose: " << r << " " << c << " " << val << endl;
            return new Move<int>(r, c, val);
        }
    }
  
    /**
    * @brief Factory method to create a player.
    * @param name Player's name.
    * @param symbol 1 for Odd, 2 for Even.
    * @param type Human or Computer.
    * @return Pointer to new Player object.
    */
    Player<int>* create_player(string& name, int symbol, PlayerType type) override {
 
        Player<int>* p = new Player<int>(name, symbol, type);
        return p;
    }
};
