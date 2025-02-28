#include "ai_controller.h"


namespace herding_cats_game
{
    AIController::AIController(SpriteMoveController& character) : _character(character) {}

    void AIController::moveToTarget(float targetX, float targetY, float deltaTime) const
    {
        Vector2 pos = _character.getPosition();
        float dx = targetX - pos.x;
        float dy = targetY - pos.y;
        float distance = sqrt(dx * dx + dy * dy);

        if (distance > 1.0f)
        {
            float velX = (dx / distance) * _character.getSpeed();
            float velY = (dy / distance) * _character.getSpeed();
            _character.setVelocity(velX, velY);
        }
        else 
        {
            _character.setVelocity(0, 0);
        }

        _character.update(deltaTime);
    }
}

