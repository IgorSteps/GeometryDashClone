#include "Bounds.h"
#include <BoxBounds.h>

bool Bounds::checkCollison(Bounds& b1, Bounds& b2)
{
    if (b1.type == b2.type && b1.type == Box)
    {
        return BoxBounds::checkCollision((BoxBounds&) b1, (BoxBounds&) b2);
    }
    return false;
}

std::string Bounds::serialise(int tabSize)
{
    return std::string();
}

Component* Bounds::copy()
{
    return nullptr;
}
