#include <Windows.h>
#include <windowsx.h>
#include "res/resource.h"

#define ID_QUIT            1
#define TRAY_ICON_ID       (WM_APP + 1)
#define TRAY_ICON_MESSAGE  (WM_APP + 2)

NOTIFYICONDATA niData;
HICON hAppIcon;

void ShowTrayMenu(const HWND hWnd)
{
  POINT point;
  HMENU hMenu;
  HMENU hMenuTrackPopup;
   
  hMenu = LoadMenu(GetModuleHandle(NULL), "TrayMenu");
  hMenuTrackPopup = GetSubMenu(hMenu, 0);
  GetCursorPos((LPPOINT) &point);
  TrackPopupMenu(hMenuTrackPopup, TPM_LEFTALIGN | TPM_LEFTBUTTON, point.x, point.y, 0, hWnd, NULL);

  DestroyMenu(hMenu);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
  switch(uMsg)
  {
  case WM_COMMAND:
    if(wParam == ID_TRAY_EXIT)
      DestroyWindow(hWnd);
    break;
    
  case TRAY_ICON_MESSAGE:
    switch(lParam)
    {
    case WM_LBUTTONDOWN:
      ShowWindow(hWnd, SW_RESTORE);
      break;
    case WM_RBUTTONDOWN:
      ShowTrayMenu(hWnd);
      break;
    }
  break;
    
  case WM_CREATE:
    //CreateWindow(
    ZeroMemory(&niData, sizeof(NOTIFYICONDATA));
    niData.cbSize = sizeof(NOTIFYICONDATA);
    niData.uID    = TRAY_ICON_ID;
    niData.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
    niData.hIcon  = hAppIcon;
    niData.hWnd   = hWnd;
    niData.uCallbackMessage = TRAY_ICON_MESSAGE;

    Shell_NotifyIcon(NIM_ADD, &niData);
    break;

  case WM_MBUTTONDOWN:
    switch(wParam)
    {
    case MK_MBUTTON:
      SendMessage(hWnd, WM_CLOSE, 0, 0);
      break;
    }
    break;
    
  case WM_CLOSE:
    ShowWindow(hWnd, SW_HIDE);
    break;

  case WM_DESTROY:
    PostQuitMessage(0);
    Shell_NotifyIcon(NIM_DELETE, &niData);
    break;

  default:
    return DefWindowProc(hWnd, uMsg, wParam, lParam);
  }
  return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pCmdLine, int nShowCmd)
{
  MSG msg;
  WNDCLASSEX wc;
  HWND hWnd;

  hAppIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_RADIO));
  
  ZeroMemory(&wc, sizeof(WNDCLASSEX));
  wc.cbSize = sizeof(WNDCLASSEX);
  wc.lpfnWndProc = WndProc;
  wc.hInstance = hInstance;
  wc.hIcon = hAppIcon;
  wc.hCursor = LoadCursor(NULL, IDC_ARROW);
  wc.lpszClassName = "MainWindow";
  wc.hbrBackground = GetSysColorBrush(COLOR_3DFACE);

  RegisterClassEx(&wc);
  hWnd = CreateWindowEx(0, wc.lpszClassName, "WinLofi",
		 WS_OVERLAPPED | WS_SYSMENU | WS_VISIBLE,
		 CW_USEDEFAULT, CW_USEDEFAULT, 400, 500,
		 NULL, NULL, hInstance, NULL);
  
  for(;msg.message != WM_QUIT;)
  {
    BOOL res = GetMessage(&msg, NULL, 0, 0);
    if(res == -1)
    {
      MessageBox(NULL, "Unknown error", "Error", MB_OK | MB_ICONERROR);
      return 1;
    }

    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }
  return msg.wParam;
}
