#include "../include/draw_utils.h"

void draw_horizontal_bar(PrintConsole *console, int pos_y, const char *color) {
    console->cursorX = 0;
    console->cursorY = pos_y;
    printf("%s%s", color, CONSOLE_REVERSE);
    printf("%-50s", "");
    printf(CONSOLE_RESET);
}

void draw_horizontal_bar_with_text_at_end(PrintConsole *console, std::string text,
                                          int pos_y, const char *color) {
    console->cursorX = 0;
    console->cursorY = pos_y;
    int len = text.length();
    int padlen = 50 - len;

    printf("%s%s", color, CONSOLE_REVERSE);
    printf("%*s%s",  padlen, "", text.c_str());
    printf(CONSOLE_RESET);
}

void draw_horizontal_bar_with_text_at_begin(PrintConsole *console, std::string text,
                                            int pos_y, const char *color) {
    console->cursorX = 0;
    console->cursorY = pos_y;
    int len = text.length();
    int padlen = 50 - len;

    printf("%s%s", color, CONSOLE_REVERSE);
    printf("%s%*s", text.c_str(), padlen, "");
    printf(CONSOLE_RESET);
}

void draw_horizontal_bar_with_text_at_center(PrintConsole *console, std::string text,
                                             int pos_y, const char *color) {
    console->cursorX = 0;
    console->cursorY = pos_y;
    int len = text.length();
    int padlen = (50 - len) / 2;
    int padlen2 = 50 - padlen - len;

    printf("%s%s", color, CONSOLE_REVERSE);
    printf("%*s%s%*s", padlen, "", text.c_str(), padlen2, "");
    printf(CONSOLE_RESET);
}

void draw_horizontal_line(PrintConsole *console, int pos_y, const char *color) {
    console->cursorX = 0;
    console->cursorY = pos_y;
    for (int i = 0; i < 50; ++i) {
        printf("%s-", color);
    }
    printf(CONSOLE_RESET);
}

void draw_horizontal_line_with_text_at_begin(PrintConsole *console, std::string text,
                                             int pos_y, const char *color) {
    console->cursorX = 0;
    console->cursorY = pos_y;
    int len = text.length();
    printf("%s%s", color, text.c_str());
    for (int i = 0; i < 50 - len; ++i) {
        printf("%s-", color);
    }
    printf(CONSOLE_RESET);
}

void draw_horizontal_line_with_text_at_end(PrintConsole *console, std::string text,
                                           int pos_y, const char *color) {
    console->cursorX = 0;
    console->cursorY = pos_y;
    int len = text.length();
    for (int i = 0; i < 50 - len; ++i) {
        printf("%s-", color);
    }
    printf("%s%s", color, text.c_str());
    printf(CONSOLE_RESET);
}

void draw_text_line(PrintConsole *console, std::string text, int pos_x, int pos_y,
                    const char* color) {
    console->cursorX = pos_x;
    console->cursorY = pos_y;
    printf("%s%s%s", color, text.c_str(), CONSOLE_RESET);
}
