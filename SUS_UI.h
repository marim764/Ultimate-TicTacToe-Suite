#pragma once
#include "BoardGame_Classes.h"
#include <limits>
#include <set>
using namespace std;

/**
 * @class SUS_UI
 * @brief User Interface class for the SUS game
 * 
 * Handles player interactions, move input, and board display.
 * Supports both Human players and Computer opponents.
 */
class SUS_UI : public UI<char> {
private:
    SUS_Board* current_board = nullptr; ///< Reference to the current game board for Computer moves

public: 
    /**
     * @brief Constructor for SUS_UI
     */
    SUS_UI() : UI<char>("Welcome to SUS Game!", 2) {}
    
    /**
     * @brief Creates a new player for the SUS game
     * @param name Player's name
     * @param symbol Player's symbol ('S' or 'U')
     * @param type Player type (HUMAN, COMPUTER, AI)
     * @return Pointer to the newly created Player object
     */
    Player<char>* create_player(string& name, char symbol, PlayerType type) override { return new Player<char>(name, symbol, type); }
    
    /**
     * @brief Gets a move from a player (Human or Computer)
     * @param player Pointer to the Player object making the move
     * @return Pointer to the Move object containing the chosen move
     * 
     * For human players: prompts for row and column input
     * For Computer players: uses minimax algorithm to find the best move
     */
    Move<char>* get_move(Player<char>* player) override {
        int r, c;
        cout << "\nIt's " << player->get_name() << " (" << player->get_symbol() << ")'s turn.\n";
        if (player->get_type() == PlayerType::HUMAN) {
            // Human player input
            while (true) {
                cout << "Enter Row (0-2), Column (0-2): ";
                if (cin >> r >> c) { return new Move<char>(r, c, player->get_symbol()); }
                else {
                    // Handle invalid input
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid input format. Please enter two integers: Row Column.\n";
                }
            }
        } else {
            // Computer player input
            cout << "Computer is making a move...\n";
                // Get Computer's best move using minimax algorithm
                pair<int, int> bestMove = current_board->get_best_move(player->get_symbol());
                r = bestMove.first;
                c = bestMove.second;
                cout << "Computer chose: " << r << " " << c << endl;
                return new Move<char>(r, c, player->get_symbol());
        }
    }

    /**
     * @brief Sets the current game board reference for Computer moves
     * @param board Pointer to the SUS_Board object
     */
    void set_board(SUS_Board* board) { current_board = board; }

    /**
     * @brief Displays the game board in a formatted grid
     * @param matrix 2D vector representing the board state
     */
    void display_board_matrix(const vector<vector<char>>& matrix) const {
        cout << "\nBoard:\n";
        cout << "    ";
        // Print column headers
        for (int j = 0; j < (int)matrix[0].size(); ++j) cout << j << "   ";
        cout << "\n";
        // Print top border
        cout << "  ";
        for (int j = 0; j < (int)matrix[0].size(); ++j) cout << "----";
        cout << "-\n";
        // Print board rows with borders
        for (int i = 0; i < (int)matrix.size(); ++i) {
            cout << i << " | ";
            for (int j = 0; j < (int)matrix[i].size(); ++j) {
                // Display '.' for empty cells, otherwise the symbol
                cout << (matrix[i][j] == ' ' ? '.' : matrix[i][j]) << " | ";
            }
            cout << "\n"; 
            // Print row separator
            cout << "  ";
            for (int j = 0; j < (int)matrix[0].size(); ++j) cout << "----";
            cout << "-\n";
        }
        cout << "\n";
    }

};
