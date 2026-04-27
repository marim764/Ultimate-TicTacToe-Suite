/**
 * @file Numerical_TicTacToe_Board.h
 * @brief Header file for Numerical Tic-Tac-Toe Board.
 */
#pragma once
#include "BoardGame_Classes.h"
#include <vector>
#include <iostream>

using namespace std;

/**
 * @class Numerical_TicTacToe_Board
 * @brief Represents a 3x3 board for Numerical Tic-Tac-Toe.
 * Player 1 uses odd numbers, Player 2 uses even numbers.
 * Win condition: Sum of line equals 15.
 */
class Numerical_TicTacToe_Board : public Board<int> {
public:
    /**
     * @brief Constructor to initialize 3x3 board with zeros.
     */
    Numerical_TicTacToe_Board(): Board<int>(3, 3)
    {
        // initialize board cells to 0 explicitly (Board constructor already default-constructed)
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < columns; ++j)
                board[i][j] = 0;
    }

    /**
     * @brief Updates the board with the player's move.
     * @param move Pointer to the move (row, col, value).
     * @return True if move is valid and number is not used.
     */
    bool update_board(Move<int>* move) override {
        if (!move) return false;
        int x = move->get_x();
        int y = move->get_y();
        int val = move->get_symbol();

        if (x < 0 || x >= rows || y < 0 || y >= columns) return false;
        if (board[x][y] != 0) {
            cout << "Invalid move: Cell (" << x << "," << y << ") is already occupied.\n";
            return false; // occupied
        }
        // Validate value is allowed (1..9). We don't check ownership here (UI/Player should ensure)
        if (val < 1 || val > 9) return false;

        // Also ensure number not already used on board
        if (is_number_used(val)) 
        {
            cout << "Invalid move: Number " << val << " has already been used on the board. Choose another.\n";
            return false;
        }

        board[x][y] = val;
        ++n_moves;
        return true;
    }

    /**
     * @brief Checks if the player wins (sum of line is 15).
     * @param player Pointer to the player.
     * @return True if player has a winning line.
     */
    bool is_win(Player<int>* player) override {
        if (!player) return false;
        int playerFlag = player->get_symbol(); // 1 => odd-player, 2 => even-player

        // check rows
        for (int i = 0; i < 3; ++i) {
            if (line_sum(i, 0, 0, 1) == 15 && line_belongs_to_player(i, 0, 0, 1, playerFlag))
                return true;
        }
        // check cols
        for (int j = 0; j < 3; ++j) {
            if (line_sum(0, j, 1, 0) == 15 && line_belongs_to_player(0, j, 1, 0, playerFlag))
                return true;
        }
        // main diagonal
        if (line_sum(0, 0, 1, 1) == 15 && line_belongs_to_player(0, 0, 1, 1, playerFlag))
            return true;
        // anti-diagonal
        if (line_sum(0, 2, 1, -1) == 15 && line_belongs_to_player(0, 2, 1, -1, playerFlag))
            return true;

        return false;
    }

    /**
     * @brief Checks if the player loses (if opponent has winning line).
     * @return True if opponent wins.
     */
    bool is_lose(Player<int>* player) override {
        if (!player) return false;
        int opponentFlag = (player->get_symbol() == 1) ? 2 : 1;

        // check all lines for opponent
        for (int i = 0; i < 3; ++i) {
            if (line_sum(i, 0, 0, 1) == 15 && line_belongs_to_player(i, 0, 0, 1, opponentFlag))
                return true;
        }
        for (int j = 0; j < 3; ++j) {
            if (line_sum(0, j, 1, 0) == 15 && line_belongs_to_player(0, j, 1, 0, opponentFlag))
                return true;
        }
        if (line_sum(0, 0, 1, 1) == 15 && line_belongs_to_player(0, 0, 1, 1, opponentFlag))
            return true;
        if (line_sum(0, 2, 1, -1) == 15 && line_belongs_to_player(0, 2, 1, -1, opponentFlag))
            return true;

        return false;
    }

    /**
     * @brief Checks for a draw.
     * @return True if board is full and no winner.
     */
    bool is_draw(Player<int>* player) override {
        (void)player;
        // draw when board full and no winner
        if (n_moves < rows * columns) return false;
        if (any_winning_line()) return false;
        return true;
    }
    /**
     * @brief Checks if game is over (win, lose, or draw).
     */
    bool game_is_over(Player<int>* player) override {
        return is_win(player) || is_lose(player) || is_draw(player);
    }

    /**
     * @brief Getter for the board matrix.
     */
    vector<vector<int>> get_board_matrix() const {
        return board;
    }

private:
    /**
     * @brief Checks if a number has already been played on the board.
     * @param val The number to check.
     * @return True if used, False otherwise.
     */
    bool is_number_used(int val) const {
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < columns; ++j)
                if (board[i][j] == val) return true;
        return false;
    }

    /**
     * @brief Calculates the sum of a line (row, col, or diagonal).
     * @param sx Starting row index.
     * @param sy Starting column index.
     * @param dx Row increment (delta).
     * @param dy Column increment (delta).
     * @return Sum of the numbers in that line.
     */
    int line_sum(int sx, int sy, int dx, int dy) const {
        int s = 0;
        for (int k = 0; k < 3; ++k) {
            int r = sx + k * dx;
            int c = sy + k * dy;
            s += board[r][c];
        }
        return s;
    }

    /**
     * @brief Checks if a line belongs to a specific player (Odd or Even parity).
     * @param sx Starting row index.
     * @param sy Starting column index.
     * @param dx Row delta.
     * @param dy Column delta.
     * @param playerFlag 1 for Odd, 2 for Even.
     * @return True if all numbers in the line match the player's parity.
     */
    bool line_belongs_to_player(int sx, int sy, int dx, int dy, int playerFlag) const {
        for (int k = 0; k < 3; ++k) {
            int r = sx + k * dx;
            int c = sy + k * dy;
            int val = board[r][c];
            if (val == 0) return false;
            if (playerFlag == 1) {
                if (val % 2 == 0) return false;
            }
            else {
                if (val % 2 != 0) return false;
            }
        }
        return true;
    }

    /**
     * @brief Checks if ANY winning line exists (used for Draw logic).
     * @return True if there is a winner.
     */
    bool any_winning_line() const {
        // check rows
        for (int i = 0; i < 3; ++i) {
            int s = line_sum(i, 0, 0, 1);
            if (s == 15 && (line_belongs_to_player(i, 0, 0, 1, 1) || line_belongs_to_player(i, 0, 0, 1, 2)))
                return true;
        }
        // cols
        for (int j = 0; j < 3; ++j) {
            int s = line_sum(0, j, 1, 0);
            if (s == 15 && (line_belongs_to_player(0, j, 1, 0, 1) || line_belongs_to_player(0, j, 1, 0, 2)))
                return true;
        }
        // diags
        if (line_sum(0, 0, 1, 1) == 15 && (line_belongs_to_player(0, 0, 1, 1, 1) || line_belongs_to_player(0, 0, 1, 1, 2)))
            return true;
        if (line_sum(0, 2, 1, -1) == 15 && (line_belongs_to_player(0, 2, 1, -1, 1) || line_belongs_to_player(0, 2, 1, -1, 2)))
            return true;
        return false;
    }

}; // end class
