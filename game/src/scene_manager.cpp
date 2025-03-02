#include "scene_manager.h"
#include "raylib.h"
#include "scene_ending.h"
#include "scene_gameplay.h"
#include "scene_logo.h"
#include "scene_options.h"
#include "scene_title.h"

namespace hcg
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

    void SceneManager::UpdateFrame()
    {
        if (transitionEnabled)
        {
            UpdateTransition();
        }
        else if (currentScene)
        {
            currentScene->Update();
            if (currentScene->IsSceneFinished())
            {
                switch (currentScene->GetSceneType())
                {
                case scene_type::LOGO:
                    TransitionToScene(std::make_unique<SceneTitle>());
                    break;
                case scene_type::TITLE:
                    TransitionToScene(std::make_unique<SceneGameplay>());
                    break;
                case scene_type::OPTIONS:
                    TransitionToScene(std::make_unique<SceneOptions>());
                    break;
                case scene_type::GAMEPLAY:
                    TransitionToScene(std::make_unique<SceneEnding>());
                    break;
                case scene_type::ENDING:
                    TransitionToScene(std::make_unique<SceneTitle>());
                    break;
                }
            }
        }
    }

    void SceneManager::DrawFrame() const
    {
        BeginDrawing();
        
        ClearBackground(RAYWHITE);

        if (currentScene)
        {
            currentScene->Draw();
        }
        if (transitionEnabled)
        {
            DrawTransition();
        }

        EndDrawing();
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




    void SceneManager::DrawTransition() const
    {
        ClearBackground(RAYWHITE);
        DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(BLACK, transitionAlpha));
    }

    void SceneManager::Cleanup() {
        if (currentScene)
        {
            currentScene->Unload();
            currentScene.reset();
        }
        if (nextScene)
        {
            nextScene->Unload();
            nextScene.reset();
        }
    }

}