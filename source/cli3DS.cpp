#include "../include/cli3DS.h"
#include <string>
#include <vector>

Cli::Cli(gfxScreen_t _screen) : screen(_screen){
	console = consoleInit(_screen, NULL);
	current_option = 0;
}

void Cli::draw_string(const char* str, int pos_x, int pos_y, const char* color){
    console->cursorX = pos_x;
    console->cursorY = pos_y;
    printf("%s%s%s", color, str, CONSOLE_RESET);

    gfxFlushBuffers();
}

void Cli::set_options(std::vector<std::string> _options){
	options = _options;
}

void Cli::draw(){
	consoleClear();
	const char *current_color;
	int current_print_option = 0;

	for (std::string option : options) {
		if(current_print_option == current_option)
			current_color = CONSOLE_REVERSE;
		else
			current_color = CONSOLE_WHITE;

		draw_string(option.c_str(), 0, current_print_option, current_color);
		current_print_option++;
	}
}

void Cli::manage_input(){
	u32 key = hidKeysDown();
	int number_options = options.size();
    int last_option = number_options - 1;
	
    if (key & KEY_UP) {
        if (current_option <= 0) {
            current_option = last_option;
        } else {
            current_option--;
        }
    } else if (key & KEY_DOWN) {
        if (current_option >= last_option) {
            current_option = 0;
        } else {
            current_option++;
        }
    } else if (key & KEY_RIGHT) {
        current_option = last_option;
    } else if (key & KEY_LEFT) {
        current_option = 0;
    }
}

void Cli::run(){
	draw();
	manage_input();
}
	
