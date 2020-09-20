#include "../include/cli3DS.h"

Option::Option(std::string _text) : text(_text) {
    selectable = false;
    selected = false;
    view_entry = NULL;
}

std::string Option::get_text() {
    return text;
}

void Option::set_selectable() {
    view_entry = NULL;
    selectable = true;
}

bool Option::get_selectable() {
    return selectable;
}

void Option::toggle_selected() {
    if(selected)
        selected = false;
    else
        selected = true;
}

bool Option::get_selected() {
    return selected;
}

void Option::set_current_view(View *_view) {
    current_view = _view;
}

void Option::set_view_entry(View *_view_entry) {
    view_entry = _view_entry;
    selectable = false;
}

View *Option::click() {
    if(selectable) {
        selected = !selected;
    } else if(view_entry != NULL) {
        if(view_entry->is_executable()) {
            ((ExecutionSplash*) view_entry)->start_execution();
            ((ExecutionSplash*) view_entry)->set_previous_view(current_view);
        } else {
            ((Menu*) view_entry)->set_previous_view(current_view);
        }
        return view_entry;
    }
    return NULL;
}
