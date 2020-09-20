#include "../include/cli3DS.h"
#include "../include/draw_utils.h"
#include <vector>

Menu::Menu() {
    current_option = 0;
    height = 27;
    max_options_page = height;
    offset_y = 2;
    previous_view = NULL;
}

Menu::~Menu() {
    delete options_pages;
}

void Menu::set_console(PrintConsole *_console) {
    console = _console;
}

void Menu::set_options(std::vector<Option *> *_options) {
    options = _options;
    for(Option *option : *options) {
        option->set_current_view(this);
    }
    options_pages = paginate(options);
    number_pages = options_pages->size();
}

void Menu::draw_options_page(int page_number, std::vector<Option *> *options_page, int pos_y) {
    const char *current_color;
    int current_print_option = 0;

    for (Option *option : *options_page) {
        if(current_print_option == current_option % max_options_page)
            current_color = CONSOLE_REVERSE;
        else
            current_color = CONSOLE_WHITE;

        draw_option(option, current_print_option + pos_y, current_color);
        current_print_option++;
    }
}

std::vector<Option *> Menu::get_selected_options() {
    std::vector<Option *> seleted_options;
    for(Option *option : *options) {
        if(option->get_selected()) {
            seleted_options.push_back(option);
        }
    }
    return seleted_options;
}

void Menu::draw_option(Option *option, int pos_y, const char *color) {
    draw_text_line(console, option->get_text(), 0, pos_y, color);
    if(option->get_selectable()) {
        if(option->get_selected())
            draw_text_line(console, "(X)", 47, pos_y, color);
        else
            draw_text_line(console, "( )", 47, pos_y, color);
    }
}

void Menu::draw() {
    int current_page = current_option / max_options_page;

    draw_options_page(current_page, &options_pages->at(current_page), offset_y);
    draw_horizontal_bar_with_text_at_end(console, std::to_string(current_page + 1) +
                                         "/" + std::to_string(number_pages),
                                         offset_y + height, CONSOLE_WHITE);
}

std::vector<std::vector<Option *>> *Menu::paginate(std::vector<Option *> *_options) {
    std::vector<std::vector<Option *>> *_pages = new std::vector<std::vector<Option *>>;
    int count_options_in_page = 0;
    std::vector<Option *> *page = new std::vector<Option *>;
    Option *last_option = _options->back();

    for (Option *option : *_options) {
        page->push_back(option);
        count_options_in_page++;
        if(count_options_in_page >= max_options_page) {
            _pages->push_back(*page);
            count_options_in_page = 0;
            page = new std::vector<Option *>;
        }
        else if(option == last_option) {
            _pages->push_back(*page);
        }
    }
    return _pages;
}

bool Menu::is_executable() {
    return false;
}

void Menu::set_previous_view(View *view) {
    previous_view = view;
}

View *Menu::manage_input() {
    u32 key = hidKeysDown();
    int number_options = options->size();
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
    } else if (key & KEY_B) {
        return previous_view;
    } else if (key & KEY_RIGHT) {
        current_option = last_option;
    } else if (key & KEY_LEFT) {
        current_option = 0;
    } else if (key & KEY_A) {
        if(options->at(current_option)->get_selectable()) {
            options->at(current_option)->toggle_selected();
            return NULL;
        } else {
            return options->at(current_option)->click();
        }
    }
    return NULL;
}

void Menu::set_text(std::string _text) {
    text = _text;
}

void Menu::set_title(std::string _title) {
    title = _title;
}

void Menu::clear_text() {
    text.clear();
}

void Menu::clear_title() {
    title.clear();
}

void Menu::set_offset_y(int _offset_y) {
    offset_y = _offset_y;
}

void Menu::set_height(int _height) {
    height = _height;
}
