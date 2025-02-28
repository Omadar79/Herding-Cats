#include "scene_options.h"
#include "game.h"

namespace herding_cats_game
{
    void SceneOptions::Init()
    {
		_frameCounter = 0;
		_finishScreen = false;
    }

    void SceneOptions::Update()
    {
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
}