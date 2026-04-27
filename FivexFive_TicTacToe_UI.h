/**
 * @file FivexFive_TicTacToe_UI.h
 * @brief Header file for 5x5 Tic-Tac-Toe User Interface.
 */

#pragma once
#include "BoardGame_Classes.h"
#include "FivexFive_TicTacToe_Board.h"
#include <iostream>
#include <vector>
#include <limits>

using namespace std;
/**
 * @class FivexFive_TicTacToe_UI
 * @brief UI class for handling I/O for 5x5 Tic-Tac-Toe.
 */
class FivexFive_TicTacToe_UI : public UI<char> {
private:
    FivexFive_TicTacToe_Board* boardPtr; ///< Pointer to board for calling AI functions.

public:
    /**
     * @brief Constructor.
     * @param b Pointer to the game board.
     */
    FivexFive_TicTacToe_UI(FivexFive_TicTacToe_Board* b);

    /**
     * @brief Creates a player (Human or Computer).
     * @param name Player's name.
     * @param symbol Player's symbol.
     * @param type Player type (Human/Computer).
     * @return Pointer to the created player.
     */
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;

    /**
     * @brief Gets a move. Uses AI logic if player is Computer.
     * @param player Pointer to the player.
     * @return Pointer to the Move object.
     */
    Move<char>* get_move(Player<char>* player) override;

    /**
     * @brief Displays the board state.
     * @param matrix 2D vector representing board state.
     */
    void display_board_matrix(const vector<vector<char>>& matrix) const override;
};
