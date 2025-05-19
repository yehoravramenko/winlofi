#include <windows.h>

auto WINAPI WinMain(HINSTANCE, HINSTANCE, PSTR, int) -> int
{
    ::MessageBox(nullptr, "win32 is amazing!", "hey!", MB_OK);
    return 0;
}