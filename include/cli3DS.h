#ifndef INCLUDE_CLI3DS_H_
#define INCLUDE_CLI3DS_H_

#include <3ds.h>
#include <string>
#include <vector>

using namespace std;

#define CONSOLE_REVERSE CONSOLE_ESC(7m)

class View {
  public:
    virtual void set_screen(gfxScreen_t _screen) = 0;
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
        void set_options(vector<Option> *_options);
	void set_screen(gfxScreen_t _screen);
        View *manage_input();

    private:
        PrintConsole *console;
	vector<Option> *options;
        vector<vector<Option>> *options_pages;
        int max_options_page;
        int current_option;
        void draw_string(const char *str, int pos_x, int pos_y, const char *color);
        void draw_options_page(int page_number, vector<Option> *options_page);
        vector<vector<Option>> *paginate(vector<Option> *_options);
        void draw();
};

class Splash : public View {
};

class Cli {
    public:
        Cli(gfxScreen_t _screen);
	void push_back_menu(Menu *menu);
        void run();
        
    private:
    vector<Menu *> menus;
	View *current_view;
        gfxScreen_t screen;
        void draw();
        void manage_input();
};

#endif // INCLUDE_CLI3DS_H_
