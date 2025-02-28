#include "scene_options.h"
#include "game.h"

namespace hcg
{
    void SceneOptions::Init()
    {
		_frameCounter = 0;
		_finishScreen = false;
    }

    void SceneOptions::Update()
    {
		UpdateMusicStream(g_music);
    }

    void SceneOptions::Draw()
	{
	}

	void SceneOptions::Unload()
	{
	}

	bool SceneOptions::Finish()
	{
		return _finishScreen;
	}

	scene_type SceneOptions::GetSceneType()
	{
		return scene_type::OPTIONS;
	}
}