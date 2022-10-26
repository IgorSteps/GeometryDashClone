#include "TriangleBounds.h"
#include "Parser.h"
#include "GameObject.h"

TriangleBounds::TriangleBounds(float base, float h)
{
    type = Triangle;
    m_Base = base;
    m_Height = h;
    m_HalfHeight = h / 2.0f;
    m_HalfWidth = base / 2.0f;
    m_EnclosingRadius = std::max(m_HalfHeight, m_HalfWidth);
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

void TriangleBounds::start()
{
    calculateTransform();
}

void TriangleBounds::calculateTransform()
{
    float rAngle = glm::radians(gameObj->transform->rotateion);
    glm::vec2 p1(gameObj->transform->position.x - m_HalfWidth, gameObj->transform->position.y + m_HalfHeight);  // bottom left
    glm::vec2 p2(gameObj->transform->position.x, gameObj->transform->position.y - m_HalfHeight);                // top
    glm::vec2 p3(gameObj->transform->position.x + m_HalfWidth, gameObj->transform->position.y + m_HalfHeight);  // bottom right

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
}

bool TriangleBounds::checkCollision(BoxBounds& b1, TriangleBounds& t2)
{
    if (t2.broadPhase(b1))
    {
        std::cout << "Broadphase collision\n";
        return t2.narrowPhase(b1);
    }

    return false;
}

bool TriangleBounds::broadPhase(BoxBounds& b1)
{
    float bRadius = b1.m_EnclosingRadius;
    float tRadius = m_EnclosingRadius;

    glm::vec2 dist(b1.gameObj->transform->position.x - m_X2, b1.gameObj->transform->position.y - this->gameObj->transform->position.y);

    float magSquared = pow(dist.x, 2) + pow(dist.y, 2);
    float radiiSquared = pow(bRadius + tRadius, 2);

    return magSquared <= radiiSquared;
}

bool TriangleBounds::narrowPhase(BoxBounds& b1)
{
    return true;
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