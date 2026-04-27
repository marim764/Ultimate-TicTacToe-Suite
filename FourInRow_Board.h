#pragma once
#include "BoardGame_Classes.h"
#include <algorithm>
#include <limits>
using namespace std;

/**
 * @class FourInRow_Board
 * @brief Implements Four In Row game logic on a 6x7 grid
 * 
 * This class manages the Four In Row game board where players drop pieces
 * into columns. Pieces fall to the lowest available position in the chosen column.
 * The game ends when a player gets four pieces in a row horizontally,
 * vertically, or diagonally.
 */
class FourInRow_Board : public Board<char> {
private:
    /**
     * @brief Checks if a column is valid for a move
     * @param col Column index to check
     * @return true if column exists and has empty space, false otherwise
     */
    bool is_valid_column(int col) { return (col >= 0 && col < columns && rows > 0 && board[0][col] == ' '); }

    /**
     * @brief Evaluates board position from the perspective of 'X' player
     * @return Positive score favors X, negative favors O, 0 for neutral
     */
    int evaluate_board() {
        int score = 0;
        char player = 'X';
        char opponent = 'O';
        // Center control bonus (column 3 is most valuable)
        for (int i = 0; i < rows; i++) {
            if (board[i][3] == player) score += 3;
            else if (board[i][3] == opponent) score -= 3;
        }
        // Evaluate all possible windows of 4
        score += evaluate_window(player, opponent);
        return score;
    }
    
