#pragma once
#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <windows.h>
#include <string>
#include <vector>

class GameBoard {
public:
    GameBoard();  // Constructor

    // Function to validate the board size
    bool ValidateBoardSize(int size);

    // Function to create the board grid
    void CreateBoard(HWND hwnd, int size);

    // Function to display an error message if the size is invalid
    void DisplayError(HWND hwnd);

private:
    const int MIN_SIZE = 3;
    const int MAX_SIZE = 10;
    std::vector<HWND> gridButtons;
};

#endif  // GAMEBOARD_H
