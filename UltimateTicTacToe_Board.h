/**
 * @file UltimateTicTacToe_Board.h
 * @brief Defines the board class for Ultimate Tic-Tac-Toe game.
 *
 * Ultimate Tic-Tac-Toe is played on a 9x9 board divided into 3x3 small boards.
 * Players win small boards, and winning the main 3x3 of small boards wins the game.
 */

#ifndef ULTIMATETICTACTOE_BOARD_H
#define ULTIMATETICTACTOE_BOARD_H

#include "BoardGame_Classes.h"
#include <vector>

using namespace std;

/**
 * @class UltimateTicTacToe_Board
 * @brief Represents the Ultimate Tic-Tac-Toe board with small boards tracking.
 */
class UltimateTicTacToe_Board : public Board<char> {
private:
    char blank = '.';                    ///< Character for empty cells
    char main_claims[3][3];              ///< Tracks the winner of each 3x3 small board

    /**
     * @brief Checks if a 3x3 small board is won by a player.
     * @param br Row index of small board (0-2)
     * @param bc Column index of small board (0-2)
     * @param sym Player's symbol
     * @return true if the small board is won
     */
    bool check_small_win(int br, int bc, char sym) const;

    /**
     * @brief Checks if the main 3x3 board is won by a player.
     * @param sym Player's symbol
     * @return true if the main board is won
     */
    bool check_main_win(char sym) const;

public:
    /**
     * @brief Constructor initializes a 9x9 board and empty main claims.
     */
    UltimateTicTacToe_Board();

    /**
     * @brief Updates the board with a player's move.
     * @param m Pointer to the move object
     * @return true if move applied successfully, false otherwise
     */
    bool update_board(Move<char>* m) override;

    /**
     * @brief Checks if the given player has won the game.
     * @param p Pointer to the player
     * @return true if the player won
     */
    bool is_win(Player<char>* p) override;

    /**
     * @brief Checks if the player has lost.
     * @return Always false (not implemented)
     */
    bool is_lose(Player<char>*) override { return false; }

    /**
     * @brief Checks if the game ended in a draw.
     * @param p Pointer to the player
     * @return true if board is full and no winner
     */
    bool is_draw(Player<char>* p) override;

    /**
     * @brief Determines if the game is over.
     * @param p Pointer to the player
     * @return true if win or draw
     */
    bool game_is_over(Player<char>* p) override;

    /**
     * @brief Returns a copy of the main 3x3 claims board.
     * @return 3x3 vector representing the winner of each small board
     */
    vector<vector<char>> get_main_claims() const;
};

#endif // ULTIMATETICTACTOE_BOARD_H
