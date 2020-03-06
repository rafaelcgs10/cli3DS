#ifndef INCLUDE_CLI3DS_H_
#define INCLUDE_CLI3DS_H_

#include <3ds.h>
#include <string>
#include <vector>

using namespace std;

#define CONSOLE_REVERSE CONSOLE_ESC(7m)

class Cli;

class Option {
    public:
        Option(string _text);
	void set_call_back(void *_call_back);
	void set_selectable();
	void set_cli_entry(Cli *_cli_entry);
	string get_text();
    private:
        string text;
        bool selectable;
	void *call_back;
	Cli *cli_entry;
};

class Cli {
    public:
        Cli(gfxScreen_t _screen);
        void set_options(vector<Option> _options);
        void run();
        
    private:
        PrintConsole *console;
        gfxScreen_t screen;
	vector<Option> options;
        vector<vector<Option>> options_pages;
        int max_options_page;
        int current_option;
        void draw_string(const char *str, int pos_x, int pos_y, const char *color);
        void draw_options_page(int page_number, vector<Option> options_page);
        vector<vector<Option>> paginate(vector<Option> _options);
        void draw();
        void manage_input();
};

#endif // INCLUDE_CLI3DS_H_
