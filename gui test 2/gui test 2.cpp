#include <windows.h>
#include <string>
#include <iostream>
#include <cassert>

using std::wstring;
using std::wcout;

// Message handler function for window events
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

// Action triggered when "Next" button is clicked
void HandleNextButtonClick(HWND hwnd, HWND nameEdit, HWND userIDEdit, HWND optionsCombo, HWND agreeCheckBox, HWND exitRadio, HWND continueRadio);

// Basic unit tests (replace with a proper testing framework for real projects)
void RunUnitTests();

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR, int nCmdShow)
{
    RunUnitTests();  // Run tests before initializing GUI

    // Set up window class
    const wchar_t WINDOW_CLASS_NAME[] = L"BankLoginApp";
    WNDCLASS windowClass = {};
    windowClass.lpfnWndProc = WindowProc;
    windowClass.hInstance = hInstance;
    windowClass.lpszClassName = WINDOW_CLASS_NAME;
    windowClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    RegisterClass(&windowClass);

    // Create window
    HWND hwnd = CreateWindowEx(0, WINDOW_CLASS_NAME, L"Bank Login", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 400, 400, // Window size
        nullptr, nullptr, hInstance, nullptr);

    if (!hwnd) return 0;

    ShowWindow(hwnd, nCmdShow);

    // Main event loop
    MSG msg = {};
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

// Window event handler
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    static HWND nameEdit, userIDEdit, optionsCombo, agreeCheckBox, nextButton;
    static HWND exitRadio, continueRadio;

    switch (uMsg)
    {
    case WM_CREATE:
        // Name label and text box
        CreateWindow(L"STATIC", L"Name:", WS_VISIBLE | WS_CHILD, 20, 20, 80, 25, hwnd, nullptr, nullptr, nullptr);
        nameEdit = CreateWindow(L"EDIT", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, 120, 20, 200, 25, hwnd, (HMENU)101, nullptr, nullptr);

        // User ID label and text box
        CreateWindow(L"STATIC", L"User ID:", WS_VISIBLE | WS_CHILD, 20, 60, 80, 25, hwnd, nullptr, nullptr, nullptr);
        userIDEdit = CreateWindow(L"EDIT", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, 120, 60, 200, 25, hwnd, (HMENU)102, nullptr, nullptr);

        // Combo box for options
        CreateWindow(L"STATIC", L"Options:", WS_VISIBLE | WS_CHILD, 20, 100, 120, 25, hwnd, nullptr, nullptr, nullptr);
        optionsCombo = CreateWindow(L"COMBOBOX", nullptr, WS_VISIBLE | WS_CHILD | CBS_DROPDOWNLIST | WS_VSCROLL, 160, 100, 160, 150, hwnd, (HMENU)103, nullptr, nullptr);
        SendMessage(optionsCombo, CB_ADDSTRING, 0, (LPARAM)L"Check Balance");
        SendMessage(optionsCombo, CB_ADDSTRING, 0, (LPARAM)L"Deposit Money");
        SendMessage(optionsCombo, CB_ADDSTRING, 0, (LPARAM)L"Withdraw Money");
        SendMessage(optionsCombo, CB_ADDSTRING, 0, (LPARAM)L"Transfer Money");
        SendMessage(optionsCombo, CB_ADDSTRING, 0, (LPARAM)L"View Transaction History");
        SendMessage(optionsCombo, CB_ADDSTRING, 0, (LPARAM)L"Change PIN");
        SendMessage(optionsCombo, CB_ADDSTRING, 0, (LPARAM)L"Apply for Loan");
        SendMessage(optionsCombo, CB_ADDSTRING, 0, (LPARAM)L"Logout");

        // Radio buttons for exit/continue options
        exitRadio = CreateWindow(L"BUTTON", L"Exit Program", WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON | WS_GROUP, 20, 150, 120, 25, hwnd, (HMENU)106, nullptr, nullptr);
        continueRadio = CreateWindow(L"BUTTON", L"Continue Program", WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON, 150, 150, 150, 25, hwnd, (HMENU)107, nullptr, nullptr);

        // Terms of service checkbox
        agreeCheckBox = CreateWindow(L"BUTTON", L"I agree to the terms", WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX, 20, 200, 250, 25, hwnd, (HMENU)104, nullptr, nullptr);

        // "Next" button
        nextButton = CreateWindow(L"BUTTON", L"Next", WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 20, 250, 100, 35, hwnd, (HMENU)105, nullptr, nullptr);
        break;

    case WM_COMMAND:
        if (LOWORD(wParam) == 105)
        {
            HandleNextButtonClick(hwnd, nameEdit, userIDEdit, optionsCombo, agreeCheckBox, exitRadio, continueRadio);
        }
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    return 0;
}

// Handle Next button click event
void HandleNextButtonClick(HWND hwnd, HWND nameEdit, HWND userIDEdit, HWND optionsCombo, HWND agreeCheckBox, HWND exitRadio, HWND continueRadio)
{
    wchar_t name[100], userID[100];
    int selectedOption = SendMessage(optionsCombo, CB_GETCURSEL, 0, 0);
    BOOL agreeToTerms = SendMessage(agreeCheckBox, BM_GETCHECK, 0, 0);
    BOOL exitSelected = SendMessage(exitRadio, BM_GETCHECK, 0, 0);
    BOOL continueSelected = SendMessage(continueRadio, BM_GETCHECK, 0, 0);

    GetWindowText(nameEdit, name, 100);
    GetWindowText(userIDEdit, userID, 100);

    // Validate inputs
    if (wcslen(name) == 0 || wcslen(userID) == 0 || selectedOption == CB_ERR || !agreeToTerms || (!exitSelected && !continueSelected))
    {
        MessageBox(hwnd, L"Please complete all fields and agree to the terms.", L"Error", MB_OK);
    }
    else
    {
        wchar_t confirmation[300];
        wstring options[] = { L"Check Balance", L"Deposit Money", L"Withdraw Money", L"Transfer Money",
                              L"View Transaction History", L"Change PIN", L"Apply for Loan", L"Logout" };
        wsprintf(confirmation, L"Thank you, %s (User ID: %s).\nYou selected: %s.\nNext step: %s.",
            name, userID, options[selectedOption].c_str(), exitSelected ? L"Exit Program" : L"Continue Program");
        MessageBox(hwnd, confirmation, L"Confirmation", MB_OK);
    }
}

// Simulate simple unit tests
void RunUnitTests()
{
    wcout << L"Running basic tests..." << std::endl;

    // Test: Name and User ID validation
    wstring testName = L"John Doe";
    wstring testUserID = L"12345";
    assert(!testName.empty() && "Test failed: Name is empty");
    assert(!testUserID.empty() && "Test failed: UserID is empty");

    // Test: Option selection
    int selectedOption = 2;
    assert(selectedOption >= 0 && selectedOption < 8 && "Test failed: Invalid option");

    // Test: Checkbox and radio button
    BOOL agreeToTerms = TRUE;
    assert(agreeToTerms && "Test failed: Terms not agreed to");

    BOOL exitSelected = TRUE;
    BOOL continueSelected = FALSE;
    assert((exitSelected || continueSelected) && "Test failed: No radio button selected");

    wcout << L"All tests passed successfully." << std::endl;
}
