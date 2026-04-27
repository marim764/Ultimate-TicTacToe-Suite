/**
 * @file Obstacles_TicTacToe_UI.h
 * @brief Header file for Obstacles Tic-Tac-Toe UI.
 */
#pragma once
#include "BoardGame_Classes.h"
#include <iostream>
#include <vector>
#include <limits> 

using namespace std;

/**
 * @class Obstacles_TicTacToe_UI
 * @brief Handles I/O for the Obstacles game.
 */
class Obstacles_TicTacToe_UI : public UI<char> 
{
public:
    /**
     * @brief Constructor to initialize UI.
     */
    Obstacles_TicTacToe_UI();

    /**
     * @brief Creates a player.
     * @param name Player name.
     * @param symbol Player symbol.
     * @param type Human or Computer.
     */
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;

    /**
     * @brief Gets move from player or generates random move for AI.
     */
    Move<char>* get_move(Player<char>* player) override;

    /**
     * @brief Displays the 6x6 board grid.
     */
    void display_board_matrix(const vector<vector<char>>& matrix) const override;
};