#include "clipboard_utils.h"
#include <windows.h>

void PasteFromClipboard() {
    Sleep(100);
    keybd_event(VK_CONTROL, 0, 0, 0);
    keybd_event('V', 0, 0, 0);
    keybd_event('V', 0, KEYEVENTF_KEYUP, 0);
    keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
}

std::wstring GetClipboardText() {
    if (!OpenClipboard(nullptr)) return L"";
    HANDLE hData = GetClipboardData(CF_UNICODETEXT);
    if (hData == nullptr) { CloseClipboard(); return L""; }
    wchar_t* pszText = static_cast<wchar_t*>(GlobalLock(hData));
    if (pszText == nullptr) { CloseClipboard(); return L""; }
    std::wstring text(pszText);
    GlobalUnlock(hData);
    CloseClipboard();
    return text;
}

void SetClipboardText(const std::wstring& text) {
    if (!OpenClipboard(nullptr)) return;
    EmptyClipboard();
    size_t sizeInBytes = (text.size() + 1) * sizeof(wchar_t);
    HGLOBAL hGlobal = GlobalAlloc(GMEM_MOVEABLE, sizeInBytes);
    if (hGlobal == nullptr) { CloseClipboard(); return; }
    wchar_t* pGlobal = static_cast<wchar_t*>(GlobalLock(hGlobal));
    wcscpy_s(pGlobal, text.size() + 1, text.c_str());
    GlobalUnlock(pGlobal);
    SetClipboardData(CF_UNICODETEXT, hGlobal);
    CloseClipboard();
}