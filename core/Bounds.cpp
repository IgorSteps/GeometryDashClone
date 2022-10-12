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

void Bounds::resolveCollison(Bounds* b1, GameObject& plr)
{
    if (b1->type == Box)
    {
        BoxBounds* box = (BoxBounds*)b1;
        box->resolveCollision(plr);
    }
}

std::string Bounds::serialise(int tabSize)
{
    return std::string();
}

Component* Bounds::copy()
{
    return nullptr;
}
