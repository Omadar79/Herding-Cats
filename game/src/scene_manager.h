#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include "scene.h"
#include <memory>

namespace hcg
{
    class SceneManager
	{
    public:
        void SetScene(std::unique_ptr<Scene> newScene);
        void TransitionToScene(std::unique_ptr<Scene> newScene, bool withTransition = true);
        void UpdateFrame();
        void DrawFrame() const;
		void Cleanup();

    private:

        void UpdateTransition();
        void DrawTransition() const;

		std::unique_ptr<Scene> currentScene;
        std::unique_ptr<Scene> nextScene;

        bool transitionEnabled = false;
        bool transitionFadeOut = false;
        float transitionAlpha = 0.0f;
    };

}
#endif