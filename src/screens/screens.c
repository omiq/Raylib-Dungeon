#include "screens.h"
#include "../include/globals.h"
#include "../include/maze.h"
#include "../input/input.h"
#include "../logic/game_logic.h"
#include "../display/raylib_display.h"
#include <raylib.h>
#include "../include/notconio.h"
#include <string.h>

unsigned char show_titles;

unsigned char logo[] = {
    46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46,
    35, 35, 35, 35, 46, 46, 35, 46, 46, 35, 46, 35, 46, 46, 46, 35, 46, 46, 35, 35, 35, 35, 46, 46, 35, 35, 35, 35, 46, 46, 35, 35, 35, 46, 46, 35, 46, 46, 46, 35,
    46, 35, 46, 46, 35, 46, 35, 46, 46, 35, 46, 35, 35, 46, 46, 35, 46, 35, 46, 46, 46, 46, 35, 46, 35, 46, 46, 46, 46, 35, 46, 46, 46, 35, 46, 35, 35, 46, 46, 35,
    46, 35, 46, 46, 35, 46, 35, 46, 46, 35, 46, 35, 46, 35, 46, 35, 46, 35, 46, 46, 46, 46, 46, 46, 35, 35, 46, 46, 46, 35, 46, 46, 46, 35, 46, 35, 46, 35, 46, 35,
    46, 35, 46, 46, 35, 46, 35, 46, 46, 35, 46, 35, 46, 46, 35, 35, 46, 35, 46, 35, 35, 35, 35, 46, 35, 46, 46, 46, 46, 35, 46, 46, 46, 35, 46, 35, 46, 46, 35, 35,
    46, 35, 46, 46, 35, 46, 35, 46, 46, 35, 46, 35, 46, 46, 46, 35, 46, 35, 46, 46, 46, 46, 35, 46, 35, 46, 46, 46, 46, 35, 46, 46, 46, 35, 46, 35, 46, 46, 46, 35,
    35, 35, 35, 35, 46, 46, 46, 35, 35, 46, 46, 35, 46, 46, 46, 35, 46, 46, 35, 35, 35, 35, 46, 46, 35, 35, 35, 35, 46, 46, 35, 35, 35, 46, 46, 35, 46, 46, 46, 35,
    46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46
};

void center_text(unsigned char row, char *text) {
    sprintf(output, "%s", text);
    cputsxy((40-strlen(text))/2, row, output);
    refresh();
}

void display_titles(void) {
    // Show the word DUNGEON using the custom character set
    char line[41];  // 40 chars plus null terminator
    int row;
    
    // Output the logo line by line
    for (row = 0; row < 8; row++) {
        // Copy 40 characters from the logo array into our line buffer
        memcpy(line, &logo[row * 40], 40);
        line[40] = '\0';  // Null terminate the string
        
        // Draw each character in the line
        for (int col = 0; col < 40; col++) {
            if (line[col] == 35) { // '#' character
                cputcxy(col, row, '#');
            } else {
                cputcxy(col, row, '.');
            }
        }
    }

    sprintf(output, "The Dungeon");
    center_text(10, output);
    center_text(15, "a game by retrogamecoders.com");
    center_text(20, "press a key");
}

void display_instructions(void) {
    center_text(6, "instructions");
    center_text(12, "use the wasd keys to move");
    center_text(14, "collect the treasure");
    center_text(16, "avoid the monsters");
    center_text(20, "press a key to start");
}

// This is the default title screen
int title_screen(void) {
    counter = 0;
    show_titles = 1;
    clrscr();
    
    while (!kbhit()) { 
        BeginDrawing();
        clear_screen();
        
        // Switch display every 500 ticks
        if (counter >= 250) {
            counter = 0;
            show_titles = !show_titles;
        } else {
            counter++; 
        }
        
        if (show_titles) {
            display_titles();
        } else {
            display_instructions();
        }
        
        EndDrawing();
    }
    
    in_play = true;
    clrscr();
    return counter;
}

bool game_over(void) {
    clrscr();
    BeginDrawing();
    
    center_text(10, "game over");
    
    timer = dumb_wait(1000);

    center_text(12, "ah, such a shame,");
    center_text(14, "you were doing so well!");
    timer = dumb_wait(1000);
    
    sprintf(output, "score:%03d", score);
    center_text(18, output);
    center_text(19, "play again (y/n)?");
    
    EndDrawing();
    
    key = cgetc();
    in_play = false;
    if (key == 'n') {
        cursor(1);
        echo();
        refresh();
        return false;
    } else {
        return true;
    }
} 