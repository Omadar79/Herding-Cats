/*******************************************************************************************
*
*   Class: Sprite
*   Description: The base class to encapsulate a sprite using raylib.
*   Programming: Dustin Taub
* 
********************************************************************************************/

#include "sprite.h"
#include "raylib.h"
#include <string>

namespace my_raylib_utils
{
    Sprite::Sprite(const std::string& file_path, int frame_width, int frame_height, int num_frames, float frame_time)
        : _frameWidth(frame_width), _frameHeight(frame_height), _numFrames(num_frames), _frameTime(frame_time), _currentFrameTime(0), _currentFrame(0)
    {
        _texture = LoadTexture(file_path.c_str());
        _sourceRec = { 0.0f, 0.0f, static_cast<float>(frame_width), static_cast<float>(frame_height) };
        _destRec = { 0.0f, 0.0f, static_cast<float>(frame_width), static_cast<float>(frame_height) };
        _origin = { static_cast<float>(frame_width) / 2, static_cast<float>(frame_height) / 2 };
        _scale = 1.0f;
    }

    Sprite::~Sprite()
    {
        UnloadTexture(_texture);
    }


    void Sprite::update()
    {
        _currentFrameTime += GetFrameTime();

        if (_currentFrameTime >= _frameTime)
        {
            _currentFrameTime = 0;
            _currentFrame++;
            if (_currentFrame >= _numFrames)
            {
                _currentFrame = 0;
            }
            _sourceRec.x = static_cast<float>(_frameWidth * _currentFrame);
        }
    }

    void Sprite::draw(Vector2 position) 
    {
        _destRec.x = position.x;
        _destRec.y = position.y;

        Rectangle _draw_Rec = _destRec;
    	_draw_Rec.height = _draw_Rec.height * _scale;
        _draw_Rec.width = _draw_Rec.width * _scale;

        DrawTexturePro(_texture, _sourceRec, _draw_Rec, _origin, 0.0f, WHITE);
    }

    void Sprite::setScale(float new_scale)
	{
        _scale = new_scale;
    }

}