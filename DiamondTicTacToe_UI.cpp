#include "DiamondTicTacToe_UI.h"
#include "DiamondTicTacToe_Board.h"
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <vector>
#include <string>

using namespace std;

/**
 * @brief UI handler for Diamond Tic-Tac-Toe.
 */
DiamondTicTacToe_UI::DiamondTicTacToe_UI()
    : UI(3), instructions_shown(false) {
    srand(static_cast<unsigned>(time(0)));
}

/**
 * @brief Creates a new player.
 * @param name Player name.
 * @param symbol Player mark.
 * @param type Human or Computer.
 */
Player<char>* DiamondTicTacToe_UI::create_player(string& name, char symbol, PlayerType type) {
    return new Player<char>(name, symbol, type);
}

/**
 * @brief Gets a move from a human or chooses random move for computer.
 * @param p Player requesting a move.
 * @return Pointer to created Move.
 */
Move<char>* DiamondTicTacToe_UI::get_move(Player<char>* p) {
    int x, y;

    if (p->get_type() == PlayerType::HUMAN) {
        cout << "\n" << p->get_name() << " (" << p->get_symbol()
            << "), enter row (0-4) and column (0-4): ";
        cin >> x >> y;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        while (x < 0 || x > 4 || y < 0 || y > 4) {
            cout << "Invalid position. Enter row (0-4) and column (0-4): ";
            cin >> x >> y;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    else {
        vector<pair<int, int>> available;

        Board<char>* boardPtr = p->get_board_ptr();
        if (boardPtr) {
            for (int i = 0; i < 5; i++) {
                for (int j = 0; j < 5; j++) {
                    if (boardPtr->get_cell(i, j) == '.') {
                        available.push_back({ i, j });
                    }
                }
            }
        }

        if (!available.empty()) {
            int idx = rand() % available.size();
            x = available[idx].first;
            y = available[idx].second;
            cout << "\nComputer (" << p->get_symbol() << ") chooses: "
                << x << " " << y << endl;
        }
        else {
            x = 2; y = 2;
        }
    }
    return new Move<char>(x, y, p->get_symbol());
}

/**
 * @brief Displays the board as a diamond-shaped grid.
 * @param matrix 5x5 board matrix.
 */
void DiamondTicTacToe_UI::display_board_matrix(const vector<vector<char>>& matrix) const {
    if (matrix.empty()) return;

    cout << "\n=== DIAMOND TIC-TAC-TOE ===\n\n";

    vector<vector<char>> diamond(9, vector<char>(9, ' '));

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            int d_row = i + j;
            int d_col = i - j + 4;
            diamond[d_row][d_col] = matrix[i][j];
        }
    }

    for (int row = 0; row < 9; row++) {
        int cells_in_row = (row < 5 ? row + 1 : 9 - row);
        int indent = (9 - cells_in_row) * 2;

        for (int s = 0; s < indent; s++)
            cout << " ";

        int printed = 0;
        for (int col = 0; col < 9; col++) {
            if (diamond[row][col] != ' ') {
                cout << diamond[row][col];
                printed++;
                if (printed < cells_in_row) cout << "   ";
            }
        }
        cout << "\n";
    }

    cout << "\nGrid positions: (row, column) where row=0-4, column=0-4\n";
}

/**
 * @brief Displays game instructions once.
 */
void DiamondTicTacToe_UI::show_instructions() {
    if (!instructions_shown) {
        cout << "\n=== DIAMOND TIC-TAC-TOE ===\n";
        cout << "All positions from (0,0) to (4,4) are playable\n";
        cout << "\nWinning Condition:\n";
        cout << "  Complete TWO lines:\n";
        cout << "  - One line of THREE marks\n";
        cout << "  - One line of FOUR marks\n";
        cout << "  Lines must be in DIFFERENT directions.\n";
        cout << "=============================\n";
        instructions_shown = true;
    }
}
