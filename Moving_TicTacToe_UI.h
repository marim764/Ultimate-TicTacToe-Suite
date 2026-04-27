#ifndef MOVING_TICTACTOE_UI_H
#define MOVING_TICTACTOE_UI_H

#include "BoardGame_Classes.h"

/**
 * @class Moving_XO_UI
 * @brief UI class for 4x4 Moving Tic-Tac-Toe game.
 *
 * Handles human and computer player interactions, including:
 *  - Creating players
 *  - Getting moves (source and destination for moving tokens)
 */
class Moving_XO_UI : public UI<char> {
public:
    /**
     * @brief Constructor. Initializes the UI with the game title.
     */
    Moving_XO_UI();

    /// Destructor
    ~Moving_XO_UI() {}

    /**
     * @brief Creates a player (human or computer).
     * @param name Player's name.
     * @param symbol Player's symbol ('X' or 'O').
     * @param type Player type (HUMAN or COMPUTER).
     * @return Pointer to the created Player object.
     */
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;

    /**
     * @brief Gets a move from the player.
     *
     * For humans:
     *  - Enter source x,y and destination x,y.
     *  - Validates ownership, empty destination, and orthogonal adjacency.
     *
     * For computer:
     *  - Randomly selects a movable token and a valid destination.
     *
     * @param player Pointer to the Player object.
     * @return Pointer to the Move object representing the destination placement.
     */
    Move<char>* get_move(Player<char>* player) override;
};

#endif // MOVING_TICTACTOE_UI_H
