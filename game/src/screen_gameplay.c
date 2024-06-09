/**********************************************************************************************
*
*   raylib - Advance Game template
*
*   Gameplay Screen Functions Definitions (Init, Update, Draw, Unload)
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

#define NUM_CITIES 6
#define NUM_BASES 3


// local variables
static int framesCounter = 0;
static int finishScreen = 0;


// Define structures for missiles, bases, and cities
typedef struct Missile 
{
    Vector2 position;
    Vector2 target;
    Vector2 velocity;
    bool active;
} Missile;

typedef struct Base 
{
    Vector2 position;
    int health;
} Base;

typedef struct City 
{
    Vector2 position;
    bool active;
} City;


// Define arrays for missiles, bases, and cities
Missile playerMissiles[10];
Missile enemyMissiles[20];
Base playerBases[NUM_BASES];
City playerCities[NUM_CITIES];

//----------------------------------------------------------------------------------
// Gameplay Screen Functions 
void LaunchMissile(Missile missile);


// Gameplay Screen Initialization logic
void InitGameplayScreen(void)
{
    // TODO: Initialize GAMEPLAY screen variables here!
    framesCounter = 0;
    finishScreen = 0;

    int baseY = GetScreenHeight() - 50;

    // Example initialization for bases and cities
    for (int i = 0; i < NUM_BASES; i++)
    {
        playerBases[i].position = (Vector2){ (float)GetScreenWidth() / (NUM_BASES + 1) * (i + 1), (float)baseY };
        playerBases[i].health = 3;
    }

    for (int i = 0; i < NUM_CITIES; i++) {
        playerCities[i].position = (Vector2){ (float)GetScreenWidth() / (NUM_BASES + 1) * (i + 1), (float)baseY - 50 };
        playerCities[i].active = true;
    }
}

// Gameplay Screen Update logic
void UpdateGameplayScreen(void)
{
    // TODO: Update GAMEPLAY screen variables here!
     // Launch new missiles if inactive
    for (int i = 0; i < 20; i++)
    {
        if (!enemyMissiles[i].active)
        {
            LaunchMissile(enemyMissiles[i]);
        }
    }

    // Update missile positions
    for (int i = 0; i < 20; i++) {
        if (enemyMissiles[i].active) 
        {
            enemyMissiles[i].position.x += enemyMissiles[i].velocity.x;
            enemyMissiles[i].position.y += enemyMissiles[i].velocity.y;

            // Check if missile reached its target
            if (fabs(enemyMissiles[i].position.x - enemyMissiles[i].target.x) < 5 && fabs(enemyMissiles[i].position.y - enemyMissiles[i].target.y) < 5) 
            {
                enemyMissiles[i].active = false;  // Deactivate missile
            }
        }
    }


    // Press enter or tap to change to ENDING screen
    if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
    {
        finishScreen = 1;
        PlaySound(fxCoin);
    }
}

// Gameplay Screen Draw logic
void DrawGameplayScreen(void)
{
    // TODO: Draw GAMEPLAY screen here!
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), PURPLE);
    Vector2 pos = { 20, 10 };
    DrawTextEx(font, "GAMEPLAY SCREEN", pos, font.baseSize*3.0f, 4, MAROON);
    DrawText("PRESS ENTER or TAP to JUMP to ENDING SCREEN", 130, 220, 20, MAROON);

    // Draw bases
    for (int i = 0; i < NUM_BASES; i++)
    {
        DrawRectangle(playerBases[i].position.x - 20.0f, playerBases[i].position.y - 20.0f, 40, 40, GRAY);
    }

    // Draw cities
    for (int i = 0; i < NUM_CITIES; i++)
    {
        if (playerCities[i].active) 
        {
            DrawRectangle(playerCities[i].position.x - 15.0f, playerCities[i].position.y - 15.0f, 30, 30, DARKGRAY);
        }
    }

    // Draw missiles
    // ...


}

void LaunchMissile(Missile missile)
{
    missile.position.x = (float)(rand() % GetScreenWidth());
    missile.position.y = 0.0f;

    int targetCityIndex = rand() % NUM_CITIES;
    missile.target = playerCities[targetCityIndex].position;

    // Calculate velocity
    float dx = missile.target.x - missile.position.x;
    float dy = missile.target.y - missile.position.y;
    float distance = sqrt(dx * dx + dy * dy);
    missile.velocity.x = dx / distance * 3;
    missile.velocity.y = dy / distance * 3;  // Speed of 3 units per frame

    missile.active = true;
} 


// Gameplay Screen Unload logic
void UnloadGameplayScreen(void)
{
    // TODO: Unload GAMEPLAY screen variables here!
}

// Gameplay Screen should finish?
int FinishGameplayScreen(void)
{
    return finishScreen;
}