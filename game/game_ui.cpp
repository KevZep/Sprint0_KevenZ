#include "game_ui.h"
#include <windows.h>
#include "GameBoard.h"

GameUI::GameUI(HINSTANCE hInst) : hInstance(hInst) {}


void GameUI::CreateUI(HWND hwnd) {
    // Store the pointer to the current instance of GameUI in the window's user data
    SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));

    CreateTitle(hwnd);
    CreateGameModeOptions(hwnd);
    CreateSizeInput(hwnd);
    CreatePlayerOptions(hwnd);
    CreateGameControlButtons(hwnd);
    CreateGameArea(hwnd);
}


void GameUI::CreateTitle(HWND hwnd) {
    hTitle = CreateWindowW(L"Static", L"SOS Game", WS_VISIBLE | WS_CHILD,
        200, 10, 400, 30, hwnd, nullptr, hInstance, nullptr);
}

void GameUI::CreateGameModeOptions(HWND hwnd) {
    CreateWindowW(L"Static", L"Game Mode:", WS_VISIBLE | WS_CHILD,
        20, 50, 100, 30, hwnd, nullptr, hInstance, nullptr);

    // Radio button group: First radio button has WS_GROUP
    hSimpleMode = CreateWindowW(L"Button", L"Simple", WS_VISIBLE | WS_CHILD | BS_RADIOBUTTON | WS_GROUP,
        150, 50, 100, 30, hwnd, (HMENU)1, hInstance, nullptr);
    hGeneralMode = CreateWindowW(L"Button", L"General", WS_VISIBLE | WS_CHILD | BS_RADIOBUTTON,
        270, 50, 100, 30, hwnd, (HMENU)2, hInstance, nullptr);

    // Set "Simple Mode" as the default selected option
    CheckRadioButton(hwnd, 1, 2, 1);  // Select "Simple Mode" by default
}


void GameUI::CreateSizeInput(HWND hwnd) {
    CreateWindowW(L"Static", L"Size:", WS_VISIBLE | WS_CHILD,
        400, 50, 50, 30, hwnd, nullptr, hInstance, nullptr);
    hSizeInput = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER,
        460, 50, 50, 30, hwnd, nullptr, hInstance, nullptr);
}

void GameUI::CreatePlayerOptions(HWND hwnd) {
    // Blue player options (left side)
    CreateWindowW(L"Static", L"Blue player:", WS_VISIBLE | WS_CHILD,
        20, 200, 100, 30, hwnd, nullptr, hInstance, nullptr);

    hHumanBlue = CreateWindowW(L"Button", L"Human", WS_VISIBLE | WS_CHILD | BS_RADIOBUTTON | WS_GROUP,
        20, 240, 100, 30, hwnd, (HMENU)3, hInstance, nullptr);

    // Indent S and O for Blue player
    hSBlue = CreateWindowW(L"Button", L"S", WS_VISIBLE | WS_CHILD | BS_RADIOBUTTON,
        40, 280, 50, 30, hwnd, (HMENU)4, hInstance, nullptr);
    hOBlue = CreateWindowW(L"Button", L"O", WS_VISIBLE | WS_CHILD | BS_RADIOBUTTON,
        40, 320, 50, 30, hwnd, (HMENU)5, hInstance, nullptr);

    hComputerBlue = CreateWindowW(L"Button", L"Computer", WS_VISIBLE | WS_CHILD | BS_RADIOBUTTON,
        20, 360, 100, 30, hwnd, (HMENU)6, hInstance, nullptr);

    // Initially disable S and O buttons for Blue
    EnableWindow(hSBlue, FALSE);
    EnableWindow(hOBlue, FALSE);

    // Red player options (right side)
    CreateWindowW(L"Static", L"Red player:", WS_VISIBLE | WS_CHILD,
        500, 200, 100, 30, hwnd, nullptr, hInstance, nullptr);

    hHumanRed = CreateWindowW(L"Button", L"Human", WS_VISIBLE | WS_CHILD | BS_RADIOBUTTON | WS_GROUP,
        500, 240, 100, 30, hwnd, (HMENU)7, hInstance, nullptr);

    // Indent S and O for Red player
    hSRed = CreateWindowW(L"Button", L"S", WS_VISIBLE | WS_CHILD | BS_RADIOBUTTON,
        520, 280, 50, 30, hwnd, (HMENU)8, hInstance, nullptr);
    hORed = CreateWindowW(L"Button", L"O", WS_VISIBLE | WS_CHILD | BS_RADIOBUTTON,
        520, 320, 50, 30, hwnd, (HMENU)9, hInstance, nullptr);

    hComputerRed = CreateWindowW(L"Button", L"Computer", WS_VISIBLE | WS_CHILD | BS_RADIOBUTTON,
        500, 360, 100, 30, hwnd, (HMENU)10, hInstance, nullptr);

    // Initially disable S and O buttons for Red
    EnableWindow(hSRed, FALSE);
    EnableWindow(hORed, FALSE);
}


