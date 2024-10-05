#pragma once
#ifndef GAME_UI_H
#define GAME_UI_H

#include <windows.h>
#include "GameBoard.h"  // Include the GameBoard header

class GameUI {
public:
    GameUI(HINSTANCE hInst);
    void CreateUI(HWND hwnd);
    static LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);

private:
    HINSTANCE hInstance;

    // Add this member for the game board
    GameBoard gameBoard;  // Declare gameBoard as a member

    // Declare all the UI elements as members
    HWND hTitle;
    HWND hSimpleMode;
    HWND hGeneralMode;
    HWND hSizeInput;
    HWND hHumanBlue;
    HWND hSBlue;
    HWND hOBlue;
    HWND hComputerBlue;
    HWND hHumanRed;
    HWND hSRed;
    HWND hORed;
    HWND hComputerRed;
    HWND hReplayBtn;
    HWND hNewGameBtn;
    HWND hRecordBox;
    HWND hCurrentTurn;

    // Declare the creation functions
    void CreateTitle(HWND hwnd);
    void CreateGameModeOptions(HWND hwnd);
    void CreateSizeInput(HWND hwnd);
    void CreatePlayerOptions(HWND hwnd);
    void CreateGameControlButtons(HWND hwnd);
    void CreateGameArea(HWND hwnd);
};

#endif
