#include "../include/cli3DS.h"

Cli::Cli(gfxScreen_t _screen) : screen(_screen){
    current_view = NULL;
}

void Cli::draw(){
    current_view->draw();
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