    /**
     * @brief Evaluates all possible 4-cell windows for both players
     * @param player Current player symbol
     * @param opponent Opponent symbol
     * @return Net score advantage for player
     */
    int evaluate_window(char player, char opponent) {
        int player_score = 0;
        int opponent_score = 0;
        // Check horizontal windows
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns - 3; j++) {
                player_score += evaluate_four_cells(board[i][j], board[i][j+1], board[i][j+2], board[i][j+3], player, opponent);
                opponent_score += evaluate_four_cells(board[i][j], board[i][j+1], board[i][j+2], board[i][j+3], opponent, player);
            }
        }
        // Check vertical windows
        for (int i = 0; i < rows - 3; i++) {
            for (int j = 0; j < columns; j++) {
                player_score += evaluate_four_cells(board[i][j], board[i+1][j], board[i+2][j], board[i+3][j], player, opponent);
                opponent_score += evaluate_four_cells(board[i][j], board[i+1][j], board[i+2][j], board[i+3][j], opponent, player);
            }
        }
        // Check diagonal (top-left to bottom-right)
        for (int i = 0; i < rows - 3; i++) {
            for (int j = 0; j < columns - 3; j++) {
                player_score += evaluate_four_cells(board[i][j], board[i+1][j+1], board[i+2][j+2], board[i+3][j+3], player, opponent);
                opponent_score += evaluate_four_cells(board[i][j], board[i+1][j+1], board[i+2][j+2], board[i+3][j+3], opponent, player);
            }
        }
        // Check diagonal (bottom-left to top-right)
        for (int i = 3; i < rows; i++) {
            for (int j = 0; j < columns - 3; j++) {
                player_score += evaluate_four_cells(board[i][j], board[i-1][j+1], board[i-2][j+2], board[i-3][j+3], player, opponent);
                opponent_score += evaluate_four_cells(board[i][j], board[i-1][j+1], board[i-2][j+2], board[i-3][j+3], opponent, player);
            }
        }
        return player_score - opponent_score;
    }
    
    /**
     * @brief Evaluates a single 4-cell window
     * @param c1,c2,c3,c4 The four cells in the window
     * @param player Player symbol being evaluated
     * @param opponent Opponent symbol
     * @return Score for this window configuration
     */
    int evaluate_four_cells(char c1, char c2, char c3, char c4, char player, char opponent) {
        int player_count = 0;
        int opponent_count = 0;
        int empty_count = 0;
        char cells[4] = {c1, c2, c3, c4};
        for (char cell : cells) {
            if (cell == player) player_count++;
            else if (cell == opponent) opponent_count++;
            else empty_count++;
        }
        // Scoring based on window configuration
        if (player_count == 4) return 100;           // Win
        if (player_count == 3 && empty_count == 1) return 10;  // Almost win
        if (player_count == 2 && empty_count == 2) return 5;   // Potential
        if (opponent_count == 3 && empty_count == 1) return -80; // Block needed
        if (opponent_count == 4) return -100;        // Opponent win (shouldn't happen)
        return 0;
    }
    
    /**
     * @brief Minimax algorithm with alpha-beta pruning
     * @param depth How many moves ahead to search
     * @param alpha Best already explored option for maximizer
     * @param beta Best already explored option for minimizer  
     * @param is_maximizing True if current player is maximizing (X), false for minimizing (O)
     * @return Best evaluation score for current board state
     */
    int minimax(int depth, int alpha, int beta, bool is_maximizing) {
        // Base cases: terminal node or depth limit reached
        if (depth == 0) { return evaluate_board(); }
        if (is_maximizing) {
            int max_eval = -10000;
            for (int col = 0; col < columns; col++) {
                if (is_valid_column(col)) {
                    int row = get_next_row(col);
                    board[row][col] = 'X';
                    n_moves++;
                    // Create temporary player for win checking
                    Player<char> temp_player("temp", 'X', PlayerType::HUMAN);
                    if (is_win(&temp_player)) {
                        board[row][col] = ' ';
                        n_moves--;
                        return 10000; // Immediate win for maximizer
                    }
                    int eval = minimax(depth - 1, alpha, beta, false);
                    board[row][col] = ' ';
                    n_moves--;
                    max_eval = max(max_eval, eval);
                    alpha = max(alpha, eval);
                    if (beta <= alpha) break; // Alpha-beta pruning
                }
            }
            return max_eval;
        } else {
            int min_eval = 10000;
            for (int col = 0; col < columns; col++) {
                if (is_valid_column(col)) {
                    int row = get_next_row(col);
                    board[row][col] = 'O';
                    n_moves++;
                    // Create temporary player for win checking
                    Player<char> temp_player("temp", 'O', PlayerType::HUMAN);
                    if (is_win(&temp_player)) {
                        board[row][col] = ' ';
                        n_moves--;
                        return -10000; // Immediate win for minimizer
                    }
                    int eval = minimax(depth - 1, alpha, beta, true);
                    board[row][col] = ' ';
                    n_moves--;
                    min_eval = min(min_eval, eval);
                    beta = min(beta, eval);
                    if (beta <= alpha) break; // Alpha-beta pruning
                }
            }
            return min_eval;
        }
    }

    /**
     * @brief Finds the next available row in a column
     * @param col Column to check
     * @return Row index where piece would land, or -1 if column is full
     */
    int get_next_row(int col) {
        for (int i = rows - 1; i >= 0; i--) { if (board[i][col] == ' ') return i; }
        return -1;
    }
    
    /**
     * @brief Checks if placing a piece in a column would create a win
     * @param symbol Player symbol to test
     * @param col Column to test the move in
     * @return true if move creates a winning line, false otherwise
     * 
     * Temporarily places the piece, checks all winning patterns,
     * then removes it to restore board state.
     */
    bool move_wins(char symbol, int col) {
        if (!is_valid_column(col)) return false;
        int row = get_next_row(col);
        board[row][col] = symbol;
        bool wins = false;
        // Check horizontal wins
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns - 3; j++) {
                if (board[i][j] == symbol && board[i][j+1] == symbol && board[i][j+2] == symbol && board[i][j+3] == symbol) {
                    wins = true;
                    break;
                }
            }
            if (wins) break;
        }
        // Check vertical wins
        if (!wins) {
            for (int i = 0; i < rows - 3; i++) {
                for (int j = 0; j < columns; j++) {
                    if (board[i][j] == symbol && board[i+1][j] == symbol && board[i+2][j] == symbol && board[i+3][j] == symbol) {
                        wins = true;
                        break;
                    }
                }
                if (wins) break;
            }
        }
        // Check diagonal (top-left to bottom-right)
        if (!wins) {
            for (int i = 0; i < rows - 3; i++) {
                for (int j = 0; j < columns - 3; j++) {
                    if (board[i][j] == symbol && board[i+1][j+1] == symbol && board[i+2][j+2] == symbol && board[i+3][j+3] == symbol) {
                        wins = true;
                        break;
                    }
                }
                if (wins) break;
            }
        }
        // Check diagonal (bottom-left to top-right)
        if (!wins) {
            for (int i = 3; i < rows; i++) {
                for (int j = 0; j < columns - 3; j++) {
                    if (board[i][j] == symbol && board[i-1][j+1] == symbol && board[i-2][j+2] == symbol && board[i-3][j+3] == symbol) {
                        wins = true;
                        break;
                    }
                }
                if (wins) break;
            }
        }
        // Restore board state
        board[row][col] = ' ';
        return wins;
    }

