#pragma once
#include "BoardGame_Classes.h"
#include <queue>
#include <limits>
using namespace std;

/**
 * @class Infinity_TicTacToe_Board
 * @brief Implements Infinity Tic-Tac-Toe with disappearing moves
 * 
 * A 3x3 Tic-Tac-Toe variant where after every 3 moves, the oldest move
 * on the board disappears. Players must achieve 3-in-a-row before their
 * pieces vanish. Creates a dynamic, time-pressured gameplay experience.
 */
class Infinity_TicTacToe_Board : public Board<char> {
private:
    queue<pair<int, int>> move_history; ///< Tracks move order for removal
    
public:
    /**
     * @brief Constructor - initializes 3x3 board with empty spaces
     */
    Infinity_TicTacToe_Board() : Board<char>(3, 3) { for (int i = 0; i < rows; ++i) { for (int j = 0; j < columns; ++j) { board[i][j] = ' '; }}}
    
    /**
     * @brief Updates board with player's move and manages move removal
     * @param move Pointer to Move object containing position and symbol
     * @return true if move was valid and executed, false otherwise
     * 
     * Special Infinity Tic-Tac-Toe behavior:
     * - Records move in history queue
     * - After every 3 moves, removes the oldest move from board
     * - Players must win quickly before their pieces disappear
     */
    bool update_board(Move<char>* move) override {
        if (!move) return false;
        int r = move->get_x();
        int c = move->get_y();
        char symbol = move->get_symbol();
        // Validate move position
        if (r < 0 || r >= rows || c < 0 || c >= columns) return false;
        if (board[r][c] != ' ') {
            cout << "Invalid move: Cell (" << r << "," << c << ") is already occupied.\n";
            return false;
        }
        // Execute the move
        board[r][c] = symbol;
        n_moves++;
        // Record move in history for potential removal
        move_history.push({r, c});
        // Infinity mechanic: Remove oldest move after every 3 moves
        if (n_moves >= 3 && n_moves % 3 == 0 && !move_history.empty()) {
            auto oldest_move = move_history.front();
            move_history.pop();
            board[oldest_move.first][oldest_move.second] = ' ';
            cout << "Oldest move at (" << oldest_move.first << "," << oldest_move.second << ") has been removed!\n";
        }
        return true;
    }  
    
    /**
     * @brief Checks if a player has won the game
     * @param player Pointer to Player object to check
     * @return true if player has three in a row, false otherwise
     * 
     * Checks all standard Tic-Tac-Toe winning patterns:
     * - 3 horizontal rows
     * - 3 vertical columns  
     * - 2 diagonals
     * 
     * Win must be achieved before pieces start disappearing.
     */
    bool is_win(Player<char>* player) override {
        char symbol = player->get_symbol();
        // Check horizontal wins (3 rows)
        for (int i = 0; i < rows; i++) { if (board[i][0] == symbol && board[i][1] == symbol && board[i][2] == symbol) return true; }
        // Check vertical wins (3 columns)
        for (int j = 0; j < columns; j++) { if (board[0][j] == symbol && board[1][j] == symbol && board[2][j] == symbol) return true; }
        // Check main diagonal (top-left to bottom-right)
        if (board[0][0] == symbol && board[1][1] == symbol && board[2][2] == symbol) return true;
        // Check anti-diagonal (top-right to bottom-left)
        if (board[0][2] == symbol && board[1][1] == symbol && board[2][0] == symbol) return true;
        return false;
    }

    /**
     * @brief Checks if a player has lost the game
     * @param player Pointer to Player object to check
     * @return true if opponent has three in a row, false otherwise
     * 
     * Loss occurs when opponent achieves 3-in-a-row.
     * Similar logic to is_win() but checks opponent's symbol.
     */
    bool is_lose(Player<char>* player) override {
        char symbol = player->get_symbol();
        char opponent_symbol = (symbol == 'X') ? 'O' : 'X';
        // Check horizontal wins for opponent
        for (int i = 0; i < rows; i++) { if (board[i][0] == opponent_symbol && board[i][1] == opponent_symbol && board[i][2] == opponent_symbol) return true; }
        // Check vertical wins for opponent
        for (int j = 0; j < columns; j++) { if (board[0][j] == opponent_symbol && board[1][j] == opponent_symbol && board[2][j] == opponent_symbol) return true; }
        // Check diagonals for opponent
        if (board[0][0] == opponent_symbol && board[1][1] == opponent_symbol && board[2][2] == opponent_symbol) return true;
        if (board[0][2] == opponent_symbol && board[1][1] == opponent_symbol && board[2][0] == opponent_symbol) return true;
        return false;
    }
    
    /**
     * @brief Checks if the game is a draw
     * @param player Pointer to Player object (unused, required by interface)
     * @return true if board is full with no winner, false otherwise
     * 
     * In Infinity Tic-Tac-Toe, draws are rare because pieces
     * keep disappearing, but possible if board fills without a winner.
     */
    bool is_draw(Player<char>* player) override {
        // Check if any empty spaces remain
        for (int i = 0; i < rows; i++) { for (int j = 0; j < columns; j++) { if (board[i][j] == ' ') return false; }}
        // Draw if board full but no winner
        return !is_win(player);
    }
    
    /**
     * @brief Checks if the game is over
     * @param player Pointer to Player object to check status for
     * @return true if game has ended (win or draw), false otherwise
     * 
     * Note: In this implementation, is_lose() is not included because
     * a player losing means opponent winning, which is covered by is_win().
     */
    bool game_is_over(Player<char>* player) override { return is_win(player) || is_draw(player); }

};
