#ifndef SCENE_OPTIONS_H
#define SCENE_OPTIONS_H
#include "scene.h"

namespace herding_cats_game
{
	class SceneOptions : public Scene
	{
	public:
		void Init() override;
		void Update() override;
		void Draw() override;
		void Unload() override;
		bool Finish() override;

	private:
		int _frameCounter = 0;
		bool _finishScreen = false;
	};
}
#endif

