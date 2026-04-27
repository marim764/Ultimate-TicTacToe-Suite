#include "Moving_TicTacToe_Classes.h"
#include <cctype>

/**
 * @brief Constructor. Initializes 4x4 moving-XO board with starting layout.
 */
Moving_XO_Board::Moving_XO_Board() : Board<char>(4, 4) {
    // initialize all to blank
    for (auto& row : board)
        for (auto& cell : row)
            cell = blank_symbol;

    // Starting layout
    board[0][0] = 'O'; board[0][1] = 'X'; board[0][2] = 'O'; board[0][3] = 'X';
    board[3][0] = 'X'; board[3][1] = 'O'; board[3][2] = 'X'; board[3][3] = 'O';

    n_moves = 8; // initial tokens placed
}

/**
 * @brief Updates the board with a move or clears a cell.
 * @param move Pointer to the Move object.
 * @return true if the move/clear is valid.
 */
bool Moving_XO_Board::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char mark = move->get_symbol();

    // Validate coordinates
    if (x < 0 || x >= rows || y < 0 || y >= columns)
        return false;

    // Clear cell if mark == 0
    if (mark == 0) {
        if (board[x][y] != blank_symbol) {
            n_moves--;
            board[x][y] = blank_symbol;
            return true;
        }
        return false;
    }

    // Place mark if cell empty
    if (board[x][y] == blank_symbol) {
        n_moves++;
        board[x][y] = toupper(mark);
        return true;
    }

    return false;
}

/**
 * @brief Checks if the given player has won (3 in a row, column, or diagonal).
 * @param player Pointer to Player object.
 * @return true if player has 3-in-a-row.
 */
bool Moving_XO_Board::is_win(Player<char>* player) {
    char sym = player->get_symbol();

    auto all_equal_three = [&](int x1, int y1, int x2, int y2, int x3, int y3) {
        return board[x1][y1] == sym && board[x2][y2] == sym && board[x3][y3] == sym;
        };

    // Horizontal
    for (int r = 0; r < rows; ++r)
        for (int c = 0; c <= columns - 3; ++c)
            if (all_equal_three(r, c, r, c + 1, r, c + 2)) return true;

    // Vertical
    for (int c = 0; c < columns; ++c)
        for (int r = 0; r <= rows - 3; ++r)
            if (all_equal_three(r, c, r + 1, c, r + 2, c)) return true;

    // Descending diagonals
    for (int r = 0; r <= rows - 3; ++r)
        for (int c = 0; c <= columns - 3; ++c)
            if (all_equal_three(r, c, r + 1, c + 1, r + 2, c + 2)) return true;

    // Ascending diagonals
    for (int r = 2; r < rows; ++r)
        for (int c = 0; c <= columns - 3; ++c)
            if (all_equal_three(r, c, r - 1, c + 1, r - 2, c + 2)) return true;

    return false;
}

/**
 * @brief Checks if the game is a draw.
 * @param player Pointer to Player object (unused).
 * @return false; moving-XO variant relies on is_win only.
 */
bool Moving_XO_Board::is_draw(Player<char>* /*player*/) {
    return false;
}

/**
 * @brief Checks if the game is over (win or draw).
 * @param player Pointer to Player object.
 * @return true if game is won or draw (rare).
 */
bool Moving_XO_Board::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player);
}
