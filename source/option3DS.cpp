#include "../include/cli3DS.h"
#include <string>
#include <vector>

Option::Option(string _text) : text(_text) {
}

string Option::get_text() {
    return text;
}
