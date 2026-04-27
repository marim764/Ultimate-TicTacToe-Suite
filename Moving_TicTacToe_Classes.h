#ifndef MOVING_TICTACTOE_CLASSES_H
#define MOVING_TICTACTOE_CLASSES_H

#include "BoardGame_Classes.h"
using namespace std;

/**
 * @class Moving_XO_Board
 * @brief 4x4 Tic-Tac-Toe board where players start with 4 tokens each and move tokens.
 *
 * Rules implemented:
 *  - Board size: 4x4
 *  - Starting layout:
 *      Row 0:  O X O X
 *      Row 1:  . . . .
 *      Row 2:  . . . .
 *      Row 3:  X O X O
 *  - On a turn, a player picks one of his tokens and moves it to an adjacent
 *    (horizontal or vertical) empty square. No diagonal moves, no jumping.
 *  - Winning condition: first player to align THREE of their tokens in a row,
 *    column, or diagonal wins.
 */
class Moving_XO_Board : public Board<char> {
private:
    /// Symbol representing an empty cell
    char blank_symbol = '.';

public:
    /**
     * @brief Constructor. Initializes 4x4 board with starting layout.
     */
    Moving_XO_Board();

    /**
     * @brief Updates the board with a move or clears a cell.
     * @param move Pointer to the Move object.
     * @return true if the move or clear is valid.
     */
    bool update_board(Move<char>* move) override;

    /**
     * @brief Checks if the given player has won (3-in-a-row).
     * @param player Pointer to Player object.
     * @return true if player has 3 tokens aligned.
     */
    bool is_win(Player<char>* player) override;

    /**
     * @brief Misère not used; always returns false.
     */
    bool is_lose(Player<char>*) override { return false; };

    /**
     * @brief Checks if the game is a draw (no simple draw condition).
     * @param player Pointer to Player object (unused).
     * @return false; draw not handled in moving-XO variant.
     */
    bool is_draw(Player<char>* player) override;

    /**
     * @brief Checks if the game is over (win or draw).
     * @param player Pointer to Player object.
     * @return true if game is over.
     */
    bool game_is_over(Player<char>* player) override;
};

#endif // MOVING_TICTACTOE_CLASSES_H
