#ifndef CLI_H
#define CLI_H

#include <3ds.h>
#include <string>
#include <vector>

#define CONSOLE_REVERSE		CONSOLE_ESC(7m)

class Cli {
public:
	Cli(gfxScreen_t _screen);
	void set_options(std::vector<std::string> _options);
	void run();
private:
	PrintConsole *console;
	gfxScreen_t screen;
	std::vector<std::string> options;
	int current_option;
	void draw_string(const char* str, int pos_x, int pos_y, const char* color);
	void draw();
	void manage_input();
};

#endif
