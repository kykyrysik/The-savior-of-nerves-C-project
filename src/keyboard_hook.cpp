#include "keyboard_hook.h"
#include "convert_utils.h"
#include "clipboard_utils.h"
#include "layout_utils.h"
#include "ini.h"
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>

static HHOOK keyboardHook = nullptr;
static int g_hotkey = 0;

int GetHotkeyFromConfig() {
    int vk = 45;
    FILE* f = nullptr;
    if (fopen_s(&f, "config.ini", "r") == 0 && f != nullptr) {
        ini_parse_file(f, [](void* user, const char* section, const char* name, const char* value) {
            if (strcmp(section, "Hotkey") == 0 && strcmp(name, "vk") == 0) {
                *(int*)user = atoi(value);
            }
            return 1;
            }, &vk);
        fclose(f);
    }
    return vk;
}

LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode == HC_ACTION && wParam == WM_KEYDOWN) {
        KBDLLHOOKSTRUCT* p = (KBDLLHOOKSTRUCT*)lParam;
        // Можно оставить отладочный вывод, если нужно
        // std::cout << "Key pressed: " << p->vkCode << std::endl;
        if (p->vkCode == g_hotkey) {
            // Копируем выделенный текст
            Sleep(100);
            keybd_event(VK_CONTROL, 0, 0, 0);
            keybd_event('C', 0, 0, 0);
            keybd_event('C', 0, KEYEVENTF_KEYUP, 0);
            keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
            Sleep(100);

            std::wstring selectedText = GetClipboardText();
            if (!selectedText.empty()) {
                std::wstring convertedText = ConvertLayout(selectedText);
                SetClipboardText(convertedText);
                Sleep(100);
                PasteFromClipboard();
                SwitchToRussianLayout();
            }
            return 1;
        }
    }
    return CallNextHookEx(keyboardHook, nCode, wParam, lParam);
}

bool InstallKeyboardHook() {
    g_hotkey = GetHotkeyFromConfig();
    keyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, GetModuleHandle(nullptr), 0);
    return (keyboardHook != nullptr);
}

void UninstallKeyboardHook() {
    if (keyboardHook) {
        UnhookWindowsHookEx(keyboardHook);
        keyboardHook = nullptr;
    }
}
