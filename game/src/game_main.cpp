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
#include "screens.h"    // NOTE: Declares global (extern) variables and screens functions
#include "sprite.h"

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif

//----------------------------------------------------------------------------------
// global variables shared between modules through screens.h
GameScreen currentScreen = TITLE;
Image logoImage;
Texture2D mainTexture;
Font font = {0};
Music music = {0};
Sound fxCoin = {0};
my_raylib_utils::Sprite* cat1Sprite = nullptr;
my_raylib_utils::Sprite* cat2Sprite = nullptr;
my_raylib_utils::Sprite* cat3Sprite = nullptr;
my_raylib_utils::Sprite* cat4Sprite = nullptr;
my_raylib_utils::Sprite* cat5Sprite = nullptr;
my_raylib_utils::Sprite* cat6Sprite = nullptr;


//------------------------------------------------------------------------------
// local variables
static const int screenWidth = 800;
static const int screenHeight = 600;

// Required variables to manage screen transitions (fade-in, fade-out)
static float transAlpha = 0.0f;
static bool onTransition = false;
static bool transFadeOut = false;
static int transFromScreen = -1;
static GameScreen transToScreen = UNKNOWN;

//----------------------------------------------------------------------------------
// local functions
void ChangeToScreen(int screen); // Change to screen, no transition effect
void TransitionToScreen(int screen); // Request transition to next screen
void UpdateTransition(void); // update transition effect
void DrawTransition(void); // draw transition effect (full-screen rectangle)
void UpdateDrawFrame(void); // update and draw one frame
void InitializeGame(void);
void InitializeAssets(void);
void UnloadGame(void);
void CleanUpObjects(void);


// Main game entry point
int main(void)
{
	InitWindow(screenWidth, screenHeight, "Herding Cats");

	InitializeGame();

	//my_raylib_utils.MySprite catSprite("resources/cat1.png", 32, 32, 4, 0.1f);

#if defined(PLATFORM_WEB)
    emscripten_set_main_loop(UpdateDrawFrame, 60, 1);
#else
	SetTargetFPS(60); // Set our game to run at 60 frames-per-second


	// Main game loop
	while (!WindowShouldClose()) // Detect window close button or ESC key
	{
		UpdateDrawFrame();
	}
#endif

	UnloadGame();

	return 0;
}

// Game Initialization
void InitializeGame(void)
{
	InitAudioDevice(); // Initialize audio device

	InitializeAssets();

	SetMusicVolume(music, 1.0f);
	PlayMusicStream(music);

	// Setup and init first screen
	currentScreen = TITLE;
	InitTitleScreen();
}

