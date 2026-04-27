/**
 * @file GameApp.cpp
 * @brief Main application file containing the game menu and runners.
 * @details This file handles the user interface for selecting games and initializing
 * the specific board and players for the chosen game.
 */
#include <iostream>
#include <string>
#include <limits>

#include "BoardGame_Classes.h"

#include "SUS_Board.h"
#include "SUS_UI.h"
#include "FourInRow_Board.h"
#include "FourInRow_UI.h"
#include "FivexFive_TicTacToe_Board.h"
#include "FivexFive_TicTacToe_UI.h"
#include "Word_TicTacToe_Classes.h"
#include "Misere_TicTacToe_Board.h"
#include "Misere_TicTacToe_UI.h"
#include "Moving_TicTacToe_Classes.h"
#include "Moving_TicTacToe_UI.h"
#include "Numerical_TicTacToe_Board.h"
#include "Numerical_TicTacToe_UI.h"
#include "Obstacles_TicTacToe_Board.h"
#include "Obstacles_TicTacToe_UI.h"
#include "Infinity_TicTacToe_Board.h"
#include "Infinity_TicTacToe_UI.h"
#include "DiamondTicTacToe_Board.h"
#include "DiamondTicTacToe_UI.h"
#include "UltimateTicTacToe_Board.h"
#include "UltimateTicTacToe_UI.h"
#include "PyramidTicTacToe_Classes.h"
#include "MemoryTicTacToe_Classes.h"


using namespace std;

// ================= Function Definitions =================

/**
 * @brief Initializes and runs the SUS game.
 */
