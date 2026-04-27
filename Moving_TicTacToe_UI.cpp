#include "Moving_TicTacToe_UI.h"
#include "Moving_TicTacToe_Classes.h"
#include <iostream>
#include <cstdlib>
#include <vector>
#include <ctime>

using namespace std;

/**
 * @brief Constructor. Initializes UI with game title and 3 players.
 * Seeds random number generator for computer moves.
 */
Moving_XO_UI::Moving_XO_UI()
    : UI<char>("Welcome to 4x4 Moving Tic-Tac-Toe (align 3 to win)", 3) {
    srand((unsigned)time(nullptr));
}

/**
 * @brief Creates a player (human or computer).
 * @param name Player's name.
 * @param symbol Player's symbol ('X' or 'O').
 * @param type Player type (HUMAN or COMPUTER).
 * @return Pointer to created Player object.
 */
Player<char>* Moving_XO_UI::create_player(string& name, char symbol, PlayerType type) {
    cout << "Creating " << (type == PlayerType::HUMAN ? "Human" : "Computer")
        << " player: " << name << " (" << symbol << ")\n";
    return new Player<char>(name, symbol, type);
}

/**
 * @brief Gets a move from the player (human input or computer random move).
 *
 * For humans:
 *  - Enter source x,y and destination x,y.
 *  - Validates: source contains player's symbol, dest is empty, orthogonally adjacent.
 *  - Clears source cell via board->update_board(mark==0), then returns dest move.
 *
 * For computer:
 *  - Builds list of all movable tokens and possible destinations.
 *  - Picks one randomly, clears source, returns destination move.
 *
 * @param player Pointer to Player object.
 * @return Pointer to Move object representing the placement at destination.
 */
Move<char>* Moving_XO_UI::get_move(Player<char>* player) {
    int sx, sy, dx, dy;
    Board<char>* boardPtr = player->get_board_ptr();

    if (!boardPtr) {
        cout << "Error: board pointer not set for player.\n";
        return new Move<char>(-1, -1, player->get_symbol());
    }

    if (player->get_type() == PlayerType::HUMAN) {
        while (true) {
            cout << "\nEnter source x y and destination x y (0 to 3). Example: 0 1 1 1\n";
            cin >> sx >> sy >> dx >> dy;

            // validate input
            if (cin.fail() || sx < 0 || sx >= boardPtr->get_rows() || sy < 0 || sy >= boardPtr->get_columns()
                || dx < 0 || dx >= boardPtr->get_rows() || dy < 0 || dy >= boardPtr->get_columns()) {
                cout << "Invalid coordinates, try again.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }

            // source must contain player's symbol
            if (boardPtr->get_cell(sx, sy) != player->get_symbol()) {
                cout << "Source cell does not contain your token.\n";
                continue;
            }

            // destination must be empty
            if (boardPtr->get_cell(dx, dy) != '.') {
                cout << "Destination is not empty.\n";
                continue;
            }

            // must be orthogonally adjacent
            int manhattan = abs(dx - sx) + abs(dy - sy);
            if (manhattan != 1) {
                cout << "Destination must be orthogonally adjacent.\n";
                continue;
            }

            // clear source
            Move<char> clearMove(sx, sy, 0);
            if (!boardPtr->update_board(&clearMove)) {
                cout << "Failed to clear source cell. Try again.\n";
                continue;
            }

            return new Move<char>(dx, dy, player->get_symbol());
        }
    }
    else { // COMPUTER
        vector<pair<pair<int, int>, pair<int, int>>> candidates;

        for (int r = 0; r < boardPtr->get_rows(); ++r) {
            for (int c = 0; c < boardPtr->get_columns(); ++c) {
                if (boardPtr->get_cell(r, c) == player->get_symbol()) {
                    const int dr[4] = { -1, 1, 0, 0 };
                    const int dc[4] = { 0, 0, -1, 1 };
                    for (int k = 0; k < 4; ++k) {
                        int nr = r + dr[k];
                        int nc = c + dc[k];
                        if (nr >= 0 && nr < boardPtr->get_rows() && nc >= 0 && nc < boardPtr->get_columns()) {
                            if (boardPtr->get_cell(nr, nc) == '.') {
                                candidates.push_back({ {r, c}, {nr, nc} });
                            }
                        }
                    }
                }
            }
        }

        if (candidates.empty()) {
            return new Move<char>(-1, -1, player->get_symbol());
        }

        auto pick = candidates[rand() % candidates.size()];
        sx = pick.first.first;
        sy = pick.first.second;
        dx = pick.second.first;
        dy = pick.second.second;

        // clear source
        Move<char> clearMove(sx, sy, 0);
        boardPtr->update_board(&clearMove);

        cout << "\nComputer moves from (" << sx << "," << sy << ") to (" << dx << "," << dy << ")\n";
        return new Move<char>(dx, dy, player->get_symbol());
    }
}
