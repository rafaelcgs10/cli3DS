#include "../include/cli3DS.h"

Option::Option(string _text) : text(_text) {
    selectable = false;
    call_back = NULL;
    view_entry = NULL;
}

string Option::get_text() {
    return text;
}

void Option::set_view_entry(View *_view_entry) {
    view_entry = _view_entry;
    call_back = NULL;
    selectable = false;
}

View *Option::click() {
    if(selectable) {
	selected = !selected;
    } else if(call_back != NULL) {
	call_back();
    } else if(view_entry != NULL) {
	return view_entry;
    }
    return NULL;
}

