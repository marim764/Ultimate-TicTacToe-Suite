/**
 * @file Word_TicTacToe_Classes.cpp
 * @brief Implementation of Word Tic-Tac-Toe logic.
 */

#include "Word_TicTacToe_CLasses.h"
#include <iostream>
#include <cstdlib>   //For srand and rand
#include <ctime>
#include <cctype>       

using namespace std;
// ================= Implementation of Word_TicTacToe_Board =================

// --- Board Constructor ---
Word_TicTacToe_Board::Word_TicTacToe_Board() : Board<char>(3, 3) 
{
    empty_symbol = '.'; // Sets the character for an empty cell
    // Loops through all rows of the board
    for (int i = 0; i < rows; ++i) 
    {
        // Loops through all columns of the board
        for (int j = 0; j < columns; ++j) 
        {
            board[i][j] = empty_symbol; 
        }
    }
    load_dictionary(); //Calls the helper function to load words from the dictionary file
}

// --- Dictionary Loading Function ---
void Word_TicTacToe_Board::load_dictionary() 
{
    ifstream file("dic.txt"); //open the dictionary file in the same directory
    if (!file.is_open()) 
    { 
        // Checks if opening the file failed
        cout << "Error, could not open dic.txt file. Make sure it's in the same directory.\n"; 
        exit(1);
    }
    string word; //to store each word read from the file
    while (getline(file, word)) 
    { 
        // Reads the file line by line until the end
        if (word.length() == 3) 
        {
            // Converts the entire word to uppercase
            transform(word.begin(), word.end(), word.begin(), ::toupper);
            dictionary.insert(word); // Inserts the word into the dictionary set
        }
    }
    file.close(); // Closes the file after reading is complete
}

// --- Helper Function to Check a Single Line ---
bool Word_TicTacToe_Board::check_line(char c1, char c2, char c3) 
{
    //check if any cell in the line is empty, it cannot form a complete word
    if (c1 == empty_symbol || c2 == empty_symbol || c3 == empty_symbol) 
    {
        return false;
    }
    string formed_word = ""; //An empty string to concatenate the characters
    formed_word += c1; 
    formed_word += c2; 
    formed_word += c3; 

    // Searches for the formed word within the dictionary set
    return dictionary.count(formed_word) > 0;     // The count() function returns 1 if the word is found, 0 otherwis
}

// --- Function to Update the Board (Execute a Move) ---
bool Word_TicTacToe_Board::update_board(Move<char>* move) 
{
    int r = move->get_x(); 
    int c = move->get_y(); 
    char letter = toupper(move->get_symbol()); 

    if (r < 0 || r >= rows || c < 0 || c >= columns) 
    {
        return false;
    }
    if (board[r][c] != empty_symbol) 
    {
        return false;
    }

    if (!isalpha(letter)) {
        cout << "Invalid Input: You must enter a letter (A-Z).\n";
        return false;
    }

    board[r][c] = letter; //place the letter on the board
    n_moves++; 
    return true;
}

// --- Function to Check for a Win ---
bool Word_TicTacToe_Board::is_win(Player<char>* player) {
    //1.Check all horizontal rows
    for (int i = 0; i < 3; ++i)
    {
        if (check_line(board[i][0], board[i][1], board[i][2])) return true;
    }
    //2.Check all vertical columns
    for (int j = 0; j < 3; ++j)
    {
        if (check_line(board[0][j], board[1][j], board[2][j])) return true;
    }
    //3.Check the main diagonal
    if (check_line(board[0][0], board[1][1], board[2][2])) return true;

    //4.Check the anti-diagonal
    if (check_line(board[0][2], board[1][1], board[2][0])) return true;

    return false;
}

// --- Function to Check for a Draw ---
bool Word_TicTacToe_Board::is_draw(Player<char>*player) 
{
// A draw occurs if the total number of moves reaches the maximum (9) AND there is no winner
        return (n_moves == rows * columns && !is_win(player));
}

// --- Function to Check if the Game is Over ---
bool Word_TicTacToe_Board::game_is_over(Player<char>*player) 
{
        // The game ends either with a win OR with a draw
        return is_win(player) || is_draw(player);
}
Move<char> Word_TicTacToe_Board::get_best_move() {
    // 1. Try to find a winning move
    for (int i = 0; i < rows; ++i) 
    {
        for (int j = 0; j < columns; ++j) 
        {
            if (board[i][j] == empty_symbol) 
            {
                // Try every letter from A to Z
                for (char c = 'A'; c <= 'Z'; ++c) 
                {
                    board[i][j] = c; // Make move
                    if (is_win(nullptr)) 
                    { // Check if it wins
                        board[i][j] = empty_symbol; // Undo move
                        return Move<char>(i, j, c); // Found winning move!
                    }
                    board[i][j] = empty_symbol; // Undo move
                }
            }
        }
    }
    // 2. If no winning move, pick random empty cell
    int r, c;
    do {
        r = rand() % 3;
        c = rand() % 3;
    } while (board[r][c] != empty_symbol);

    // Pick a random letter
    char randomChar = 'A' + (rand() % 26);
    return Move<char>(r, c, randomChar);
}

// ================= Implementation of Word_TicTacToe_UI =================

// --- Constructor ---
Word_TicTacToe_UI::Word_TicTacToe_UI(Word_TicTacToe_Board* b) : UI<char>("Word Tic-Tac-Toe", 2)
{
    boardPtr = b;
    srand(time(0));
}

// --- Function to Create a Player ---
Player<char>* Word_TicTacToe_UI::create_player(string& name, char symbol, PlayerType type) 
{
    return new Player<char>(name, symbol, type);
}

// --- Function to Get a Move from a User or Computer ---
Move<char>* Word_TicTacToe_UI::get_move(Player<char>* player) 
{
    int r, c;
    char letter;
    cout << "\nIt's " << player->get_name() << "'s turn.\n";

    if (player->get_type() == PlayerType::HUMAN)  //If the player is human
    { 
        while (true) 
        { 
            cout << "Enter Row (0-2), Column (0-2), and a Letter (a-z) (e.g., 1 1 A): ";
            if (cin >> r >> c >> letter) 
            {
                return new Move<char>(r, c, toupper(letter));
            }
            else 
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignores any remaining invalid input on the line
                cout << "Invalid input format. Please try again.\n";
            }
        }
    }
    else 
    { 
        // --- Smart AI Move ---
        cout << "Computer is thinking...\n";

        Move<char> bestMove = boardPtr->get_best_move();

        cout << "Computer chose: " << bestMove.get_x() << " " << bestMove.get_y()
            << " " << bestMove.get_symbol() << endl;
        return new Move<char>(bestMove.get_x(), bestMove.get_y(), bestMove.get_symbol());
    }
}