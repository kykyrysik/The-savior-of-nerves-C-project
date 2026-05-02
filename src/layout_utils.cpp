#include "layout_utils.h"
#include <windows.h>

void SwitchToRussianLayout() {
    HWND hWnd = GetForegroundWindow();
    if (!hWnd) return;
    HKL hklRussian = LoadKeyboardLayoutW(L"00000419", KLF_ACTIVATE);
    if (hklRussian) {
        PostMessageW(hWnd, WM_INPUTLANGCHANGEREQUEST, 0, (LPARAM)hklRussian);
    }
}