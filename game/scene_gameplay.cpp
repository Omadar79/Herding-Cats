#include "scene_gameplay.h"
#include "game.h"


namespace herding_cats_game
{
	void SceneGameplay::Init()
	{
		_frameCounter = 0;
		_finishScreen = false;
	}

	void SceneGameplay::Update()
	{
	}

	void SceneGameplay::Draw()
	{
	}

	void SceneGameplay::Unload()
	{
	}

	bool SceneGameplay::Finish()
	{
		return _finishScreen;
	}
}
