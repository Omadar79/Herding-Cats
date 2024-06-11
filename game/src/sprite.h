#ifndef SPRITE_H
#define SPRITE_H

#include <string>
#include "raylib.h"

namespace my_raylib_utils
{
    class Sprite
    {
    public:
        Sprite(const std::string& file_path, int frame_width, int frame_height, int num_frames, float frame_time);
        ~Sprite();
       
        void update();
        void draw(Vector2 position);
        void setScale(float new_scale);

    private:
        Texture2D _texture; //raylib texture
        int _frameWidth;
        int _frameHeight;
        int _numFrames;
        float _frameTime;
        float _currentFrameTime;
        int _currentFrame;
        Rectangle _sourceRec;
        Rectangle _destRec;
        Vector2 _origin;
        float _scale; // Scaling factor
    };

  
}
#endif
