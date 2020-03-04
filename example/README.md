CLI Example
===========

## Build
1. Make sure that you have installed the cli3DS library.
2. Run: `make`
3. Execute the `.3dsx` file how you want to (in the homebrew app or in an emulator).

Notice the `-lcli3DS` flag in the `LIBS` variable in the `Makefile`. The order of those flags matter. You will need to add this flag to the `Makefile` of your project.
