#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <3ds.h>
#include <cli3DS.h>

int main(int argc, char* argv[]){
    gfxInitDefault();
    Cli cli(GFX_TOP);
    cli.set_title("CLI TITLE");
    cli.set_text("CLI TEXT CLI TEXT CLI TEXT CLI TEXT CLI TEXT");
    Menu first_menu;
    Menu second_menu;
    Option entry("Menu entry");

    entry.set_view_entry(&second_menu);

    std::vector<Option> options1 { entry, Option("Option 2"),
                                  Option("Option 3"), Option("Option 4"),
                                  Option("Option 5"), Option("Option 6") };
    std::vector<Option> options2{Option("Option 7"), Option("Option 8")};

    first_menu.set_options(&options1);
    second_menu.set_options(&options2);
    cli.push_back_menu(&first_menu);
    cli.push_back_menu(&second_menu);

    while (aptMainLoop()){
        gspWaitForVBlank();
        gfxSwapBuffers();
        hidScanInput();

        cli.run();
        u32 kDown = hidKeysDown();
        if (kDown & KEY_START)
            break; // break in order to return to hbmenu
    }

    gfxExit();
    return 0;
}
