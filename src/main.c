// Raylib and SearchAndSetResourceDir
#include "raylib.h"
#include "resource_dir.h"	

struct GameObject {
	unsigned char x;
	unsigned char y;
	Texture sprite;

};

struct GameObject player;


void draw_screen(void) {


			// Setup the back buffer for drawing (clear color and depth buffers)
			ClearBackground(BLACK);
	
			// draw some text using the default font
			DrawText("Raylib Demo", 0, 0, 42, RED);
	
			// draw our player on the screen
			DrawTexture(player.sprite, player.x, player.y, WHITE);
			

}

void get_input(void) {

	if (IsKeyDown(KEY_UP)) player.y -= 16 * GetFrameTime();
	if (IsKeyDown(KEY_DOWN)) player.y += 16 * GetFrameTime();
	if (IsKeyDown(KEY_LEFT)) player.x -= 16 * GetFrameTime();
	if (IsKeyDown(KEY_RIGHT)) player.x += 16 * GetFrameTime();

}

void move_sprites(void) {

}

int main ()
{

	player.x=100;
	player.y=100;

	// Set to 60 frames-per-second
	SetTargetFPS(60);               

	// Tell the window to use vsync and work on high DPI displays
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	// Create the window and OpenGL context
	InitWindow(800, 600, "Raylib Demo");

	// Utility function from resource_dir.h to find the resources folder 
	// and set it as the current working directory so we can load from it
	SearchAndSetResourceDir("resources");

	// Load a sprite graphic from the resources directory
	player.sprite = LoadTexture("sprite.png");
	
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
