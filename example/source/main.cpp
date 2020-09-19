#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <unistd.h>
#include <3ds.h>
#include <cli3DS.h>

typedef struct Count {
   int count;
   int progress;
} Count;

void count_down(void *_count) {
    Count *count = (Count*) _count;
    for (int i = 0; i <= count->count; ++i) {
        count->progress = (int) 100 * (i / (float) count->count);
        sleep(1);
    }
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
        options1.push_back(new Option("Useless option " + std::to_string(i)));
    }

    loading_screen.set_title("Loading");
    loading_screen.set_execution_function(&count_down);
    Count count;
    count.count = 7;
    count.progress = 0;
    loading_screen.set_arg(&count);
    loading_screen.set_execution_progress(&count.progress);

    std::vector<Option *> options2{ new Option("Useless option"), new Option("Loading screen") };
    options2[1]->set_view_entry(&loading_screen);

    first_menu.set_options(&options1);
    second_menu.set_options(&options2);

    cli.push_back_menu(&first_menu);
    cli.push_back_menu(&second_menu);
    cli.push_back_splash(&loading_screen);

    while (aptMainLoop()){
        gspWaitForVBlank();
        gfxSwapBuffers();
        hidScanInput();

        cli.run();
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
