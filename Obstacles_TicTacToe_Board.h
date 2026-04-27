/**
 * @file Obstacles_TicTacToe_Board.h
 * @brief Header file for Obstacles Tic-Tac-Toe Board.
 */
#pragma once
#include "BoardGame_Classes.h"
#include <vector>
#include <iostream>

using namespace std;

/**
 * @class Obstacles_TicTacToe_Board
 * @brief 6x6 Board where obstacles are added every round.
 * Goal is to get 4-in-a-row.
 */
class Obstacles_TicTacToe_Board : public Board<char> 
{
private:
    char empty_symbol; ///< Symbol for empty cell.
    char obstacle_symbol; ///< Symbol for obstacle.
    int total_moves_made; ///< Counter for total moves.

    /**
     * @brief Adds 2 random obstacles to the board.
     */
    void add_random_obstacles();

    /**
     * @brief Helper to check for 4 consecutive symbols.
     */
    bool check_line_for_win(int r_start, int c_start, int r_delta, int c_delta, char player_symbol) const;

public:

    /**
     * @brief Constructor to initialize 6x6 board.
     */
    Obstacles_TicTacToe_Board();

    /**
     * @brief Updates board with move and adds obstacles if needed.
     * @param move Pointer to the move.
     * @return True if move is valid.
     */
    bool update_board(Move<char>* move) override;

    /**
     * @brief Checks if player won (4-in-a-row).
     * @return True if winner found.
     */
    bool is_win(Player<char>* player) override;

    /**
     * @brief Checks if player loses (Always false here).
     */
    bool is_lose(Player<char>* player) override { return false; }

    /**
     * @brief Checks for draw (board full, no winner).
     */
    bool is_draw(Player<char>* player) override;

    /**
     * @brief Checks if game is over.
     */
    bool game_is_over(Player<char>* player) override;
};