#include <windows.h>
#include <string>
#include "game_ui.h"
#include "GameBoard.h"

// Constructor
GameBoard::GameBoard() {}

// Validate if the board size is between 3 and 10
bool GameBoard::ValidateBoardSize(int size) {
    return size >= MIN_SIZE && size <= MAX_SIZE;
}

// Create the game board in the center of the window
void GameBoard::CreateBoard(HWND hwnd, int size) {
    // Clear existing grid if any
    for (HWND button : gridButtons) {
        DestroyWindow(button);
    }
    gridButtons.clear();

    // Calculate dimensions based on size
    int buttonSize = 300 / size;  // Assuming game area is 300x300
    int xOffset = 150;
    int yOffset = 100;

    // Create the grid buttons
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            HWND button = CreateWindowW(
                L"Button",
                L"",
                WS_VISIBLE | WS_CHILD | WS_BORDER,
                xOffset + j * buttonSize,
                yOffset + i * buttonSize,
                buttonSize,
                buttonSize,
                hwnd,
                nullptr,
                nullptr,
                nullptr);

            gridButtons.push_back(button);
        }
    }
}



// Display an error message if the size is invalid
void GameBoard::DisplayError(HWND hwnd) {
    MessageBox(hwnd, L"Invalid size! Please enter a size between 3 and 10.", L"Error", MB_OK | MB_ICONERROR);
}
