#include "console_color.hpp"
#include <string>

namespace Console
{



std::string Color(ColorCode code, std::string text)
    {
        const char *color_str = color_default;
        const char *default_str = color_default;
        switch (code)
        {
        case ColorCode::DEFAULT:
            color_str = color_default;
            break;
        case ColorCode::FOREGROUND_BLACK:
            color_str = color_foreground_black;
            break;
        case ColorCode::FOREGROUND_DARK_RED:
            color_str = color_foreground_dark_red;
            break;
        case ColorCode::FOREGROUND_DARK_GREEN:
            color_str = color_foreground_dark_green;
            break;
        case ColorCode::FOREGROUND_DARK_YELLOW:
            color_str = color_foreground_dark_yellow;
            break;
        case ColorCode::FOREGROUND_DARK_BLUE:
            color_str = color_foreground_dark_blue;
            break;
        case ColorCode::FOREGROUND_DARK_MAGENTA:
            color_str = color_foreground_dark_magenta;
            break;
        case ColorCode::FOREGROUND_DARK_CYAN:
            color_str = color_foreground_dark_cyan;
            break;
        case ColorCode::FOREGROUND_DARK_WHITE:
            color_str = color_foreground_dark_white;
            break;
        case ColorCode::FOREGROUND_BRIGHT_BLACK:
            color_str = color_foreground_bright_black;
            break;
        case ColorCode::FOREGROUND_BRIGHT_RED:
            color_str = color_foreground_bright_red;
            break;
        case ColorCode::FOREGROUND_BRIGHT_GREEN:
            color_str = color_foreground_bright_green;
            break;
        case ColorCode::FOREGROUND_BRIGHT_YELLOW:
            color_str = color_foreground_bright_yellow;
            break;
        case ColorCode::FOREGROUND_BRIGHT_BLUE:
            color_str = color_foreground_bright_blue;
            break;
        case ColorCode::FOREGROUND_BRIGHT_MAGENTA:
            color_str = color_foreground_bright_magenta;
            break;
        case ColorCode::FOREGROUND_BRIGHT_CYAN:
            color_str = color_foreground_bright_cyan;
            break;
        case ColorCode::FOREGROUND_WHITE:
            color_str = color_foreground_white;
            break;
        case ColorCode::BACKGROUND_BLACK:
            color_str = color_background_black;
            break;
        case ColorCode::BACKGROUND_DARK_RED:
            color_str = color_background_dark_red;
            break;
        case ColorCode::BACKGROUND_DARK_GREEN:
            color_str = color_background_dark_green;
            break;
        case ColorCode::BACKGROUND_DARK_YELLOW:
            color_str = color_background_dark_yellow;
            break;
        case ColorCode::BACKGROUND_DARK_BLUE:
            color_str = color_background_dark_blue;
            break;
        case ColorCode::BACKGROUND_DARK_MAGENTA:
            color_str = color_background_dark_magenta;
            break;
        case ColorCode::BACKGROUND_DARK_CYAN:
            color_str = color_background_dark_cyan;
            break;
        case ColorCode::BACKGROUND_DARK_WHITE:
            color_str = color_background_dark_white;
            break;
        case ColorCode::BACKGROUND_BRIGHT_BLACK:
            color_str = color_background_bright_black;
            break;
        case ColorCode::BACKGROUND_BRIGHT_RED:
            color_str = color_background_bright_red;
            break;
        case ColorCode::BACKGROUND_BRIGHT_GREEN:
            color_str = color_background_bright_green;
            break;
        case ColorCode::BACKGROUND_BRIGHT_YELLOW:
            color_str = color_background_bright_yellow;
            break;
        case ColorCode::BACKGROUND_BRIGHT_BLUE:
            color_str = color_background_bright_blue;
            break;
        case ColorCode::BACKGROUND_BRIGHT_MAGENTA:
            color_str = color_background_bright_magenta;
            break;
        case ColorCode::BACKGROUND_BRIGHT_CYAN:
            color_str = color_background_bright_cyan;
            break;
        case ColorCode::BACKGROUND_WHITE:
            color_str = color_background_white;
            break;
        case ColorCode::BOLD:
            color_str = color_bold;
            break;
        case ColorCode::UNDERLINE:
            color_str = color_underline;
            break;
        case ColorCode::NO_UNDERLINE:
            color_str = color_no_underline;
            break;
        case ColorCode::REVERSE_TEXT:
            color_str = color_reverse_text;
            break;
        case ColorCode::NOT_REVERSED:
            color_str = color_not_reversed;
            break;
        }

        return color_str + text + default_str;
    }

