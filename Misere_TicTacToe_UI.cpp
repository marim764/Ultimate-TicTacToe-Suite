#include "Misere_TicTacToe_UI.h"
#include <iostream>
#include <cstdlib>

using namespace std;

/**
 * @brief Constructor. Initializes UI with game title and 3 players.
 */
Misere_TicTacToe_UI::Misere_TicTacToe_UI()
    : UI<char>("Welcome to Misère Tic-Tac-Toe (avoid making 3-in-a-row)", 3) {}

/**
 * @brief Creates a player.
 * @param name Player's name.
 * @param symbol Player's symbol ('X' or 'O').
 * @param type Player type (HUMAN or COMPUTER).
 * @return Pointer to the created Player object.
 */
Player<char>* Misere_TicTacToe_UI::create_player(string& name, char symbol, PlayerType type) {
    cout << "Creating " << (type == PlayerType::HUMAN ? "Human" : "Computer")
        << " player: " << name << " (" << symbol << ")\n";
    return new Player<char>(name, symbol, type);
}

/**
 * @brief Gets a move from the player (human input or computer random move).
 * @param player Pointer to the Player object.
 * @return Pointer to the created Move object.
 */
Move<char>* Misere_TicTacToe_UI::get_move(Player<char>* player) {
    int x = 0, y = 0;

    if (player->get_type() == PlayerType::HUMAN) {
        cout << "\nPlease enter your move x and y (0 to 2): ";
        cin >> x >> y;
    }
    else {
        // simple random computer move
        // Keep picking until we select an empty cell
        do {
            x = rand() % player->get_board_ptr()->get_rows();
            y = rand() % player->get_board_ptr()->get_columns();
        } while (player->get_board_ptr()->get_cell(x, y) != '.');
    }

    return new Move<char>(x, y, player->get_symbol());
}
