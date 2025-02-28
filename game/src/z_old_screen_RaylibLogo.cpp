/**********************************************************************************************
*
*   raylib - Advance Game template
*
*   Logo Screen Functions Definitions (Init, Update, Draw, Unload)
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


//----------------------------------------------------------------------------------
// Module Variables Definition (local)
//----------------------------------------------------------------------------------
static int frame_counter = 0;
static int finish_screen = 0;

static int logo_position_x = 0;
static int logo_position_y = 0;

static int letters_count = 0;

static int top_side_rect_width = 0;
static int left_side_rect_height = 0;

static int bottom_side_rect_width = 0;
static int right_side_rect_height = 0;

static int state = 0;              // Logo animation states
static float alpha = 1.0f;         // Useful for fading

//----------------------------------------------------------------------------------
// Logo Screen Functions Definition
//----------------------------------------------------------------------------------

// Logo Screen Initialization logic
void InitLogoScreen(void)
{
    finish_screen = 0;
    frame_counter = 0;
    letters_count = 0;

    logo_position_x = GetScreenWidth()/2 - 128;
    logo_position_y = GetScreenHeight()/2 - 128;

    top_side_rect_width = 16;
    left_side_rect_height = 16;
    bottom_side_rect_width = 16;
    right_side_rect_height = 16;

    state = 0;
    alpha = 1.0f;
}

// Logo Screen Update logic
void UpdateLogoScreen(void)
{
    if (state == 0)                 // State 0: Top-left square corner blink logic
    {
        frame_counter++;

        if (frame_counter == 80)
        {
            state = 1;
            frame_counter = 0;      // Reset counter... will be used later...
        }
    }
    else if (state == 1)            // State 1: Bars animation logic: top and left
    {
        top_side_rect_width += 8;
        left_side_rect_height += 8;

        if (top_side_rect_width == 256) state = 2;
    }
    else if (state == 2)            // State 2: Bars animation logic: bottom and right
    {
        bottom_side_rect_width += 8;
        right_side_rect_height += 8;

        if (bottom_side_rect_width == 256) state = 3;
    }
    else if (state == 3)            // State 3: "raylib" text-write animation logic
    {
        frame_counter++;

        if (letters_count < 10)
        {
            if (frame_counter/12)   // Every 12 frames, one more letter!
            {
                letters_count++;
                frame_counter = 0;
            }
        }
        else    // When all letters have appeared, just fade out everything
        {
            if (frame_counter > 200)
            {
                alpha -= 0.02f;

                if (alpha <= 0.0f)
                {
                    alpha = 0.0f;
                    finish_screen = 1;   // Jump to next screen
                }
            }
        }
    }
}

// Logo Screen Draw logic
void DrawLogoScreen(void)
{
    if (state == 0)         // Draw blinking top-left square corner
    {
        if ((frame_counter/10)%2) DrawRectangle(logo_position_x, logo_position_y, 16, 16, BLACK);
    }
    else if (state == 1)    // Draw bars animation: top and left
    {
        DrawRectangle(logo_position_x, logo_position_y, top_side_rect_width, 16, BLACK);
        DrawRectangle(logo_position_x, logo_position_y, 16, left_side_rect_height, BLACK);
    }
    else if (state == 2)    // Draw bars animation: bottom and right
    {
        DrawRectangle(logo_position_x, logo_position_y, top_side_rect_width, 16, BLACK);
        DrawRectangle(logo_position_x, logo_position_y, 16, left_side_rect_height, BLACK);

        DrawRectangle(logo_position_x + 240, logo_position_y, 16, right_side_rect_height, BLACK);
        DrawRectangle(logo_position_x, logo_position_y + 240, bottom_side_rect_width, 16, BLACK);
    }
    else if (state == 3)    // Draw "raylib" text-write animation + "powered by"
    {
        DrawRectangle(logo_position_x, logo_position_y, top_side_rect_width, 16, Fade(BLACK, alpha));
        DrawRectangle(logo_position_x, logo_position_y + 16, 16, left_side_rect_height - 32, Fade(BLACK, alpha));

        DrawRectangle(logo_position_x + 240, logo_position_y + 16, 16, right_side_rect_height - 32, Fade(BLACK, alpha));
        DrawRectangle(logo_position_x, logo_position_y + 240, bottom_side_rect_width, 16, Fade(BLACK, alpha));

        DrawRectangle(GetScreenWidth()/2 - 112, GetScreenHeight()/2 - 112, 224, 224, Fade(RAYWHITE, alpha));

        DrawText(TextSubtext("raylib", 0, letters_count), GetScreenWidth()/2 - 44, GetScreenHeight()/2 + 48, 50, Fade(BLACK, alpha));

        if (frame_counter > 20) DrawText("powered by", logo_position_x, logo_position_y - 27, 20, Fade(DARKGRAY, alpha));
    }
}

// Logo Screen Unload logic
void UnloadLogoScreen(void)
{
    // Unload LOGO screen variables here!
}

// Logo Screen should finish?
int FinishLogoScreen(void)
{
    return finish_screen;
}
