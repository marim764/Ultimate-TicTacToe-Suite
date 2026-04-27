#include "DiamondTicTacToe_Board.h"
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

static int DX[8] = { 0, 1, 1, 1, 0, -1, -1, -1 };
static int DY[8] = { 1, 1, 0, -1, -1, -1, 0, 1 };

/**
 * @brief Constructor for the Diamond Tic-Tac-Toe board (5x5 grid).
 *        Initializes all cells to blank.
 */
DiamondTicTacToe_Board::DiamondTicTacToe_Board()
    : Board(5, 5)
{
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            board[i][j] = blank;
}

/**
 * @brief Updates the board with the player's move if the cell is valid and empty.
 *
 * @param move Pointer to Move<char> containing x, y, and symbol.
 * @return true if the move was placed successfully, false otherwise.
 */
bool DiamondTicTacToe_Board::update_board(Move<char>* move) {
    int x = move->get_x(), y = move->get_y();
    char sym = move->get_symbol();
    if (x < 0 || x >= 5 || y < 0 || y >= 5) return false;
    if (board[x][y] != blank) return false;

    board[x][y] = sym;
    n_moves++;
    return true;
}

/**
 * @brief Checks if there is a line of given length starting from (x, y) in a given direction.
 *
 * @param x Starting row index.
 * @param y Starting column index.
 * @param sym Symbol to check (X or O).
 * @param length Required consecutive cells.
 * @param dx Direction in x-axis.
 * @param dy Direction in y-axis.
 * @return true if the line exists, false otherwise.
 */
bool DiamondTicTacToe_Board::has_line(int x, int y, char sym, int length, int dx, int dy) const {
    for (int start = -(length - 1); start <= 0; start++) {
        bool ok = true;
        for (int k = 0; k < length; k++) {
            int a = x + (start + k) * dx;
            int b = y + (start + k) * dy;

            if (a < 0 || a >= 5 || b < 0 || b >= 5) {
                ok = false;
                break;
            }
            if (board[a][b] != sym) {
                ok = false;
                break;
            }
        }
        if (ok) return true;
    }
    return false;
}

/**
 * @brief Checks if the given player has won the Diamond Tic-Tac-Toe game.
 *        Win condition: player must have BOTH a 3-in-a-row and a 4-in-a-row in different directions.
 *
 * @param player Pointer to the player object.
 * @return true if the player wins, false otherwise.
 */
bool DiamondTicTacToe_Board::is_win(Player<char>* player) {
    char sym = player->get_symbol();

    vector<bool> has3_dir(4, false);
    vector<bool> has4_dir(4, false);

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (board[i][j] == sym) {
                for (int d = 0; d < 8; d++) {
                    int dir_category;
                    if (DX[d] == 0) dir_category = 0;          // vertical
                    else if (DY[d] == 0) dir_category = 1;     // horizontal
                    else if (DX[d] == DY[d]) dir_category = 2; // main diagonal
                    else dir_category = 3;                     // anti diagonal

                    if (!has3_dir[dir_category] && has_line(i, j, sym, 3, DX[d], DY[d]))
                        has3_dir[dir_category] = true;
                    if (!has4_dir[dir_category] && has_line(i, j, sym, 4, DX[d], DY[d]))
                        has4_dir[dir_category] = true;
                }
            }
        }
    }

    // Must have 3-in-a-row in one direction AND 4-in-a-row in another
    for (int d3 = 0; d3 < 4; d3++) {
        if (has3_dir[d3]) {
            for (int d4 = 0; d4 < 4; d4++) {
                if (d3 != d4 && has4_dir[d4]) {
                    return true;
                }
            }
        }
    }

    return false;
}

/**
 * @brief Checks if the game is a draw (board is full and no winner).
 *
 * @param player Pointer to current player (not used).
 * @return true if board is full and no moves left.
 */
bool DiamondTicTacToe_Board::is_draw(Player<char>* player) {
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            if (board[i][j] == blank)
                return false;
    return true;
}

/**
 * @brief Determines whether the game has finished.
 *
 * @param player Pointer to current player.
 * @return true if player wins or the board is full (draw).
 */
bool DiamondTicTacToe_Board::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player);
}
