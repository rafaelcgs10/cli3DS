#ifndef INCLUDE_DRAW_UTILS_H_
#define INCLUDE_DRAW_UTILS_H_

#include <3ds.h>
#include <string>
#include <vector>
#include "definitions.h"

void draw_horizontal_bar(PrintConsole *console, int pos_y, const char *color);
void draw_horizontal_bar_with_text_at_end(PrintConsole *console, std::string text,
					  int pos_y, const char *color);
void draw_horizontal_bar_with_text_at_begin(PrintConsole *console, std::string text,
					    int pos_y, const char *color);
void draw_horizontal_bar_with_text_at_center(PrintConsole *console, std::string text,
					     int pos_y, const char *color);
void draw_horizontal_line(PrintConsole *console, int pos_y, const char *color);
void draw_horizontal_line_with_text_at_begin(PrintConsole *console, std::string text,
					     int pos_y, const char *color);
void draw_horizontal_line_with_text_at_end(PrintConsole *console, std::string text,
					   int pos_y, const char *color);
void draw_text_line(PrintConsole *console, std::string text, int pos_x, int pos_y,
		    const char* color);

#endif // INCLUDE_DRAW_UTILS_H_
