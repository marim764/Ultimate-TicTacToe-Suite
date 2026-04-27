#pragma once
#include "BoardGame_Classes.h"
#include <queue>
#include <limits>
using namespace std;

/**
 * @class Infinity_TicTacToe_UI
 * @brief User Interface for Infinity Tic-Tac-Toe game
 * 
 * Handles player interactions, move input, and board display
 * for the Infinity Tic-Tac-Toe variant.
 */
class Infinity_TicTacToe_UI : public UI<char> {
public: 
    /**
     * @brief Constructor - initializes UI with game title
     */
    Infinity_TicTacToe_UI() : UI<char>("Welcome to Infinity Tic-Tac-Toe!", 2) {}
    
    /**
     * @brief Creates a new player
     * @param name Player's name
     * @param symbol Player's symbol ('X' or 'O')
     * @param type Player type (HUMAN or COMPUTER)
     * @return Pointer to newly created Player object
     */
    Player<char>* create_player(string& name, char symbol, PlayerType type) override { return new Player<char>(name, symbol, type); }
    
    /**
     * @brief Gets a move from a player
     * @param player Pointer to Player object making the move
     * @return Pointer to Move object representing the chosen move
     * 
     * For human players: prompts for row and column input (0-2)
     * For computer players: generates random valid move
     */
    Move<char>* get_move(Player<char>* player) override {
        int r, c;
        cout << "\nIt's " << player->get_name() << " (" << player->get_symbol() << ")'s turn.\n";
        if (player->get_type() == PlayerType::HUMAN) {
            // Human player input with validation
            while (true) {
                cout << "Enter Row (0-2), Column (0-2): ";
                if (cin >> r >> c) {
                    // Input accepted, create move object
                    return new Move<char>(r, c, player->get_symbol());
                } else {
                    // Handle invalid input (non-numeric)
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid input format. Please enter two integers: Row Column.\n";
                }
            }
        } else {
            // Computer player: random move generation
            cout << "Computer is making a move...\n";
            r = rand() % 3;  // Random row 0-2
            c = rand() % 3;  // Random column 0-2
            cout << "Computer chose: " << r << " " << c << endl;
            return new Move<char>(r, c, player->get_symbol());
        }
    }
    
    /**
     * @brief Displays the game board in a formatted grid
     * @param matrix 2D vector representing the board state
     * 
     * Shows row and column indices for easy reference.
     * Empty cells are displayed as '.', player pieces as 'X' or 'O'.
     */
    void display_board_matrix(const vector<vector<char>>& matrix) const {
        cout << "\nBoard:\n";
        // Display column numbers at top
        cout << "    ";
        for (int j = 0; j < (int)matrix[0].size(); ++j) cout << j << "   ";
        cout << "\n";
        // Display top border
        cout << "  ";
        for (int j = 0; j < (int)matrix[0].size(); ++j) cout << "----";
        cout << "-\n";
        // Display each row with row number and cell contents
        for (int i = 0; i < (int)matrix.size(); ++i) {
            cout << i << " | ";
            for (int j = 0; j < (int)matrix[i].size(); ++j) cout << (matrix[i][j] == ' ' ? '.' : matrix[i][j]) << " | ";
            cout << "\n";
            // Display row separator
            cout << "  ";
            for (int j = 0; j < (int)matrix[0].size(); ++j) cout << "----";
            cout << "-\n";
        }
        cout << "\n";
    }
};
