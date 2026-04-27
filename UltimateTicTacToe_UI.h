#ifndef ULTIMATETICTACTOE_UI_H
#define ULTIMATETICTACTOE_UI_H

#include "BoardGame_Classes.h"

/**
 * @brief UI class for Ultimate Tic-Tac-Toe.
 */
class UltimateTicTacToe_UI : public UI<char> {
public:
    /// Constructor
    UltimateTicTacToe_UI();

    /// Create player
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;

    /// Get move from player
    Move<char>* get_move(Player<char>* player) override;

    /// Display 9x9 board
    void display_board_matrix(const vector<vector<char>>& m) const override;
};

#endif
