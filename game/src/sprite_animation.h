#ifndef SPRITEANIMATION_H
#define SPRITEANIMATION_H

#include <string>
#include "raylib.h"

namespace herding_cats_game
{
    struct SpriteAnimation
    {
        Texture2D _texture;
        int _frameWidth;
        int _frameHeight;
        int _numFrames;
        float _frameTime;
        Rectangle* _frames;

        SpriteAnimation(const std::string& file_path, int frame_width, int frame_height, int num_frames, float frame_time);

    	~SpriteAnimation();

    };

}

#endif

