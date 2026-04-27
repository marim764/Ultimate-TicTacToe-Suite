#include "PyramidTicTacToe_Classes.h"
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <limits>

using namespace std;

// ==================== PyramidTicTacToe_Board Implementation ====================

/**
 * @brief Constructs a Pyramid Tic-Tac-Toe board with 3 rows and 5 columns.
 * Initializes all cells with blank_symbol.
 */
PyramidTicTacToe_Board::PyramidTicTacToe_Board() : Board(3, 5) {
    for (auto& row : board) {
        for (auto& cell : row) {
            cell = blank_symbol;
        }
    }
}

/**
 * @brief Checks whether a given (x,y) lies within the pyramid shape.
 * @param x Row index
 * @param y Column index
 * @return true if position is valid in pyramid; false otherwise
 */
bool PyramidTicTacToe_Board::is_valid_position(int x, int y) const {
    if (x < 0 || x >= rows || y < 0 || y >= columns)
        return false;

    switch (x) {
    case 0: return (y == 2);               // Top
    case 1: return (y >= 1 && y <= 3);     // Middle
    case 2: return (y >= 0 && y <= 4);     // Base
    default: return false;
    }
}

/**
 * @brief Applies a player's move if valid and cell is empty.
 * @param move The move containing (x,y) and player's symbol
 * @return true if board updated; false otherwise
 */
bool PyramidTicTacToe_Board::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char mark = move->get_symbol();

    if (is_valid_position(x, y) && board[x][y] == blank_symbol) {
        board[x][y] = mark;
        n_moves++;
        return true;
    }
    return false;
}

/**
 * @brief Checks if a player has achieved a winning line.
 * Winning lines include horizontal, vertical, and diagonal.
 * @param player Pointer to the player to check
 * @return true if player has won; false otherwise
 */
bool PyramidTicTacToe_Board::is_win(Player<char>* player) {
    char symbol = player->get_symbol();

    // Middle row horizontal
    if (board[1][1] == symbol && board[1][2] == symbol && board[1][3] == symbol)
        return true;

    // Base row horizontal 3-in-a-row
    for (int start = 0; start <= 2; start++) {
        if (board[2][start] == symbol &&
            board[2][start + 1] == symbol &&
            board[2][start + 2] == symbol)
            return true;
    }

    // Vertical center column
    if (board[0][2] == symbol && board[1][2] == symbol && board[2][2] == symbol)
        return true;

    // Diagonal left
    if (board[2][0] == symbol && board[1][1] == symbol && board[0][2] == symbol)
        return true;

    // Diagonal right
    if (board[2][4] == symbol && board[1][3] == symbol && board[0][2] == symbol)
        return true;

    return false;
}

/**
 * @brief Determines whether the match is a draw.
 * @param player Player whose result is evaluated
 * @return true if board filled and no winner; false otherwise
 */
bool PyramidTicTacToe_Board::is_draw(Player<char>* player) {
    return (n_moves >= 9 && !is_win(player));
}

/**
 * @brief Checks whether the game is finished (win or draw).
 * @param player Player whose end condition is checked
 * @return true if game is over; false otherwise
 */
bool PyramidTicTacToe_Board::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player);
}

// ==================== PyramidTicTacToe_UI Implementation ====================

/**
 * @brief Constructs the UI handler for Pyramid Tic-Tac-Toe.
 */
PyramidTicTacToe_UI::PyramidTicTacToe_UI() : UI<char>("", 3) {
    srand(static_cast<unsigned>(time(0)));
}

/**
 * @brief Creates a new player instance.
 * @param name Player's name
 * @param symbol Player's symbol (X/O)
 * @param type HUMAN or COMPUTER
 * @return Pointer to created Player object
 */
Player<char>* PyramidTicTacToe_UI::create_player(string& name, char symbol, PlayerType type) {
    return new Player<char>(name, symbol, type);
}

/**
 * @brief Gets a move from the player (human input or computer AI).
 * @param player Player whose move is required
 * @return Pointer to newly allocated Move object
 */
Move<char>* PyramidTicTacToe_UI::get_move(Player<char>* player) {
    PyramidTicTacToe_Board* board = dynamic_cast<PyramidTicTacToe_Board*>(player->get_board_ptr());

    if (player->get_type() == PlayerType::HUMAN) {
        int x, y;
        cout << "\n" << player->get_name() << " (" << player->get_symbol()
            << "), enter row and column: ";
        cin >> x >> y;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return new Move<char>(x, y, player->get_symbol());
    }

    // Computer AI
    vector<pair<int, int>> valid_positions = {
        {0,2}, {1,1},{1,2},{1,3}, {2,0},{2,1},{2,2},{2,3},{2,4}
    };

    vector<pair<int, int>> available;

    if (board) {
        for (auto& pos : valid_positions) {
            if (board->get_cell(pos.first, pos.second) == '.')
                available.push_back(pos);
        }
    }

    if (!available.empty()) {
        int idx = rand() % available.size();
        cout << "\nComputer (" << player->get_symbol() << ") chooses: "
            << available[idx].first << " " << available[idx].second << endl;
        return new Move<char>(available[idx].first, available[idx].second, player->get_symbol());
    }

    return new Move<char>(0, 2, player->get_symbol());
}

/**
 * @brief Displays the pyramid game board in visual pyramid form.
 * @param matrix 2D vector representing the board cells
 */
void PyramidTicTacToe_UI::display_board_matrix(const vector<vector<char>>& matrix) const {
    if (matrix.empty()) return;

    cout << "\n--- PYRAMID BOARD ---\n\n";

    char cells[3][5] = { {'.'} }; // initialize all to '.'

    for (int i = 0; i < min(3, (int)matrix.size()); i++) {
        for (int j = 0; j < min(5, (int)matrix[i].size()); j++) {
            cells[i][j] = matrix[i][j];
        }
    }

    cout << "       " << cells[0][2] << "\n";
    cout << "     " << cells[1][1] << " " << cells[1][2] << " " << cells[1][3] << "\n";
    cout << "   " << cells[2][0] << " " << cells[2][1] << " " << cells[2][2]
        << " " << cells[2][3] << " " << cells[2][4] << "\n\n";
}
