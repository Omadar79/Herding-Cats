#include "animation.h"

namespace my_raylib_utils
{

    Animation::Animation(const std::string& file_path, int frame_width, int frame_height, int num_frames, float frame_time)
        : _frameWidth(frame_width), _frameHeight(frame_height), _numFrames(num_frames), _frameTime(frame_time)
	{
        _texture = LoadTexture(file_path.c_str());
       _frames = new Rectangle[num_frames];

        for (int i = 0; i < num_frames; i++)
        {
            _frames[i] = { static_cast<float>(i * frame_width), 0, static_cast<float>(frame_width), static_cast<float>(frame_height) };
        }
    }

	Animation::~Animation()
	{
        UnloadTexture(_texture);
        delete[] _frames;
    };
}