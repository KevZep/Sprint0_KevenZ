#include "game_ui.h"
#include <windows.h>
#include "GameBoard.h"

LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow) {
    WNDCLASSW wc = { 0 };

    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wc.hInstance = hInst;
    wc.lpszClassName = L"gameWindowClass";
    wc.lpfnWndProc = GameUI::WindowProcedure;

    if (!RegisterClassW(&wc)) return -1;

    HWND hwnd = CreateWindowW(L"gameWindowClass", L"SOS Game", WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        100, 100, 600, 700, nullptr, nullptr, hInst, nullptr);

    GameUI ui(hInst);
    ui.CreateUI(hwnd);

    MSG msg = { 0 };

    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}
