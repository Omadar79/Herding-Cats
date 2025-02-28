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
#include "game.h"    // NOTE: Declares global (extern) variables and screens functions
#include "sprite.h"
#include "scene_manager.h"
#include "scene_title.h"


//----------------------------------------------------------------------------------
// global variables shared between modules through screens.h
//Game_Screen g_current_screen = TITLE;
Image g_logo_image;
Texture2D g_main_texture;
Font g_font = { 0 };
Music g_music = { 0 };
Sound g_fx_coin = { 0 };
herding_cats_game::Sprite *p_cat1_sprite = nullptr;
herding_cats_game::Sprite *p_cat2_sprite = nullptr;
herding_cats_game::Sprite *p_cat3_sprite = nullptr;
herding_cats_game::Sprite *p_cat4_sprite = nullptr;
herding_cats_game::Sprite *p_cat5_sprite = nullptr;
herding_cats_game::Sprite *p_cat6_sprite = nullptr;


//------------------------------------------------------------------------------
// local variables
static constexpr int screen_width = 1024;
static constexpr int screen_height = 768;

// Required variables to manage screen transitions (fade-in, fade-out)
// static float transition_alpha = 0.0f;
// static bool transition_enabled = false;
// static bool transition_fade_out = false;
// static int transition_from_screen = -1;
// static Game_Screen transition_to_screen = UNKNOWN;

//----------------------------------------------------------------------------------
// local functions
// static void TransitionToScreen(Game_Screen current_screen, Game_Screen new_screen); // Request transition to next screen
// static void UpdateTransition(void); // update transition effect
// static void DrawTransition(void); // draw transition effect (full-screen rectangle)
// static void GameLoop(void); // main loop called every frame
// static void UpdateCurrentScreen(void); // Update current screen (logic)
// static void DrawCurrentScreen (void); // Draw current screen (graphics)
static void InitializeGame(void); // Initialize game variables
static void InitializeAssets(void); // Initialize files and load assets
static void UnloadGame(void); // Unload current screen and free resources
static void CleanUpObjects(void); // Clean up pointers and instantiated objects


