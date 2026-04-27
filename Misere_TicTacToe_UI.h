#ifndef MISERE_TICTACTOE_UI_H
#define MISERE_TICTACTOE_UI_H

#include "BoardGame_Classes.h"

/**
 * @brief Class handling the UI for Misère Tic-Tac-Toe.
 * Inherits from UI<char> and provides methods for player creation and moves.
 */
class Misere_TicTacToe_UI : public UI<char> {
public:
    /**
     * @brief Constructor. Sets up the game title and 3 players.
     */
    Misere_TicTacToe_UI();

    /// Destructor
    ~Misere_TicTacToe_UI() {}

    /**
     * @brief Creates a player.
     * @param name Player's name.
     * @param symbol Player's symbol ('X' or 'O').
     * @param type Player type (HUMAN or COMPUTER).
     * @return Pointer to the created Player object.
     */
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;

    /**
     * @brief Gets a move from the player (human input or computer random move).
     * @param player Pointer to the Player object.
     * @return Pointer to the created Move object.
     */
    Move<char>* get_move(Player<char>* player) override;
};

#endif // MISERE_TICTACTOE_UI_H
