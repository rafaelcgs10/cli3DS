#include "../include/cli3DS.h"
#include "../include/draw_utils.h"
#include <3ds/console.h>
#include <3ds/thread.h>

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

void ExecutionSplash::free_execution_thread() {
    threadJoin(execution_thread, U64_MAX);
    threadFree(execution_thread);
}

void ExecutionSplash::set_console(PrintConsole *_console) {
    console = _console;
}

void ExecutionSplash::set_execution_finished(bool *_execution_finished) {
    execution_finished = _execution_finished;
}

void ExecutionSplash::set_execution_log(std::string *_execution_log) {
    execution_log = _execution_log;
}

void ExecutionSplash::set_execution_progress(int *_execution_progress) {
    execution_progress = _execution_progress;
}

void ExecutionSplash::start_execution() {
	s32 prio = 0;
	svcGetThreadPriority(&prio, CUR_THREAD_HANDLE);
    execution_thread = threadCreate(execution, arg, STACKSIZE, prio-1, -2, false);
}

int ExecutionSplash::read_execution_progress() {
    return *execution_progress;
}

void ExecutionSplash::set_previous_view(View *view) {
    previous_view = view;
}

View *ExecutionSplash::manage_input() {
    u32 key = hidKeysDown();
    if(*execution_finished) {
        if (key & KEY_B) {
            return previous_view;
        }
    }
    return NULL;
}

void ExecutionSplash::draw() {
    if(*execution_finished) {
        free_execution_thread();
        draw_text_line(console, "Operation finished", 16, 14, CONSOLE_WHITE);
        draw_text_line(console, "Press B to return", 16, 20, CONSOLE_WHITE);
    } else {
        draw_text_line(console, "Progress: " + std::to_string(*execution_progress) + "%", 16, 14, CONSOLE_WHITE);
        draw_text_line(console, *execution_log, 0, 20, CONSOLE_WHITE);
    }
}

bool ExecutionSplash::is_executable() {
    return true;
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
