#pragma once
#include "Bounds.h"
#include <BoxBounds.h>
class TriangleBounds :
    public Bounds
{
public:
    TriangleBounds(float base, float h);
    ~TriangleBounds();
    float getHeight();
    float getWidth();

    void calculateTransform();
    void start();
    static bool checkCollision(BoxBounds& b1, TriangleBounds& t2);
    Component* copy();
    std::string serialise(int tabsize);
    static TriangleBounds* deseriaise();
private:
    bool broadPhase(BoxBounds& b1);
    bool narrowPhase(BoxBounds& b1);
    glm::vec2 rotatePoint(float angle, glm::vec2 p, glm::vec2 o);

    float m_Base, m_Height, m_HalfHeight, m_HalfWidth;
    float m_EnclosingRadius;
    float m_X1, m_X2, m_X3, m_Y1, m_Y2, m_Y3;
    static TriangleBounds* deserialsiedTB;
};

