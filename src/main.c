// Raylib and SearchAndSetResourceDir
#include "raylib.h"
#include "display/raylib_display.h"
#include "include/globals.h"
#include "include/maze.h"
#include "input/input.h"
#include "logic/game_logic.h"
#include "screens/screens.h"
#include "resource_dir.h"
#include <limits.h>
#include "include/notconio.h"




int main(void) {
    // Initialize Raylib display
    init_raylib_display();
    
    bool should_continue = true;
    
    while (should_continue && !window_should_close()) {
        // Show title screen first
        //title_screen();
        
		// Initialize if not already running a game
        //if (in_play != true) {
        //    init();
        //}

		run = true;
		printf("loading room");
		load_room();
		// Game on!
        in_play = true;

        // Main game loop
        while (in_play && !window_should_close()) {
            // Update game state
            update_game();
            
            // Check for ESCAPE or Q key press to end the game
            if (IsKeyPressed(KEY_ESCAPE) || IsKeyPressed(KEY_Q)) {
                in_play = false;
            }
            
            // Clear screen and begin drawing
            clear_screen();
            BeginDrawing();
            
            // Draw game state
            draw_game();
            
            // Debug, arbitrarily show textures:
            //cputcxy(10, 10, '@');
            //cputcxy(8, 8, 'g');


            // End drawing
            EndDrawing();
        }
        
        // If we're not in play but haven't closed the window, show game over
        if (!window_should_close()) {
            should_continue = game_over();
        }
    }
    
    // Cleanup
    close_raylib_display();
    return 0;
} 
