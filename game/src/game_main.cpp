/*******************************************************************************************
*
*   Title: Herding Cats
*   Description: My attempt at a simple cute cat game
* 
*   Programming: Dustin Taub
*
*   This game has been created using raylib (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
********************************************************************************************/

#include "raylib.h"
#include "game.h"    // NOTE: Declares global (extern) variables
#include "sprite.h"
#include "scene_manager.h"
#include "scene_title.h"
#include "scene_logo.h"


//----------------------------------------------------------------------------------
// global variables shared between modules through game.h
Image g_logo_image;
Texture2D g_main_texture;
Font g_font = { 0 };
Music g_music = { 0 };
Sound g_fx_coin = { 0 };
hcg::Sprite *p_cat1_sprite = nullptr;
hcg::Sprite *p_cat2_sprite = nullptr;
hcg::Sprite *p_cat3_sprite = nullptr;
hcg::Sprite *p_cat4_sprite = nullptr;
hcg::Sprite *p_cat5_sprite = nullptr;
hcg::Sprite *p_cat6_sprite = nullptr;
hcg::SceneManager SceneManager;

//------------------------------------------------------------------------------
// local variables
static constexpr int screen_width = 1024;
static constexpr int screen_height = 768;

static void InitializeGame(void); // Initialize game variables
static void InitializeAssets(void); // Initialize files and load assets
static void UnloadGame(void); // Unload current screen and free resources
static void CleanUpObjects(void); // Clean up pointers and instantiated objects


// Main game entry point
int main(void)
{
	InitWindow(screen_width, screen_height, "Herding Cats");

	InitializeGame();

#ifdef GAMETESTING
	SceneManager.SetScene(std::make_unique<hcg::SceneTitle>());
#else
	SceneManager.SetScene(std::make_unique<hcg::SceneLogo>());
#endif


	SetTargetFPS(60); // Set our game to run at 60 frames-per-second

	// Main game loop
	while (!WindowShouldClose()) // Detect window close button or ESC key
	{
		// the game loop logic depends on which scene we are in
		SceneManager.Update(); 
		BeginDrawing();
		ClearBackground(RAYWHITE);
		SceneManager.Draw();
		EndDrawing();
	}

	UnloadGame();

	return 0;
}

// Game Initialization
void InitializeGame(void)
{
	InitAudioDevice(); // Initialize audio device

	InitializeAssets();

	SetMusicVolume(g_music, 1.0f);
	PlayMusicStream(g_music);
}

