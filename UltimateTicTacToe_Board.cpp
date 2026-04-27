#include "UltimateTicTacToe_Board.h"

/**
 * @brief Constructor for Ultimate Tic-Tac-Toe board.
 *
 * Initializes a 9x9 board with '.' and 3x3 main claims with '.'.
 */
UltimateTicTacToe_Board::UltimateTicTacToe_Board()
    : Board<char>(9, 9)
{
    for (int i = 0;i < 9;i++)
        for (int j = 0;j < 9;j++)
            board[i][j] = '.';

    for (int i = 0;i < 3;i++)
        for (int j = 0;j < 3;j++)
            main_claims[i][j] = '.';
}

/**
 * @brief Updates the board with a player's move.
 *
 * Checks if the small board is not already claimed and the cell is empty.
 * Marks the cell and updates main claim if small board is won.
 *
 * @param m Pointer to the move object.
 * @return true if the move was applied successfully, false otherwise.
 */
bool UltimateTicTacToe_Board::update_board(Move<char>* m) {
    int x = m->get_x(), y = m->get_y();
    char sym = toupper(m->get_symbol());
    if (x < 0 || x >= 9 || y < 0 || y >= 9) return false;

    int br = x / 3, bc = y / 3;
    if (main_claims[br][bc] != '.') return false;
    if (board[x][y] != '.') return false;

    board[x][y] = sym;
    n_moves++;

    if (check_small_win(br, bc, sym))
        main_claims[br][bc] = sym;

    return true;
}

/**
 * @brief Checks if a 3x3 small board is won by the given symbol.
 *
 * @param br Small board row index (0-2)
 * @param bc Small board column index (0-2)
 * @param sym Player's symbol
 * @return true if the small board is won, false otherwise
 */
bool UltimateTicTacToe_Board::check_small_win(int br, int bc, char sym) const {
    int sx = br * 3, sy = bc * 3;

    for (int i = 0;i < 3;i++)
        if (board[sx + i][sy] == sym && board[sx + i][sy + 1] == sym && board[sx + i][sy + 2] == sym)
            return true;

    for (int j = 0;j < 3;j++)
        if (board[sx][sy + j] == sym && board[sx + 1][sy + j] == sym && board[sx + 2][sy + j] == sym)
            return true;

    if (board[sx][sy] == sym && board[sx + 1][sy + 1] == sym && board[sx + 2][sy + 2] == sym)
        return true;

    if (board[sx][sy + 2] == sym && board[sx + 1][sy + 1] == sym && board[sx + 2][sy] == sym)
        return true;

    return false;
}

/**
 * @brief Checks if a player has won the main 3x3 board.
 *
 * @param sym Player's symbol
 * @return true if player won the main board, false otherwise
 */
bool UltimateTicTacToe_Board::check_main_win(char sym) const {
    for (int i = 0;i < 3;i++)
        if (main_claims[i][0] == sym && main_claims[i][1] == sym && main_claims[i][2] == sym)
            return true;

    for (int j = 0;j < 3;j++)
        if (main_claims[0][j] == sym && main_claims[1][j] == sym && main_claims[2][j] == sym)
            return true;

    if (main_claims[0][0] == sym && main_claims[1][1] == sym && main_claims[2][2] == sym)
        return true;

    if (main_claims[0][2] == sym && main_claims[1][1] == sym && main_claims[2][0] == sym)
        return true;

    return false;
}

/**
 * @brief Checks if the given player has won the game.
 *
 * @param p Pointer to the player
 * @return true if player won the main board, false otherwise
 */
bool UltimateTicTacToe_Board::is_win(Player<char>* p) {
    return check_main_win(p->get_symbol());
}

/**
 * @brief Checks if the game has ended in a draw.
 *
 * @param p Pointer to the player
 * @return true if all 81 cells are filled and no one won
 */
bool UltimateTicTacToe_Board::is_draw(Player<char>* p) {
    if (n_moves >= 81) return !is_win(p);
    return false;
}

/**
 * @brief Determines whether the game is over.
 *
 * @param p Pointer to the player
 * @return true if game is won or drawn
 */
bool UltimateTicTacToe_Board::game_is_over(Player<char>* p) {
    return is_win(p) || is_draw(p);
}

/**
 * @brief Returns a copy of the 3x3 main claims board.
 *
 * @return 3x3 vector representing the state of small boards
 */
vector<vector<char>> UltimateTicTacToe_Board::get_main_claims() const {
    vector<vector<char>> v(3, vector<char>(3, '.'));
    for (int i = 0;i < 3;i++)
        for (int j = 0;j < 3;j++)
            v[i][j] = main_claims[i][j];
    return v;
}