// Asset Initialization
void InitializeAssets(void)
{
	//  (assets that must be available in all screens, i.e. font)
	font = LoadFont("resources/misc/mecha.png");
	logoImage = LoadImage("resources/misc/herdingcatslogo.png");
	music = LoadMusicStream("resources/music/cats_spies.wav");
	fxCoin = LoadSound("resources/sfx/confirm.wav");

	mainTexture = LoadTextureFromImage(logoImage);
	// Create a sprite object
	cat1Sprite = new my_raylib_utils::Sprite(2);
	cat1Sprite->addAnimation("idle", "resources/sprites/Cat-1-Idle.png", 50, 50, 10, 0.1f);
	cat1Sprite->addAnimation("itch", "resources/sprites/Cat-1-Itch.png", 50, 50, 2, 0.1f);
	cat1Sprite->addAnimation("laying", "resources/sprites/Cat-1-Laying.png", 50, 50, 8, 0.1f);
	cat1Sprite->addAnimation("licking", "resources/sprites/Cat-1-Licking.png", 50, 50, 5, 0.1f);
	cat1Sprite->addAnimation("lickingButt", "resources/sprites/Cat-1-LickingButt.png", 50, 50, 5, 0.1f);
	cat1Sprite->addAnimation("stretching", "resources/sprites/Cat-1-Stretching.png", 50, 50, 15, 0.1f);
	cat1Sprite->addAnimation("meow", "resources/sprites/Cat-1-Meow.png", 50, 50, 4, 0.1f);
	cat1Sprite->addAnimation("walk", "resources/sprites/Cat-1-Walk.png", 50, 50, 8, 0.1f);
	cat1Sprite->addAnimation("run", "resources/sprites/Cat-1-Run.png", 50, 50, 8, 0.1f);
	cat1Sprite->addAnimation("sitting", "resources/sprites/Cat-1-Sitting.png", 50, 50, 1, 0.1f);
	cat1Sprite->addAnimation("sleeping1", "resources/sprites/Cat-1-Sleeping1.png", 50, 50, 1, 0.1f);
	cat1Sprite->addAnimation("sleeping2", "resources/sprites/Cat-1-Sleeping2.png", 50, 50, 1, 0.1f);
	cat1Sprite->setAnimation("idle");

	cat2Sprite = new my_raylib_utils::Sprite(2);
	cat2Sprite->addAnimation("idle", "resources/sprites/Cat-2-Idle.png", 50, 50, 10, 0.1f);
	cat2Sprite->addAnimation("itch", "resources/sprites/Cat-2-Itch.png", 50, 50, 2, 0.1f);
	cat2Sprite->addAnimation("laying", "resources/sprites/Cat-2-Laying.png", 50, 50, 8, 0.1f);
	cat2Sprite->addAnimation("licking", "resources/sprites/Cat-2-Licking.png", 50, 50, 5, 0.1f);
	cat2Sprite->addAnimation("lickingButt", "resources/sprites/Cat-2-LickingButt.png", 50, 50, 5, 0.1f);
	cat2Sprite->addAnimation("stretching", "resources/sprites/Cat-2-Stretching.png", 50, 50, 15, 0.1f);
	cat2Sprite->addAnimation("meow", "resources/sprites/Cat-2-Meow.png", 50, 50, 4, 0.1f);
	cat2Sprite->addAnimation("walk", "resources/sprites/Cat-2-Walk.png", 50, 50, 8, 0.1f);
	cat2Sprite->addAnimation("run", "resources/sprites/Cat-2-Run.png", 50, 50, 8, 0.1f);
	cat2Sprite->addAnimation("sitting", "resources/sprites/Cat-2-Sitting.png", 50, 50, 1, 0.1f);
	cat2Sprite->addAnimation("sleeping1", "resources/sprites/Cat-2-Sleeping1.png", 50, 50, 1, 0.1f);
	cat2Sprite->addAnimation("sleeping2", "resources/sprites/Cat-2-Sleeping2.png", 50, 50, 1, 0.1f);

	cat2Sprite->setAnimation("itch");

	cat3Sprite = new my_raylib_utils::Sprite(2);
	cat3Sprite->addAnimation("idle", "resources/sprites/Cat-3-Idle.png", 50, 50, 10, 0.1f);
	cat3Sprite->addAnimation("itch", "resources/sprites/Cat-3-Itch.png", 50, 50, 2, 0.1f);
	cat3Sprite->addAnimation("laying", "resources/sprites/Cat-3-Laying.png", 50, 50, 8, 0.1f);
	cat3Sprite->addAnimation("licking", "resources/sprites/Cat-3-Licking.png", 50, 50, 5, 0.1f);
	cat3Sprite->addAnimation("lickingButt", "resources/sprites/Cat-3-LickingButt.png", 50, 50, 5, 0.1f);
	cat3Sprite->addAnimation("stretching", "resources/sprites/Cat-3-Stretching.png", 50, 50, 15, 0.1f);
	cat3Sprite->addAnimation("meow", "resources/sprites/Cat-3-Meow.png", 50, 50, 4, 0.1f);
	cat3Sprite->addAnimation("walk", "resources/sprites/Cat-3-Walk.png", 50, 50, 8, 0.1f);
	cat3Sprite->addAnimation("run", "resources/sprites/Cat-3-Run.png", 50, 50, 8, 0.1f);
	cat3Sprite->addAnimation("sitting", "resources/sprites/Cat-3-Sitting.png", 50, 50, 1, 0.1f);
	cat3Sprite->addAnimation("sleeping1", "resources/sprites/Cat-3-Sleeping1.png", 50, 50, 1, 0.1f);
	cat3Sprite->addAnimation("sleeping2", "resources/sprites/Cat-3-Sleeping2.png", 50, 50, 1, 0.1f);
	cat3Sprite->setAnimation("stretching");

	cat4Sprite = new my_raylib_utils::Sprite(2);
	cat4Sprite->addAnimation("idle", "resources/sprites/Cat-4-Idle.png", 50, 50, 10, 0.1f);
	cat4Sprite->addAnimation("itch", "resources/sprites/Cat-4-Itch.png", 50, 50, 2, 0.1f);
	cat4Sprite->addAnimation("laying", "resources/sprites/Cat-4-Laying.png", 50, 50, 8, 0.1f);
	cat4Sprite->addAnimation("licking", "resources/sprites/Cat-4-Licking.png", 50, 50, 5, 0.1f);
	cat4Sprite->addAnimation("lickingButt", "resources/sprites/Cat-4-LickingButt.png", 50, 50, 5, 0.1f);
	cat4Sprite->addAnimation("stretching", "resources/sprites/Cat-4-Stretching.png", 50, 50, 15, 0.1f);
	cat4Sprite->addAnimation("meow", "resources/sprites/Cat-4-Meow.png", 50, 50, 4, 0.1f);
	cat4Sprite->addAnimation("walk", "resources/sprites/Cat-4-Walk.png", 50, 50, 8, 0.1f);
	cat4Sprite->addAnimation("run", "resources/sprites/Cat-4-Run.png", 50, 50, 8, 0.1f);
	cat4Sprite->addAnimation("sitting", "resources/sprites/Cat-4-Sitting.png", 50, 50, 1, 0.1f);
	cat4Sprite->addAnimation("sleeping1", "resources/sprites/Cat-4-Sleeping1.png", 50, 50, 1, 0.1f);
	cat4Sprite->addAnimation("sleeping2", "resources/sprites/Cat-4-Sleeping2.png", 50, 50, 1, 0.1f);
	cat4Sprite->setAnimation("lickingButt");

	cat5Sprite = new my_raylib_utils::Sprite(2);
	cat5Sprite->addAnimation("idle", "resources/sprites/Cat-5-Idle.png", 50, 50, 10, 0.1f);
	cat5Sprite->addAnimation("itch", "resources/sprites/Cat-5-Itch.png", 50, 50, 2, 0.1f);
	cat5Sprite->addAnimation("laying", "resources/sprites/Cat-5-Laying.png", 50, 50, 8, 0.1f);
	cat5Sprite->addAnimation("licking", "resources/sprites/Cat-5-Licking.png", 50, 50, 5, 0.1f);
	cat5Sprite->addAnimation("lickingButt", "resources/sprites/Cat-5-LickingButt.png", 50, 50, 5, 0.1f);
	cat5Sprite->addAnimation("stretching", "resources/sprites/Cat-5-Stretching.png", 50, 50, 15, 0.1f);
	cat5Sprite->addAnimation("meow", "resources/sprites/Cat-5-Meow.png", 50, 50, 4, 0.1f);
	cat5Sprite->addAnimation("walk", "resources/sprites/Cat-5-Walk.png", 50, 50, 8, 0.1f);
	cat5Sprite->addAnimation("run", "resources/sprites/Cat-5-Run.png", 50, 50, 8, 0.1f);
	cat5Sprite->addAnimation("sitting", "resources/sprites/Cat-5-Sitting.png", 50, 50, 1, 0.1f);
	cat5Sprite->addAnimation("sleeping1", "resources/sprites/Cat-5-Sleeping1.png", 50, 50, 1, 0.1f);
	cat5Sprite->addAnimation("sleeping2", "resources/sprites/Cat-5-Sleeping2.png", 50, 50, 1, 0.1f);
	cat5Sprite->setAnimation("sleeping1");

	cat6Sprite = new my_raylib_utils::Sprite(2);
	cat6Sprite->addAnimation("idle", "resources/sprites/Cat-6-Idle.png", 50, 50, 10, 0.1f);
	cat6Sprite->addAnimation("itch", "resources/sprites/Cat-6-Itch.png", 50, 50, 2, 0.1f);
	cat6Sprite->addAnimation("laying", "resources/sprites/Cat-6-Laying.png", 50, 50, 8, 0.1f);
	cat6Sprite->addAnimation("licking", "resources/sprites/Cat-6-Licking.png", 50, 50, 5, 0.1f);
	cat6Sprite->addAnimation("lickingButt", "resources/sprites/Cat-6-LickingButt.png", 50, 50, 5, 0.1f);
	cat6Sprite->addAnimation("stretching", "resources/sprites/Cat-6-Stretching.png", 50, 50, 15, 0.1f);
	cat6Sprite->addAnimation("meow", "resources/sprites/Cat-6-Meow.png", 50, 50, 4, 0.1f);
	cat6Sprite->addAnimation("walk", "resources/sprites/Cat-6-Walk.png", 50, 50, 8, 0.1f);
	cat6Sprite->addAnimation("run", "resources/sprites/Cat-6-Run.png", 50, 50, 8, 0.1f);
	cat6Sprite->addAnimation("sitting", "resources/sprites/Cat-6-Sitting.png", 50, 50, 1, 0.1f);
	cat6Sprite->addAnimation("sleeping1", "resources/sprites/Cat-6-Sleeping1.png", 50, 50, 1, 0.1f);
	cat6Sprite->addAnimation("sleeping2", "resources/sprites/Cat-6-Sleeping2.png", 50, 50, 1, 0.1f);
	cat6Sprite->setAnimation("licking");
}



