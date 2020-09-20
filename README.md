CLI 3DS Library
===========

The goal of this library is to provide a quick and simple way to implement a basic CLI (Command-line interface) in your Nintendo 3DS homebrew application.

If you don't want to lose time implementing a GUI at the early stages of your project, this is for you.

## Build and install

1. Check that you have the usual 3DS dependencies: `devkitARM` and `libctru`.
2. Clone this repo: `git clone https://github.com/rafaelcgs10/cli3DS`.
3. Run: `cd cli3DS`
4. Run: `make`
5. Run: `sudo make install`. Since you run this command with `sudo`, then the environment variable `DEVKITPRO` must have been set system wide. This command will copy `include/cli3DS.h` to `$(DEVKITPRO)/libctru/include/` and `lib/libcli3DS.a` to `$(DEVKITPRO)/libctru/lib/`, plus it will `chmod 644` them. You could do this using your own hands though.

Look the example in the `example` folder to see how to use this library. Also, check the `README.md` file there too.

## TODO

- [x] Abstract options as a class.
- [x] Pagination for dealing with long lists of options.
- [x] Multiple menus navegation.
- [x] Options can be selectable.
- [x] Splash screen for processing selected options.
- [ ] Manage multiple screens.

Feel free to help me out with those tasks!
