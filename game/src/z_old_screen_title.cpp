/**********************************************************************************************
*
*   raylib - Advance Game template
*
*   Title Screen Functions Definitions (Init, Update, Draw, Unload)
*
*   Copyright (c) 2014-2022 Ramon Santamaria (@raysan5)
*
*   This software is provided "as-is", without any express or implied warranty. In no event
*   will the authors be held liable for any damages arising from the use of this software.
*
*   Permission is granted to anyone to use this software for any purpose, including commercial
*   applications, and to alter it and redistribute it freely, subject to the following restrictions:
*
*     1. The origin of this software must not be misrepresented; you must not claim that you
*     wrote the original software. If you use this software in a product, an acknowledgment
*     in the product documentation would be appreciated but is not required.
*
*     2. Altered source versions must be plainly marked as such, and must not be misrepresented
*     as being the original software.
*
*     3. This notice may not be removed or altered from any source distribution.
*
**********************************************************************************************/

#include "raylib.h"
#include "z_old_screens.h"


// local variables
static int frame_counter = 0;
static int finish_screen = 0;

//----------------------------------------------------------------------------------
// Title Screen Functions Definition
//----------------------------------------------------------------------------------

// Title Screen Initialization logic
void InitTitleScreen(void)
{

    frame_counter = 0;
    finish_screen = 0;
    p_cat1_sprite->setFlipHorizontal(false);
    p_cat2_sprite->setFlipHorizontal(false);
    p_cat3_sprite->setFlipHorizontal(false);
    p_cat4_sprite->setFlipHorizontal(true);
    p_cat5_sprite->setFlipHorizontal(true);
    p_cat6_sprite->setFlipHorizontal(true);
}

// Title Screen Update logic
void UpdateTitleScreen(void)
{

    // Press enter or tap to change to GAMEPLAY screen
    if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
    {
        //finishScreen = 1;   // OPTIONS
        //finishScreen = 2;   // GAMEPLAY
        //PlaySound(fxCoin);


    }
    p_cat1_sprite->update(GetFrameTime());
    p_cat2_sprite->update(GetFrameTime());
    p_cat3_sprite->update(GetFrameTime());
    p_cat4_sprite->update(GetFrameTime());
    p_cat5_sprite->update(GetFrameTime());
    p_cat6_sprite->update(GetFrameTime());
}

// Title Screen Draw logic
void DrawTitleScreen(void)
{
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), BLUE);
    Vector2 pos = { 30, 500 };

    DrawText("Press Enter to Start Game", 350, 700, 20, WHITE);

    double scale = 1.5;

    float mainLogoX = GetScreenWidth() / 2 - (g_main_texture.width * scale) / 2;
    float mainLogoY = GetScreenHeight() / 3 - (g_main_texture.height * scale) / 2;

    Vector2 logoPos = { mainLogoX, mainLogoY };
    DrawTextureEx(g_main_texture, logoPos, 0, scale, WHITE);

    p_cat1_sprite->draw(75, 50);
    p_cat2_sprite->draw(75, 350);
    p_cat3_sprite->draw(75, 600);
    p_cat4_sprite->draw(900, 50);
    p_cat5_sprite->draw(900, 350);
    p_cat6_sprite->draw(900, 600);
}

// Title Screen Unload logic
void UnloadTitleScreen(void)
{
    // TODO: Unload TITLE screen variables here!
}

// Title Screen should finish?
int FinishTitleScreen(void)
{
    return finish_screen;
}
 