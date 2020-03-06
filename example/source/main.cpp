#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <3ds.h>
#include <cli3DS.h>

int main(int argc, char* argv[]){
    gfxInitDefault();
    Cli my_cli(GFX_TOP);
    std::vector<Option> options { Option("Option 1"), Option("Option 2"),
                                  Option("Option 3"), Option("Option 4"),
                                  Option("Option 5"), Option("Option 6") };
    my_cli.set_options(options);

    while (aptMainLoop()){
        gspWaitForVBlank();
        gfxSwapBuffers();
        hidScanInput();

        my_cli.run();
        u32 kDown = hidKeysDown();
        if (kDown & KEY_START)
            break; // break in order to return to hbmenu
    }

    gfxExit();
    return 0;
}