void GameUI::CreateGameControlButtons(HWND hwnd) {
    hReplayBtn = CreateWindowW(L"Button", L"Replay", WS_VISIBLE | WS_CHILD | WS_BORDER,
        200, 550, 100, 40, hwnd, (HMENU)11, hInstance, nullptr);
    hNewGameBtn = CreateWindowW(L"Button", L"New Game", WS_VISIBLE | WS_CHILD | WS_BORDER,
        320, 550, 100, 40, hwnd, (HMENU)12, hInstance, nullptr);

    // Checkbox for recording game
    hRecordBox = CreateWindowW(L"Button", L"Record Game", WS_VISIBLE | WS_CHILD | BS_CHECKBOX,
        20, 550, 120, 30, hwnd, (HMENU)13, hInstance, nullptr);

    hCurrentTurn = CreateWindowW(L"Static", L"Current turn: Blue", WS_VISIBLE | WS_CHILD,
        450, 550, 150, 30, hwnd, nullptr, hInstance, nullptr);
}

void GameUI::CreateGameArea(HWND hwnd) {
    CreateWindowW(L"Static", L"Game Area", WS_VISIBLE | WS_CHILD | WS_BORDER,
        150, 100, 300, 300, hwnd, nullptr, hInstance, nullptr);  // Adjusted position and size
}

// This function processes messages for the main window.
LRESULT CALLBACK GameUI::WindowProcedure(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
    GameUI* pGameUI = reinterpret_cast<GameUI*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));

    switch (msg) {
    case WM_CREATE:
        //SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)lpCreateStruct->lpCreateParams);
        break;

    case WM_COMMAND: {
        if (pGameUI == nullptr) {
            return DefWindowProc(hwnd, msg, wp, lp);
        }

        int wmId = LOWORD(wp);

        switch (wmId) {
        case 1: // Simple mode radio button
            CheckRadioButton(hwnd, 1, 2, 1);
            break;
        case 2: // General mode radio button
            CheckRadioButton(hwnd, 1, 2, 2);
            break;

            // Blue Player - Human
        case 3: // Blue player - Human selected
            CheckRadioButton(hwnd, 3, 6, 3); // Ensure "Human" is selected for Blue
            EnableWindow(pGameUI->hSBlue, TRUE);  // Enable "S" for Blue
            EnableWindow(pGameUI->hOBlue, TRUE);  // Enable "O" for Blue
            break;

            // Blue Player - Computer
        case 6: // Blue player - Computer selected
            CheckRadioButton(hwnd, 3, 6, 6); // Ensure "Computer" is selected for Blue
            EnableWindow(pGameUI->hSBlue, FALSE);  // Disable "S" for Blue
            EnableWindow(pGameUI->hOBlue, FALSE);  // Disable "O" for Blue
            break;

            // Blue Player - 'S' selected
        case 4:
            CheckRadioButton(hwnd, 4, 5, 4); // Ensure 'S' is selected for Blue
            break;

            // Blue Player - 'O' selected
        case 5:
            CheckRadioButton(hwnd, 4, 5, 5); // Ensure 'O' is selected for Blue
            break;

            // Red Player - Human
        case 7: // Red player - Human selected
            CheckRadioButton(hwnd, 7, 10, 7); // Ensure "Human" is selected for Red
            EnableWindow(pGameUI->hSRed, TRUE);  // Enable "S" for Red
            EnableWindow(pGameUI->hORed, TRUE);  // Enable "O" for Red
            break;

            // Red Player - Computer
        case 10: // Red player - Computer selected
            CheckRadioButton(hwnd, 7, 10, 10); // Ensure "Computer" is selected for Red
            EnableWindow(pGameUI->hSRed, FALSE);  // Disable "S" for Red
            EnableWindow(pGameUI->hORed, FALSE);  // Disable "O" for Red
            break;

            // Red Player - 'S' selected
        case 8:
            CheckRadioButton(hwnd, 8, 9, 8); // Ensure 'S' is selected for Red
            break;

            // Red Player - 'O' selected
        case 9:
            CheckRadioButton(hwnd, 8, 9, 9); // Ensure 'O' is selected for Red
            break;

            // New Game Button Logic
        case 12: {
            wchar_t buffer[10];
            GetWindowText(pGameUI->hSizeInput, buffer, 10);
            int size = _wtoi(buffer);

            if (pGameUI->gameBoard.ValidateBoardSize(size)) {
                pGameUI->gameBoard.CreateBoard(hwnd, size);  // Create the board in the game area
            }
            else {
                pGameUI->gameBoard.DisplayError(hwnd);  // Display error if invalid
            }
            break;
        }

        case 13: // Record Game checkbox (no action needed here)
            break;
        }
        break;
    }


    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hwnd, msg, wp, lp);
    }
    return 0;
}

/*
    //GRID GAME
    GameUI* pGameUI = reinterpret_cast<GameUI*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));

    switch (msg) {
    case WM_COMMAND: {
        int wmId = LOWORD(wp);

        // Handle the "New Game" button click
if (wmId == 12 && pGameUI) {  // New Game button ID
    wchar_t buffer[10];
    GetWindowText(pGameUI->hSizeInput, buffer, 10);  // Get the input size
    int size = _wtoi(buffer);  // Convert to integer

    // Validate the size
    if (pGameUI->gameBoard.ValidateBoardSize(size)) {
        pGameUI->gameBoard.CreateBoard(hwnd, size);  // Create the board in the game area
    } else {
        pGameUI->gameBoard.DisplayError(hwnd);  // Display error if invalid
    }
}

        break;
    }

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hwnd, msg, wp, lp);
    }
    return 0;
}
*/



