#pragma once
#include <string>

std::wstring GetClipboardText();
void SetClipboardText(const std::wstring& text);
void PasteFromClipboard();