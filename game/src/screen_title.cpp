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
#include "screens.h"


// local variables
static int framesCounter = 0;
static int finishScreen = 0;

//----------------------------------------------------------------------------------
// Title Screen Functions Definition
//----------------------------------------------------------------------------------

// Title Screen Initialization logic
void InitTitleScreen(void)
{
      
    framesCounter = 0;
    finishScreen = 0;
    cat1Sprite->setScale(3.0f);
    cat1Sprite->setFlipHorizontal(false);
    cat2Sprite->setScale(3.0f);
    cat2Sprite->setFlipHorizontal(false);
    cat3Sprite->setScale(3.0f);
    cat3Sprite->setFlipHorizontal(false);
    cat4Sprite->setScale(3.0f);
    cat4Sprite->setFlipHorizontal(true);
    cat5Sprite->setScale(3.0f);
    cat5Sprite->setFlipHorizontal(true);
    cat6Sprite->setScale(3.0f);
    cat6Sprite->setFlipHorizontal(true);
}

// Title Screen Update logic
void UpdateTitleScreen(void)
{

    // Press enter or tap to change to GAMEPLAY screen
    if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
    {
        //finishScreen = 1;   // OPTIONS
    //    finishScreen = 2;   // GAMEPLAY
      //  PlaySound(fxCoin);
    

    }
    cat1Sprite->update( GetFrameTime());
    cat2Sprite->update(GetFrameTime());
    cat3Sprite->update(GetFrameTime());
	cat4Sprite->update(GetFrameTime());
    cat5Sprite->update(GetFrameTime());
    cat6Sprite->update(GetFrameTime());
}

// Title Screen Draw logic
void DrawTitleScreen(void)
{
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), BLUE);
    Vector2 pos = { 30, 500 };

    DrawText("Press Enter to Start Game", 150, 400, 20, WHITE);

    int mainLogoX= GetScreenWidth() / 2 - mainTexture.width / 2;
    int mainLogoY = GetScreenHeight() / 3 - mainTexture.height / 2;

    DrawTexture(mainTexture, mainLogoX, mainLogoY, WHITE);

    cat1Sprite->draw(50,50);
    cat2Sprite->draw(50, 150);
    cat3Sprite->draw(50, 300);
    cat4Sprite->draw(700, 50);
    cat5Sprite->draw(700, 150);
    cat6Sprite->draw(700, 300);
}

// Title Screen Unload logic
void UnloadTitleScreen(void)
{
    // TODO: Unload TITLE screen variables here!
}

// Title Screen should finish?
int FinishTitleScreen(void)
{
    return finishScreen;
}