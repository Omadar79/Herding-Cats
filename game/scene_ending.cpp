#include "scene_ending.h"
#include "game.h"


namespace herding_cats_game
{
	void SceneEnding::Init()
	{
		_frameCounter = 0;
		_finishScreen = false;
	}

	void SceneEnding::Update()
	{
		// TODO: Update ENDING screen variables here!

		 // Press enter or tap to return to TITLE screen
		if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
		{
			_finishScreen = 1;
			PlaySound(g_fx_coin);
		}
	}

	void SceneEnding::Draw()
	{
		// TODO: Draw ENDING screen here!
		DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), BLUE);

		Vector2 pos = { 20, 10 };
		DrawTextEx(g_font, "Game Over", pos, g_font.baseSize * 3.0f, 4, DARKBLUE);
		DrawText("PRESS ENTER or TAP to RETURN to Start Again", 120, 220, 20, DARKBLUE);
	}

	void SceneEnding::Unload()
	{
	}

	bool SceneEnding::Finish()
	{
		return _finishScreen;
	}
}
