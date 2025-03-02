/*******************************************************************************************
*
*   Title: Herding Cats
*   File Description: The game header file contain globals and testing variables
*
*   Programming: Dustin Taub
*
*   This game has been created using raylib (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
********************************************************************************************/
// comment this out for final build
#define GAMETESTING

#ifndef GAME_H
#define GAME_H

#include "sprite_move_controller.h"
#include "scene_manager.h"
#include "sprite.h"


//----------------------------------------------------------------------------------
// Global Variables Declaration (shared by several modules)
//----------------------------------------------------------------------------------
//extern Game_Screen g_current_screen;
extern Image g_logo_image;
extern Texture2D g_main_texture;
extern Font g_font;
extern Music g_music;
extern Sound g_fx_coin;
extern hcg::Sprite *p_cat1_sprite;
extern hcg::Sprite *p_cat2_sprite;
extern hcg::Sprite *p_cat3_sprite;
extern hcg::Sprite *p_cat4_sprite;
extern hcg::Sprite *p_cat5_sprite;
extern hcg::Sprite *p_cat6_sprite;
extern hcg::SpriteMoveController *p_sprite_mover;
extern hcg::SceneManager SceneManager;



#ifdef __cplusplus
extern "C" {            // Prevents name mangling of functions
#endif


#ifdef __cplusplus
}
#endif


#endif