// De-Initialization and unload current screen data before closing
void UnloadGame(void)
{
	switch (currentScreen)
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

	// Unload global data loaded
	UnloadFont(font);
	UnloadMusicStream(music);
	UnloadSound(fxCoin);
	UnloadImage(logoImage);
	// Once image has been converted to texture and uploaded to VRAM, it can be unloaded from RAM
	UnloadTexture(mainTexture);
	CleanUpObjects();

	CloseAudioDevice(); // Close audio context

	CloseWindow(); // Close window and OpenGL context
	//--------------------------------------------------------------------------------------
}

void CleanUpObjects()
{
	delete cat1Sprite;
	delete cat2Sprite;
	delete cat3Sprite;
	delete cat4Sprite;
	delete cat5Sprite;
	delete cat6Sprite;
}

// Change to next screen, no transition
void ChangeToScreen(GameScreen screen)
{
	// Unload current screen
	switch (currentScreen)
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

	// Init next screen
	switch (screen)
	{
	case LOGO:
		InitLogoScreen();
		break;

	case TITLE:
		InitTitleScreen();
		break;

	case GAMEPLAY:
		InitGameplayScreen();
		break;

	case ENDING:
		InitEndingScreen();
		break;

	default:
		break;
	}

	currentScreen = screen;
}

