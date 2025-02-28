/*******************************************************************************************
*
*   File Description: The Scene base class is derived for individual game scenes.  Scenes
*                     have their own logic update and drawing routines for the main loop
*
*   Programming: Dustin Taub
*
********************************************************************************************/

#ifndef SCENE_H
#define SCENE_H

namespace hcg
{

	typedef enum scene_type
	{
		//UNKNOWN = -1,
		LOGO = 0,
		TITLE = 1,
		OPTIONS = 2,
		GAMEPLAY = 3,
		ENDING = 4,

	}scene_type;


	class Scene
	{
	public:

		virtual ~Scene() = default;

		virtual void Init() = 0;
		virtual void Update() = 0;
		virtual void Draw() = 0;
		virtual void Unload() = 0;
		virtual bool Finish() = 0;
		virtual scene_type GetSceneType() = 0;
	};

}

#endif
