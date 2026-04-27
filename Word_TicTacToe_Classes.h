/**
 * @file Word_TicTacToe_Classes.h
 * @brief Header file for Word Tic-Tac-Toe game classes.
 */

#ifndef WORD_TICTACTOE_CLASSES_H //Start of include guard
#define WORD_TICTACTOE_CLASSES_H

#include "BoardGame_Classes.h" 
#include <set>                
#include <string>              
#include <fstream>             
#include <algorithm>           
#include <cctype>              
#include <vector>          

using namespace std;

/**
 * @class Word_TicTacToe_Board
 * @brief Represents the 3x3 board for Word Tic-Tac-Toe.
 * Players place letters to form valid 3-letter words.
 */
class Word_TicTacToe_Board : public Board<char> {
private:
    set<string> dictionary;  ///< Stores valid 3-letter words. 
    char empty_symbol;       ///< Symbol for empty cells.  
    
    /**
     * @brief Loads the dictionary file (dic.txt) into memory.
     */
    void load_dictionary();    

    /**
     * @brief Checks if three characters form a valid word.
     * @param c1 First character.
     * @param c2 Second character.
     * @param c3 Third character.
     * @return True if the word exists in the dictionary.
     */
    bool check_line(char c1, char c2, char c3); 

public:

    /**
     * @brief Constructor. Initializes board and loads dictionary.
     */
    Word_TicTacToe_Board();

    /**
     * @brief Updates the board with a letter.
     * @param move Pointer to the move object.
     * @return True if move is valid.
     */
    bool update_board(Move<char>* move) override; 

    /**
     * @brief Checks if a winning word is formed.
     * @param player Pointer to the player.
     * @return True if a valid word is found on the board.
     */
    bool is_win(Player<char>* player) override;

    /**
     * @brief Checks if the player loses.
     * @return Always false for this game.
     */
    bool is_lose(Player<char>* player) override { return false; }

    /**
     * @brief Checks for a draw (board full and no winning words).
     * @param player Pointer to the player.
     * @return True if draw.
     */
    bool is_draw(Player<char>* player) override;

    /**
     * @brief Checks if the game is over.
     * @return True if win or draw.
     */
    bool game_is_over(Player<char>* player) override; 

    /**
     * @brief AI Function: Tries to find a winning move.
     * @return A Move object containing the best row, col, and letter.
     */
    Move<char> get_best_move();

};
/**
 * @class Word_TicTacToe_UI
 * @brief User Interface for Word Tic-Tac-Toe.
 */
class Word_TicTacToe_UI : public UI<char> {
private:
    Word_TicTacToe_Board* boardPtr; ///< Pointer to access board logic for AI.

public:
    /**
     * @brief Constructor.
     * @param b Pointer to the board.
     */
    Word_TicTacToe_UI(Word_TicTacToe_Board* b);

    /**
     * @brief Creates a player.
     * @param name Player's name.
     * @param symbol Placeholder symbol (not used strictly in this game).
     * @param type Human or Computer.
     * @return Pointer to the created player.
     */
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;

    /**
     * @brief Gets a move (row, col, char) from the player.
     * @param player Pointer to the player.
     * @return Pointer to the Move object.
     */
    Move<char>* get_move(Player<char>* player) override;
};
#endif //End of include guard