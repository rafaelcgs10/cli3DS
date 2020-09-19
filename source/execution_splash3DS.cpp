#include "../include/cli3DS.h"
#include "../include/draw_utils.h"

ExecutionSplash::ExecutionSplash() {
}

ExecutionSplash::~ExecutionSplash() {
}

void ExecutionSplash::set_execution_function(void (*_execution)(void *arg)) {
    execution = _execution;
}

void ExecutionSplash::set_arg(void *_arg) {
    arg = _arg;
}

void ExecutionSplash::set_console(PrintConsole *_console) {
    console = _console;
}

void ExecutionSplash::set_execution_progress(int *_execution_progress) {
    execution_progress = _execution_progress;
}

void ExecutionSplash::start_execution() {
    execution(arg);
}

int ExecutionSplash::read_execution_progress() {
    return *execution_progress;
}

View *ExecutionSplash::manage_input() {
    return NULL;
}

void ExecutionSplash::draw() {
    draw_text_line(console, "oi", 20, 20, CONSOLE_CYAN);
}

bool ExecutionSplash::is_executable() {
    return false;
}

void ExecutionSplash::set_text(std::string _text) {
    text = _text;
}

void ExecutionSplash::set_title(std::string _title) {
    title = _title;
}

void ExecutionSplash::clear_text() {
    text.clear();
}

void ExecutionSplash::clear_title() {
    title.clear();
}

void ExecutionSplash::set_offset_y(int _offset_y) {
    offset_y = _offset_y;
}

void ExecutionSplash::set_height(int _height) {
    height = _height;
}
