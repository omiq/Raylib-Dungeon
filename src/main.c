// Raylib and SearchAndSetResourceDir
#include "raylib.h"
#include "resource_dir.h"	

Texture wall;

struct GameObject {
	float x;
	float y;
	Texture sprite;

};

struct GameObject player;

int screenWidth = 800;
int screenHeight = 600;

char map[8][8] = {
    {1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 1, 1, 1},
    {1, 1, 1, 1, 0, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 1, 0, 1},
    {1, 0, 0, 0, 0, 1, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1}
};


void draw_screen(void) {


			// Setup the back buffer for drawing (clear color and depth buffers)
			ClearBackground(BLACK);

			for (int y = 0; y < 8; y++) {
				for (int x = 0; x < 8; x++) {
					if (map[y][x] == 1)
						DrawTexture(wall, (x*64)+100, (y*64)+100, WHITE);
				}
			}
			
	
			char buffer[40];
			sprintf(buffer, "Key: %d", GetKeyPressed());

			// draw some text using the default font
			DrawText(buffer, 0, 0, 42, RED);
	
			// draw our player on the screen
			DrawTexture(player.sprite, player.x, player.y, WHITE);
			

}

void get_input(void) {

	if (IsKeyDown(KEY_W)) player.y -= 64 * GetFrameTime();
	if (IsKeyDown(KEY_S)) player.y += 64 * GetFrameTime();
	if (IsKeyDown(KEY_A)) player.x -= 64 * GetFrameTime();
	if (IsKeyDown(KEY_D)) player.x += 64 * GetFrameTime();

}

void move_sprites(void) {

}

int main ()
{


	player.x=(screenWidth/2)-32;
	player.y=(screenHeight/2)-32;

	// Set to 60 frames-per-second
	SetTargetFPS(60);               

	// Tell the window to use vsync and work on high DPI displays
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	// Create the window and OpenGL context
	InitWindow(screenWidth, screenHeight, "Raylib Demo");

	// Utility function from resource_dir.h to find the resources folder 
	// and set it as the current working directory so we can load from it
	SearchAndSetResourceDir("resources");

	// Load a sprite graphic from the resources directory
	player.sprite = LoadTexture("sprite.png");
	wall = LoadTexture("brick.png");

	
	// run until ESCAPE or the window is closed
	while (!WindowShouldClose()) {

		// Start the frame
		BeginDrawing();

		// Game logic
		get_input();
		move_sprites();
		draw_screen();

		// end the frame
		EndDrawing();
	}

	// cleanup
	// unload our texture so it can be cleaned up
	UnloadTexture(player.sprite);

	// destroy the window and cleanup the OpenGL context
	CloseWindow();
	return 0;
}
