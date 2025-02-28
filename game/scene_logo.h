#ifndef SCENE_LOGO_H
#define SCENE_LOGO_H
#include "scene.h"

namespace herding_cats_game
{
	class SceneLogo : public Scene
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

		int _logoPositionX = 0;
		int _logoPositionY = 0;

		int _lettersCount = 0;

		int _topSideRectWidth = 0;
		int _leftSideRectHeight = 0;

		int _bottomSideRectWidth = 0;
		int _rightSideRectHeight = 0;

		int _state = 0;              // Logo animation states
		float _alpha = 1.0f;         // Useful for fading

	};
}
#endif
