#pragma once
#include "BoardGame_Classes.h"
#include <limits>
#include <set>
using namespace std;

/**
 * @class SUS_Board
 * @brief Represents the game board for the SUS (S-U-S) game
 * 
 * The game is played on a 3x3 grid where players take turns placing
 * 'S' (Player 1) and 'U' (Player 2). Points are scored by creating
 * "S-U-S" sequences horizontally, vertically, or diagonally.
 * The player with the most points when the board is full wins.
 */
class SUS_Board : public Board<char> {
private:
    int S_Score = 0;          ///< Score for Player 1 (S player)
    int U_Score = 0;          ///< Score for Player 2 (U player)
    set<string> counted_sequences; ///< Tracks already counted sequences to prevent double counting

    /**
     * @brief Checks and updates scores after a move
     * @param last_r Row index of the last move
     * @param last_c Column index of the last move
     * @param last_symbol Symbol ('S' or 'U') of the last move
     * 
     * This function checks if the last move completed any "S-U-S" sequences
     * and awards points accordingly:
     * - U player gets a point if they placed 'U' between two 'S's
     * - S player gets a point if they placed 'S' that completed the sequence
     */
    void check_and_update_scores(int last_r, int last_c, char last_symbol) {
        int r = last_r;
        // Check row for SUS pattern
        if (board[r][0] == 'S' && board[r][1] == 'U' && board[r][2] == 'S') {
            string seq_id = "row_" + to_string(r);
            if (counted_sequences.find(seq_id) == counted_sequences.end()) {
                // U player gets point for placing middle U between two S's
                if (last_symbol == 'U' && last_c == 1) {
                    U_Score++;
                    counted_sequences.insert(seq_id);
                } 
                // S player gets point for placing S that completes the sequence
                else if (last_symbol == 'S' && (last_c == 0 || last_c == 2)) {
                    S_Score++;
                    counted_sequences.insert(seq_id);
                }
            }
        }
        int c = last_c;
        // Check column for SUS pattern
        if (board[0][c] == 'S' && board[1][c] == 'U' && board[2][c] == 'S') {
            string seq_id = "col_" + to_string(c);
            if (counted_sequences.find(seq_id) == counted_sequences.end()) {
                if (last_symbol == 'U' && last_r == 1) {
                    U_Score++;
                    counted_sequences.insert(seq_id);
                } else if (last_symbol == 'S' && (last_r == 0 || last_r == 2)) {
                    S_Score++;
                    counted_sequences.insert(seq_id);
                }
            }
        }
        // Check main diagonal (top-left to bottom-right) for SUS pattern
        if (board[0][0] == 'S' && board[1][1] == 'U' && board[2][2] == 'S') {
            string seq_id = "diag1";
            if (counted_sequences.find(seq_id) == counted_sequences.end()) {
                if (last_symbol == 'U' && last_r == 1 && last_c == 1) {
                    U_Score++;
                    counted_sequences.insert(seq_id);
                } else if (last_symbol == 'S' && ((last_r == 0 && last_c == 0) || (last_r == 2 && last_c == 2))) {
                    S_Score++;
                    counted_sequences.insert(seq_id);
                }
            }
        }
        // Check anti-diagonal (top-right to bottom-left) for SUS pattern
        if (board[0][2] == 'S' && board[1][1] == 'U' && board[2][0] == 'S') {
            string seq_id = "diag2";
            if (counted_sequences.find(seq_id) == counted_sequences.end()) {
                if (last_symbol == 'U' && last_r == 1 && last_c == 1) {
                    U_Score++;
                    counted_sequences.insert(seq_id);
                } else if (last_symbol == 'S' && ((last_r == 0 && last_c == 2) || (last_r == 2 && last_c == 0))) {
                    S_Score++;
                    counted_sequences.insert(seq_id);
                }
            }
        }
    }

