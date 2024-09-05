#include "pch.h"
#include "Vector2.h"

Engine::Math::Vector2 Engine::Math::Vector2::Zero()
{
    return {0.f, 0.f};
}

Engine::Math::Vector2 Engine::Math::Vector2::One()
{
    return {1.f, 1.f};
}

Engine::Math::Vector2 Engine::Math::Vector2::Half()
{
    return {0.5f, 0.5f};
}

Engine::Math::Vector2 Engine::Math::Vector2::Right()
{
    return {1.f, 0.f};
}

Engine::Math::Vector2 Engine::Math::Vector2::Left()
{
    return {-1.f, 0.f};
}

Engine::Math::Vector2 Engine::Math::Vector2::Up()
{
    return {0.f, -1.f};
}

Engine::Math::Vector2 Engine::Math::Vector2::Down()
{
    return {0.f, 1.f};
}

Engine::Math::Vector2::Vector2()
    : D2D1_VECTOR_2F({0.f, 0.f})
{
}

Engine::Math::Vector2::Vector2(const float x, const float y)
    : D2D1_VECTOR_2F({x, y})
{
}

Engine::Math::Vector2::Vector2(const D2D1_SIZE_F size)
    : D2D1_VECTOR_2F({size.width, size.height})
{
}

Engine::Math::Vector2::Vector2(const D2D1_POINT_2F point)
    : D2D1_VECTOR_2F({point.x, point.y})
{
}

Engine::Math::Vector2::Vector2(const Animation::Center center)
    : D2D1_VECTOR_2F({center.x, center.y})
{
}

Engine::Math::Vector2::Vector2(const Input::Value value)
    : D2D1_VECTOR_2F({value.x, value.y})
{
}

Engine::Math::Vector2::operator D2D_POINT_2F() const
{
    return {x, y};
}

Engine::Math::Vector2::operator D2D_SIZE_F() const
{
    return {x, y};
}

Engine::Math::Vector2::operator D2D_SIZE_U() const
{
    return {static_cast<UINT32>(x), static_cast<UINT32>(y)};
}

Engine::Math::Vector2::operator tagSIZE() const
{
    return {static_cast<LONG>(x), static_cast<LONG>(y)};
}

Engine::Math::Vector2 Engine::Math::Vector2::operator+(const Vector2& other) const
{
    return {x + other.x, y + other.y};
}

Engine::Math::Vector2 Engine::Math::Vector2::operator-(const Vector2& other) const
{
    return {x - other.x, y - other.y};
}

Engine::Math::Vector2 Engine::Math::Vector2::operator*(const float scala) const
{
    return {x * scala, y * scala};
}

Engine::Math::Vector2 Engine::Math::Vector2::operator/(float scala) const
{
    if (scala == 0) return Vector2(0, 0);
    return {x / scala, y / scala};
}

bool Engine::Math::Vector2::operator==(const Vector2& other) const
{
    return (x == other.x && y == other.y);
}

bool Engine::Math::Vector2::operator!=(const Vector2& other) const
{
    return !(*this == other);
}

Engine::Math::Vector2 Engine::Math::Vector2::operator-() const
{
    return Vector2(-x, -y);
}

Engine::Math::Vector2& Engine::Math::Vector2::operator=(const Vector2& other)
{
    if (*this != other)
    {
        x = other.x;
        y = other.y;
    }
    return *this;
}

Engine::Math::Vector2& Engine::Math::Vector2::operator+=(const Vector2& other)
{
    x += other.x;
    y += other.y;
    return *this;
}

Engine::Math::Vector2& Engine::Math::Vector2::operator-=(const Vector2& other)
{
    x -= other.x;
    y -= other.y;
    return *this;
}

Engine::Math::Vector2& Engine::Math::Vector2::operator*=(const Vector2& other)
{
    x *= other.x;
    y *= other.y;
    return *this;
}

Engine::Math::Vector2& Engine::Math::Vector2::operator*=(float scala)
{
    x *= scala;
    y *= scala;
    return *this;
}

Engine::Math::Vector2& Engine::Math::Vector2::operator/=(float scala)
{
    x /= scala;
    y /= scala;
    return *this;
}

