#include <Windows.h>

HWND g_mainWindow = nullptr;

[[noreturn]] inline auto ProgramError(LPCSTR message) -> void
{
    MessageBox(nullptr, message, "Error", MB_OK | MB_ICONERROR);
    ExitProcess(1);
}

auto CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
    -> LRESULT
{
    switch (uMsg)
    {
    case WM_CLOSE: {
        DestroyWindow(hWnd);
        break;
    }
    case WM_DESTROY: {
        PostQuitMessage(0);
        break;
    }
    }
    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

auto WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int) -> int
{
    MSG uMsg{};
    WNDCLASSEX wc;

    wc.cbSize        = sizeof(WNDCLASSEX);
    wc.style         = 0;
    wc.lpfnWndProc   = WndProc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.hInstance     = hInstance;
    wc.hIcon         = LoadIcon(nullptr, IDI_APPLICATION);
    wc.hCursor       = LoadCursor(nullptr, IDC_ARROW);
    wc.hbrBackground = GetSysColorBrush(COLOR_WINDOW);
    wc.lpszMenuName  = nullptr;
    wc.lpszClassName = "MainWindow";
    wc.hIconSm       = nullptr;

    if (!RegisterClassEx(&wc))
    {
        ProgramError("Failed to register window class");
    }

    g_mainWindow = CreateWindowEx(
        0, "MainWindow", "WinLofi", WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, nullptr,
        nullptr, hInstance, nullptr);

    if (g_mainWindow == nullptr)
    {
        ProgramError("Failed to create window");
    }

    UpdateWindow(g_mainWindow);

    while (true)
    {
        auto msgRet = GetMessage(&uMsg, nullptr, 0, 0);
        if (msgRet == -1)
        {
            ProgramError("An error occured");
        }
        else if (msgRet == 0)
        {
            break;
        }
        TranslateMessage(&uMsg);
        DispatchMessage(&uMsg);
    }

    return static_cast<int>(uMsg.wParam);
}