    /**
     * @brief Evaluates the current board position
     * @return Evaluation score (positive favors S, negative favors U)
     * 
     * Simple evaluation function that returns the score difference.
     * Used by the minimax algorithm for AI decision making.
     */
    int evaluate_board() { return S_Score - U_Score; }
    
    /**
     * @brief Minimax algorithm with alpha-beta pruning for AI decision making
     * @param depth Search depth (how many moves ahead to look)
     * @param isMaximizing True if it's the maximizing player's turn (S player)
     * @param alpha Alpha value for alpha-beta pruning
     * @param beta Beta value for alpha-beta pruning
     * @return Best evaluation score for the current position
     * 
     * Recursive algorithm that explores all possible moves to find
     * the optimal move. Uses alpha-beta pruning to improve efficiency.
     */
    int minimax(int depth, bool isMaximizing, int alpha, int beta) {
        // Base case: reached depth limit or game is over
        if (depth == 0 || n_moves == 9) return evaluate_board(); 

        if (isMaximizing) {
            // S player's turn (maximizing player)
            int maxEval = -1000;
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < columns; j++) {
                    if (board[i][j] == ' ') {
                        // Try placing S at empty cell
                        board[i][j] = 'S';
                        n_moves++;
                        // Save current state
                        int current_S = S_Score;
                        int current_U = U_Score;
                        set<string> current_counted = counted_sequences;
                        // Update scores for this move
                        check_and_update_scores(i, j, 'S');
                        // Recursively evaluate this move
                        int eval = minimax(depth - 1, false, alpha, beta);
                        // Undo the move (backtracking)
                        board[i][j] = ' ';
                        n_moves--;
                        S_Score = current_S;
                        U_Score = current_U;
                        counted_sequences = current_counted;
                        // Update best evaluation
                        maxEval = max(maxEval, eval);
                        alpha = max(alpha, eval);
                        // Alpha-beta pruning
                        if (beta <= alpha) break;
                    }
                }
            }
            return maxEval;
        } else {
            // U player's turn (minimizing player)
            int minEval = 1000;
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < columns; j++) {
                    if (board[i][j] == ' ') {
                        // Try placing U at empty cell
                        board[i][j] = 'U';
                        n_moves++;
                        // Save current state
                        int current_S = S_Score;
                        int current_U = U_Score;
                        set<string> current_counted = counted_sequences;
                        // Update scores for this move
                        check_and_update_scores(i, j, 'U');
                        // Recursively evaluate this move
                        int eval = minimax(depth - 1, true, alpha, beta);
                        // Undo the move (backtracking)
                        board[i][j] = ' ';
                        n_moves--;
                        S_Score = current_S;
                        U_Score = current_U;
                        counted_sequences = current_counted;
                        // Update best evaluation
                        minEval = min(minEval, eval);
                        beta = min(beta, eval);
                        // Alpha-beta pruning
                        if (beta <= alpha) break;
                    }
                }
            }
            return minEval;
        }
    }
    
