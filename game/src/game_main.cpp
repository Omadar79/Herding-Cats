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
Font font = { 0 };
Music music = { 0 };
Sound fxCoin = { 0 };
my_raylib_utils::Sprite* mySprite = nullptr;

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
void ChangeToScreen(int screen);     // Change to screen, no transition effect
void TransitionToScreen(int screen); // Request transition to next screen
void UpdateTransition(void);         // update transition effect
void DrawTransition(void);           // draw transition effect (full-screen rectangle)
void UpdateDrawFrame(void);          // update and draw one frame
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
    SetTargetFPS(60);       // Set our game to run at 60 frames-per-second
    

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
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
    InitAudioDevice();      // Initialize audio device

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
    mySprite = new my_raylib_utils::Sprite("resources/sprites/Cat-1-Idle.png", 50, 50, 10, 0.1f);
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
    UnloadImage(logoImage);   // Once image has been converted to texture and uploaded to VRAM, it can be unloaded from RAM
    UnloadTexture(mainTexture);
    CleanUpObjects();

    CloseAudioDevice();     // Close audio context

    CloseWindow();          // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
}

void CleanUpObjects()
{
    delete mySprite;
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
    else  // Transition fade out logic
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
        switch(currentScreen)
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
    else  //if we are in screen transition lets update it
    {
        UpdateTransition();
    }

    //----------------------------------------------------------------------------------
    // Main draw Routine
    //----------------------------------------------------------------------------------
    BeginDrawing();

        ClearBackground(RAYWHITE);

        //draw the current screen/scene
        switch(currentScreen)
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
