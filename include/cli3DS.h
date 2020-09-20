#ifndef INCLUDE_CLI3DS_H_
#define INCLUDE_CLI3DS_H_

#include <3ds.h>
#include <string>
#include <vector>
#include <functional>
#include "definitions.h"

class View {
    public:
        virtual void set_console(PrintConsole *_console) = 0;
        virtual void draw() = 0;
        virtual View *manage_input() = 0;
        virtual bool is_executable() = 0;

    private:
        PrintConsole *console;
        std::string title;
        std::string text;
};

class Option {
    public:
        Option(std::string _text);
        void set_selectable();
        bool get_selectable();
        void toggle_selected();
        bool get_selected();
        void set_current_view(View *_view);
        void set_view_entry(View *_view_entry);
        std::string get_text();
        View *click();

    private:
        View *current_view;
        std::string text;
        bool selectable;
        bool selected;
        View *view_entry;
        void set_text(std::string _text);
        void set_title(std::string _title);
        void clear_text();
        void clear_title();
        void set_offset_y(int _offset_y);
        void set_height(int _height);
};

class Menu : public View {
    public:
        Menu();
        ~Menu();
        void set_options(std::vector<Option *> *_options);
        void set_console(PrintConsole *_console);
        View *manage_input();
        void draw();
        void set_text(std::string _text);
        void set_title(std::string _title);
        void clear_text();
        void clear_title();
        void set_offset_y(int _offset_y);
        void set_height(int _height);
        void set_previous_view(View *view);
        bool is_executable();
        std::vector<Option *> get_selected_options();

    private:
        View *previous_view;
        PrintConsole *console;
        std::vector<Option *> *options;
        std::vector<std::vector<Option *>> *options_pages;
        std::string title;
        std::string text;
        int offset_y;
        int height;
        int max_options_page;
        int number_pages;
        int current_option;
        void draw_option(Option *option, int pos_y, const char *color);
        void draw_options_page(int page_number, std::vector<Option *> *options_page,
                               int pos_y);
        std::vector<std::vector<Option *>> *paginate(std::vector<Option *> *_options);
};

class ExecutionSplash : public View {
    public:
        ExecutionSplash();
        ~ExecutionSplash();
        void set_console(PrintConsole *_console);
        void set_execution_function(void (*_execution)(void *arg));
        void set_text(std::string _text);
        void set_title(std::string _title);
        void clear_text();
        void clear_title();
        void set_previous_view(View *view);
        void set_offset_y(int _offset_y);
        void set_height(int _height);
        void set_execution_finished(bool *_execution_finished);
        void set_execution_log(std::string *_execution_log);
        void set_execution_progress(int *execution_progress);
        void set_arg(void *_arg);
        int read_execution_progress();
        void draw();
        void start_execution();
        View *manage_input();
        bool is_executable();
        void free_execution_thread();

    private:
        View *previous_view;
        PrintConsole *console;
        bool *execution_finished;
        std::string *execution_log;
        int *execution_progress;
        std::string title;
        std::string text;
        int offset_y;
        int height;
        void (*execution)(void *arg);
        void *arg;
	Thread execution_thread;
};

class Cli {
    public:
        Cli(gfxScreen_t _screen);
        PrintConsole *console;
        void push_back_menu(Menu *menu);
        void push_back_splash(ExecutionSplash *splash);
        void set_text(std::string _text);
        void set_title(std::string _title);
        void clear_title();
        void run();

    private:
        Menu *last_menu;
        std::vector<Menu *> menus;
        std::vector<ExecutionSplash *> splashes;
        View *current_view;
        std::string title;
        gfxScreen_t screen;
        void manage_events();
        void draw();
};

#endif // INCLUDE_CLI3DS_H_
