#include "../include/cli3DS.h"

Option::Option(std::string _text) : text(_text) {
    selectable = false;
    view_entry = NULL;
}

std::string Option::get_text() {
    return text;
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
            // ((ExecutionSplash*) view_entry)->start_execution();
        }
        return view_entry;
    }
    return NULL;
}
