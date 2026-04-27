#ifndef DIAMONDTICTACTOE_BOARD_H
#define DIAMONDTICTACTACTOE_BOARD_H

#include "BoardGame_Classes.h"
#include <vector>

/**
 * @brief Diamond Tic-Tac-Toe board (5x5) with custom win rules.
 */
class DiamondTicTacToe_Board : public Board<char> {
private:
    char blank = '.';

    /**
     * @brief Checks if a line of given length exists from (x, y) in direction (dx, dy).
     */
    bool has_line(int x, int y, char sym, int length, int dx, int dy) const;

public:
    /**
     * @brief Initializes a 5x5 board.
     */
    DiamondTicTacToe_Board();

    ~DiamondTicTacToe_Board() {}

    /**
     * @brief Places a move on the board.
     * @param move Player move.
     * @return true if move is valid.
     */
    bool update_board(Move<char>* move) override;

    /**
     * @brief Checks win condition.
     * @return true if player wins.
     */
    bool is_win(Player<char>* player) override;

    /**
     * @brief Checks draw condition.
     * @return true if board is full.
     */
    bool is_draw(Player<char>* player) override;

    /**
     * @brief Diamond version has no lose condition.
     */
    bool is_lose(Player<char>* player) override { return false; }

    /**
     * @brief Checks if game ended (win or draw).
     */
    bool game_is_over(Player<char>* player) override;
};

#endif
