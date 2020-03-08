#include "../include/cli3DS.h"

Cli::Cli(gfxScreen_t _screen) : screen(_screen){
    current_view = NULL;
}

void Cli::draw(){
    consoleClear();
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
    menu->set_screen(screen);
    menus.push_back(menu);
}


void Cli::set_text(string _text) {
    text = _text;
}

void Cli::set_title(string _title) {
    title = _title;
}

void Cli::clear_text() {
    text.clear();
}

void Cli::clear_title() {
    title.clear();
}
