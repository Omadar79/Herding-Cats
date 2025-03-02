#include "scene_title.h"
#include "game.h"

namespace hcg
{
    void SceneTitle::Init()
    {
        p_cat1_sprite->setFlipHorizontal(false);
        p_cat2_sprite->setFlipHorizontal(false);
        p_cat3_sprite->setFlipHorizontal(false);
        p_cat4_sprite->setFlipHorizontal(true);
        p_cat5_sprite->setFlipHorizontal(true);
        p_cat6_sprite->setFlipHorizontal(true);
        _frameCounter = 0;
        _transitionScreen = scene_type::NONE;
        _sceneFinished = false;


        
       
    }

    void SceneTitle::Update()
    {
        UpdateMusicStream(g_music);

    	//  ---------------------- Check Input ----------------------
        if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
        {
            PlaySound(g_fx_coin);
            _sceneFinished = true;
            _transitionScreen = scene_type::GAMEPLAY;
        }

        p_cat1_sprite->update(GetFrameTime());
        p_cat2_sprite->update(GetFrameTime());
        p_cat3_sprite->update(GetFrameTime());
        p_cat4_sprite->update(GetFrameTime());
        p_cat5_sprite->update(GetFrameTime());
        p_cat6_sprite->update(GetFrameTime());
    }

    void SceneTitle::Draw()
    {
        DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), BLUE);
        Vector2 pos = { 30, 500 };

        DrawText("Press Enter to Start Game", 350, 700, 20, WHITE);

        double scale = 1.5;

        float mainLogoX = GetScreenWidth() / 2 - (g_main_texture.width * scale) / 2;
        float mainLogoY = GetScreenHeight() / 3 - (g_main_texture.height * scale) / 2;

        Vector2 logoPos = { mainLogoX, mainLogoY };
        DrawTextureEx(g_main_texture, logoPos, 0, scale, WHITE);

        p_cat1_sprite->draw(75, 50);
        p_cat2_sprite->draw(75, 350);
        p_cat3_sprite->draw(75, 600);
        p_cat4_sprite->draw(900, 50);
        p_cat5_sprite->draw(900, 350);
        p_cat6_sprite->draw(900, 600);
    }

    void SceneTitle::Unload()
    {
        // Unload resources specific to the gameplay screen
    }

    bool SceneTitle::IsSceneFinished()
    {
        return _sceneFinished;
    }

    scene_type SceneTitle::GetTransitionSceneType()
    {
        return _transitionScreen;
    }

    scene_type SceneTitle::GetSceneType()
    {
        return scene_type::TITLE;
    }
}