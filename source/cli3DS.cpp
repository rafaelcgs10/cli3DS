#include "../include/cli3DS.h"
#include <string>
#include <vector>

using namespace std;

Cli::Cli(gfxScreen_t _screen) : screen(_screen){
    console = consoleInit(_screen, NULL);
    current_option = 0;
    max_options_page = 5;
}

void Cli::draw_string(const char* str, int pos_x, int pos_y, const char* color){
    console->cursorX = pos_x;
    console->cursorY = pos_y;
    printf("%s%s%s", color, str, CONSOLE_RESET);

    gfxFlushBuffers();
}

void Cli::set_options(vector<string> _options){
    options = _options;
    options_pages = paginate(options);
}

void Cli::draw_options_page(int page_number, vector<string> options_page){
    consoleClear();
    const char *current_color;
    int current_print_option = 0;

    for (string option : options_page) {
        if(current_print_option == current_option % max_options_page)
            current_color = CONSOLE_REVERSE;
        else
            current_color = CONSOLE_WHITE;

        draw_string(option.c_str(), 0, current_print_option, current_color);
        current_print_option++;
    }
}

vector<vector<string>> Cli::paginate(vector<string> _options){
    vector<vector<string>> _pages;
    int count_options_in_page = 0;
    vector<string> *page = new vector<string>;

    for (string option : _options) {
        page->push_back(option);
        count_options_in_page++;
        if(count_options_in_page >= max_options_page) {
            _pages.push_back(*page);
            count_options_in_page = 0;
            page = new vector<string>;
        }
        else if(option == _options.back()) {
            _pages.push_back(*page);
        }
    }
    return _pages;
}

void Cli::draw(){
    int current_page = current_option / max_options_page;
    draw_options_page(current_page, options_pages.at(current_page));
}

void Cli::manage_input(){
    u32 key = hidKeysDown();
    int number_options = options.size();
    int last_option = number_options - 1;
    
    if (key & KEY_UP) {
        if (current_option <= 0) {
            current_option = last_option;
        } else {
            current_option--;
        }
    } else if (key & KEY_DOWN) {
        if (current_option >= last_option) {
            current_option = 0;
        } else {
            current_option++;
        }
    } else if (key & KEY_RIGHT) {
        current_option = last_option;
    } else if (key & KEY_LEFT) {
        current_option = 0;
    }
}

void Cli::run(){
    draw();
    manage_input();
}
