#ifndef DIAMONDTICTACTOE_UI_H
#define DIAMONDTICTACTOE_UI_H

#include "BoardGame_Classes.h"
#include <string>

/**
 * @brief UI controller for Diamond Tic-Tac-Toe.
 */
class DiamondTicTacToe_UI : public UI<char> {
private:
    bool instructions_shown;  ///< Tracks if instructions were already displayed.

public:
    /**
     * @brief Initializes the UI.
     */
    DiamondTicTacToe_UI();

    /**
     * @brief Creates a new player.
     * @param name Player name.
     * @param symbol Player symbol ('X'/'O').
     * @param type HUMAN or COMPUTER.
     */
    Player<char>* create_player(std::string& name, char symbol, PlayerType type) override;

    /**
     * @brief Gets a move from human or generates one for computer.
     * @param player Player requesting the move.
     * @return Pointer to Move object.
     */
    Move<char>* get_move(Player<char>* player) override;

    /**
     * @brief Displays the board in a diamond-shaped layout.
     * @param matrix 5x5 board matrix.
     */
    void display_board_matrix(const std::vector<std::vector<char>>& matrix) const override;

    /**
     * @brief Shows game instructions once.
     */
    void show_instructions();
};

#endif
