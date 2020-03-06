#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <3ds.h>
#include <cli3DS.h>

int main(int argc, char* argv[]){
	gfxInitDefault();
	Cli my_cli(GFX_TOP);
	std::vector<std::string> options { "A thing", "Something", "Some other thing",
									   "One more thing", "More more more!", "Quit" };
	my_cli.set_options(options);

	// Main loop
	while (aptMainLoop()){
		gspWaitForVBlank();
		gfxSwapBuffers();
		hidScanInput();

		// Your code goes here
		my_cli.run();
		u32 kDown = hidKeysDown();
		if (kDown & KEY_START)
			break; // break in order to return to hbmenu
	}

	gfxExit();
	return 0;
}