// Main game entry point
int main(void)
{
	InitWindow(screen_width, screen_height, "Herding Cats");

	InitializeGame();

	herding_cats_game::SceneManager SceneManager;
	SceneManager.SetScene(std::make_unique<herding_cats_game::SceneTitle>());


	SetTargetFPS(60); // Set our game to run at 60 frames-per-second

	// Main game loop
	while (!WindowShouldClose()) // Detect window close button or ESC key
	{
		//GameLoop();
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

	// Setup and init first screen
	g_current_screen = TITLE;
	InitTitleScreen();
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
	p_cat1_sprite = new herding_cats_game::Sprite(3);
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

	p_cat2_sprite = new herding_cats_game::Sprite(3);
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

	p_cat3_sprite = new herding_cats_game::Sprite(3);
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

	p_cat4_sprite = new herding_cats_game::Sprite(3);
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

	p_cat5_sprite = new herding_cats_game::Sprite(3);
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

	p_cat6_sprite = new herding_cats_game::Sprite(3);
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
	switch (g_current_screen)
	{
	case LOGO:
		UnloadLogoScreen();
		break;

	case TITLE:
		UnloadTitleScreen();
		break;

	case GAMEPLAY:
		UnloadGameplayScreen();
		break;

	case ENDING:
		UnloadEndingScreen();
		break;

	default:
		break;
	}

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

// Change to next screen, no transition
// void ChangeToScreen(Game_Screen old_screen, Game_Screen new_screen)
// {
// 	// Unload current screen
// 	switch (old_screen)
// 	{
// 		case LOGO:
// 			UnloadLogoScreen();
// 			break;
//
// 		case TITLE:
// 			UnloadTitleScreen();
// 			break;
//
// 		case GAMEPLAY:
// 			UnloadGameplayScreen();
// 			break;
//
// 		case ENDING:
// 			UnloadEndingScreen();
// 			break;
//
// 		default:
// 			break;
// 	}
//
// 	// Init next screen
// 	switch (new_screen)
// 	{
// 		case LOGO:
// 			InitLogoScreen();
// 			break;
//
// 		case TITLE:
// 			InitTitleScreen();
// 			break;
//
// 		case GAMEPLAY:
// 			InitGameplayScreen();
// 			break;
//
// 		case ENDING:
// 			InitEndingScreen();
// 			break;
//
// 		default:
// 			break;
// 	}
//
// 	g_current_screen = new_screen;
// }
//
// // Request transition to next screen
// void TransitionToScreen(Game_Screen current_screen, Game_Screen new_screen)
// {
// 	transition_enabled = true;
// 	transition_fade_out = false;
// 	transition_from_screen = current_screen;
// 	transition_to_screen = new_screen;
// 	transition_alpha = 0.0f;
// 	g_current_screen = new_screen;
// }
//
// // update transition effect (fade-in, fade-out)
// void UpdateTransition(void)
// {
// 	if (!transition_fade_out)
// 	{
// 		transition_alpha += 0.05f;
//
// 		// NOTE: Due to float internal representation, condition jumps on 1.0f instead of 1.05f
// 		// For that reason we compare against 1.01f, to avoid last frame loading stop
// 		if (transition_alpha > 1.01f)
// 		{
// 			transition_alpha = 1.0f;
//
// 			// Unload current screen
// 			switch (transition_from_screen)
// 			{
// 				case LOGO:
// 					UnloadLogoScreen();
// 					break;
//
// 				case TITLE:
// 					UnloadTitleScreen();
// 					break;
//
// 				case OPTIONS:
// 					UnloadOptionsScreen();
// 					break;
//
// 				case GAMEPLAY:
// 					UnloadGameplayScreen();
// 					break;
//
// 				case ENDING:
// 					UnloadEndingScreen();
// 					break;
//
// 				default:
// 					break;
// 			}
//
// 			// Load next screen
// 			switch (transition_to_screen)
// 			{
// 			case LOGO:
// 				InitLogoScreen();
// 				break;
//
// 			case TITLE:
// 				InitTitleScreen();
// 				break;
//
// 			case GAMEPLAY:
// 				InitGameplayScreen();
// 				break;
//
// 			case ENDING:
// 				InitEndingScreen();
// 				break;
//
// 			default:
// 				break;
// 			}
//
// 			g_current_screen = transition_to_screen;
//
// 			// Activate fade out effect to next loaded screen
// 			transition_fade_out = true;
// 		}
// 	}
// 	else // Transition fade out logic
// 	{
// 		transition_alpha -= 0.02f;
//
// 		if (transition_alpha < -0.01f)
// 		{
// 			transition_alpha = 0.0f;
// 			transition_fade_out = false;
// 			transition_enabled = false;
// 			transition_from_screen = -1;
// 			transition_to_screen = UNKNOWN;
// 		}
// 	}
// }
//
// // draw transition effect (full-screen rectangle)
// void DrawTransition(void)
// {
// 	DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(BLACK, transition_alpha));
// }
//
// // update the current screen and transition if necessary
// void UpdateCurrentScreen(Game_Screen current_screen)
// {
//     switch (current_screen)
//     {
//         case LOGO:
//             UpdateLogoScreen();
//             if (FinishLogoScreen())
//             {
//                 TransitionToScreen(current_screen,TITLE);
//             }
//             break;
//         case TITLE:
//             UpdateTitleScreen();
//             if (FinishTitleScreen() == 1)
//             {
//                 TransitionToScreen(current_screen, OPTIONS);
//             }
//             else if (FinishTitleScreen() == 2)
//             {
//                 TransitionToScreen(current_screen, GAMEPLAY);
//             }
//             break;
//         case OPTIONS:
//             UpdateOptionsScreen();
//             if (FinishOptionsScreen())
//             {
//                 TransitionToScreen(current_screen, TITLE);
//             }
//             break;
//         case GAMEPLAY:
//             UpdateGameplayScreen();
//             if (FinishGameplayScreen() == 1)
//             {
//                 TransitionToScreen(current_screen,ENDING);
//             }
//             break;
//         case ENDING:
//             UpdateEndingScreen();
//             if (FinishEndingScreen() == 1)
//             {
//                 TransitionToScreen(current_screen,TITLE);
//             }
//             break;
//         default:
//             break;
//     }
// }
//
// // Draw the current screen
// void DrawCurrentScreen(Game_Screen current_screen)
// {
// 	switch (current_screen)
// 	{
// 		case LOGO:
// 			DrawLogoScreen();
// 			break;
// 		case TITLE:
// 			DrawTitleScreen();
// 			break;
// 		case OPTIONS:
// 			DrawOptionsScreen();
// 			break;
// 		case GAMEPLAY:
// 			DrawGameplayScreen();
// 			break;
// 		case ENDING:
// 			DrawEndingScreen();
// 			break;
// 		default:
// 			break;
// 	}
// }
//
// // Main game loop
// void GameLoop(void)
// {
// 	// Music keeps playing between screens
//     UpdateMusicStream(g_music);
//
//     // Make sure we are not in screen transition
//     if (!transition_enabled)
//     {
// 		UpdateCurrentScreen(g_current_screen);
//     }
//     else // if we are in screen transition lets update it
//     {
//         UpdateTransition();
//     }
//
//     //-------------------
//     // Main draw Routine
//     //-------------------
// 	BeginDrawing();  
//
//     ClearBackground(RAYWHITE);
//
// 	DrawCurrentScreen(g_current_screen);
//
// 	//if needed draw transition effect
//     if (transition_enabled)
//     {
//         DrawTransition();
//     }
//
//     EndDrawing();
//     //----------------------------------------------------------------------------------
//
// }