// Asset Initialization
void InitializeAssets(void)
{
	//  (assets that must be available in all screens, i.e. font)
	g_font = LoadFont("resources/misc/mecha.png");
	g_logo_image = LoadImage("resources/misc/herdingcatslogo.png");
	g_music = LoadMusicStream("resources/music/cats_spies.wav");
	g_fx_coin = LoadSound("resources/sfx/confirm.wav");

	float idleFrameTime = 0.2f;
	float itchFrameTime = 0.4f;
	float lickingFrameTime = 0.1f;

	g_main_texture = LoadTextureFromImage(g_logo_image);
	// Create a sprite object
	p_cat1_sprite = new hcg::Sprite(3);
	p_cat1_sprite->addAnimation("idle", "resources/sprites/Cat-1-Idle.png", 50, 50, 10, idleFrameTime);
	p_cat1_sprite->addAnimation("itch", "resources/sprites/Cat-1-Itch.png", 50, 50, 2, itchFrameTime);
	p_cat1_sprite->addAnimation("laying", "resources/sprites/Cat-1-Laying.png", 50, 50, 8, 0.1f);
	p_cat1_sprite->addAnimation("licking", "resources/sprites/Cat-1-Licking.png", 50, 50, 5, lickingFrameTime);
	p_cat1_sprite->addAnimation("lickingButt", "resources/sprites/Cat-1-LickingButt.png", 50, 50, 5, lickingFrameTime);
	p_cat1_sprite->addAnimation("stretching", "resources/sprites/Cat-1-Stretching.png", 50, 50, 15, 0.1f);
	p_cat1_sprite->addAnimation("meow", "resources/sprites/Cat-1-Meow.png", 50, 50, 4, 0.1f);
	p_cat1_sprite->addAnimation("walk", "resources/sprites/Cat-1-Walk.png", 50, 50, 8, 0.1f);
	p_cat1_sprite->addAnimation("run", "resources/sprites/Cat-1-Run.png", 50, 50, 8, 0.1f);
	p_cat1_sprite->addAnimation("sitting", "resources/sprites/Cat-1-Sitting.png", 50, 50, 1, 0.1f);
	p_cat1_sprite->addAnimation("sleeping1", "resources/sprites/Cat-1-Sleeping1.png", 50, 50, 1, 0.1f);
	p_cat1_sprite->addAnimation("sleeping2", "resources/sprites/Cat-1-Sleeping2.png", 50, 50, 1, 0.1f);
	p_cat1_sprite->setAnimation("idle");

	p_cat2_sprite = new hcg::Sprite(3);
	p_cat2_sprite->addAnimation("idle", "resources/sprites/Cat-2-Idle.png", 50, 50, 10, idleFrameTime);
	p_cat2_sprite->addAnimation("itch", "resources/sprites/Cat-2-Itch.png", 50, 50, 2, itchFrameTime);
	p_cat2_sprite->addAnimation("laying", "resources/sprites/Cat-2-Laying.png", 50, 50, 8, 0.1f);
	p_cat2_sprite->addAnimation("licking", "resources/sprites/Cat-2-Licking.png", 50, 50, 5, lickingFrameTime);
	p_cat2_sprite->addAnimation("lickingButt", "resources/sprites/Cat-2-LickingButt.png", 50, 50, 5, lickingFrameTime);
	p_cat2_sprite->addAnimation("stretching", "resources/sprites/Cat-2-Stretching.png", 50, 50, 15, 0.1f);
	p_cat2_sprite->addAnimation("meow", "resources/sprites/Cat-2-Meow.png", 50, 50, 4, 0.1f);
	p_cat2_sprite->addAnimation("walk", "resources/sprites/Cat-2-Walk.png", 50, 50, 8, 0.1f);
	p_cat2_sprite->addAnimation("run", "resources/sprites/Cat-2-Run.png", 50, 50, 8, 0.1f);
	p_cat2_sprite->addAnimation("sitting", "resources/sprites/Cat-2-Sitting.png", 50, 50, 1, 0.1f);
	p_cat2_sprite->addAnimation("sleeping1", "resources/sprites/Cat-2-Sleeping1.png", 50, 50, 1, 0.1f);
	p_cat2_sprite->addAnimation("sleeping2", "resources/sprites/Cat-2-Sleeping2.png", 50, 50, 1, 0.1f);
	p_cat2_sprite->setAnimation("itch");

	p_cat3_sprite = new hcg::Sprite(3);
	p_cat3_sprite->addAnimation("idle", "resources/sprites/Cat-3-Idle.png", 50, 50, 10, idleFrameTime);
	p_cat3_sprite->addAnimation("itch", "resources/sprites/Cat-3-Itch.png", 50, 50, 2, itchFrameTime);
	p_cat3_sprite->addAnimation("laying", "resources/sprites/Cat-3-Laying.png", 50, 50, 8, 0.1f);
	p_cat3_sprite->addAnimation("licking", "resources/sprites/Cat-3-Licking.png", 50, 50, 5, lickingFrameTime);
	p_cat3_sprite->addAnimation("lickingButt", "resources/sprites/Cat-3-LickingButt.png", 50, 50, 5, lickingFrameTime);
	p_cat3_sprite->addAnimation("stretching", "resources/sprites/Cat-3-Stretching.png", 50, 50, 15, 0.1f);
	p_cat3_sprite->addAnimation("meow", "resources/sprites/Cat-3-Meow.png", 50, 50, 4, 0.1f);
	p_cat3_sprite->addAnimation("walk", "resources/sprites/Cat-3-Walk.png", 50, 50, 8, 0.1f);
	p_cat3_sprite->addAnimation("run", "resources/sprites/Cat-3-Run.png", 50, 50, 8, 0.1f);
	p_cat3_sprite->addAnimation("sitting", "resources/sprites/Cat-3-Sitting.png", 50, 50, 1, 0.1f);
	p_cat3_sprite->addAnimation("sleeping1", "resources/sprites/Cat-3-Sleeping1.png", 50, 50, 1, 0.1f);
	p_cat3_sprite->addAnimation("sleeping2", "resources/sprites/Cat-3-Sleeping2.png", 50, 50, 1, 0.1f);
	p_cat3_sprite->setAnimation("walk");

	p_cat4_sprite = new hcg::Sprite(3);
	p_cat4_sprite->addAnimation("idle", "resources/sprites/Cat-4-Idle.png", 50, 50, 10, idleFrameTime);
	p_cat4_sprite->addAnimation("itch", "resources/sprites/Cat-4-Itch.png", 50, 50, 2, itchFrameTime);
	p_cat4_sprite->addAnimation("laying", "resources/sprites/Cat-4-Laying.png", 50, 50, 8, 0.1f);
	p_cat4_sprite->addAnimation("licking", "resources/sprites/Cat-4-Licking.png", 50, 50, 5, lickingFrameTime);
	p_cat4_sprite->addAnimation("lickingButt", "resources/sprites/Cat-4-LickingButt.png", 50, 50, 5, lickingFrameTime);
	p_cat4_sprite->addAnimation("stretching", "resources/sprites/Cat-4-Stretching.png", 50, 50, 15, 0.1f);
	p_cat4_sprite->addAnimation("meow", "resources/sprites/Cat-4-Meow.png", 50, 50, 4, 0.1f);
	p_cat4_sprite->addAnimation("walk", "resources/sprites/Cat-4-Walk.png", 50, 50, 8, 0.1f);
	p_cat4_sprite->addAnimation("run", "resources/sprites/Cat-4-Run.png", 50, 50, 8, 0.1f);
	p_cat4_sprite->addAnimation("sitting", "resources/sprites/Cat-4-Sitting.png", 50, 50, 1, 0.1f);
	p_cat4_sprite->addAnimation("sleeping1", "resources/sprites/Cat-4-Sleeping1.png", 50, 50, 1, 0.1f);
	p_cat4_sprite->addAnimation("sleeping2", "resources/sprites/Cat-4-Sleeping2.png", 50, 50, 1, 0.1f);
	p_cat4_sprite->setAnimation("lickingButt");

	p_cat5_sprite = new hcg::Sprite(3);
	p_cat5_sprite->addAnimation("idle", "resources/sprites/Cat-5-Idle.png", 50, 50, 10, idleFrameTime);
	p_cat5_sprite->addAnimation("itch", "resources/sprites/Cat-5-Itch.png", 50, 50, 2, itchFrameTime);
	p_cat5_sprite->addAnimation("laying", "resources/sprites/Cat-5-Laying.png", 50, 50, 8, 0.1f);
	p_cat5_sprite->addAnimation("licking", "resources/sprites/Cat-5-Licking.png", 50, 50, 5, lickingFrameTime);
	p_cat5_sprite->addAnimation("lickingButt", "resources/sprites/Cat-5-LickingButt.png", 50, 50, 5, lickingFrameTime);
	p_cat5_sprite->addAnimation("stretching", "resources/sprites/Cat-5-Stretching.png", 50, 50, 15, 0.1f);
	p_cat5_sprite->addAnimation("meow", "resources/sprites/Cat-5-Meow.png", 50, 50, 4, 0.1f);
	p_cat5_sprite->addAnimation("walk", "resources/sprites/Cat-5-Walk.png", 50, 50, 8, 0.1f);
	p_cat5_sprite->addAnimation("run", "resources/sprites/Cat-5-Run.png", 50, 50, 8, 0.1f);
	p_cat5_sprite->addAnimation("sitting", "resources/sprites/Cat-5-Sitting.png", 50, 50, 1, 0.1f);
	p_cat5_sprite->addAnimation("sleeping1", "resources/sprites/Cat-5-Sleeping1.png", 50, 50, 1, 0.1f);
	p_cat5_sprite->addAnimation("sleeping2", "resources/sprites/Cat-5-Sleeping2.png", 50, 50, 1, 0.1f);
	p_cat5_sprite->setAnimation("run");

	p_cat6_sprite = new hcg::Sprite(3);
	p_cat6_sprite->addAnimation("idle", "resources/sprites/Cat-6-Idle.png", 50, 50, 10, idleFrameTime);
	p_cat6_sprite->addAnimation("itch", "resources/sprites/Cat-6-Itch.png", 50, 50, 2, itchFrameTime);
	p_cat6_sprite->addAnimation("laying", "resources/sprites/Cat-6-Laying.png", 50, 50, 8, 0.1f);
	p_cat6_sprite->addAnimation("licking", "resources/sprites/Cat-6-Licking.png", 50, 50, 5, lickingFrameTime);
	p_cat6_sprite->addAnimation("lickingButt", "resources/sprites/Cat-6-LickingButt.png", 50, 50, 5, lickingFrameTime);
	p_cat6_sprite->addAnimation("stretching", "resources/sprites/Cat-6-Stretching.png", 50, 50, 15, 0.1f);
	p_cat6_sprite->addAnimation("meow", "resources/sprites/Cat-6-Meow.png", 50, 50, 4, 0.1f);
	p_cat6_sprite->addAnimation("walk", "resources/sprites/Cat-6-Walk.png", 50, 50, 8, 0.1f);
	p_cat6_sprite->addAnimation("run", "resources/sprites/Cat-6-Run.png", 50, 50, 8, 0.1f);
	p_cat6_sprite->addAnimation("sitting", "resources/sprites/Cat-6-Sitting.png", 50, 50, 1, 0.1f);
	p_cat6_sprite->addAnimation("sleeping1", "resources/sprites/Cat-6-Sleeping1.png", 50, 50, 1, 0.1f);
	p_cat6_sprite->addAnimation("sleeping2", "resources/sprites/Cat-6-Sleeping2.png", 50, 50, 1, 0.1f);
	p_cat6_sprite->setAnimation("licking");
}

// De-Initialization and unload current screen data before closing
void UnloadGame(void)
{
	//------ Unload global data
	UnloadFont(g_font);
	UnloadMusicStream(g_music);
	UnloadSound(g_fx_coin);
	UnloadImage(g_logo_image);

	// Once image has been converted to texture and uploaded to VRAM, it can be unloaded from RAM
	UnloadTexture(g_main_texture);

	CleanUpObjects();
	CloseAudioDevice(); // Close audio context

	CloseWindow(); // Close window and OpenGL context

}

void CleanUpObjects()
{
	delete p_cat1_sprite;
	delete p_cat2_sprite;
	delete p_cat3_sprite;
	delete p_cat4_sprite;
	delete p_cat5_sprite;
	delete p_cat6_sprite;
}
