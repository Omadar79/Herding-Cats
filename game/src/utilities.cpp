/*******************************************************************************************
*
*   Class: Utilities
*   Description: General utilities needed as I go
*   Programming: Dustin Taub
*
********************************************************************************************/

#include "utilities.h"

namespace my_raylib_utils
{
    bool isCloseToZero(float value)
    {
        return std::abs(value) < EPSILON;
    }
}