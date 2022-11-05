#include "TriangleBounds.h"
#include "Parser.h"
#include "GameObject.h"
#include <Game.h>
#include <Constants.h>


TriangleBounds::TriangleBounds(float base, float h)
{
    type = Triangle;
    m_Base = base;
    m_Height = h;
    m_HalfHeight = h / 2.0f;
    m_HalfWidth = base / 2.0f;
    m_EnclosingRadius = std::max(m_HalfHeight, m_HalfWidth);

    // load shader for lines
    if (!shader.load("lineVert for triangles", "./glslfiles/lineShader.vert", "./glslfiles/lineShader.frag"))
    {
        std::cout << "failed to load shader" << std::endl;
    }

    triangle = Line();
    float col[] = { 1.0f, 0.0f, 0.0f };
    triangle.SetHeight(20.0f);
    triangle.SetWidth(20.0f);
    triangle.setColour(col);
    triangle.setIsGrid(false);
    triangle.setIsTriangle(true);

}

TriangleBounds::~TriangleBounds()
{
    delete deserialsiedTB;
}

float TriangleBounds::getHeight()
{
    return m_Height;
}

float TriangleBounds::getWidth()
{
    return m_Base;
}

void TriangleBounds::draw(Shader& sh, glm::mat4& ModelViewMatrix, glm::mat4& ProjectionMatrix)
{
    if (isSelected)
    {
        // center on the spike
        ModelViewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(gameObj->transform->position.x - m_X1 - m_Base / 2, gameObj->transform->position.y - m_Y2 - m_Base / 2, 1.0f));
        triangle.draw(shader, ModelViewMatrix, ProjectionMatrix);
    }
}

void TriangleBounds::start()
{
    calculateTransform();
}

void TriangleBounds::calculateTransform()
{
    float rAngle = glm::radians(gameObj->transform->rotateion);
    // spike's origin is at the center
    // find corresponding edges:
    glm::vec2 p1(gameObj->transform->position.x - m_HalfWidth, gameObj->transform->position.y - m_HalfHeight);  // bottom left
    glm::vec2 p2(gameObj->transform->position.x, gameObj->transform->position.y + m_HalfHeight);                // top
    glm::vec2 p3(gameObj->transform->position.x + m_HalfWidth, gameObj->transform->position.y - m_HalfHeight);  // bottom right

    glm::vec2 origin(gameObj->transform->position.x, gameObj->transform->position.y);   // origin

    p1 = rotatePoint(rAngle, p1, origin);
    p2 = rotatePoint(rAngle, p2, origin);
    p3 = rotatePoint(rAngle, p3, origin);

    m_X1 = p1.x;
    m_Y1 = p1.y;

    m_X2 = p2.x;
    m_Y2 = p2.y;

    m_X3 = p3.x;
    m_Y3 = p3.y;

    triangle.initTriangle(shader, p1, p2, p3);
}

bool TriangleBounds::checkCollision(BoxBounds& b1, TriangleBounds& t2)
{
    if (t2.broadPhase(b1))
    {
        return t2.narrowPhase(b1);
    }

    return false;
}

bool TriangleBounds::broadPhase(BoxBounds& b1)
{
    float bRadius = b1.m_EnclosingRadius;
    float tRadius = m_EnclosingRadius;

    glm::vec2 dist(b1.gameObj->transform->position.x - m_X2, b1.gameObj->transform->position.y - this->gameObj->transform->position.y);

    float magSquared = powf(dist.x, 2) + powf(dist.y, 2);
    float radiiSquared = powf(bRadius + tRadius, 2);

    return magSquared <= radiiSquared;
}

bool TriangleBounds::narrowPhase(BoxBounds& b1)
{
    glm::vec2 p1(m_X1, m_Y1);
    glm::vec2 p2(m_X2, m_Y2);
    glm::vec2 p3(m_X3, m_Y3);

    // origin center of box bounds
    glm::vec2 origin(b1.gameObj->transform->position.x + (b1.m_Width / 2.0f), b1.gameObj->transform->position.y + (b1.m_Height / 2.0f));
    float rAngle = glm::radians(b1.gameObj->transform->rotateion);

    // rotate the points about their center
    p1 = rotatePoint(rAngle, p1, origin);
    p2 = rotatePoint(rAngle, p2, origin);
    p3 = rotatePoint(rAngle, p3, origin);


    return (boxIntersectLine(p1, p2, 0, b1, gameObj->transform->position) ||
        boxIntersectLine(p2, p3, 0, b1, gameObj->transform->position) ||
        boxIntersectLine(p3, p1, 0, b1, gameObj->transform->position));
}

