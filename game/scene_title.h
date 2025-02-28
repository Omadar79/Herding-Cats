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
		bool Finish() override;
		scene_type GetSceneType() override;
	private:
		int _frameCounter = 0;
		bool _finishScreen = false;
	};
}
#endif
