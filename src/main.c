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


void get_input(void) {

	int x,y;

	if (IsKeyDown(KEY_W)) y -= 64 * GetFrameTime();
	if (IsKeyDown(KEY_S)) y += 64 * GetFrameTime();
	if (IsKeyDown(KEY_A)) x -= 64 * GetFrameTime();
	if (IsKeyDown(KEY_D)) x += 64 * GetFrameTime();

}



void resources(void)
{

	// Find the resources directory
	if (!SearchAndSetResourceDir("resources")) {
		printf("Failed to find resources directory. Please make sure the resources folder is in the same directory as the executable.\n");
		CloseWindow();

	}

	// Load resources with error checking
	char resourcePath[PATH_MAX];
	
	GetResourcePath("sprite.png", resourcePath, sizeof(resourcePath));
	Texture2D sprite = LoadTexture(resourcePath);
	if (sprite.id == 0) {
		printf("Failed to load sprite.png\n");
		CloseWindow();

	}

	GetResourcePath("brick.png", resourcePath, sizeof(resourcePath));
	Texture2D wall = LoadTexture(resourcePath);
	if (wall.id == 0) {
		printf("Failed to load brick.png\n");
		UnloadTexture(sprite);
		CloseWindow();

	}


}


int main(void) {
    // Initialize Raylib display
    init_raylib_display();
    
    bool should_continue = true;
    
    while (should_continue && !window_should_close()) {
        // Show title screen first
        title_screen();
        
        // Initialize game state
        init_game();
        
        // Main game loop
        while (in_play && !window_should_close()) {
            // Update game state
            update_game();
            
            // Clear screen and begin drawing
            clear_screen();
            BeginDrawing();
            
            // Draw game state
            draw_game();
            
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
