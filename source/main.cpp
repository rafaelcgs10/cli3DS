#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <3ds.h>
#include "cli.h"

int main(int argc, char* argv[])
{
	gfxInitDefault();
	Cli my_cli(GFX_TOP);
	std::vector<std::string> options { "A thing", "Something", "Some other thing", "Quit" };
	my_cli.set_options(options);

	// Main loop
	while (aptMainLoop()){
		my_cli.run();
		gspWaitForVBlank();
		gfxSwapBuffers();
		hidScanInput();

		// Your code goes here
		u32 kDown = hidKeysDown();
		if (kDown & KEY_START)
			break; // break in order to return to hbmenu
	}

	gfxExit();
	return 0;
}
