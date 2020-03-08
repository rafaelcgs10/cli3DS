#ifndef INCLUDE_CLI3DS_H_
#define INCLUDE_CLI3DS_H_

#include <3ds.h>
#include <string>
#include <vector>
#include "definitions.h"

using namespace std;

class View {
  public:
    virtual void set_console(PrintConsole *_console) = 0;
    virtual void draw() = 0;
    virtual View *manage_input() = 0;
};

class Option {
    public:
        Option(string _text);
	void set_call_back(void *_call_back);
	void set_selectable();
	void set_view_entry(View *_view_entry);
	string get_text();
	View * click();

    private:
        string text;
        bool selectable;
	bool selected;
	void (*call_back)(void);
        View *manage_input();
	View *view_entry;
};

class Menu : public View {
    public:
	Menu();
	~Menu();
        void set_options(vector<Option *> *_options);
	void set_console(PrintConsole *_console);
        View *manage_input();
	void set_text(string _text);
	void set_title(string _title);
	void clear_text();
	void clear_title();
	void set_offset_y(int _offset_y);
	void set_height(int _height);

    private:
        PrintConsole *console;
	vector<Option *> *options;
        vector<vector<Option *>> *options_pages;
	string title;
	string text;
	int offset_y;
	int height;
        int max_options_page;
        int number_pages;
        int current_option;
	void draw_options_page(int page_number, vector<Option *> *options_page,
			       int pos_y);
        vector<vector<Option *>> *paginate(vector<Option *> *_options);
        void draw();
};

class Splash : public View {
};

class Cli {
    public:
        Cli(gfxScreen_t _screen);
        PrintConsole *console;
	void push_back_menu(Menu *menu);
	void set_text(string _text);
	void set_title(string _title);
	void clear_text();
	void clear_title();
        void run();
        
    private:
    vector<Menu *> menus;
	View *current_view;
	string title;
	string text;
        gfxScreen_t screen;
        void draw();
        void manage_input();
};

#endif // INCLUDE_CLI3DS_H_
