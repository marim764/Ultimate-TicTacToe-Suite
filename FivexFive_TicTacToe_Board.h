/**
 * @file FivexFive_TicTacToe_Board.h
 * @brief Header file for 5x5 Tic-Tac-Toe Board class.
 */
#pragma once
#include "BoardGame_Classes.h"
#include <vector>
#include <iostream>

using namespace std;
/**
 * @class FivexFive_TicTacToe_Board
 * @brief Represents a 5x5 board. Game ends when full. Winner has most 3-in-a-row sequences.
 */

class FivexFive_TicTacToe_Board : public Board<char> {
public:
    /**
     * @brief Constructor to initialize the 5x5 board.
     */
    FivexFive_TicTacToe_Board();

    /**
     * @brief Updates the board with the player's move.
     * @param move The move to be executed.
     * @return True if valid, False otherwise.
     */
    bool update_board(Move<char>* move) override;

    /**
     * @brief Checks if the player wins (by having more 3-in-a-row sequences).
     * @param player Pointer to the player.
     * @return True if player has higher score than opponent.
     */
    bool is_win(Player<char>* player) override;

    /**
     * @brief Checks if the player loses.
     * @return Always false for this game.
     */
    bool is_lose(Player<char>* player) override { return false; }

    /**
     * @brief Checks for a draw (equal scores when board is full).
     * @param player Pointer to the player.
     * @return True if draw.
     */
    bool is_draw(Player<char>* player) override;

    /**
     * @brief Checks if the game is over (board is full).
     * @return True if board is full (25 moves).
     */
    bool game_is_over(Player<char>* player) override;

    /**
     * @brief Counts occurrences of 3 consecutive symbols.
     * @param symbol The player's symbol (X or O).
     * @return Number of 3-in-a-row sequences.
     */
    int count_three_in_a_row(char symbol) const;

    /**
     * @brief Calculates the best move for the AI using a greedy strategy.
     * @param symbol The AI player's symbol.
     * @return A pair containing the best {row, col}.
     */
    pair<int, int> get_best_move(char symbol);
};