public:
    /**
     * @brief Constructor - initializes 6x7 board with empty spaces
     */
    FourInRow_Board() : Board<char>(6, 7) { for (int i = 0; i < rows; ++i) { for (int j = 0; j < columns; ++j) { board[i][j] = ' '; }}}
    
    /**
     * @brief Updates board with a player's move
     * @param move Pointer to Move object containing column and symbol
     * @return true if move was valid and executed, false otherwise
     * 
     * Implements Connect Four gravity: piece falls to lowest empty row
     * in the selected column.
     */
    bool update_board(Move<char>* move) override {
        if (!move) return false;
        int col = move->get_y();
        char symbol = move->get_symbol();
        if (col < 0 || col >= columns) return false;
        // Find lowest empty row in the column (gravity simulation)
        int row = -1;
        for (int i = rows - 1; i >= 0; i--) {
            if (board[i][col] == ' ') {
                row = i;
                break;
            }
        }
        if (row == -1) {
            cout << "Invalid move: Column " << col << " is full.\n";
            return false;
        }
        board[row][col] = symbol;
        n_moves++;
        return true;
    }
    
    /**
     * @brief Checks if a player has won the game
     * @param player Pointer to Player object to check
     * @return true if player has four in a row, false otherwise
     */
    bool is_win(Player<char>* player) override {
        char symbol = player->get_symbol();
        // Check horizontal lines
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns - 3; j++) {
                if (board[i][j] == symbol && board[i][j+1] == symbol && board[i][j+2] == symbol && board[i][j+3] == symbol) return true;
            }
        }
        // Check vertical lines
        for (int i = 0; i < rows - 3; i++) {
            for (int j = 0; j < columns; j++) {
                if (board[i][j] == symbol && board[i+1][j] == symbol && board[i+2][j] == symbol && board[i+3][j] == symbol) return true;
            }
        }
        // Check diagonal (bottom-left to top-right)
        for (int i = 3; i < rows; i++) {
            for (int j = 0; j < columns - 3; j++) {
                if (board[i][j] == symbol && board[i-1][j+1] == symbol && board[i-2][j+2] == symbol && board[i-3][j+3] == symbol) return true;
            }
        }
        // Check diagonal (top-left to bottom-right)
        for (int i = 0; i < rows - 3; i++) {
            for (int j = 0; j < columns - 3; j++) {
                if (board[i][j] == symbol && board[i+1][j+1] == symbol && board[i+2][j+2] == symbol && board[i+3][j+3] == symbol) return true;
            }
        }
        return false;
    }
    
    /**
     * @brief Checks if a player has lost the game
     * @param player Pointer to Player object to check
     * @return true if opponent has four in a row, false otherwise
     */
    bool is_lose(Player<char>* player) override {
        char symbol = player->get_symbol();
        char opponent_symbol = (symbol == 'X') ? 'O' : 'X';
        // Check all win conditions for opponent
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns - 3; j++) {
                if (board[i][j] == opponent_symbol && board[i][j+1] == opponent_symbol && board[i][j+2] == opponent_symbol && board[i][j+3] == opponent_symbol) return true; 
            }
        }
        for (int i = 0; i < rows - 3; i++) {
            for (int j = 0; j < columns; j++) {
                if (board[i][j] == opponent_symbol && board[i+1][j] == opponent_symbol && board[i+2][j] == opponent_symbol && board[i+3][j] == opponent_symbol) return true;
            }
        }
        for (int i = 3; i < rows; i++) {
            for (int j = 0; j < columns - 3; j++) {
                if (board[i][j] == opponent_symbol && board[i-1][j+1] == opponent_symbol && board[i-2][j+2] == opponent_symbol && board[i-3][j+3] == opponent_symbol) return true;
            }
        }
        for (int i = 0; i < rows - 3; i++) {
            for (int j = 0; j < columns - 3; j++) {
                if (board[i][j] == opponent_symbol && board[i+1][j+1] == opponent_symbol && board[i+2][j+2] == opponent_symbol && board[i+3][j+3] == opponent_symbol) return true;
            }
        }
        return false;
    }
    
    /**
     * @brief Checks if the game is a draw
     * @param player Pointer to Player object (needed for interface)
     * @return true if board is full with no winner, false otherwise
     */
    bool is_draw(Player<char>* player) override {
        for (int i = 0; i < rows; i++) { for (int j = 0; j < columns; j++) { if (board[i][j] == ' ') return false; }}
        return !is_win(player) && !is_lose(player);
    }
    
    /**
     * @brief Checks if the game is over
     * @param player Pointer to Player object to check status for
     * @return true if game has ended (win, lose, or draw), false otherwise
     */
    bool game_is_over(Player<char>* player) override { return is_win(player) || is_lose(player) || is_draw(player); }

    public:
    /**
     * @brief Gets the best move using minimax with alpha-beta pruning
     * @param symbol Player symbol ('X' or 'O')
     * @param is_smart If true uses minimax AI, if false uses random moves
     * @return Column index (0-6) representing the chosen move
     */
    int get_best_move(char symbol, bool is_smart = true) {
        if (!is_smart) {
            // Random AI
            vector<int> valid_cols;
            for (int col = 0; col < columns; col++) { if (is_valid_column(col)) valid_cols.push_back(col); }
            if (!valid_cols.empty()) return valid_cols[rand() % valid_cols.size()]; 
            return 3;
        }
        bool is_maximizing = (symbol == 'X');
        int best_score = is_maximizing ? -10000 : 10000;
        int best_col = -1;
        // First, check for immediate wins/losses (quicker than minimax)
        char opponent = (symbol == 'X') ? 'O' : 'X';
        for (int col = 0; col < columns; col++) {
            if (is_valid_column(col)) {
                if (move_wins(symbol, col)) return col;
                if (move_wins(opponent, col)) best_col = col; // Remember blocking move
            }
        }
        if (best_col != -1) return best_col; // Return blocking move if found
        // Use minimax for deeper search
        vector<int> valid_cols;
        for (int col = 0; col < columns; col++) { if (is_valid_column(col)) valid_cols.push_back(col); }
        // Shuffle columns to add variety when scores are equal
        for (int i = valid_cols.size() - 1; i > 0; i--) {
            int j = rand() % (i + 1);
            swap(valid_cols[i], valid_cols[j]);
        }
        for (int col : valid_cols) {
            int row = get_next_row(col);
            board[row][col] = symbol;
            n_moves++;
            int score = minimax(5, -10000, 10000, !is_maximizing); // Depth 5 search
            board[row][col] = ' ';
            n_moves--;
            if ((is_maximizing && score > best_score) || (!is_maximizing && score < best_score)) {
                best_score = score;
                best_col = col;
            }
        }
        // Fallback: center or first valid column
        if (best_col == -1) {
            if (is_valid_column(3)) return 3;
            if (!valid_cols.empty()) return valid_cols[0];
        }
        return best_col;
    }
};