void play_sus() {
    cout << "\n=== Starting SUS Game ===\n";
    cout << "Player 1 plays 'S', Player 2 plays 'U'.\n";
    cout << "Goal: Create as many 'S-U-S' sequences as possible in rows, columns, or diagonals.\n";

    SUS_Board* board = new SUS_Board();
    SUS_UI* ui = new SUS_UI();
    ui->set_board(board);
    Player<char>* p1;
    Player<char>* p2;
    string name1, name2;
    int choice;
    PlayerType p1_type, p2_type;

    cout << "Enter Player 1 name: ";
    getline(cin >> ws, name1);
    cout << name1 << " (S): (1) Human or (2) Computer? ";
    while (!(cin >> choice) || (choice != 1 && choice != 2)) {
        cout << "Invalid choice. Please enter 1 or 2: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    p1_type = (choice == 1) ? PlayerType::HUMAN : PlayerType::COMPUTER;
    p1 = ui->create_player(name1, 'S', p1_type);

    cout << "Enter Player 2 name: ";
    getline(cin >> ws, name2);
    cout << name2 << " (U): (1) Human or (2) Computer? ";
    while (!(cin >> choice) || (choice != 1 && choice != 2)) {
        cout << "Invalid choice. Please enter 1 or 2: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    p2_type = (choice == 1) ? PlayerType::HUMAN : PlayerType::COMPUTER;
    p2 = ui->create_player(name2, 'U', p2_type);

    Player<char>* playersArr[2] = { p1, p2 };
    GameManager<char> game(board, playersArr, ui);
    game.run();

    cout << "\n=== Game Over ===\n";
    cout << name1 << " (S): " << board->get_S_score() << " points\n";
    cout << name2 << " (U): " << board->get_U_score() << " points\n";
    if (board->get_S_score() > board->get_U_score()) cout << name1 << " (S) wins!\n";
    else if (board->get_U_score() > board->get_S_score()) cout << name2 << " (U) wins!\n";
    else cout << "It's a draw!\n";

    delete p1;
    delete p2;
    delete ui;
    delete board;
}

/**
 * @brief Initializes and runs the Four-in-a-row game.
 */
void play_four_in_row() {
    cout << "\n=== Starting Connect Four ===\n";
    cout << "Goal: Be the first to get four of your marks in a row (horizontally, vertically, or diagonally).\n";
    cout << "Rules: Choose a column (0-6) to drop your piece. Pieces fall to the lowest available position.\n";

    FourInRow_Board* board = new FourInRow_Board();
    FourInRow_UI* ui = new FourInRow_UI();
    ui->set_board(board);
    Player<char>* p1, * p2;
    string name1, name2;
    int choice;
    PlayerType p1_type, p2_type;

    cout << "Enter Player 1 name: ";
    getline(cin >> ws, name1);
    cout << name1 << " (X): (1) Human or (2) Computer? ";
    while (!(cin >> choice) || (choice != 1 && choice != 2)) {
        cout << "Invalid choice. Please enter 1 or 2: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    p1_type = (choice == 1) ? PlayerType::HUMAN : PlayerType::COMPUTER;
    p1 = ui->create_player(name1, 'X', p1_type);

    cout << "Enter Player 2 name: ";
    getline(cin >> ws, name2);
    cout << name2 << " (O): (1) Human or (2) Computer? ";
    while (!(cin >> choice) || (choice != 1 && choice != 2)) {
        cout << "Invalid choice. Please enter 1 or 2: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    p2_type = (choice == 1) ? PlayerType::HUMAN : PlayerType::COMPUTER;
    p2 = ui->create_player(name2, 'O', p2_type);

    Player<char>* playersArr[2] = { p1, p2 };
    GameManager<char> game(board, playersArr, ui);
    game.run();
    cout << "\n=== Game Over ===\n";

    delete p1;
    delete p2;
    delete ui;
    delete board;
}

/**
 * @brief Initializes and runs the 5x5 Tic-Tac-Toe game.
 */
void play_5x5_ttt() {
    cout << "\n=== Starting 5x5 Tic-Tac-Toe ===\n";
    cout << "Goal: Get the most '3-in-a-row' sequences.\n";
    cout << "Rule: Game ends when the board (5x5) is completely FULL.\n\n";

    FivexFive_TicTacToe_Board* board = new FivexFive_TicTacToe_Board();
    FivexFive_TicTacToe_UI* ui = new FivexFive_TicTacToe_UI(board);
    Player<char>* p1, * p2;
    string name1, name2;
    int choice;
    PlayerType p1_type, p2_type;

    cout << "Enter Player 1 name: "; getline(cin >> ws, name1);
    cout << name1 << " (X): (1) Human or (2) Smart computer? ";
    while (!(cin >> choice) || (choice != 1 && choice != 2))
    {
        cout << "Invalid. 1 or 2: "; cin.clear(); cin.ignore(10000, '\n');
    }
    p1_type = (choice == 1) ? PlayerType::HUMAN : PlayerType::COMPUTER;
    p1 = ui->create_player(name1, 'X', p1_type);

    cout << "Enter Player 2 name: "; getline(cin >> ws, name2);
    cout << name2 << " (O): (1) Human or (2) Smart computer? ";
    while (!(cin >> choice) || (choice != 1 && choice != 2))
    {
        cout << "Invalid. 1 or 2: "; cin.clear(); cin.ignore(10000, '\n');
    }
    p2_type = (choice == 1) ? PlayerType::HUMAN : PlayerType::COMPUTER;
    p2 = ui->create_player(name2, 'O', p2_type);

    Player<char>* playersArr[2] = { p1, p2 };
    GameManager<char> game(board, playersArr, ui);
    game.run();
    delete p1;
    delete p2;
    delete ui;
    delete board;
}

/**
 * @brief Initializes and runs the Word Tic-Tac-Toe game.
 */
void play_word_ttt() {
    cout << "\n=== Starting Word Tic-Tac-Toe ===\n";
    cout << "Goal: Be the first to complete a valid 3-letter word.\n";

    Word_TicTacToe_Board* board = new Word_TicTacToe_Board();
    Word_TicTacToe_UI* ui = new Word_TicTacToe_UI(board);
    Player<char>* p1;
    Player<char>* p2;
    string name1, name2;
    int choice;
    PlayerType p1_type, p2_type;

    cout << "Enter Player 1 name: ";
    getline(cin >> ws, name1);
    cout << name1 << ": (1) Human or (2) Smart computer? ";
    while (!(cin >> choice) || (choice != 1 && choice != 2)) {
        cout << "Invalid choice. Please enter 1 or 2: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    p1_type = (choice == 1) ? PlayerType::HUMAN : PlayerType::COMPUTER;
    p1 = ui->create_player(name1, '1', p1_type);

    cout << "Enter Player 2 name: ";
    getline(cin >> ws, name2);
    cout << name2 << ": (1) Human or (2) Smart computer? ";
    while (!(cin >> choice) || (choice != 1 && choice != 2)) {
        cout << "Invalid choice. Please enter 1 or 2: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    p2_type = (choice == 1) ? PlayerType::HUMAN : PlayerType::COMPUTER;
    p2 = ui->create_player(name2, '2', p2_type);

    Player<char>* playersArr[2] = { p1, p2 };
    GameManager<char> game(board, playersArr, ui);
    game.run();

    delete p1;
    delete p2;
    delete ui;
    delete board;
}

/**
 * @brief Initializes and runs the Misere Tic-Tac-Toe game.
 */
void play_misere_ttt() {
    cout << "\n=== Starting Misère Tic-Tac-Toe ===\n";
    cout << "Goal: Avoid making three of your marks in a row.\n";

    Misere_TicTacToe_Board* board = new Misere_TicTacToe_Board();
    Misere_TicTacToe_UI* ui = new Misere_TicTacToe_UI();
    Player<char>* p1;
    Player<char>* p2;
    string name1, name2;
    int choice;
    PlayerType p1_type, p2_type;

    cout << "Enter Player 1 name: ";
    getline(cin >> ws, name1);
    cout << name1 << " (X): (1) Human or (2) Computer? ";
    while (!(cin >> choice) || (choice != 1 && choice != 2)) {
        cout << "Invalid choice. Please enter 1 or 2: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    p1_type = (choice == 1) ? PlayerType::HUMAN : PlayerType::COMPUTER;
    p1 = ui->create_player(name1, 'X', p1_type);

    cout << "Enter Player 2 name: ";
    getline(cin >> ws, name2);
    cout << name2 << " (O): (1) Human or (2) Computer? ";
    while (!(cin >> choice) || (choice != 1 && choice != 2)) {
        cout << "Invalid choice. Please enter 1 or 2: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    p2_type = (choice == 1) ? PlayerType::HUMAN : PlayerType::COMPUTER;
    p2 = ui->create_player(name2, 'O', p2_type);

    Player<char>* playersArr[2] = { p1, p2 };
    GameManager<char> game(board, playersArr, ui);
    game.run();

    delete p1;
    delete p2;
    delete ui;
    delete board;
}

/**
 * @brief Initializes and runs the Diamond Tic-Tac-Toe game.
 */
void play_DiamondTicTacToe() {
    cout << "=== Starting Diamond Tic-Tac-Toe ===\n";
    cout << "Goal: Complete two lines simultaneously to win (one of 3 marks, one of 4 marks, different directions).\n";
    DiamondTicTacToe_Board* board = new DiamondTicTacToe_Board();
    DiamondTicTacToe_UI* ui = new DiamondTicTacToe_UI();


    string n1, n2; int ch;
    cout << "Player 1 name: "; getline(cin >> ws, n1);
    cout << n1 << " (X) Human=1 Computer=2: "; cin >> ch;
    PlayerType t1 = (ch == 1 ? PlayerType::HUMAN : PlayerType::COMPUTER);
    Player<char>* p1 = ui->create_player(n1, 'X', t1);

    cout << "Player 2 name: "; getline(cin >> ws, n2);
    cout << n2 << " (O) Human=1 Computer=2: "; cin >> ch;
    PlayerType t2 = (ch == 1 ? PlayerType::HUMAN : PlayerType::COMPUTER);
    Player<char>* p2 = ui->create_player(n2, 'O', t2);

    Player<char>* arr[2] = { p1,p2 };
    GameManager<char> g(board, arr, ui);
    g.run();

    delete p1; delete p2; delete ui; delete board;
}


/**
 * @brief Initializes and runs the 4x4 Moving Tic-Tac-Toe game.
 */
void play_moving_ttt() {
    cout << "\n=== Starting 4x4 Moving Tic-Tac-Toe ===\n";
    cout << "Rules:\n- Move your token to adjacent empty cell.\n- Align 3 to win.\n";

    Moving_XO_Board* board = new Moving_XO_Board();
    Moving_XO_UI* ui = new Moving_XO_UI();
    Player<char>* p1;
    Player<char>* p2;
    string name1, name2;
    int choice;
    PlayerType p1_type, p2_type;

    cout << "Enter Player 1 name: ";
    getline(cin >> ws, name1);
    cout << name1 << " (X): (1) Human or (2) Computer? ";
    while (!(cin >> choice) || (choice != 1 && choice != 2)) {
        cout << "Invalid choice. Please enter 1 or 2: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    p1_type = (choice == 1) ? PlayerType::HUMAN : PlayerType::COMPUTER;
    p1 = ui->create_player(name1, 'X', p1_type);

    cout << "Enter Player 2 name: ";
    getline(cin >> ws, name2);
    cout << name2 << " (O): (1) Human or (2) Computer? ";
    while (!(cin >> choice) || (choice != 1 && choice != 2)) {
        cout << "Invalid choice. Please enter 1 or 2: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    p2_type = (choice == 1) ? PlayerType::HUMAN : PlayerType::COMPUTER;
    p2 = ui->create_player(name2, 'O', p2_type);

    Player<char>* playersArr[2] = { p1, p2 };
    GameManager<char> game(board, playersArr, ui);
    game.run();

    delete p1;
    delete p2;
    delete ui;
    delete board;
}

/**
 * @brief Initializes and runs the Pyramid Tic-Tac-Toe game.
 */
void play_pyramid_ttt() {

    cout << "\n=== Starting Pyramid Tic-Tac-Toe ===\n";
    cout << "Pyramid shape: Base=5, Middle=3, Top=1\n";
    cout << "Valid positions: (0,2) | (1,1) (1,2) (1,3) | (2,0) (2,1) (2,2) (2,3) (2,4)\n";
    cout << "Goal: Get three marks in a row (horizontal, vertical, or diagonal)\n";
    cout << "===========================================\n";

    PyramidTicTacToe_Board* board = new PyramidTicTacToe_Board();
    PyramidTicTacToe_UI* ui = new PyramidTicTacToe_UI();
    Player<char>* p1;
    Player<char>* p2;
    string name1, name2;
    int choice;
    PlayerType p1_type, p2_type;

    cout << "Enter Player 1 name: ";
    getline(cin >> ws, name1);
    cout << name1 << " (X): (1) Human or (2) Computer? ";
    cin >> choice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    p1_type = (choice == 1) ? PlayerType::HUMAN : PlayerType::COMPUTER;
    p1 = ui->create_player(name1, 'X', p1_type);

    cout << "Enter Player 2 name: ";
    getline(cin >> ws, name2);
    cout << name2 << " (O): (1) Human or (2) Computer? ";
    cin >> choice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    p2_type = (choice == 1) ? PlayerType::HUMAN : PlayerType::COMPUTER;
    p2 = ui->create_player(name2, 'O', p2_type);

    Player<char>* playersArr[2] = { p1, p2 };
    GameManager<char> game(board, playersArr, ui);
    game.run();

    delete p1;
    delete p2;
    delete ui;
    delete board;
}
/**
 * @brief Initializes and runs the Numerical Tic-Tac-Toe game.
 */
void play_numerical_ttt() {
    cout << "\n=== Starting Numerical Tic-Tac-Toe ===\n";
    cout << "Player 1 plays odd numbers (1,3,5,7,9), Player 2 plays even numbers (2,4,6,8).\n";
    cout << "Goal: Get a line of 3 numbers that sum to 15.\n";

    Numerical_TicTacToe_Board* board = new Numerical_TicTacToe_Board();
    Numerical_TicTacToe_UI* ui = new Numerical_TicTacToe_UI();
    Player<int>* p1;
    Player<int>* p2;
    string name1, name2;
    int choice;
    PlayerType p1_type, p2_type;

    cout << "Enter Player 1 name: ";
    getline(cin >> ws, name1);
    cout << name1 << ": (1) Human or (2) Computer? ";
    while (!(cin >> choice) || (choice != 1 && choice != 2)) {
        cout << "Invalid choice. Please enter 1 or 2: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    p1_type = (choice == 1) ? PlayerType::HUMAN : PlayerType::COMPUTER;
    p1 = ui->create_player(name1, 1, p1_type);

    cout << "Enter Player 2 name: ";
    getline(cin >> ws, name2);
    cout << name2 << ": (1) Human or (2) Computer? ";
    while (!(cin >> choice) || (choice != 1 && choice != 2)) {
        cout << "Invalid choice. Please enter 1 or 2: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    p2_type = (choice == 1) ? PlayerType::HUMAN : PlayerType::COMPUTER;
    p2 = ui->create_player(name2, 2, p2_type);

    Player<int>* playersArr[2] = { p1, p2 };
    GameManager<int> game(board, playersArr, ui);
    game.run();

    delete p1;
    delete p2;
    delete ui;
    delete board;
}

/**
 * @brief Initializes and runs the Obstacles Tic-Tac-Toe game.
 */
void play_obstacles_ttt() {
    cout << "\n=== Starting Obstacles Tic-Tac-Toe ===\n";
    cout << "Goal: Align four of your marks. 2 new obstacles '#' appear each round.\n";

    Obstacles_TicTacToe_Board* board = new Obstacles_TicTacToe_Board();
    Obstacles_TicTacToe_UI* ui = new Obstacles_TicTacToe_UI();
    Player<char>* p1;
    Player<char>* p2;
    string name1, name2;
    int choice;
    PlayerType p1_type, p2_type;

    cout << "Enter Player 1 name: ";
    getline(cin >> ws, name1);
    cout << name1 << " (X): (1) Human or (2) Computer? ";
    while (!(cin >> choice) || (choice != 1 && choice != 2)) {
        cout << "Invalid choice. Please enter 1 or 2: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    p1_type = (choice == 1) ? PlayerType::HUMAN : PlayerType::COMPUTER;
    p1 = ui->create_player(name1, 'X', p1_type);

    cout << "Enter Player 2 name: ";
    getline(cin >> ws, name2);
    cout << name2 << " (O): (1) Human or (2) Computer? ";
    while (!(cin >> choice) || (choice != 1 && choice != 2)) {
        cout << "Invalid choice. Please enter 1 or 2: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    p2_type = (choice == 1) ? PlayerType::HUMAN : PlayerType::COMPUTER;
    p2 = ui->create_player(name2, 'O', p2_type);

    Player<char>* playersArr[2] = { p1, p2 };
    GameManager<char> game(board, playersArr, ui);
    game.run();

    delete p1;
    delete p2;
    delete ui;
    delete board;
}

/**
 * @brief Initializes and runs the Infinity Tic-Tac-Toe game.
 */
void play_infinity_ttt() {
    cout << "\n=== Starting Infinity Tic-Tac-Toe ===\n";
    cout << "Goal: Be the first to align three of your marks in a row.\n";
    cout << "Rule: After every 3 moves, the oldest mark on the board disappears!\n";
    cout << "Strategy: Make your winning moves before they get removed!\n\n";

    Infinity_TicTacToe_Board* board = new Infinity_TicTacToe_Board();
    Infinity_TicTacToe_UI* ui = new Infinity_TicTacToe_UI();
    Player<char>* p1, * p2;
    string name1, name2;
    int choice;
    PlayerType p1_type, p2_type;

    cout << "Enter Player 1 name: ";
    getline(cin >> ws, name1);
    cout << name1 << " (X): (1) Human or (2) Computer? ";
    while (!(cin >> choice) || (choice != 1 && choice != 2)) {
        cout << "Invalid choice. Please enter 1 or 2: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    p1_type = (choice == 1) ? PlayerType::HUMAN : PlayerType::COMPUTER;
    p1 = ui->create_player(name1, 'X', p1_type);

    cout << "Enter Player 2 name: ";
    getline(cin >> ws, name2);
    cout << name2 << " (O): (1) Human or (2) Computer? ";
    while (!(cin >> choice) || (choice != 1 && choice != 2)) {
        cout << "Invalid choice. Please enter 1 or 2: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    p2_type = (choice == 1) ? PlayerType::HUMAN : PlayerType::COMPUTER;
    p2 = ui->create_player(name2, 'O', p2_type);

    Player<char>* playersArr[2] = { p1, p2 };
    GameManager<char> game(board, playersArr, ui);
    game.run();
    cout << "\n=== Game Over ===\n";
    delete p1;
    delete p2;
    delete ui;
    delete board;
}

/**
 * @brief Initializes and runs the Ultimate Tic-Tac-Toe game.
 */
void play_UltimateTicTacToe() {
    cout << "=== Starting Ultimate Tic-Tac-Toe ===\n";
    cout << "Meta-game: 3x3 main grid, each cell is a 3x3 board.\n";
    cout << "Win a small board to claim its cell. First to align 3 main cells wins.\n";
    UltimateTicTacToe_Board* board = new UltimateTicTacToe_Board();
    UltimateTicTacToe_UI* ui = new UltimateTicTacToe_UI();

    string n1, n2; int ch;
    cout << "Player 1 name: "; getline(cin >> ws, n1);
    cout << n1 << " (X) Human=1 Computer=2: "; cin >> ch;
    PlayerType t1 = (ch == 1 ? PlayerType::HUMAN : PlayerType::COMPUTER);
    Player<char>* p1 = ui->create_player(n1, 'X', t1);

    cout << "Player 2 name: "; getline(cin >> ws, n2);
    cout << n2 << " (O) Human=1 Computer=2: "; cin >> ch;
    PlayerType t2 = (ch == 1 ? PlayerType::HUMAN : PlayerType::COMPUTER);
    Player<char>* p2 = ui->create_player(n2, 'O', t2);

    Player<char>* arr[2] = { p1,p2 };
    GameManager<char> g(board, arr, ui);
    g.run();

    delete p1; delete p2; delete ui; delete board;
}

/**
 * @brief Initializes and runs the Memory Tic-Tac-Toe game.
 */
void play_memory_ttt() {
    cout << "\n=== Starting Memory Tic-Tac-Toe ===\n";

    MemoryTicTacToe_Board* board = new MemoryTicTacToe_Board();
    MemoryTicTacToe_UI* ui = new MemoryTicTacToe_UI();

    string name1, name2;
    int choice;

    cout << "Enter Player 1 name: "; getline(cin >> ws, name1);
    cout << name1 << " (X): (1) Human or (2) Computer? "; cin >> choice;
    PlayerType t1 = (choice == 1) ? PlayerType::HUMAN : PlayerType::COMPUTER;
    Player<char>* p1 = ui->create_player(name1, 'X', t1);

    cout << "Enter Player 2 name: "; getline(cin >> ws, name2);
    cout << name2 << " (O): (1) Human or (2) Computer? "; cin >> choice;
    PlayerType t2 = (choice == 1) ? PlayerType::HUMAN : PlayerType::COMPUTER;
    Player<char>* p2 = ui->create_player(name2, 'O', t2);

    p1->set_board_ptr(board);
    p2->set_board_ptr(board);

    // Show instructions ONLY ONCE at the beginning
    ui->display_instructions();

    Player<char>* players[2] = { p1, p2 };
    int current = 0;
    bool first_turn = true;

    while (!board->game_is_over(players[current])) {
        // Show hidden board
        ui->display_hidden_board();

        // Show reminder only on first turn
        if (first_turn) {
            cout << "\nRemember: All cells show '?'. Marks are hidden!\n";
            first_turn = false;
        }

        Player<char>* currentPlayer = players[current];
        Move<char>* move = ui->get_move(currentPlayer);

        while (!board->update_board(move)) {
            delete move;
            cout << "Invalid move! Cell already occupied.\n";
            move = ui->get_move(currentPlayer);
        }
        delete move;

        current = 1 - current; // Switch player
    }

    // Game over - reveal and announce winner
    cout << "\n=== GAME OVER ===\n";

    if (board->is_win(p1)) {
        cout << name1 << " (X) wins!\n";
    }
    else if (board->is_win(p2)) {
        cout << name2 << " (O) wins!\n";
    }
    else {
        cout << "It's a draw!\n";
    }

    // REVEAL the actual board
    board->reveal_board();

    delete p1; delete p2; delete ui; delete board;
}

/**
 * @brief Main entry point of the application.
 * @details Displays the main menu and handles user selection for the desired game.
 * @return 0 upon successful execution.
 */
int main() {
    int choice;
    do {
        cout << "\nWelcome to the Tic-Tac-Toe Games!\n";
        cout << "============ Board Games Menu =============\n";
        cout << "1. SUS\n";
        cout << "2. Four in Row\n";
        cout << "3. 5x5 Tic-Tac-Toe\n";
        cout << "4. Word Tic-Tac-Toe \n";
        cout << "5. Misère Tic-Tac-Toe \n";
        cout << "6. DiamondTicTacToe \n";
        cout << "7. 4x4 Moving Tic-Tac-Toe \n";
        cout << "8. Pyramid Tic-Tac-Toe \n";
        cout << "9. Numerical Tic-Tac-Toe\n";
        cout << "10.Obstacles Tic-Tac-Toe\n";
        cout << "11.Infinity Tic-Tac-Toe\n";
        cout << "12.UltimateTicTacToe\n";
        cout << "13.Memory Tic-Tac-Toe\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";

        while (!(cin >> choice) || (choice < 0 || choice > 13)) {
            cout << "Invalid choice. Please enter 0 through 13: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
        case 1: play_sus(); break;
        case 2: play_four_in_row(); break;
        case 3: play_5x5_ttt(); break;
        case 4: play_word_ttt(); break;
        case 5: play_misere_ttt(); break;
        case 6: play_DiamondTicTacToe(); break;
        case 7: play_moving_ttt(); break;
        case 8: play_pyramid_ttt(); break;
        case 9: play_numerical_ttt(); break;
        case 10:play_obstacles_ttt(); break;
        case 11:play_infinity_ttt(); break;
        case 12: play_UltimateTicTacToe(); break;
        case 13: play_memory_ttt(); break;
        case 0: cout << "Exiting.... \nGoodbye!\n"; break;
        default: break;
        }
    } while (choice != 0);

    return 0;
}
