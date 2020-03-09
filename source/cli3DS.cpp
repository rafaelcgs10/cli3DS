#include "../include/cli3DS.h"
#include "../include/draw_utils.h"

Cli::Cli(gfxScreen_t _screen) : screen(_screen){
    console = consoleInit(_screen, NULL);
    current_view = NULL;
}

void Cli::draw(){
    consoleClear();
    draw_horizontal_bar_with_text_at_center(console, title, 0, CONSOLE_WHITE);
    current_view->draw();
    gfxFlushBuffers();
}

void Cli::manage_input() {
    View *view = current_view->manage_input();
    if(view != NULL) {
	current_view = view;
    }
}

void Cli::run(){
    manage_input();
    draw();
}

void Cli::push_back_menu(Menu *menu) {
    if(menus.size() == 0)
	current_view = menu;
    menu->set_console(console);
    menus.push_back(menu);
}


void Cli::set_title(string _title) {
    title = _title;
}

void Cli::clear_title() {
    title.clear();
}
