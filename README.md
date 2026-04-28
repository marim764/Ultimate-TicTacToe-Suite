# Ultimate-TicTacToe-Suite
A massive C++ game engine featuring **13 unique variations of Tic-Tac-Toe and logic board games**. 
This project is a comprehensive implementation of **Object-Oriented Programming (OOP)**, showcasing advanced class hierarchies, polymorphism, and modular design.

# 🕹️ Integrated Games Menu

Our engine provides a unified interface to play any of the following 13 games:

1.  **SUS:** Search for the "S-U-S" sequence to win.
2.  **Four in Row:** Strategic 5x5 grid where you connect 4 symbols.
3.  **5x5 Tic-Tac-Toe:** High-scoring variant based on multiple alignments.
4.  **Word Tic-Tac-Toe:** Tactical word formation using letters.
5.  **Misère Tic-Tac-Toe:** The "Anti-Tic-Tac-Toe"—avoid getting 3 in a row!
6.  **Diamond Tic-Tac-Toe:** Played on a unique diamond-shaped board.
7.  **4x4 Moving Tic-Tac-Toe:** Dynamic board where pieces can shift positions.
8.  **Pyramid Tic-Tac-Toe:** Triangular board with 3 levels of difficulty.
9.  **Numerical Tic-Tac-Toe:** Mathematical version—reach a sum of 15.
10. **Obstacles Tic-Tac-Toe:** Standard play but with blocked/forbidden cells.
11. **Infinity Tic-Tac-Toe:** Pieces disappear after a certain number of moves.
12. **Ultimate Tic-Tac-Toe:** A massive 9x9 board containing 9 smaller games.
13. **Memory Tic-Tac-Toe (Bonus):** Symbols are hidden—test your mental memory!

## 🏗️ Technical Highlights (OOP Architecture)

This project strictly follows the **A-PIE** principles:
* **Abstraction:** Base `Board` and `Player` classes define the blueprint for all games.
* **Polymorphism:** Dynamic binding allows the `GameManager` to run any game logic through a single pointer.
* **Inheritance:** 13 specialized classes inherit from the core framework, reducing code duplication.
* **Encapsulation:** Safe management of game states, move validation, and board updates.

## 🤖 Smart AI
The engine includes a **Strategic AI** (Minimax-inspired logic) that can play against humans, providing a challenging experience.

## 👥 Team Members
* Marayam Nabil
* Firas Adnan
* Amal Ahmed
* Rodina Ahmed
