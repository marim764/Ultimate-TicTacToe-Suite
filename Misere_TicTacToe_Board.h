#ifndef MISERE_TICTACTOE_BOARD_H
#define MISERE_TICTACTOE_BOARD_H

#include "BoardGame_Classes.h"

/**
 * @brief Class representing a Misère Tic-Tac-Toe board.
 * Inherits from Board<char> and implements misère rules:
 * completing 3 in a row = LOSS for the player who moved.
 */
class Misere_TicTacToe_Board : public Board<char> {
private:
    /// Symbol representing an empty cell
    char blank_symbol = '.';

    /**
     * @brief Helper function to check if a symbol has three in a row.
     * @param sym Symbol to check ('X' or 'O').
     * @return true if there are 3 in a row, column, or diagonal.
     */
    bool has_three_in_row(char sym) const;

public:
    /**
     * @brief Constructor. Initializes 3x3 board with blank symbols.
     */
    Misere_TicTacToe_Board();

    /**
     * @brief Updates the board with a move or undo.
     * @param move Pointer to Move object.
     * @return true if the move/undo is valid.
     */
    bool update_board(Move<char>* move) override;

    /**
     * @brief Misère: completing 3 in a row is not a win.
     * @return Always returns false.
     */
    bool is_win(Player<char>*) override { return false; }

    /**
     * @brief Checks if the current player has lost (3-in-row).
     * @param player Pointer to Player object.
     * @return true if player completed 3 in a row.
     */
    bool is_lose(Player<char>* player) override;

    /**
     * @brief Checks if the game is a draw.
     * @param player Pointer to Player (unused).
     * @return true if board full and no 3-in-row exists.
     */
    bool is_draw(Player<char>* player) override;

    /**
     * @brief Checks if the game is over.
     * @param player Pointer to Player object.
     * @return true if player lost or game is draw.
     */
    bool game_is_over(Player<char>* player) override;
};

#endif // MISERE_TICTACTOE_BOARD_H
