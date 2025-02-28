#include "sprite_move_controller.h"
#include "utilities.h"


namespace herding_cats_game
{
    SpriteMoveController::SpriteMoveController(Sprite& sprite, float speed)
		: _sprite(sprite), _posX(0), _posY(0), _velX(0), _velY(0), _speed(speed) {}

    void SpriteMoveController::update(float delta_time)
    {
        _posX += _velX * delta_time;
        _posY += _velY * delta_time;
    }

    // GETTER and SETTERS
    float SpriteMoveController::getSpeed() const
    {
        return _speed;
    }

    void SpriteMoveController::setSpeed(float newSpeed)
    {
        if (newSpeed > 0.0f)
        {
            _speed = newSpeed;
        }
    }

    void SpriteMoveController::setPosition(float x, float y)
	{
        _posX = x;
        _posY = y;
    }

    void SpriteMoveController::setVelocity(float vx, float vy)
	{
        _velX = vx;
        _velY = vy;
        if (my_raylib_utils::isCloseToZero(vx) && my_raylib_utils::isCloseToZero(vy))
        {
            _sprite.setAnimation("idle"); 
        }
        else 
        {
            _sprite.setAnimation("moving"); 
        }
    }

    Vector2 SpriteMoveController::getPosition() const
	{
        return { _posX, _posY };
    }


}