public:
    /**
     * @brief Constructor for SUS_Board
     * Initializes a 3x3 game board with all cells empty
     */
    SUS_Board() : Board<char>(3, 3) { for (int i = 0; i < rows; ++i) { for (int j = 0; j < columns; ++j) { board[i][j] = ' '; }}} 

    /**
     * @brief Determines the best move for the Computer player
     * @param symbol Player symbol ('S' or 'U') for which to find the best move
     * @return Pair of integers representing the best move coordinates (row, column)
     * 
     * Uses minimax algorithm with alpha-beta pruning to find the optimal move.
     * Searches to a depth of 5 moves ahead for reasonable performance.
     */
    pair<int, int> get_best_move(char symbol) {
        int bestScore = (symbol == 'S') ? -1000 : 1000;
        pair<int, int> bestMove = {-1, -1};
        // Try all possible moves
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                if (board[i][j] == ' ') {
                    // Simulate this move
                    board[i][j] = symbol;
                    n_moves++;
                    // Save current state
                    int current_S = S_Score;
                    int current_U = U_Score;
                    set<string> current_counted = counted_sequences;
                    // Update scores for this move
                    check_and_update_scores(i, j, symbol);
                    // Evaluate this move using minimax (depth 5)
                    int moveScore = minimax(5, (symbol == 'U'), -1000, 1000);
                    // Undo the move
                    board[i][j] = ' ';
                    n_moves--;
                    S_Score = current_S;
                    U_Score = current_U;
                    counted_sequences = current_counted;
                    // Update best move if this is better
                    if ((symbol == 'S' && moveScore > bestScore) || 
                        (symbol == 'U' && moveScore < bestScore)) {
                        bestScore = moveScore;
                        bestMove = {i, j};
                    }
                }
            }
        }
        
        return bestMove;
    }
    
    /**
     * @brief Updates the board with a player's move
     * @param move Pointer to the Move object containing move details
     * @return True if the move was valid and executed, false otherwise
     * 
     * Validates the move, checks if it's the player's turn with correct symbol,
     * updates the board, and checks for completed sequences to update scores.
     */
    bool update_board(Move<char>* move) override {
        if (!move) return false;
        int r = move->get_x();
        int c = move->get_y();
        char symbol = move->get_symbol();
        // Validate move coordinates
        if (r < 0 || r >= rows || c < 0 || c >= columns) return false;
        // Check if cell is empty
        if (board[r][c] != ' ') {
            cout << "Invalid move: Cell (" << r << "," << c << ") is already occupied.\n";
            return false;
        }
        // Validate turn order: even moves (0,2,4,6,8) must be 'S', odd moves must be 'U'
        if (n_moves % 2 == 0 && symbol != 'S') return false;
        if (n_moves % 2 == 1 && symbol != 'U') return false;
        // Execute the move
        board[r][c] = symbol;
        n_moves++;
        // Check if this move completed any SUS sequences
        check_and_update_scores(r, c, symbol);
        return true;
    }  
    
    /**
     * @brief Checks if the specified player has won
     * @param player Pointer to the Player object to check
     * @return True if the player has won, false otherwise
     * 
     * A player wins if the game is over (board full) and they have more points
     * than their opponent.
     */
    bool is_win(Player<char>* player) override {
        char symbol = player->get_symbol();
        // Game must be over (board full) to determine winner
        if (n_moves == 9 && symbol == 'S' && S_Score > U_Score) return true;
        if (n_moves == 9 && symbol == 'U' && U_Score > S_Score) return true;
        return false;
    }
    
    /**
     * @brief Checks if the specified player has lost
     * @param player Pointer to the Player object to check
     * @return True if the player has lost, false otherwise
     * 
     * A player loses if the game is over and they have fewer points
     * than their opponent.
     */
    bool is_lose(Player<char>* player) override {
        char symbol = player->get_symbol();
        if (n_moves == 9 && symbol == 'S' && U_Score > S_Score) return true;
        if (n_moves == 9 && symbol == 'U' && S_Score > U_Score) return true;
        return false;
    }
    
    /**
     * @brief Checks if the game is a draw
     * @param player Pointer to the Player object (unused, for interface compatibility)
     * @return True if the game is a draw, false otherwise
     * 
     * The game is a draw if the board is full and both players have equal scores.
     */
    bool is_draw(Player<char>* player) override { return (n_moves == 9) && (S_Score == U_Score); }
    
    /**
     * @brief Checks if the game is over
     * @param player Pointer to the Player object (unused, for interface compatibility)
     * @return True if the game is over, false otherwise
     * 
     * The game is over when the board is completely filled (9 moves).
     */
    bool game_is_over(Player<char>* player) override { return (n_moves == 9); }
    
    /**
     * @brief Gets the current score for Player 1 (S player)
     * @return S player's score
     */
    int get_S_score() const { return S_Score; }
    
    /**
     * @brief Gets the current score for Player 2 (U player)
     * @return U player's score
     */
    int get_U_score() const { return U_Score; }

};
