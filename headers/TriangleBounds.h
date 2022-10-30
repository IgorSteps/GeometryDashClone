#pragma once
#include "Bounds.h"
#include <BoxBounds.h>
#include <Line.h>

class TriangleBounds :
    public Bounds
{
public:
    TriangleBounds(float base, float h);
    ~TriangleBounds();
    float getHeight();
    float getWidth();
    void draw(Shader& shader, glm::mat4& ModelViewMatrix, glm::mat4& ProjectionMatrix);
    void calculateTransform();
    void start();
    static bool checkCollision(BoxBounds& b1, TriangleBounds& t2);
    Component* copy();
    std::string serialise(int tabsize);
    static TriangleBounds* deseriaise();
private:
    Shader shader;
    Line line1;
    Line line2;
    Line line3;
    bool broadPhase(BoxBounds& b1);
    bool narrowPhase(BoxBounds& b1);
    glm::vec2 rotatePoint(float angle, glm::vec2 p, glm::vec2 o);
    bool boxIntersectLine(glm::vec2 p1, glm::vec2 p2, int depth, BoxBounds& bounds, glm::vec2 position);
    int computeRegionCode(glm::vec2 p, BoxBounds& b);

    float m_Base, m_Height, m_HalfHeight, m_HalfWidth;
    float m_EnclosingRadius;
    float m_X1, m_X2, m_X3, m_Y1, m_Y2, m_Y3;
    static TriangleBounds* deserialsiedTB;
   
    const int INSIDE = 0; // 0000
    const int LEFT = 1;   // 0001
    const int RIGHT = 2;  // 0010
    const int BOTTOM = 4; // 0100
    const int TOP = 8;    // 1000
};

