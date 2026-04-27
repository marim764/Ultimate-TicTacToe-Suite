#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include "MemoryTicTacToe_Classes.h"

using namespace std;

/**
 * @brief Constructor for MemoryTicTacToe_Board.
 * Initializes a 3x3 board with empty cells ('.').
 */
MemoryTicTacToe_Board::MemoryTicTacToe_Board() : Board(3, 3) {
    for (auto& row : board)
        for (auto& cell : row)
            cell = '.';
}

/**
 * @brief Updates the board with a move.
 * @param move Pointer to the Move object containing x, y, and symbol.
 * @return true if the move was successful, false if invalid or cell occupied.
 */
bool MemoryTicTacToe_Board::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char symbol = move->get_symbol();

    if (x < 0 || x >= 3 || y < 0 || y >= 3) {
        return false;
    }

    if (is_cell_occupied(x, y)) {
        return false;
    }

    if (symbol == 'X') {
        x_moves.push_back({ x, y });
    }
    else if (symbol == 'O') {
        o_moves.push_back({ x, y });
    }

    board[x][y] = symbol;
    n_moves++;
    return true;
}

/**
 * @brief Checks if a player has won the game.
 * @param player Pointer to the Player object.
 * @return true if the player has 3 in a row, column, or diagonal.
 */
bool MemoryTicTacToe_Board::is_win(Player<char>* player) {
    char symbol = player->get_symbol();
    const vector<pair<int, int>>& moves = (symbol == 'X') ? x_moves : o_moves;

    if (moves.size() < 3) return false;

    bool temp_grid[3][3] = { {false} };
    for (const auto& move : moves) {
        temp_grid[move.first][move.second] = true;
    }

    // Check rows
    for (int i = 0; i < 3; i++) {
        if (temp_grid[i][0] && temp_grid[i][1] && temp_grid[i][2]) {
            return true;
        }
    }

    // Check columns
    for (int j = 0; j < 3; j++) {
        if (temp_grid[0][j] && temp_grid[1][j] && temp_grid[2][j]) {
            return true;
        }
    }

    // Check diagonals
    if (temp_grid[0][0] && temp_grid[1][1] && temp_grid[2][2]) {
        return true;
    }
    if (temp_grid[0][2] && temp_grid[1][1] && temp_grid[2][0]) {
        return true;
    }

    return false;
}

/**
 * @brief Checks if the game is a draw.
 * @param player Pointer to any Player object.
 * @return true if all cells are filled and no player has won.
 */
bool MemoryTicTacToe_Board::is_draw(Player<char>* player) {
    return (n_moves == 9) && !is_win(player);
}

/**
 * @brief Checks if the game is over.
 * @param player Pointer to any Player object.
 * @return true if the player has won or the game is a draw.
 */
bool MemoryTicTacToe_Board::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player);
}

/**
 * @brief Reveals and prints the full board.
 */
void MemoryTicTacToe_Board::reveal_board() const {
    cout << "\n=== REVEALED BOARD ===\n";
    cout << "    0   1   2\n";
    cout << "  -------------\n";

    for (int i = 0; i < 3; i++) {
        cout << i << " |";
        for (int j = 0; j < 3; j++) {
            cout << " ";
            cout << (board[i][j] == '.' ? ' ' : board[i][j]);
            cout << " |";
        }
        cout << "\n  -------------\n";
    }
    cout << endl;
}

/**
 * @brief Checks if a specific cell is already occupied.
 * @param x Row index.
 * @param y Column index.
 * @return true if cell contains 'X' or 'O', false otherwise.
 */
bool MemoryTicTacToe_Board::is_cell_occupied(int x, int y) const {
    return board[x][y] != '.';
}

/**
 * @brief Constructor for MemoryTicTacToe_UI.
 * Initializes UI with game title and 2 players.
 */
MemoryTicTacToe_UI::MemoryTicTacToe_UI()
    : UI<char>("Welcome to Memory Tic-Tac-Toe!", 2) {}

/**
 * @brief Creates a player.
 * @param name Player's name.
 * @param symbol Player's symbol ('X' or 'O').
 * @param type PlayerType (HUMAN or COMPUTER).
 * @return Pointer to the created Player object.
 */
Player<char>* MemoryTicTacToe_UI::create_player(string& name, char symbol, PlayerType type) {
    cout << "Creating " << (type == PlayerType::HUMAN ? "Human" : "Computer")
        << " player: " << name << " (" << symbol << ")\n";
    return new Player<char>(name, symbol, type);
}

/**
 * @brief Gets a move from the player (human input or AI random choice).
 * @param player Pointer to the Player object.
 * @return Pointer to the created Move object.
 */
Move<char>* MemoryTicTacToe_UI::get_move(Player<char>* player) {
    int x, y;

    if (player->get_type() == PlayerType::HUMAN) {
        cout << player->get_name() << " (" << player->get_symbol()
            << "), enter row and column (0-2): ";
        cin >> x >> y;

        while (x < 0 || x > 2 || y < 0 || y > 2) {
            cout << "Invalid! Enter values between 0 and 2: ";
            cin >> x >> y;
        }
    }
    else {
        srand(time(0));
        do {
            x = rand() % 3;
            y = rand() % 3;
        } while (player->get_board_ptr()->get_cell(x, y) != '.');

        cout << player->get_name() << " (Computer) chooses: "
            << x << ", " << y << endl;
    }

    return new Move<char>(x, y, player->get_symbol());
}

/**
 * @brief Displays the board with hidden cells ('?') for gameplay.
 */
void MemoryTicTacToe_UI::display_hidden_board() const {
    cout << "\n=== Memory Tic-Tac-Toe ===\n";
    cout << "    0   1   2\n";
    cout << "  -------------\n";

    for (int i = 0; i < 3; i++) {
        cout << i << " |";
        for (int j = 0; j < 3; j++) {
            cout << " ? |";
        }
        cout << "\n  -------------\n";
    }
}

/**
 * @brief Displays the game instructions.
 */
void MemoryTicTacToe_UI::display_instructions() const {
    cout << "\n=== MEMORY TIC-TAC-TOE ===\n";
    cout << "RULES:\n";
    cout << "1. Marks (X/O) are COMPLETELY HIDDEN during gameplay\n";
    cout << "2. All cells appear as '?' - you see nothing!\n";
    cout << "3. You must remember ALL moves (yours and opponent's)\n";
    cout << "4. First to get 3 marks in a row wins\n";
    cout << "5. Board will be revealed at the end\n";
    cout << "==========================================\n";
}