    std::string Default(std::string text) { return Color(ColorCode::DEFAULT, text); }
    std::string FgBlack(std::string text) { return Color(ColorCode::FOREGROUND_BLACK, text); }
    std::string FgDarkRed(std::string text) { return Color(ColorCode::FOREGROUND_DARK_RED, text); }
    std::string FgDarkGreen(std::string text) { return Color(ColorCode::FOREGROUND_DARK_GREEN, text); }
    std::string FgDarkYellow(std::string text) { return Color(ColorCode::FOREGROUND_DARK_YELLOW, text); }
    std::string FgDarkBlue(std::string text) { return Color(ColorCode::FOREGROUND_DARK_BLUE, text); }
    std::string FgDarkMagenta(std::string text) { return Color(ColorCode::FOREGROUND_DARK_MAGENTA, text); }
    std::string FgDarkCyan(std::string text) { return Color(ColorCode::FOREGROUND_DARK_CYAN, text); }
    std::string FgDarkWhite(std::string text) { return Color(ColorCode::FOREGROUND_DARK_WHITE, text); }
    std::string FgBrightBlack(std::string text) { return Color(ColorCode::FOREGROUND_BRIGHT_BLACK, text); }
    std::string FgBrightRed(std::string text) { return Color(ColorCode::FOREGROUND_BRIGHT_RED, text); }
    std::string FgBrightGreen(std::string text) { return Color(ColorCode::FOREGROUND_BRIGHT_GREEN, text); }
    std::string FgBrightYellow(std::string text) { return Color(ColorCode::FOREGROUND_BRIGHT_YELLOW, text); }
    std::string FgBrightBlue(std::string text) { return Color(ColorCode::FOREGROUND_BRIGHT_BLUE, text); }
    std::string FgBrightMagenta(std::string text) { return Color(ColorCode::FOREGROUND_BRIGHT_MAGENTA, text); }
    std::string FgBrightCyan(std::string text) { return Color(ColorCode::FOREGROUND_BRIGHT_CYAN, text); }
    std::string FgWhite(std::string text) { return Color(ColorCode::FOREGROUND_WHITE, text); }
    std::string BgBlack(std::string text) { return Color(ColorCode::BACKGROUND_BLACK, text); }
    std::string BgDarkRed(std::string text) { return Color(ColorCode::BACKGROUND_DARK_RED, text); }
    std::string BgDarkGreen(std::string text) { return Color(ColorCode::BACKGROUND_DARK_GREEN, text); }
    std::string BgDarkYellow(std::string text) { return Color(ColorCode::BACKGROUND_DARK_YELLOW, text); }
    std::string BgDarkBlue(std::string text) { return Color(ColorCode::BACKGROUND_DARK_BLUE, text); }
    std::string BgDarkMagenta(std::string text) { return Color(ColorCode::BACKGROUND_DARK_MAGENTA, text); }
    std::string BgDarkCyan(std::string text) { return Color(ColorCode::BACKGROUND_DARK_CYAN, text); }
    std::string BgDarkWhite(std::string text) { return Color(ColorCode::BACKGROUND_DARK_WHITE, text); }
    std::string BgBrightBlack(std::string text) { return Color(ColorCode::BACKGROUND_BRIGHT_BLACK, text); }
    std::string BgBrightRed(std::string text) { return Color(ColorCode::BACKGROUND_BRIGHT_RED, text); }
    std::string BgBrightGreen(std::string text) { return Color(ColorCode::BACKGROUND_BRIGHT_GREEN, text); }
    std::string BgBrightYellow(std::string text) { return Color(ColorCode::BACKGROUND_BRIGHT_YELLOW, text); }
    std::string BgBrightBlue(std::string text) { return Color(ColorCode::BACKGROUND_BRIGHT_BLUE, text); }
    std::string BgBrightMagenta(std::string text) { return Color(ColorCode::BACKGROUND_BRIGHT_MAGENTA, text); }
    std::string BgBrightCyan(std::string text) { return Color(ColorCode::BACKGROUND_BRIGHT_CYAN, text); }
    std::string BgWhite(std::string text) { return Color(ColorCode::BACKGROUND_WHITE, text); }
    std::string Bold(std::string text) { return Color(ColorCode::BOLD, text); }
    std::string Underline(std::string text) { return Color(ColorCode::UNDERLINE, text); }
    std::string NoUnderline(std::string text) { return Color(ColorCode::NO_UNDERLINE, text); }
    std::string ReverseText(std::string text) { return Color(ColorCode::REVERSE_TEXT, text); }
    std::string NotReversed(std::string text) { return Color(ColorCode::NOT_REVERSED, text); }


}
