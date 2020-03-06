#ifndef _cli3DS_h_
#define _cli3DS_h_

#include <3ds.h>
#include <string>
#include <vector>

using namespace std;

#define CONSOLE_REVERSE		CONSOLE_ESC(7m)

class Cli{
public:
	Cli(gfxScreen_t _screen);
	void set_options(vector<string> _options);
	void run();
private:
	PrintConsole *console;
	gfxScreen_t screen;
	vector<string> options;
	vector<vector<string>> options_pages;
	int max_options_page;
	int current_option;
	void draw_string(const char* str, int pos_x, int pos_y, const char* color);
	void draw_options_page(int page_number, vector<string> options_page);
	vector<vector<string>> paginate(vector<string> _options);
	void draw();
	void manage_input();
};

#endif
