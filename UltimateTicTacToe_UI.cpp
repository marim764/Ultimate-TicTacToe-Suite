#include "UltimateTicTacToe_UI.h"
#include "UltimateTicTacToe_Board.h"
#include <iostream>

using namespace std;

/// Constructor
UltimateTicTacToe_UI::UltimateTicTacToe_UI()
    : UI<char>("Ultimate Tic-Tac-Toe", 2) {}

/// Create player
Player<char>* UltimateTicTacToe_UI::create_player(string& name, char sym, PlayerType t) {
    return new Player<char>(name, sym, t);
}

/// Get player's move
Move<char>* UltimateTicTacToe_UI::get_move(Player<char>* p) {
    int x, y;
    if (p->get_type() == PlayerType::HUMAN) cin >> x >> y;
    else do { x = rand() % 9; y = rand() % 9; } while (p->get_board_ptr()->get_cell(x, y) != '.');
    return new Move<char>(x, y, p->get_symbol());
}

/// Display 9x9 board
void UltimateTicTacToe_UI::display_board_matrix(const vector<vector<char>>& m) const {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            cout << m[i][j] << " ";
            if (j % 3 == 2) cout << "| ";
        }
        cout << "\n";
        if (i % 3 == 2) cout << "----------------------------\n";
    }
}
