#include <windows.h>
#include <iostream>
#include <locale.h>
#include "keyboard_hook.h"

int main() {
    setlocale(LC_ALL, "");

    // Инициализация консоли (можно убрать, если не нужна)
    AllocConsole();
    FILE* fDummy;
    freopen_s(&fDummy, "CONOUT$", "w", stdout);
    freopen_s(&fDummy, "CONOUT$", "w", stderr);
    std::cout << "Program started." << std::endl;

    if (!InstallKeyboardHook()) {
        std::cerr << "Failed to install keyboard hook!" << std::endl;
        return 1;
    }

    // Цикл сообщений
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    UninstallKeyboardHook();
    return 0;
}