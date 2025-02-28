#ifndef SCENE_ENDING_H
#define SCENE_ENDING_H
#include "scene.h"

namespace hcg
{
	class SceneEnding : public Scene
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
