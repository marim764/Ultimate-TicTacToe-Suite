#ifndef MEMORY_TICTACTOE_CLASSES_H
#define MEMORY_TICTACTOE_CLASSES_H

#include "BoardGame_Classes.h"
#include <vector>
#include <utility>
using namespace std;

/**
 * @brief Class representing the Memory Tic-Tac-Toe board.
 * Inherits from Board<char> and tracks moves for X and O players.
 */
class MemoryTicTacToe_Board : public Board<char> {
private:
    /// Stores moves made by player X as (row, column) pairs
    vector<pair<int, int>> x_moves;

    /// Stores moves made by player O as (row, column) pairs
    vector<pair<int, int>> o_moves;

public:
    /**
     * @brief Constructor. Initializes a 3x3 board with empty cells.
     */
    MemoryTicTacToe_Board();

    /**
     * @brief Updates the board with a given move.
     * @param move Pointer to the Move object containing position and symbol.
     * @return true if the move is valid and placed successfully, false otherwise.
     */
    bool update_board(Move<char>* move);

    /**
     * @brief Checks if the specified player has won.
     * @param player Pointer to the Player object.
     * @return true if the player has three in a row, column, or diagonal.
     */
    bool is_win(Player<char>* player);

    /**
     * @brief Checks if the specified player has lost.
     * @param player Pointer to the Player object.
     * @return Always returns false (Memory Tic-Tac-Toe doesn't use this).
     */
    bool is_lose(Player<char>*) { return false; }

    /**
     * @brief Checks if the game is a draw.
     * @param player Pointer to any Player object.
     * @return true if all cells are filled and no player has won.
     */
    bool is_draw(Player<char>* player);

    /**
     * @brief Determines if the game is over.
     * @param player Pointer to any Player object.
     * @return true if the game is won or drawn.
     */
    bool game_is_over(Player<char>* player);

    /**
     * @brief Reveals the full board and prints it to console.
     */
    void reveal_board() const;

    /**
     * @brief Checks if a specific cell is already occupied.
     * @param x Row index.
     * @param y Column index.
     * @return true if cell contains 'X' or 'O', false otherwise.
     */
    bool is_cell_occupied(int x, int y) const;
};

/**
 * @brief Class handling the UI for Memory Tic-Tac-Toe.
 * Inherits from UI<char> and provides methods for player input and display.
 */
class MemoryTicTacToe_UI : public UI<char> {
public:
    /**
     * @brief Constructor. Sets up the game title and number of players.
     */
    MemoryTicTacToe_UI();

    /// Destructor
    ~MemoryTicTacToe_UI() {}

    /**
     * @brief Creates a player.
     * @param name Player's name.
     * @param symbol Player's symbol ('X' or 'O').
     * @param type Player type (HUMAN or COMPUTER).
     * @return Pointer to the created Player object.
     */
    Player<char>* create_player(string& name, char symbol, PlayerType type);

    /**
     * @brief Gets a move from the player (human input or AI random choice).
     * @param player Pointer to the Player object.
     * @return Pointer to the created Move object.
     */
    virtual Move<char>* get_move(Player<char>* player);

    /**
     * @brief Displays the board with all cells hidden as '?'.
     */
    void display_hidden_board() const;

    /**
     * @brief Displays instructions and rules for Memory Tic-Tac-Toe.
     */
    void display_instructions() const;
};

#endif
