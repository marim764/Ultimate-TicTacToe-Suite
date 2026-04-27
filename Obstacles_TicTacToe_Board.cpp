/**
 * @file Obstacles_TicTacToe_Board.cpp
 * @brief Implementation of Obstacles Board logic.
 */
#include "Obstacles_TicTacToe_Board.h"
#include <cstdlib> 
#include <ctime>

// Constructor
Obstacles_TicTacToe_Board::Obstacles_TicTacToe_Board() : Board<char>(6, 6) 
{
    empty_symbol = '.';
    obstacle_symbol = '#';
    total_moves_made = 0;

    for (int i = 0; i < rows; ++i) 
    {
        for (int j = 0; j < columns; ++j) 
        {
            board[i][j] = empty_symbol;
        }
    }
}
// Helper to add two random obstacles to the board
void Obstacles_TicTacToe_Board::add_random_obstacles() 
{
    int obstacles_added = 0;
    while (obstacles_added < 2) 
    {
        int r = rand() % rows;
        int c = rand() % columns;
        //Only add obstacle if cell is empty AND not already an obstacle
        if (board[r][c] == empty_symbol) 
        {
            board[r][c] = obstacle_symbol;
            obstacles_added++;
        }
    }
}

//update the board with a player's move
bool Obstacles_TicTacToe_Board::update_board(Move<char>* move) 
{
    if (!move) return false;
    int r = move->get_x();
    int c = move->get_y();
    char symbol = move->get_symbol();

    if (r < 0 || r >= rows || c < 0 || c >= columns) return false;

    if (board[r][c] != empty_symbol) 
    {
        cout << "Invalid move: Cell (" << r << "," << c << ") is already occupied or is an obstacle.\n";
        return false;
    }

    board[r][c] = symbol;
    n_moves++;
    total_moves_made++;

    // Add obstacles AFTER every two successful player moves (one round)
    if (total_moves_made > 0 && total_moves_made % 2 == 0) 
    {
        add_random_obstacles();
        cout << "Two new obstacles have been added to the board!\n";
    }
    return true;
}

// Helper to check if a line of 4 cells has the same player symbol
bool Obstacles_TicTacToe_Board::check_line_for_win(int r_start, int c_start, int r_delta, int c_delta, char player_symbol) const 
{
    int count = 0;
    for (int k = 0; k < 4; ++k) 
    { 
        int r = r_start + k * r_delta;
        int c = c_start + k * c_delta;

        if (r < 0 || r >= rows || c < 0 || c >= columns) return false;

        if (board[r][c] == player_symbol) 
        {
            count++;
        }
        else 
        {
            count = 0;
            if (board[r][c] == obstacle_symbol || board[r][c] == empty_symbol) 
            {
                return false;
            }
        }
        if (count == 4) return true;
    }
    return false;
}

//Check if the current player has won
bool Obstacles_TicTacToe_Board::is_win(Player<char>* player) 
{
    char player_symbol = player->get_symbol();

    //Check horizontal lines
    for (int r = 0; r < rows; ++r) 
    {
        for (int c = 0; c <= columns - 4; ++c) 
        {
            if (check_line_for_win(r, c, 0, 1, player_symbol)) return true;
        }
    }

    // Check vertical lines
    for (int c = 0; c < columns; ++c) 
    {
        for (int r = 0; r <= rows - 4; ++r) 
        {
            if (check_line_for_win(r, c, 1, 0, player_symbol)) return true;
        }
    }

    // Check main diagonals 
    for (int r = 0; r <= rows - 4; ++r) 
    {
        for (int c = 0; c <= columns - 4; ++c) 
        {
            if (check_line_for_win(r, c, 1, 1, player_symbol)) return true;
        }
    }

    // Check anti-diagonals 
    for (int r = 0; r <= rows - 4; ++r) 
    {
        for (int c = 3; c < columns; ++c) 
        {
            if (check_line_for_win(r, c, 1, -1, player_symbol)) return true;
        }
    }

    return false;
}

// Check for a draw condition
bool Obstacles_TicTacToe_Board::is_draw(Player<char>* player) 
{
    int empty_cells_count = 0;
    for (int i = 0; i < rows; ++i) 
    {
        for (int j = 0; j < columns; ++j) 
        {
            if (board[i][j] == empty_symbol) 
            {
                empty_cells_count++;
            }
        }
    }
    return (empty_cells_count == 0 && !is_win(player));
}

// Check if the game is over (win or draw)
bool Obstacles_TicTacToe_Board::game_is_over(Player<char>* player) 
{
    return is_win(player) || is_draw(player);
}