bool TriangleBounds::boxIntersectLine(glm::vec2 p1, glm::vec2 p2, int depth, BoxBounds& bounds, glm::vec2 position)
{
    // Cohen Sutherland clipping algorithm
    if (depth > 5)
    {
        std::cout << "Max Depth Exceeded\n";
        return true;
    }

    int code1 = computeRegionCode(p1, bounds);
    int code2 = computeRegionCode(p2, bounds);
    
    // check if line is completely inside, or outside, or half in and half out
    if (code1 == 0 && code2 == 0)
    {
        // line is completely inside
        return true;
    }
    else if ((code1 & code2) != 0)
    {
        // line is completely outside
        return false;
    }
    else if (code1 == 0 || code2 == 0)
    {
        // one point is inside, one is outside
        return true;
    }

    int xmax = (int)(position.x + bounds.m_Width);
    int xmin = (int)(position.x);

    // y = mx + b
    float m = (p2.y - p1.y) / (p2.x - p1.x);
    float b = p2.y - (m * p2.x);

    if ((code1 & LEFT) == LEFT)
    {
        // add 1 to ensure we are inside the clipping polygon
        p1.x = xmin + 1;
    }
    else if ((code1 & RIGHT) == RIGHT)
    {
        // subtract 1 to ensure we are inside the clipping polygon
        p1.x = xmax - 1;
    }
     p1.y = (m * p1.x) + b;

     // repeat for p2
     if ((code2 & LEFT) == LEFT)
     {
         // add 1 to ensure we are inside the clipping polygon
         p2.x = xmin + 1;
     }
     else if ((code2 & RIGHT) == RIGHT)
     {
         // subtract 1 to ensure we are inside the clipping polygon
         p2.x = xmax - 1;
     }
     p2.y = (m * p2.x) + b;

     return boxIntersectLine(p1, p2, depth + 1, bounds, position);
}

int TriangleBounds::computeRegionCode(glm::vec2 point, BoxBounds& b)
{
    int code = INSIDE;
    glm::vec2 topLeft(b.gameObj->transform->position);

    // check if p is on the left or right of the bounds
    if (point.x < topLeft.x)
    {
        code |= LEFT;
    }
    else if (point.x > topLeft.x + b.m_Width)
    {
        code |= RIGHT;
    }
    
    // check if point is above or below the bounds
    if (point.y < topLeft.y)
    {
        code |= TOP;
    }
    else if (point.y > topLeft.y + b.m_Height)
    {
        code |= BOTTOM;
    }

    return code;
}

bool TriangleBounds::raycast(glm::vec2 position)
{
    // Compute vectors
    glm::vec2 v0(m_X3 - m_X1, m_Y3 - m_Y1);
    glm::vec2 v1(m_X2 - m_X1, m_Y2 - m_Y1);
    glm::vec2 v2(position.x - m_X1, position.y - m_Y1);

    // Compute dot products
    float dot00 = dot(v0, v0);
    float dot01 = dot(v0, v1);
    float dot02 = dot(v0, v2);
    float dot11 = dot(v1, v1);
    float dot12 = dot(v1, v2);

    // Compute barycentric coordinates
    float invDenom = 1 / (dot00 * dot11 - dot01 * dot01);
    float u = (dot11 * dot02 - dot01 * dot12) * invDenom;
    float v = (dot00 * dot12 - dot01 * dot02) * invDenom;

    // Check if point is in triangle
    return (u >= 0.0f) && (v >= 0.0f) && (u + v < 1.0f);
}


glm::vec2 TriangleBounds::rotatePoint(float angle, glm::vec2 p, glm::vec2 o)
{
    float cos = cosf(angle);
    float sin = sinf(angle);
    glm::vec2 newVector(p.x, p.y);
    newVector.x -= o.x;
    newVector.y -= o.y;

    float newX = (float)((newVector.x * cos) - (newVector.y * sin));
    float newY = (float)((newVector.x * sin) - (newVector.y * cos));

    newVector = glm::vec2(newX + o.x, newY + o.y);
    return newVector;
}


Component* TriangleBounds::copy()
{
    return new TriangleBounds(m_Base, m_Height);
}

std::string TriangleBounds::serialise(int tabSize)
{
    std::string builder;
    builder.append(beginObjectProperty("TriangleBounds", tabSize));
    builder.append(addFloatProperty("Base", m_Base, tabSize + 1, true, true));
    builder.append(addFloatProperty("Height", m_Height, tabSize + 1, true, false));
    builder.append(closeObjectProperty(tabSize));

    return builder;
}

TriangleBounds* TriangleBounds::deseriaise()
{
    float base = Parser::consumeFloatProperty("Base");
    Parser::consume(',');
    float height = Parser::consumeFloatProperty("Height");
    Parser::consumeEndObjectProperty();
    deserialsiedTB = new TriangleBounds(base, height);
    return deserialsiedTB;
}


TriangleBounds* TriangleBounds::deserialsiedTB = nullptr;