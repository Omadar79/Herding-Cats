#ifndef CHARACTERCONTROLLER_H
#define CHARACTERCONTROLLER_H

#include "raylib.h"
#include "Sprite.h"


namespace herding_cats_game
{
    class SpriteMoveController
	{
    public:
        SpriteMoveController(Sprite& sprite, float speed = 100.0f);

        void update(float delta_time);

        // GETTER and SETTERS
        void setPosition(float x, float y);
        void setVelocity(float vx, float vy);
        Vector2 getPosition() const;
        float getSpeed() const;
        void setSpeed(float newSpeed);

    private:
        Sprite& _sprite;
        float _posX;
    	float _posY;
        float _velX;
    	float _velY;
        float _speed;
    };

}


#endif

