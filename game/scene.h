#ifndef SCENE_H
#define SCENE_H

namespace herding_cats_game
{

	typedef enum game_scene
	{
		UNKNOWN = -1,
		LOGO = 0,
		TITLE = 1,
		OPTIONS = 2,
		GAMEPLAY = 3,
		ENDING = 4,

	} game_scene;


	class Scene
	{
	public:

		virtual ~Scene() = default;

		virtual void Init() = 0;
		virtual void Update() = 0;
		virtual void Draw() = 0;
		virtual void Unload() = 0;
		virtual bool Finish() = 0;

	};

}

#endif
