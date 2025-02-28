/*******************************************************************************************
*
*   Class: Sprite
*   Description: The base class to encapsulate a sprite using raylib.
*   Programming: Dustin Taub
* 
********************************************************************************************/
#include "sprite.h"

namespace herding_cats_game
{

    Sprite::Sprite()
        : _currentAnimation(nullptr), _currentFrameTime(0), _currentFrame(0), _scale(1.0f), _flipH(false), _flipV(false) {}


    Sprite::Sprite(float scale)
		: _currentAnimation(nullptr), _currentFrameTime(0), _currentFrame(0), _scale(scale),_flipH(false), _flipV(false) {}

    Sprite::~Sprite()
    {
        for (auto& anim : _animations) 
        {
            delete anim.second;
        }
    }

    void Sprite::addAnimation(const std::string& name, const std::string& file_Path, int frame_width, int frame_height, int num_frames, float frame_time) {

        _animations[name] = new SpriteAnimation(file_Path, frame_width, frame_height, num_frames, frame_time);
        if (!_currentAnimation) 
        {
            _currentAnimation = _animations[name];
        }
    }

    void Sprite::setAnimation(const std::string& name)
	{
        if (_animations.find(name) != _animations.end())
        {
            _currentAnimation = _animations[name];
            _currentFrame = 0;
            _currentFrameTime = 0;
        }
    }

    void Sprite::update(float delta_time)
	{
        if (_currentAnimation) 
        {
            _currentFrameTime += delta_time;
            if (_currentFrameTime >= _currentAnimation->_frameTime)
            {
                _currentFrameTime = 0;
                _currentFrame = (_currentFrame + 1) % _currentAnimation->_numFrames;
            }
        }
    }

    void Sprite::draw(int x, int y) const
	{
        if (_currentAnimation)
        {
            Rectangle source = _currentAnimation->_frames[_currentFrame];
            Rectangle dest = {
                static_cast<float>(x) 
                , static_cast<float>(y)
                , static_cast<float>(_currentAnimation->_frameWidth) * _scale 
                , static_cast<float>(_currentAnimation->_frameHeight) * _scale
				};
            Vector2 origin = { dest.width * 0.5f, dest.height * 0.5f }; // put origin in middle;

            source.width = source.width * (_flipH ? -1.0f : 1.0f);
            source.height = source.height * (_flipV ? -1.0f : 1.0f);

           
        	DrawTexturePro(_currentAnimation->_texture, source, dest, origin, 0.0f, WHITE);
          
        }
    }

    void Sprite::SetScale(float new_scale)
	{
        _scale = new_scale;
    }

    void Sprite::setFlip(bool flip_h, bool flip_v)
	{
        this->_flipH = flip_h;
        this->_flipV = flip_v;
    }

    void Sprite::setFlipVertical(bool flip)
    {
        this->_flipV = flip;
    }

    void Sprite::setFlipHorizontal(bool flip)
    {
        this->_flipH = flip;
    }

    bool Sprite::isFlippedHorizontal() const
    {
        return this->_flipH;
    }

    bool Sprite::isFlippedVertical() const
    {
        return this->_flipV;
    }

}