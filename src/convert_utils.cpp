#include "convert_utils.h"
#include <cctype>

// Функция преобразования строчной английской буквы в строчную русскую
wchar_t EngToRusLower(wchar_t eng) {
    switch (eng) {
    case L'q': return 0x0439; // й
    case L'w': return 0x0446; // ц
    case L'e': return 0x0443; // у
    case L'r': return 0x043A; // к
    case L't': return 0x0435; // е
    case L'y': return 0x043D; // н
    case L'u': return 0x0433; // г
    case L'i': return 0x0448; // ш
    case L'o': return 0x0449; // щ
    case L'p': return 0x0437; // з
    case L'a': return 0x0444; // ф
    case L's': return 0x044B; // ы
    case L'd': return 0x0432; // в
    case L'f': return 0x0430; // а
    case L'g': return 0x043F; // п
    case L'h': return 0x0440; // р
    case L'j': return 0x043E; // о
    case L'k': return 0x043B; // л
    case L'l': return 0x0434; // д
    case L'z': return 0x044F; // я
    case L'x': return 0x0447; // ч
    case L'c': return 0x0441; // с
    case L'v': return 0x043C; // м
    case L'b': return 0x0438; // и
    case L'n': return 0x0442; // т
    case L'm': return 0x044C; // ь
    default: return eng;
    }
}

// Функция преобразования заглавной английской буквы в заглавную русскую
wchar_t EngToRusUpper(wchar_t eng) {
    switch (eng) {
    case L'Q': return 0x0419; // Й
    case L'W': return 0x0426; // Ц
    case L'E': return 0x0423; // У
    case L'R': return 0x041A; // К
    case L'T': return 0x0415; // Е
    case L'Y': return 0x041D; // Н
    case L'U': return 0x0413; // Г
    case L'I': return 0x0428; // Ш
    case L'O': return 0x0429; // Щ
    case L'P': return 0x0417; // З
    case L'A': return 0x0424; // Ф
    case L'S': return 0x042B; // Ы
    case L'D': return 0x0412; // В
    case L'F': return 0x0410; // А
    case L'G': return 0x041F; // П
    case L'H': return 0x0420; // Р
    case L'J': return 0x041E; // О
    case L'K': return 0x041B; // Л
    case L'L': return 0x0414; // Д
    case L'Z': return 0x042F; // Я
    case L'X': return 0x0427; // Ч
    case L'C': return 0x0421; // С
    case L'V': return 0x041C; // М
    case L'B': return 0x0418; // И
    case L'N': return 0x041D; // Н (но N уже есть выше, оставим)
    case L'M': return 0x041C; // М
    default: return eng;
    }
}

// Преобразование знаков (оставляем как есть, но можно тоже через switch)
wchar_t SignToRus(wchar_t sign) {
    switch (sign) {
    case L'^': return L':';
    case L'@': return L'"';
    case L'#': return 0x2116; // №
    case L'$': return L';';
    case L'&': return L'?';
    case L'`': return 0x0451; // ё
    case L'~': return 0x0401; // Ё
    case L':': return 0x0416; // Ж
    case L'<': return 0x0411; // Б
    case L'>': return 0x042E; // Ю
    case L'{': return 0x0425; // Х
    case L'}': return 0x042A; // Ъ
    case L'?': return L',';
    case L'"': return 0x042D; // Э
    case L'\'': return 0x044D; // э
    case L',': return 0x0431; // б
    case L'.': return 0x044E; // ю
    case L'/': return L'.';
    case L';': return 0x0436; // ж
    case L'[': return 0x0445; // х
    case L']': return 0x044A; // ъ
    default: return sign;
    }
}

std::wstring ConvertLayout(const std::wstring& input) {
    std::wstring output;
    output.reserve(input.size());

    for (wchar_t c : input) {
        if (iswalpha(c)) {
            if (c >= L'A' && c <= L'Z') {
                // Заглавная латиница
                output += EngToRusUpper(c);
            }
            else if (c >= L'a' && c <= L'z') {
                // Строчная латиница
                output += EngToRusLower(c);
            }
            else {
                // Не латиница (например, уже русская) – оставляем как есть
                output += c;
            }
        }
        else {
            output += SignToRus(c);
        }
    }
    return output;
}