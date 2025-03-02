#include "scene_options.h"
#include "game.h"

namespace hcg
{
    void SceneOptions::Init()
    {
		_frameCounter = 0;
		_transitionScreen = scene_type::NONE;
		_sceneFinished = false;
    }

    void SceneOptions::Update()
    {
		UpdateMusicStream(g_music);

		//  ---------------------- Check Input ----------------------
		if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
		{
			PlaySound(g_fx_coin);
			_sceneFinished = true;
			_transitionScreen = scene_type::GAMEPLAY;
		}
    }

    void SceneOptions::Draw()
	{
	}

	void SceneOptions::Unload()
	{
	}

	bool SceneOptions::IsSceneFinished()
	{
		return _sceneFinished;
	}

	scene_type SceneOptions::GetTransitionSceneType()
	{
		return _transitionScreen;
	}

	scene_type SceneOptions::GetSceneType()
	{
		return scene_type::OPTIONS;
	}
}