const Engine::Math::Vector2& Engine::Math::Vector2::operator()(const Vector2& vector1, const Vector2& vector2)
{
    *this = vector2 - vector1;
    return *this;
}

float Engine::Math::Vector2::SquareMagnitude() const
{
    return x * x + y * y;
}

float Engine::Math::Vector2::Magnitude() const
{
    float squareMagnitude = SquareMagnitude();
    if (squareMagnitude == 1.f || squareMagnitude == 0.f) return squareMagnitude;
    return Math::Helper::SquareRoot()(squareMagnitude);
}

Engine::Math::Vector2 Engine::Math::Vector2::Normalize() const
{
    const float squareMagnitude = SquareMagnitude();
    if (squareMagnitude == 0 || squareMagnitude == 1) return *this;
    return *this * Math::Helper::InverseSquareRoot()(squareMagnitude);
}

float Engine::Math::Vector2::DotProduct(const Vector2& lhs, const Vector2& rhs)
{
    return (lhs.x * rhs.x + lhs.y * rhs.y);
}

float Engine::Math::Vector2::DotProduct(const Vector2& other) const
{
    return (x * other.x + y * other.y);
}

float Engine::Math::Vector2::CrossProduct(const Vector2& lhs, const Vector2& rhs)
{
    return (lhs.x * rhs.y - lhs.y * rhs.x);
}

float Engine::Math::Vector2::CrossProduct(const Vector2& other) const
{
    return (x * other.y - y * other.x);
}

Engine::Math::Vector2 Engine::Math::Vector2::SplitProduct(const Vector2& other) const
{
    return SplitProduct(*this, other);
}

Engine::Math::Vector2 Engine::Math::Vector2::SplitProduct(const Vector2& lhs, const Vector2& rhs)
{
    return {lhs.x * rhs.x, lhs.y * rhs.y};
}

float Engine::Math::Vector2::Distance(const Vector2& lhs, const Vector2& rhs)
{
    return Math::Helper::SquareRoot()((lhs.x - rhs.x) * (lhs.x - rhs.x) + (lhs.y - rhs.y) * (lhs.y - rhs.y));
}

float Engine::Math::Vector2::Distance(const Vector2& other) const
{
    return Distance(*this, other);
}

Engine::Math::Vector2 Engine::Math::Vector2::Reflect(const Vector2& normal) const
{
    const Math::Vector2 normalVec = normal.Normalize();
    Vector2 reflectionVec = { x, y };
    reflectionVec -= normalVec * 2.f * reflectionVec.DotProduct(normalVec);
    return reflectionVec;
}

float Engine::Math::Vector2::AngleByAxisX(const Vector2& vector)
{
    return Helper::ArcTangent2()(vector.y, vector.x);
}

float Engine::Math::Vector2::AngleByAxisX() const
{
    return AngleByAxisX(*this);
}

Engine::Math::Vector2 Engine::Math::Vector2::Rotate(float degree) const
{
    float cosTheta = 0.f;
    float sinTheta = 0.f;
    Engine::Math::Helper::GetSinCos()(sinTheta, cosTheta, degree);

    return { x * cosTheta - y * sinTheta , x * sinTheta + y * cosTheta };
}

Engine::Math::Vector2 Engine::Math::Vector2::UnitVectorFromAngle(float degree)
{
    float cosTheta = 0.f;
    float sinTheta = 0.f;
    Engine::Math::Helper::GetSinCos()(sinTheta, cosTheta, degree);

    return { cosTheta, sinTheta };
}

Engine::Math::Vector2 Engine::Math::operator*(const float scala, const Vector2& vector)
{
    return vector * scala;
}

const Engine::Math::Vector2& Engine::Math::Vector2::Lerp(const Vector2& start, const Vector2& end, const float t)
{
    return { start.x + (end.x - start.x) * t, start.y + (end.y - start.y) * t };
}

const Engine::Math::Vector2& Engine::Math::Vector2::BezierInterpolate(const Vector2& p0, const Vector2& p1, const Vector2& p2, const float t)
{
    Vector2 p = (1.0f - t) * (1.0f - t) * p0;
    p += 2 * (1.0f - t) * t * p1;
    p += t * t * p2;

    return p;
}


