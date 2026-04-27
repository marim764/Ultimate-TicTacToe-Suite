#pragma once
#include "BoardGame_Classes.h"
#include <limits>
#include <algorithm>
using namespace std;

/**
 * @class FourInRow_UI
 * @brief User Interface for Connect Four game
 * 
 * Handles player interactions, move input, and board display
 * for the Connect Four game.
 */
class FourInRow_UI : public UI<char> {
private:
    FourInRow_Board* current_board; ///< Pointer to the game board

public: 
    /**
     * @brief Constructor - initializes UI with game title
     */
    FourInRow_UI() : UI<char>("Welcome to Four in a Row!", 2), current_board(nullptr) {}
    
    /**
     * @brief Connects the UI to the game board
     * @param board Pointer to FourInRow_Board object
     */
    void set_board(FourInRow_Board* board) { current_board = board; }

    /**
     * @brief Creates a new player
     * @param name Player's name
     * @param symbol Player's symbol ('X' or 'O')
     * @param type Player type (HUMAN, COMPUTER, AI)
     * @return Pointer to newly created Player object
     */
    Player<char>* create_player(string& name, char symbol, PlayerType type) override { return new Player<char>(name, symbol, type); }
    
    /**
     * @brief Gets a move from a player
     * @param player Pointer to Player object making the move
     * @return Pointer to Move object representing the chosen move
     * 
     * For human players: prompts for column input
     * For Computer players: calls get_best_move() on the board
     */
    Move<char>* get_move(Player<char>* player) override {
        int col;
        cout << "\nIt's " << player->get_name() << " (" << player->get_symbol() << ")'s turn.\n";
        if (player->get_type() == PlayerType::HUMAN) {
            // Human player input
            while (true) {
                cout << "Enter Column (0-6): ";
                if (cin >> col) {
                    if (col >= 0 && col < 7) return new Move<char>(0, col, player->get_symbol());
                    else cout << "Invalid column. Please enter a number between 0-6.\n";
                } else {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid input format. Please enter a column number: ";
                }
            }
        } else {
            // Computer player input
            cout << "Computer is making a move...\n";
            col = current_board->get_best_move(player->get_symbol(), true);
            cout << "Computer chose: " << col << endl;
            return new Move<char>(0, col, player->get_symbol());
        }
    }

    /**
     * @brief Displays the game board in a formatted grid
     * @param matrix 2D vector representing the board state
     * 
     * Shows column numbers at top and row numbers at left.
     * Empty cells are shown as '.', player pieces as 'X' or 'O'.
     */
    void display_board_matrix(const vector<vector<char>>& matrix) const {
        cout << "\nFour In Row Board:\n";
        // Display column numbers
        cout << "  ";
        for (int j = 0; j < (int)matrix[0].size(); ++j) cout << j << "   ";
        cout << "\n";
        // Display top border
        cout << "  ";
        for (int j = 0; j < (int)matrix[0].size(); ++j) cout << "----";
        cout << "-\n";
        // Display board rows with borders
        for (int i = 0; i < (int)matrix.size(); ++i) {
            cout << "| ";
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
