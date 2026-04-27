/**
 * @file PyramidTicTacToe_Classes.h
 * @brief Defines classes for the Pyramid Tic-Tac-Toe game.
 *
 * Represents a Tic-Tac-Toe variant played on a pyramid-shaped board.
 * The pyramid consists of:
 * - 1 cell at the top (row 0)
 * - 3 cells in the middle (row 1)
 * - 5 cells at the base (row 2)
 */

#ifndef PYRAMIDTICTACTOE_CLASSES_H
#define PYRAMIDTICTACTOE_CLASSES_H

#include "BoardGame_Classes.h"
#include <string>
#include <vector>

using namespace std;

/**
 * @class PyramidTicTacToe_Board
 * @brief Represents the pyramid-shaped Tic-Tac-Toe game board.
 *
 * This class implements the rules, board layout, and win/draw conditions
 * for the Pyramid Tic-Tac-Toe game. It inherits from Board<char>.
 */
class PyramidTicTacToe_Board : public Board<char> {
private:
    char blank_symbol = '.';  ///< Character representing an empty cell.

    /**
     * @brief Checks if a given (x, y) position is valid on the pyramid board.
     *
     * Valid positions:
     * - Row 0: only column 2
     * - Row 1: columns 1, 2, 3
     * - Row 2: columns 0 to 4
     *
     * @param x Row index
     * @param y Column index
     * @return true if position is inside the pyramid shape, false otherwise
     */
    bool is_valid_position(int x, int y) const;

public:
    /**
     * @brief Constructs a Pyramid Tic-Tac-Toe board with 3 rows and 5 columns.
     *
     * All cells are initialized to blank_symbol ('.').
     */
    PyramidTicTacToe_Board();

    /**
     * @brief Updates the board by placing the player’s move.
     *
     * The move is applied only if:
     * - The cell is inside the pyramid shape.
     * - The cell is empty.
     *
     * @param move Pointer to the move object containing coordinates and symbol.
     * @return true if the move is successfully applied, false otherwise.
     */
    bool update_board(Move<char>* move) override;

    /**
     * @brief Checks whether the given player has achieved a winning pattern.
     *
     * Winning conditions include:
     * - Horizontal 3-in-a-row (middle or base rows)
     * - Vertical 3-in-a-row (center column)
     * - Diagonal pyramid alignments
     *
     * @param player Pointer to the player whose win condition is checked.
     * @return true if the player has won, false otherwise.
     */
    bool is_win(Player<char>* player) override;

    /**
     * @brief Checks if the player has lost.
     *
     * This variant does not define a losing condition for a single player.
     *
     * @param player Unused.
     * @return Always returns false.
     */
    bool is_lose(Player<char>* player) override { return false; }

    /**
     * @brief Determines if the match ended in a draw.
     *
     * A draw occurs when:
     * - All 9 valid pyramid cells are filled, AND
     * - No player has won.
     *
     * @param player Pointer to the player being evaluated.
     * @return true if game is a draw, false otherwise.
     */
    bool is_draw(Player<char>* player) override;

    /**
     * @brief Indicates whether the game has ended (either win or draw).
     *
     * @param player Player to evaluate the status for.
     * @return true if game is over, false otherwise.
     */
    bool game_is_over(Player<char>* player) override;
};

/**
 * @class PyramidTicTacToe_UI
 * @brief Handles user interaction for the Pyramid Tic-Tac-Toe game.
 *
 * Responsible for:
 * - Creating players
 * - Retrieving moves (human or computer)
 * - Displaying the pyramid board
 */
class PyramidTicTacToe_UI : public UI<char> {
public:
    /**
     * @brief Constructs the Pyramid Tic-Tac-Toe UI.
     *
     * Initializes base UI with a 3-row board.
     */
    PyramidTicTacToe_UI();

    /**
     * @brief Destructor (empty).
     */
    ~PyramidTicTacToe_UI() {}

    /**
     * @brief Creates a player object for the game.
     *
     * @param name The player's name.
     * @param symbol The character symbol (X or O).
     * @param type HUMAN or COMPUTER.
     * @return A dynamically allocated Player<char> object.
     */
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;

    /**
     * @brief Retrieves the player's move.
     *
     * - If HUMAN: reads input from console.
     * - If COMPUTER: selects a random valid empty pyramid cell.
     *
     * @param player Pointer to the player whose move is being requested.
     * @return A new Move<char> containing the chosen position and symbol.
     */
    Move<char>* get_move(Player<char>* player) override;

    /**
     * @brief Displays the board in pyramid visual layout.
     *
     * Pyramid format example:
     *        X
     *      O X O
     *    X O . . X
     *
     * @param matrix 2D vector representing board state.
     */
    void display_board_matrix(const vector<vector<char>>& matrix) const override;
};

#endif // PYRAMIDTICTACTOE_CLASSES_H
