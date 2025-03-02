#include "scene_ending.h"
#include "game.h"


namespace hcg
{
	void SceneEnding::Init()
	{
		_frameCounter = 0;
		_transitionScreen = scene_type::NONE;
		_sceneFinished = false;
	}

	void SceneEnding::Update()
	{

		UpdateMusicStream(g_music);

		 // Press enter or tap to return to TITLE screen
		if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
		{
			_sceneFinished = true;
			_transitionScreen = scene_type::TITLE;
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

	bool SceneEnding::IsSceneFinished()
	{
		return _sceneFinished;
	}

	scene_type SceneEnding::GetTransitionSceneType()
	{
		return _transitionScreen;
	}

	scene_type SceneEnding::GetSceneType()
	{
		return scene_type::ENDING;
	}
}
