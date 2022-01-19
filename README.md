# Sudoku game
[![Made With - C++](https://img.shields.io/badge/Made_With-C%2B%2B-9ACDD9?style=for-the-badge)](https://isocpp.org/)

---
## About the project
This project has been writen in C++ without using backtracking, which means that it has been done with a very basic level of C++ knowledge.
This project was originally created as an activity for my IT Engineering, Coding Fundamentals subject.

---
## Basic sudoku rules
The rules applied for this sudoku are the following:
1. A number can only be placed once per row.
2. A number can only be placed once per column.
3. A number can only appear at one cell of a quadrant (3x3 submatrix).

---
##  Game usage
In order to play the game, you must follow these instructions:
1. The first thing you must do once the game is running, is to enter a sudoku board using this format:
    ```
    0  8  0  5  7  6  2  0  0 
    0  0  0  4  0  2  0  0  0 
    0  0  0  0  3  9  5  4  8 
    6  3  0  9  0  0  8  5  2 
    0  9  0  2  0  0  3  7  0 
    8  0  0  0  5  0  6  9  4 
    2  5  7  6  0  3  4  8  9 
    3  0  8  7  0  0  0  2  5 
    0  4  0  0  0  0  0  0  6 
    ```
2. Once the board is entered, you have some options (to start any action, it must be done with one char):
    1. Option 'A':
        1. This option displays the possible values for an specific cell. To choose this option, you must use the following syntax:
            ```
            A row(number) column(char)
            A 1 H --> Display the valid values for the cell 1H.
            ```
    2. Option 'B':
        1. This option changes the value of a cell, only if it is empty (0) and it is a correct value for that cell. The syntax is the following:
            ```
            B row(number) column(char) new_value
            B 1 H 2
            ```
        2. If the cell is empty and the value is valid, it will be changed and no message will be displayed, otherwise, you will see one of the following messages:
            ```
            Casella no modificable --> Only displayed if the cell was previously filled with a value different to 0
            Valor no posible --> Only displayed if the cell is empty and the value is not valid for that cell.
            ```
    3. Option 'C':
        1. This option displays the current state of the sudoku. For this option, only the char 'C' is required. The display will be:
            ```
               A B C   D E F   G H I
            1  1 . 6 | . . 2 | 3 . 4 
            2  9 . 4 | 7 5 . | . 8 2 
            3  . . 8 | . . 6 | . . 5 
              -------+-------+-------
            4  . . 3 | . . . | . 4 . 
            5  2 . . | 4 . . | 8 3 . 
            6  4 . 7 | 5 . . | . . . 
              -------+-------+-------
            7  . . . | 6 . . | . . 8 
            8  7 . . | . 2 . | 4 5 3 
            9  . . . | 3 7 . | . 6 9 
            ```
    4. Option 'R':
        1. This option *autosolves* the sudoku, take into account that because it is coded without backtracking and using a very basic code, it may not be able to solve all types of sudokus, it works as it follows:
            1. For each empty cell (containing a zero) of the sudoku, it is searched for the possible values.
            2. If there is only one possible value for that cell, it is automatically changed to the value.
            3. If more than one value is possible, it will be checked for each possible value, if it is only possible in that cell for the row or the column.
            4. Once every cell is *checked*,  the option 'C' will be called, and the process will be restarted until the sudoku is solved or there have been no changes in the sudoku.
    5. Option 'Z':
        1. Once a 'Z' is entered through the keyboard input, the game ends.
