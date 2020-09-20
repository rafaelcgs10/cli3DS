#include "../include/cli3DS.h"
#include "../include/draw_utils.h"
#include <3ds/console.h>

Cli::Cli(gfxScreen_t _screen) : screen(_screen){
    console = consoleInit(_screen, NULL);
    current_view = NULL;
}

void Cli::draw(){
    draw_horizontal_bar_with_text_at_center(console, title, 0, CONSOLE_WHITE);
    current_view->draw();
}

void Cli::manage_events() {
    View *view = current_view->manage_input();
    if(view != NULL) {
        consoleClear();
        current_view = view;
    }
}

void Cli::run(){
    manage_events();
    draw();
}

void Cli::push_back_menu(Menu *menu) {
    if(menus.size() == 0)
        current_view = (View *) menu;
    menu->set_console(console);
    menus.push_back(menu);
}

void Cli::push_back_splash(ExecutionSplash *splash) {
    splash->set_console(console);
    splashes.push_back(splash);
}

void Cli::set_title(std::string _title) {
    title = _title;
}

void Cli::clear_title() {
    title.clear();
}
