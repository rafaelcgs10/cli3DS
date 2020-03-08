#include "../include/cli3DS.h"
#include "../include/draw_utils.h"

using namespace std;

Menu::Menu() {
    current_option = 0;
    max_options_page = 20;
}

Menu::~Menu() {
    delete options_pages;
}

void Menu::set_screen(gfxScreen_t _screen) {
    console = consoleInit(_screen, NULL);
}

void Menu::set_options(vector<Option> *_options) {
    options = _options;
    options_pages = paginate(options);
    number_pages = options_pages->size();
}

void Menu::draw_options_page(int page_number, vector<Option> *options_page,
			     int pos_y) {
    const char *current_color;
    int current_print_option = 0;

    for (Option option : *options_page) {
        if(current_print_option == current_option % max_options_page)
            current_color = CONSOLE_REVERSE;
        else
            current_color = CONSOLE_WHITE;

        draw_text_line(console, option.get_text(), 0, current_print_option + pos_y,
		       current_color);
        current_print_option++;
    }
}

void Menu::draw() {
    int current_page = current_option / max_options_page;

    draw_horizontal_bar(console, 0, CONSOLE_WHITE);
    draw_options_page(current_page, &options_pages->at(current_page), 1);
    draw_horizontal_bar_with_text_at_end(console, to_string(current_page + 1) +
					 "/" + to_string(number_pages), 29,
					 CONSOLE_WHITE);
}

vector<vector<Option>> *Menu::paginate(vector<Option> *_options) {
    vector<vector<Option>> *_pages = new vector<vector<Option>>;
    int count_options_in_page = 0;
    vector<Option> *page = new vector<Option>;
    string last_option = _options->back().get_text();

    for (Option option : *_options) {
        page->push_back(option);
        count_options_in_page++;
        if(count_options_in_page >= max_options_page) {
            _pages->push_back(*page);
            count_options_in_page = 0;
            page = new vector<Option>;
        }
        else if(option.get_text() == last_option) {
            _pages->push_back(*page);
        }
    }
    return _pages;
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
    } else if (key & KEY_RIGHT) {
        current_option = last_option;
    } else if (key & KEY_LEFT) {
        current_option = 0;
    } else if (key & KEY_A) {
	return options->at(current_option).click();
    }
    return NULL;
}

void Menu::set_text(string _text) {
    text = _text;
}

void Menu::set_title(string _title) {
    title = _title;
}

void Menu::clear_text() {
    text.clear();
}

void Menu::clear_title() {
    title.clear();
}
