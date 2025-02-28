#ifndef AICONTROLLER_H
#define AICONTROLLER_H

#include "sprite_move_controller.h"

namespace hcg
{
    class AIController
	{
    public:
        AIController(SpriteMoveController& character);

        void moveToTarget(float targetX, float targetY, float deltaTime) const;

    private:
        SpriteMoveController& _character;
    };


}
#endif

