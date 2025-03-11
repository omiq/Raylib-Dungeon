#include <raylib.h>
#include "notconio.h"
#include "../display/display.h"
#include <string.h>
#include "../include/globals.h"
#include "../logic/game_logic.h"

// Forward declaration
void update_fov(int player_x, int player_y, int radius);

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
    int titleSize = 30;
    DrawText(output, (SCREEN_WIDTH - MeasureText(output, titleSize)) / 2, 500, titleSize, WHITE);
}

void draw_screen(void) {
    // Draw whole screen
    int row, col;
    //draw_whole_screen = true;
    //screen_drawn = false;
    if (draw_whole_screen && screen_drawn == false) {
        for (row = 0; row < PLAYABLE_HEIGHT; row++) {
            for (col = 0; col < MAZE_WIDTH; col++) {
                cputcxy(col, row, get_map(col, row));
            }
        }
        screen_drawn = true;
        printf("drawing whole screen");
    } else {
        // Update the screen around the player with a set radius 
        update_fov(player_x, player_y, 2);
        //printf("updating fov");
    }
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
    // Draw player
    set_map(old_x, old_y,'.');
    cputcxy(old_x, old_y, ' ');
    cputcxy(player_x, player_y, '@');
}


void update_fov(int player_x, int player_y, int radius) {
    int dy, dx;
    for (dy = -radius; dy <= radius; dy++) {
        for (dx = -radius; dx <= radius; dx++) {
            int x = player_x + dx;
            int y = player_y + dy;

            // Ensure coordinates are within the map bounds
            if (x >= 0 && x < MAP_WIDTH-3 && y >= 0 && y < PLAYABLE_HEIGHT) {
                c = get_map(x, y);
                if (c == ' ') c = '.';
                cputcxy(x, y, c);
            }
        }
    }
} 


