/**
 * @file FivexFive_TicTacToe_Board.cpp
 * @brief Implementation of 5x5 Tic-Tac-Toe Board logic.
 */
#include "FivexFive_TicTacToe_Board.h"
#include <cstdlib> 

// Constructor
FivexFive_TicTacToe_Board::FivexFive_TicTacToe_Board() : Board<char>(5, 5) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            board[i][j] = ' '; // Initialize with space as a start
        }
    }
}

bool FivexFive_TicTacToe_Board::update_board(Move<char>* move) {
    if (!move) return false;
    int r = move->get_x();
    int c = move->get_y();
    char symbol = move->get_symbol();

    if (r < 0 || r >= rows || c < 0 || c >= columns) return false;
    if (board[r][c] != ' ') return false;

    board[r][c] = symbol;
    n_moves++;
    return true;
}

// Counts how many times symbol appears in 3 consecutive cells
int FivexFive_TicTacToe_Board::count_three_in_a_row(char symbol) const {
    int count = 0;

    // Check every cell as a starting point
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {

            // Check Horizontal (Right)
            if (j + 2 < columns) {
                if (board[i][j] == symbol && board[i][j + 1] == symbol && board[i][j + 2] == symbol)
                    count++;
            }

            // Check Vertical (Down)
            if (i + 2 < rows) {
                if (board[i][j] == symbol && board[i + 1][j] == symbol && board[i + 2][j] == symbol)
                    count++;
            }

            // Check Diagonal (Down-Right)
            if (i + 2 < rows && j + 2 < columns) {
                if (board[i][j] == symbol && board[i + 1][j + 1] == symbol && board[i + 2][j + 2] == symbol)
                    count++;
            }

            // Check Diagonal (Down-Left)
            if (i + 2 < rows && j - 2 >= 0) {
                if (board[i][j] == symbol && board[i + 1][j - 1] == symbol && board[i + 2][j - 2] == symbol)
                    count++;
            }
        }
    }
    return count;
}

pair<int, int> FivexFive_TicTacToe_Board::get_best_move(char symbol) {
    int bestScore = -1000;
    pair<int, int> bestMove = { -1, -1 };
    char oppSymbol = (symbol == 'X') ? 'O' : 'X';

    int current_my_score = count_three_in_a_row(symbol);
    int current_opp_score = count_three_in_a_row(oppSymbol);

    // Iterate through all empty cells to find the best spot
    for (int i = 0; i < rows; ++i) 
    {
        for (int j = 0; j < columns; ++j) 
        {
            if (board[i][j] == ' ')
            {
                // Test potential gain
                board[i][j] = symbol;
                int gain = count_three_in_a_row(symbol) - current_my_score;
                board[i][j] = ' ';

                // Test potential block
                board[i][j] = oppSymbol;
                int block = count_three_in_a_row(oppSymbol) - current_opp_score;
                board[i][j] = ' ';

                int moveValue = gain + block;

                if (moveValue > bestScore) 
                {
                    bestScore = moveValue;
                    bestMove = { i, j };
                }
            }
        }
    }
    // Fallback to random if no strategic move found
    if (bestMove.first == -1 || bestScore <= 0) {
        int r, c;
        do {
            r = rand() % 5;
            c = rand() % 5;
        } while (board[r][c] != ' ');
        return { r, c };
    }

    return bestMove;
}
bool FivexFive_TicTacToe_Board::is_win(Player<char>* player) 
{
    // Game only ends when board is full (25 moves)
    if (n_moves < 25) return false;

    char my_symbol = player->get_symbol(); 
    char opp_symbol = (my_symbol == 'X') ? 'O' : 'X';

    // Calculte score
    int my_score = count_three_in_a_row(my_symbol);
    int opp_score = count_three_in_a_row(opp_symbol);

    cout << "\nGame Over!\n";
    cout << "Total 3-in-a-rows for " << player->get_name() << ": " << my_score << endl;
    cout << "Total 3-in-a-rows for Opponent: " << opp_score << endl;

    return my_score > opp_score;
}

bool FivexFive_TicTacToe_Board::is_draw(Player<char>* player) {
    // Draw if full and scores are equal
    if (n_moves < 25) return false;

    char my_symbol = player->get_symbol();
    char opp_symbol = (my_symbol == 'X') ? 'O' : 'X';

    return count_three_in_a_row(my_symbol) == count_three_in_a_row(opp_symbol);
}

bool FivexFive_TicTacToe_Board::game_is_over(Player<char>* player) {
    return n_moves == 25; // Game ends ONLY when full
}