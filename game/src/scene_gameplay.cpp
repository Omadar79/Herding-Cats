#include "scene_gameplay.h"
#include "game.h"


namespace hcg
{
	void SceneGameplay::Init()
	{
		_frameCounter = 0;
		_finishScreen = false;
	}

	void SceneGameplay::Update()
	{
		UpdateMusicStream(g_music);
	}

	void SceneGameplay::Draw()
	{
		// TODO: Draw GAMEPLAY screen here!
		DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), PURPLE);
		Vector2 pos = { 20, 10 };
		DrawTextEx(g_font, "GAMEPLAY SCREEN", pos, g_font.baseSize * 3.0f, 4, MAROON);
		DrawText("PRESS ENTER or TAP to JUMP to ENDING SCREEN", 130, 220, 20, MAROON);
	}

	void SceneGameplay::Unload()
	{

	}

	bool SceneGameplay::Finish()
	{
		return _finishScreen;
	}

	scene_type SceneGameplay::GetSceneType()
	{
		return scene_type::GAMEPLAY;
	}
}
