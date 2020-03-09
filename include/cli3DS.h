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
	virtual bool is_executable() = 0;

    private:
	string title;
	string text;
};

class Option {
    public:
        Option(string _text);
	void set_selectable();
	void set_view_entry(View *_view_entry);
	string get_text();
	View *click();

    private:
        string text;
        bool selectable;
	bool selected;
	View *view_entry;
	void set_text(string _text);
	void set_title(string _title);
	void clear_text();
	void clear_title();
	void set_offset_y(int _offset_y);
	void set_height(int _height);
};

class Menu : public View {
    public:
	Menu();
	~Menu();
        void set_options(vector<Option *> *_options);
	void set_console(PrintConsole *_console);
        View *manage_input();
        void draw();
	void set_text(string _text);
	void set_title(string _title);
	void clear_text();
	void clear_title();
	void set_offset_y(int _offset_y);
	void set_height(int _height);
	bool is_executable();

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
};

class ExecutionSplash : public View {
    public:
	ExecutionSplash();
	void set_execution(void (*_execution)(void *arg));
	void set_text(string _text);
	void set_title(string _title);
	void clear_text();
	void clear_title();
	void set_offset_y(int _offset_y);
	void set_height(int _height);
	void set_execution_progress(int *execution_progress);
	void set_arg(void *_arg);
	int read_execution_progress();
        void draw();
	void start_execution();
        View *manage_input();
	bool is_executable();

    private:
	int *execution_progress;
	string title;
	string text;
	int offset_y;
	int height;
	void (*execution)(void *arg);
	void *arg;
};

class Cli {
    public:
        Cli(gfxScreen_t _screen);
        PrintConsole *console;
	void push_back_menu(Menu *menu);
	void set_text(string _text);
	void set_title(string _title);
	void clear_title();
        void run();
        
    private:
    vector<Menu *> menus;
	View *current_view;
	string title;
        gfxScreen_t screen;
        void manage_input();
        void draw();
};

#endif // INCLUDE_CLI3DS_H_
