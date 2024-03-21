#pragma once
#include <string>

namespace Console
{
    
    constexpr char color_default[] = "\x1B[0m";

    constexpr char color_foreground_black[] = "\x1B[30m";
    constexpr char color_foreground_dark_red[] = "\x1B[31m";
    constexpr char color_foreground_dark_green[] = "\x1B[32m";
    constexpr char color_foreground_dark_yellow[] = "\x1B[33m";
    constexpr char color_foreground_dark_blue[] = "\x1B[34m";
    constexpr char color_foreground_dark_magenta[] = "\x1B[35m";
    constexpr char color_foreground_dark_cyan[] = "\x1B[36m";
    constexpr char color_foreground_dark_white[] = "\x1B[37m";
    constexpr char color_foreground_bright_black[] = "\x1B[90m";
    constexpr char color_foreground_bright_red[] = "\x1B[91m";
    constexpr char color_foreground_bright_green[] = "\x1B[92m";
    constexpr char color_foreground_bright_yellow[] = "\x1B[93m";
    constexpr char color_foreground_bright_blue[] = "\x1B[94m";
    constexpr char color_foreground_bright_magenta[] = "\x1B[95m";
    constexpr char color_foreground_bright_cyan[] = "\x1B[96m";
    constexpr char color_foreground_white[] = "\x1B[97m";

    constexpr char color_background_black[] = "\x1B[40m";
    constexpr char color_background_dark_red[] = "\x1B[41m";
    constexpr char color_background_dark_green[] = "\x1B[42m";
    constexpr char color_background_dark_yellow[] = "\x1B[43m";
    constexpr char color_background_dark_blue[] = "\x1B[44m";
    constexpr char color_background_dark_magenta[] = "\x1B[45m";
    constexpr char color_background_dark_cyan[] = "\x1B[46m";
    constexpr char color_background_dark_white[] = "\x1B[47m";
    constexpr char color_background_bright_black[] = "\x1B[100m";
    constexpr char color_background_bright_red[] = "\x1B[101m";
    constexpr char color_background_bright_green[] = "\x1B[102m";
    constexpr char color_background_bright_yellow[] = "\x1B[103m";
    constexpr char color_background_bright_blue[] = "\x1B[104m";
    constexpr char color_background_bright_magenta[] = "\x1B[105m";
    constexpr char color_background_bright_cyan[] = "\x1B[106m";
    constexpr char color_background_white[] = "\x1B[107m";

    constexpr char color_bold[] = "\x1B[1m";
    constexpr char color_underline[] = "\x1B[4m";
    constexpr char color_no_underline[] = "\x1B[24m";
    constexpr char color_reverse_text[] = "\x1B[7m";
    constexpr char color_not_reversed[] = "\x1B[27m";

    enum class ColorCode
    {
        DEFAULT,
        FOREGROUND_BLACK,
        FOREGROUND_DARK_RED,
        FOREGROUND_DARK_GREEN,
        FOREGROUND_DARK_YELLOW,
        FOREGROUND_DARK_BLUE,
        FOREGROUND_DARK_MAGENTA,
        FOREGROUND_DARK_CYAN,
        FOREGROUND_DARK_WHITE,
        FOREGROUND_BRIGHT_BLACK,
        FOREGROUND_BRIGHT_RED,
        FOREGROUND_BRIGHT_GREEN,
        FOREGROUND_BRIGHT_YELLOW,
        FOREGROUND_BRIGHT_BLUE,
        FOREGROUND_BRIGHT_MAGENTA,
        FOREGROUND_BRIGHT_CYAN,
        FOREGROUND_WHITE,
        BACKGROUND_BLACK,
        BACKGROUND_DARK_RED,
        BACKGROUND_DARK_GREEN,
        BACKGROUND_DARK_YELLOW,
        BACKGROUND_DARK_BLUE,
        BACKGROUND_DARK_MAGENTA,
        BACKGROUND_DARK_CYAN,
        BACKGROUND_DARK_WHITE,
        BACKGROUND_BRIGHT_BLACK,
        BACKGROUND_BRIGHT_RED,
        BACKGROUND_BRIGHT_GREEN,
        BACKGROUND_BRIGHT_YELLOW,
        BACKGROUND_BRIGHT_BLUE,
        BACKGROUND_BRIGHT_MAGENTA,
        BACKGROUND_BRIGHT_CYAN,
        BACKGROUND_WHITE,
        BOLD,
        UNDERLINE,
        NO_UNDERLINE,
        REVERSE_TEXT,
        NOT_REVERSED,
    };

    
    std::string Color(ColorCode code, std::string text);

    std::string Default(std::string text);
    std::string FgBlack(std::string text);
    std::string FgDarkRed(std::string text);
    std::string FgDarkGreen(std::string text);
    std::string FgDarkYellow(std::string text);
    std::string FgDarkBlue(std::string text);
    std::string FgDarkMagenta(std::string text);
    std::string FgDarkCyan(std::string text);
    std::string FgDarkWhite(std::string text);
    std::string FgBrightBlack(std::string text);
    std::string FgBrightRed(std::string text);
    std::string FgBrightGreen(std::string text);
    std::string FgBrightYellow(std::string text);
    std::string FgBrightBlue(std::string text);
    std::string FgBrightMagenta(std::string text);
    std::string FgBrightCyan(std::string text);
    std::string FgWhite(std::string text);
    std::string BgBlack(std::string text);
    std::string BgDarkRed(std::string text);
    std::string BgDarkGreen(std::string text);
    std::string BgDarkYellow(std::string text);
    std::string BgDarkBlue(std::string text);
    std::string BgDarkMagenta(std::string text);
    std::string BgDarkCyan(std::string text);
    std::string BgDarkWhite(std::string text);
    std::string BgBrightBlack(std::string text);
    std::string BgBrightRed(std::string text);
    std::string BgBrightGreen(std::string text);
    std::string BgBrightYellow(std::string text);
    std::string BgBrightBlue(std::string text);
    std::string BgBrightMagenta(std::string text);
    std::string BgBrightCyan(std::string text);
    std::string BgWhite(std::string text);
    std::string Bold(std::string text);
    std::string Underline(std::string text);
    std::string NoUnderline(std::string text);
    std::string ReverseText(std::string text);
    std::string NotReversed(std::string text);
}
