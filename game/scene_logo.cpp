#include "scene_logo.h"
#include "game.h"

namespace herding_cats_game
{
	void SceneLogo::Init()
	{
		_frameCounter = 0;
		_finishScreen = false;


		_logoPositionX = GetScreenWidth() / 2 - 128;
		_logoPositionY = GetScreenHeight() / 2 - 128;

		_lettersCount = 0;

		_topSideRectWidth = 16;
		_leftSideRectHeight = 16;

		_bottomSideRectWidth = 16;
		_rightSideRectHeight = 16;

		_state = 0;              // Logo animation states
		_alpha = 1.0f;
	}

	void SceneLogo::Update()
	{
        if (_state == 0)                 // State 0: Top-left square corner blink logic
        {
            _frameCounter++;

            if (_frameCounter == 80)
            {
                _state = 1;
                _frameCounter = 0;      // Reset counter... will be used later...
            }
        }
        else if (_state == 1)            // State 1: Bars animation logic: top and left
        {
            _topSideRectWidth += 8;
            _leftSideRectHeight += 8;

            if (_topSideRectWidth == 256)
            {
                _state = 2;
            }
        }
        else if (_state == 2)            // State 2: Bars animation logic: bottom and right
        {
            _bottomSideRectWidth += 8;
            _rightSideRectHeight += 8;

            if (_bottomSideRectWidth == 256)
            {
                _state = 3;
            }
        }
        else if (_state == 3)            // State 3: "raylib" text-write animation logic
        {
            _frameCounter++;

            if (_lettersCount < 10)
            {
                if (_frameCounter / 12)   // Every 12 frames, one more letter!
                {
                    _lettersCount++;
                    _frameCounter = 0;
                }
            }
            else    // When all letters have appeared, just fade out everything
            {
                if (_frameCounter > 200)
                {
                	_alpha -= 0.02f;

                    if (_alpha <= 0.0f)
                    {
                        _alpha = 0.0f;
                        _finishScreen = 1;   // Jump to next screen
                    }
                }
            }
        }
	}

	void SceneLogo::Draw()
	{
	
        if (_state == 0)         // Draw blinking top-left square corner
        {
            if ((_frameCounter / 10) % 2) DrawRectangle(_logoPositionX, _logoPositionY, 16, 16, BLACK);
        }
        else if (_state == 1)    // Draw bars animation: top and left
        {
            DrawRectangle(_logoPositionX, _logoPositionY, _topSideRectWidth, 16, BLACK);
            DrawRectangle(_logoPositionX, _logoPositionY, 16, _leftSideRectHeight, BLACK);
        }
        else if (_state == 2)    // Draw bars animation: bottom and right
        {
            DrawRectangle(_logoPositionX, _logoPositionY, _topSideRectWidth, 16, BLACK);
            DrawRectangle(_logoPositionX, _logoPositionY, 16, _leftSideRectHeight, BLACK);

            DrawRectangle(_logoPositionX + 240, _logoPositionY, 16, _rightSideRectHeight, BLACK);
            DrawRectangle(_logoPositionX, _logoPositionY + 240, _bottomSideRectWidth, 16, BLACK);
        }
        else if (_state == 3)    // Draw "raylib" text-write animation + "powered by"
        {
            DrawRectangle(_logoPositionX, _logoPositionY, _topSideRectWidth, 16, Fade(BLACK, _alpha));
            DrawRectangle(_logoPositionX, _logoPositionY + 16, 16, _leftSideRectHeight - 32, Fade(BLACK, _alpha));

            DrawRectangle(_logoPositionX + 240, _logoPositionY + 16, 16, _rightSideRectHeight - 32, Fade(BLACK, _alpha));
            DrawRectangle(_logoPositionX, _logoPositionY + 240, _bottomSideRectWidth, 16, Fade(BLACK, _alpha));

            DrawRectangle(GetScreenWidth() / 2 - 112, GetScreenHeight() / 2 - 112, 224, 224, Fade(RAYWHITE, _alpha));

            DrawText(TextSubtext("raylib", 0, _lettersCount), GetScreenWidth() / 2 - 44, GetScreenHeight() / 2 + 48, 50, Fade(BLACK, _alpha));

            if (_frameCounter > 20) DrawText("powered by", _logoPositionX, _logoPositionY - 27, 20, Fade(DARKGRAY, _alpha));
        }
	}

	void SceneLogo::Unload()
	{
	}

	bool SceneLogo::Finish()
	{
		return _finishScreen;
	}
}