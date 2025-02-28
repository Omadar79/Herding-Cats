#ifndef GAME_H
#define GAME_H
#include "sprite.h"



// //----------------------------------------------------------------------------------
// // Types and Structures Definition
// //----------------------------------------------------------------------------------
// typedef enum game_screen : uint8_t
// {
// 	UNKNOWN = -1,
// 	LOGO = 0,
// 	TITLE = 1,
// 	OPTIONS = 2,
// 	GAMEPLAY = 3,
// 	ENDING = 4,
// } Game_Screen;


//----------------------------------------------------------------------------------
// Global Variables Declaration (shared by several modules)
//----------------------------------------------------------------------------------
//extern Game_Screen g_current_screen;
extern Image g_logo_image;
extern Texture2D g_main_texture;
extern Font g_font;
extern Music g_music;
extern Sound g_fx_coin;
extern herding_cats_game::Sprite* p_cat1_sprite;
extern herding_cats_game::Sprite* p_cat2_sprite;
extern herding_cats_game::Sprite* p_cat3_sprite;
extern herding_cats_game::Sprite* p_cat4_sprite;
extern herding_cats_game::Sprite* p_cat5_sprite;
extern herding_cats_game::Sprite* p_cat6_sprite;



#ifdef __cplusplus
extern "C" {            // Prevents name mangling of functions
#endif

	// //----------------------------------------------------------------------------------
	// // Logo Screen Functions Declaration
	// //----------------------------------------------------------------------------------
	// void InitLogoScreen(void);
	// void UpdateLogoScreen(void);
	// void DrawLogoScreen(void);
	// void UnloadLogoScreen(void);
	// int FinishLogoScreen(void);
	//
	// //----------------------------------------------------------------------------------
	// // Title Screen Functions Declaration
	// //----------------------------------------------------------------------------------
	// void InitTitleScreen(void);
	// void UpdateTitleScreen(void);
	// void DrawTitleScreen(void);
	// void UnloadTitleScreen(void);
	// int FinishTitleScreen(void);
	//
	// //----------------------------------------------------------------------------------
	// // Options Screen Functions Declaration
	// //----------------------------------------------------------------------------------
	// void InitOptionsScreen(void);
	// void UpdateOptionsScreen(void);
	// void DrawOptionsScreen(void);
	// void UnloadOptionsScreen(void);
	// int FinishOptionsScreen(void);
	//
	// //----------------------------------------------------------------------------------
	// // Gameplay Screen Functions Declaration
	// //----------------------------------------------------------------------------------
	// void InitGameplayScreen(void);
	// void UpdateGameplayScreen(void);
	// void DrawGameplayScreen(void);
	// void UnloadGameplayScreen(void);
	// int FinishGameplayScreen(void);
	//
	// //----------------------------------------------------------------------------------
	// // Ending Screen Functions Declaration
	// //----------------------------------------------------------------------------------
	// void InitEndingScreen(void);
	// void UpdateEndingScreen(void);
	// void DrawEndingScreen(void);
	// void UnloadEndingScreen(void);
	// int FinishEndingScreen(void);

#ifdef __cplusplus
}
#endif


#endif

