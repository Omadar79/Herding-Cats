#include "scene_gameplay.h"
#include "game.h"


namespace hcg
{

	void SceneGameplay::Init()
	{
		_frameCounter = 0;
		_transitionScreen = scene_type::NONE;
		_sceneFinished = false;
	}

	void SceneGameplay::Update()
	{
		UpdateMusicStream(g_music);

		if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
		{
			_sceneFinished = true;
			_transitionScreen = scene_type::ENDING;
			PlaySound(g_fx_coin);
		}

		p_sprite_mover->setPosition(30, 30);
		
	}

	void SceneGameplay::Draw()
	{

		DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), PURPLE);
		Vector2 pos = { 20, 10 };
		DrawTextEx(g_font, "GAMEPLAY SCREEN", pos, g_font.baseSize * 3.0f, 4, MAROON);
		//DrawText("PRESS ENTER or TAP to JUMP to ENDING SCREEN", 130, 220, 20, MAROON);

		p_sprite_mover->update(GetFrameTime());
	}

	void SceneGameplay::Unload()
	{

	}

	bool SceneGameplay::IsSceneFinished()
	{
		return _sceneFinished;
	}

	scene_type SceneGameplay::GetTransitionSceneType()
	{
		return _transitionScreen;
	}

	scene_type SceneGameplay::GetSceneType()
	{
		return scene_type::GAMEPLAY;
	}

}
