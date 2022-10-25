#include "Bounds.h"
#include <BoxBounds.h>
#include <TriangleBounds.h>

bool Bounds::checkCollison(Bounds& b1, Bounds& b2)
{
    // player is a box so one bounds will always be box
    if (b1.type == b2.type && b1.type == Box)
    {
        return BoxBounds::checkCollision((BoxBounds&) b1, (BoxBounds&) b2);
    }
    else if (b1.type == Box && b2.type == Triangle)
    {
        TriangleBounds::checkCollision((BoxBounds&)b1, (TriangleBounds&)b2);
    }
    else if (b1.type == Triangle && b2.type == Box)
    {
        TriangleBounds::checkCollision((BoxBounds&)b2, (TriangleBounds&)b1);
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
