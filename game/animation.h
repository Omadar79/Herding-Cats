#ifndef ANIMATION_H
#define ANIMATION_H

#include <string>
#include "raylib.h"

namespace my_raylib_utils
{
    struct Animation
    {
        Texture2D _texture;
        int _frameWidth;
        int _frameHeight;
        int _numFrames;
        float _frameTime;
        Rectangle* _frames;

        Animation(const std::string& file_path, int frame_width, int frame_height, int num_frames, float frame_time);

    	~Animation();

    };

}

#endif

