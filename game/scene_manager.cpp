#include "scene_manager.h"
#include "raylib.h"

namespace herding_cats_game
{

    void SceneManager::SetScene(std::unique_ptr<Scene> newScene)
	{
        if (currentScene) 
        {
            currentScene->Unload();
        }
        currentScene = std::move(newScene);
        if (currentScene)
        {
            currentScene->Init();
        }
    }

    void SceneManager::TransitionToScene(std::unique_ptr<Scene> newScene, bool withTransition)
	{
        if (withTransition)
        {
            transitionEnabled = true;
            transitionFadeOut = false;
            transitionAlpha = 0.0f;
            nextScene = std::move(newScene);
        }
        else 
        {
            SetScene(std::move(newScene));
        }
    }

    void SceneManager::Update()
	{
        if (transitionEnabled) 
        {
            UpdateTransition();
        }
        else if (currentScene)
        {
            currentScene->Update();
            if (currentScene->Finish())
            {
                // Handle scene transition logic here
            }
        }
    }

    void SceneManager::Draw()
	{
        if (currentScene) 
        {
            currentScene->Draw();
        }
        if (transitionEnabled)
        {
            DrawTransition();
        }
    }

    void SceneManager::UpdateTransition()
    {
        if (!transitionFadeOut)
        {
            transitionAlpha += 0.05f;
            if (transitionAlpha > 1.0f)
            {
                transitionAlpha = 1.0f;
                if (currentScene)
                {
                    currentScene->Unload();
                }
                currentScene = std::move(nextScene);
                if (currentScene)
                {
                    currentScene->Init();
                }
                transitionFadeOut = true;
            }
        }
        else
        {
            transitionAlpha -= 0.02f;
            if (transitionAlpha < 0.0f)
            {
                transitionAlpha = 0.0f;
                transitionEnabled = false;
            }
        }
    }

    void SceneManager::DrawTransition()
	{
        DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(BLACK, transitionAlpha));
    }
}