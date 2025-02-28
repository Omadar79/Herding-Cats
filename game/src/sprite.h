/*******************************************************************************************
*
*   File Description: The Sprite class encapsulates sprite drawing and animation classes
*
*   Programming: Dustin Taub
*
********************************************************************************************/

#ifndef SPRITE_H
#define SPRITE_H

#include <string>
#include <unordered_map>
#include "sprite_animation.h"

namespace hcg
{
    class Sprite
    {
    public:
        Sprite();
        Sprite(float scale);
        ~Sprite();
       
        void addAnimation(const std::string& name, const std::string& file_Path, int frame_width, int frame_height, int num_frames, float frame_time);
        void setAnimation(const std::string& name);

        void update(float delta_time);
        void draw(int x, int y) const;
        void SetScale(float new_Scale);

        void setFlip(bool flip_h, bool flip_v);
        void setFlipHorizontal(bool flip);
        void setFlipVertical(bool flip);

        bool isFlippedHorizontal() const;
        bool isFlippedVertical() const;

    private:
        std::unordered_map<std::string, SpriteAnimation*> _animations;
        SpriteAnimation* _currentAnimation;
        float _currentFrameTime;
        int _currentFrame;
        float _scale;
        bool _flipH;
        bool _flipV;
    };

  
}
#endif
