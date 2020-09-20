#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <unistd.h>
#include <3ds.h>
#include <cli3DS.h>

typedef struct SomeData {
   int count;
   int progress;
   std::string log;
   Menu *menu;
   bool execution_finished;
} SomeData;

void compute_thing(void *_data) {
    SomeData *data = (SomeData*) _data;
    std::vector<Option *> options = data->menu->get_selected_options();

    for(Option *option : options) {
        data->log = "Processing " + option->get_text();
        for (int i = 0; i <= data->count; ++i) {
            data->progress = (int) 100 * (i / (float) data->count);
            sleep(1);
        }
    }
    data->execution_finished = true;
}

int main(int argc, char* argv[]){
    gfxInitDefault();
    Cli cli(GFX_TOP);
    cli.set_title("CLI TITLE");
    Menu first_menu;
    Menu second_menu;
    ExecutionSplash loading_screen;
    Option entry("Menu entry");

    entry.set_view_entry(&second_menu);

    std::vector<Option *> options1;
    options1.push_back(&entry);
    for (int i = 1; i <= 60; ++i) {
        Option *option_aux = new Option("Useless selectable option " + std::to_string(i));
        option_aux->set_selectable();
        options1.push_back(option_aux);
    }

    loading_screen.set_title("Loading");
    SomeData data;
    data.count = 3;
    data.execution_finished = false;
    data.progress = 0;
    data.menu = &first_menu;
    loading_screen.set_arg(&data);
    loading_screen.set_execution_progress(&data.progress);
    loading_screen.set_execution_log(&data.log);
    loading_screen.set_execution_finished(&data.execution_finished);
    loading_screen.set_execution_function(&compute_thing);

    std::vector<Option *> options2{ new Option("Useless option"), new Option("Loading screen") };
    options2[1]->set_view_entry(&loading_screen);

    first_menu.set_options(&options1);
    second_menu.set_options(&options2);

    cli.push_back_menu(&first_menu);
    cli.push_back_menu(&second_menu);
    cli.push_back_splash(&loading_screen);

    while (aptMainLoop()){
        gfxFlushBuffers();
        cli.run();
        gfxSwapBuffers();
        gspWaitForVBlank();
        hidScanInput();
        u32 kDown = hidKeysDown();
        if (kDown & KEY_START)
            break; // break in order to return to hbmenu
    }

    for(Option *option : options1) {
        delete option;
    }

    for(Option *option : options2) {
        delete option;
    }

    loading_screen.free_execution_thread();

    gfxExit();
    return 0;
}
