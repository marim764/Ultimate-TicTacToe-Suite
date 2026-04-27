#include "Misere_TicTacToe_Board.h"
#include <cctype>

/**
 * @brief Constructor. Initializes 3x3 board with blank cells.
 */
Misere_TicTacToe_Board::Misere_TicTacToe_Board() : Board<char>(3, 3) {
    for (auto& row : board)
        for (auto& cell : row)
            cell = blank_symbol;
    n_moves = 0;
}

/**
 * @brief Updates the board with a move or undo.
 * @param move Pointer to Move object containing x, y, symbol.
 * @return true if the move/undo is valid.
 */
bool Misere_TicTacToe_Board::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char mark = move->get_symbol();

    if (!(x < 0 || x >= rows || y < 0 || y >= columns) &&
        (board[x][y] == blank_symbol || mark == 0)) {

        if (mark == 0) { // undo
            if (board[x][y] != blank_symbol) {
                n_moves--;
                board[x][y] = blank_symbol;
            }
        }
        else {
            n_moves++;
            board[x][y] = static_cast<char>(toupper(mark));
        }
        return true;
    }
    return false;
}

/**
 * @brief Checks if the given symbol has three in a row.
 * @param sym Symbol to check ('X' or 'O').
 * @return true if there are three in a row, column, or diagonal.
 */
bool Misere_TicTacToe_Board::has_three_in_row(char sym) const {
    auto all_equal = [&](char a, char b, char c) {
        return a == b && b == c && a != blank_symbol;
        };

    // rows and columns
    for (int i = 0; i < rows; ++i) {
        if (all_equal(board[i][0], board[i][1], board[i][2]) && board[i][0] == sym)
            return true;
        if (all_equal(board[0][i], board[1][i], board[2][i]) && board[0][i] == sym)
            return true;
    }

    // diagonals
    if (all_equal(board[0][0], board[1][1], board[2][2]) && board[1][1] == sym) return true;
    if (all_equal(board[0][2], board[1][1], board[2][0]) && board[1][1] == sym) return true;

    return false;
}

/**
 * @brief Checks if the player loses (misère rules: 3 in a row = lose).
 * @param player Pointer to Player object.
 * @return true if player has 3 in a row.
 */
bool Misere_TicTacToe_Board::is_lose(Player<char>* player) {
    char sym = player->get_symbol();
    return has_three_in_row(sym);
}

/**
 * @brief Checks if the game is a draw.
 * @param player Pointer to any Player (unused).
 * @return true if board is full and no 3-in-row exists.
 */
bool Misere_TicTacToe_Board::is_draw(Player<char>* /*player*/) {
    if (n_moves < rows * columns) return false;
    if (has_three_in_row('X')) return false;
    if (has_three_in_row('O')) return false;
    return true;
}

/**
 * @brief Checks if the game is over (lose or draw).
 * @param player Pointer to Player object.
 * @return true if player loses or game is draw.
 */
bool Misere_TicTacToe_Board::game_is_over(Player<char>* player) {
    return is_lose(player) || is_draw(player);
}