// Request transition to next screen
void TransitionToScreen(GameScreen screen)
{
	onTransition = true;
	transFadeOut = false;
	transFromScreen = currentScreen;
	transToScreen = screen;
	transAlpha = 0.0f;
}

// update transition effect (fade-in, fade-out)
void UpdateTransition(void)
{
	if (!transFadeOut)
	{
		transAlpha += 0.05f;

		// NOTE: Due to float internal representation, condition jumps on 1.0f instead of 1.05f
		// For that reason we compare against 1.01f, to avoid last frame loading stop
		if (transAlpha > 1.01f)
		{
			transAlpha = 1.0f;

			// Unload current screen
			switch (transFromScreen)
			{
			case LOGO:
				UnloadLogoScreen();
				break;

			case TITLE:
				UnloadTitleScreen();
				break;

			case OPTIONS:
				UnloadOptionsScreen();
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

			// Load next screen
			switch (transToScreen)
			{
			case LOGO:
				InitLogoScreen();
				break;

			case TITLE:
				InitTitleScreen();
				break;

			case GAMEPLAY:
				InitGameplayScreen();
				break;

			case ENDING:
				InitEndingScreen();
				break;

			default:
				break;
			}

			currentScreen = transToScreen;

			// Activate fade out effect to next loaded screen
			transFadeOut = true;
		}
	}
	else // Transition fade out logic
	{
		transAlpha -= 0.02f;

		if (transAlpha < -0.01f)
		{
			transAlpha = 0.0f;
			transFadeOut = false;
			onTransition = false;
			transFromScreen = -1;
			transToScreen = UNKNOWN;
		}
	}
}

// draw transition effect (full-screen rectangle)
void DrawTransition(void)
{
	DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(BLACK, transAlpha));
}


// update and draw game frame
void UpdateDrawFrame(void)
{
	// Music keeps playing between screens
	UpdateMusicStream(music);

	//Make sure we are not in screen transition
	if (!onTransition)
	{
		switch (currentScreen)
		{
		case LOGO:
			UpdateLogoScreen();
			if (FinishLogoScreen())
			{
				TransitionToScreen(TITLE);
			}
			break;

		case TITLE:
			UpdateTitleScreen();

			if (FinishTitleScreen() == 1)
			{
				TransitionToScreen(OPTIONS);
			}
			else if (FinishTitleScreen() == 2)
			{
				TransitionToScreen(GAMEPLAY);
			}
			break;

		case OPTIONS:
			UpdateOptionsScreen();

			if (FinishOptionsScreen())
			{
				TransitionToScreen(TITLE);
			}
			break;

		case GAMEPLAY:
			UpdateGameplayScreen();

			if (FinishGameplayScreen() == 1)
			{
				TransitionToScreen(ENDING);
			}
		//else if (FinishGameplayScreen() == 2) 
		//  {
		//      TransitionToScreen(TITLE);
		//  }
			break;

		case ENDING:
			UpdateEndingScreen();

			if (FinishEndingScreen() == 1)
			{
				TransitionToScreen(TITLE);
			}
			break;

		default:
			break;
		}
	}
	else //if we are in screen transition lets update it
	{
		UpdateTransition();
	}

	//----------------------------------------------------------------------------------
	// Main draw Routine
	//----------------------------------------------------------------------------------
	BeginDrawing();

	ClearBackground(RAYWHITE);

	//draw the current screen/scene
	switch (currentScreen)
	{
	case LOGO:
		DrawLogoScreen();
		break;

	case TITLE:
		DrawTitleScreen();
		break;

	case OPTIONS:
		DrawOptionsScreen();
		break;

	case GAMEPLAY:
		DrawGameplayScreen();
		break;

	case ENDING:
		DrawEndingScreen();
		break;

	default:
		break;
	}

	// draw full screen rectangle in front of everything
	if (onTransition)
	{
		DrawTransition();
	}

	EndDrawing();
	//----------------------------------------------------------------------------------
}
