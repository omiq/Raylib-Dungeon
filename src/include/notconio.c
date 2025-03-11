#include <raylib.h>
#include "notconio.h"
#include "../display/raylib_display.h"
#include <string.h>

// Dummy variable to satisfy ncurses references
void* stdscr = NULL;

// Text mode compatibility functions
void clrscr(void) {
    clear_screen();
}

void cputsxy(unsigned int x, unsigned int y, const char* str) {
    draw_string(x, y, str);
}

void cputcxy(unsigned int x, unsigned int y, char c) {
    draw_char(x, y, c);
}

void gotoxy(unsigned int x, unsigned int y) {
    // No-op in Raylib version
    (void)x;
    (void)y;
}

void cursor(int show) {
    // No-op in Raylib version
    (void)show;
}

void refresh(void) {
    // No-op in Raylib version - screen updates are handled by BeginDrawing/EndDrawing
}

void echo(void) {
    // No-op in Raylib version
}

void noecho(void) {
    // No-op in Raylib version
}

void nodelay(void* win, int val) {
    // No-op in Raylib version
    (void)win;
    (void)val;
}

void ungetch(int ch) {
    // No-op in Raylib version
    (void)ch;
}

int wgetch(void* win) {
    // No-op in Raylib version
    (void)win;
    return 0;
}

void wrefresh(void* win) {
    // No-op in Raylib version
    (void)win;
}

int cgetc(void) {
    // TODO: Implement proper key input using Raylib
    if (IsKeyPressed(KEY_ESCAPE)) return 27;
    if (IsKeyPressed(KEY_UP)) return 'w';
    if (IsKeyPressed(KEY_DOWN)) return 's';
    if (IsKeyPressed(KEY_LEFT)) return 'a';
    if (IsKeyPressed(KEY_RIGHT)) return 'd';
    if (IsKeyPressed(KEY_SPACE)) return ' ';
    if (IsKeyPressed(KEY_ENTER)) return '\n';
    return 0;
}

// Display functions
void output_message(void) {
    // TODO: Implement message display using Raylib
}

void draw_screen(void) {
    // No-op in Raylib version - screen updates are handled by BeginDrawing/EndDrawing
}

void draw_momentary_object(unsigned int obj_old_x, unsigned int obj_old_y,
                          unsigned int obj_x, unsigned int obj_y,
                          unsigned int obj_tile, unsigned int delay) {
    // Draw at new position
    (void)obj_old_x;
    (void)obj_old_y;
    (void)delay;
    cputcxy(obj_x, obj_y, (char)obj_tile);
}

void draw_move(bool replace) {
    // No-op in Raylib version - movement is handled by draw_momentary_object
    (void)replace;
}

void translate_cputcxy(int col, int row, char c) {
    cputcxy(col, row, c);
} 