#include "notconio.h"
#include "globals.h"
#include "raylib.h"

void cputcxy_dark(int x, int y, unsigned char c);
void update_fov(int player_x, int player_y, int radius);

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
    BeginDrawing();
    DrawText(output, (SCREEN_WIDTH - MeasureText(output, titleSize)) / 2, 500, titleSize, WHITE);
    EndDrawing();
    
    WaitTime(.5);
    
    BeginDrawing();
    DrawText(output, (SCREEN_WIDTH - MeasureText(output, titleSize)) / 2, 500, titleSize, BLACK);
    EndDrawing();
    
    output[1] = '\0';
}

void draw_screen(void) {
    // Draw whole screen
    int row, col;

//    draw_move(false);

    if (draw_whole_screen && screen_drawn == false) {
        for (row = 0; row < PLAYABLE_HEIGHT; row++) {
            for (col = 0; col < MAZE_WIDTH; col++) {
                cputcxy(col, row, get_map(col, row));
                visibility_map[MAP_WIDTH * row + col] = true;
            }
        }
        screen_drawn = true;
        printf("drawing whole screen");
    } else {
        // Update the screen around the player with a set radius 
        update_fov(player_x, player_y, 2);
        //printf("updating fov");
    }

    cputcxy(old_x, old_y, ' ');
    set_map(old_x, old_y, '.');
    cputcxy(player_x, player_y, '@');
        

}

void draw_momentary_object(unsigned int obj_old_x, unsigned int obj_old_y, 
                          unsigned int obj_x, unsigned int obj_y, 
                          unsigned int obj_tile, int delay) {
    // Replace tile
    cputcxy(obj_old_x, obj_old_y, get_map(obj_old_x, obj_old_y));

    // Draw tile in new location
    cputcxy(obj_x, obj_y, obj_tile); 
   
    // Delay
    timer = dumb_wait(delay*40);

    // Replace tile again
    cputcxy(obj_x, obj_y, get_map(obj_x, obj_y));
}


void update_fov(int player_x, int player_y, int radius) {
    for (int y = player_y - radius; y <= player_y + radius; y++) {
        for (int x = player_x - radius; x <= player_x + radius; x++) {
            // Check if coordinates are within map bounds
            if (y >= 0 && y < PLAYABLE_HEIGHT && x >= 0 && x < MAP_WIDTH) {
                // Mark tile as visible
                visibility_map[MAP_WIDTH * y + x] = true;
                
                // Draw the current FOV with full brightness
                unsigned char tile = get_map(x, y);
                if (tile != 0) {
                    cputcxy(x, y, tile);
                }
            }
        }
    }
    
    // Draw previously revealed tiles outside FOV in darker color
    for (int y = 0; y < PLAYABLE_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            // Skip tiles in current FOV
            if (abs(x - player_x) <= radius && abs(y - player_y) <= radius) {
                continue;
            }
            
            // If tile was previously revealed but not in current FOV
            if (visibility_map[MAP_WIDTH * y + x]) {
                unsigned char tile = get_map(x, y);
                if (tile != 0) {
                    cputcxy_dark(x, y, tile);
                }
            }
        }
    }
} 

void cputcxy_dark(int x, int y, unsigned char c) {
    if (c == ' ') c = '.';
    Color darkColor = {128, 128, 128, 255};  // Gray color for revealed but not in FOV
    if (textures[c].id != 0) {
        DrawTexture(textures[c], x * TILE_SIZE, y * TILE_SIZE, darkColor);
    } else if (c == '.') {
        DrawTexture(textures['.'], x * TILE_SIZE, y * TILE_SIZE, darkColor);
    }
}


