#ifndef SCENE_TITLE_H
#define SCENE_TITLE_H
#include "scene.h"

namespace hcg
{
	class SceneTitle : public Scene
	{
	public:
		void Init() override;
		void Update() override;
		void Draw() override;
		void Unload() override;
		scene_type GetTransitionSceneType() override;
		scene_type GetSceneType() override;
		bool IsSceneFinished() override;
	private:
		int _frameCounter = 0;
		bool _sceneFinished = false;
		scene_type _transitionScreen = scene_type::NONE;
	};
}
#endif
