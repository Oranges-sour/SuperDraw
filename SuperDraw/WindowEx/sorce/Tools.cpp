#include "Tools.h"

Vec2 Vec2::ZERO{0, 0};

Vec2::Vec2()
{
    x = 0;
    y = 0;
}

Vec2::Vec2(const Vec2& other)
{
    x = other.x;
    y = other.y;
}

Vec2::Vec2(float x, float y)
{
    this->x = x;
    this->y = y;
}

const Vec2 Vec2::operator+(const Vec2& other) const
{
    return Vec2{x + other.x, y + other.y};
}

const Vec2 Vec2::operator-(const Vec2& other) const
{
    return Vec2{x - other.x, y - other.y};
}

const Vec2 Vec2::operator*(float f) const { return Vec2{x * f, y * f}; }

const Vec2 Vec2::operator/(float f) const { return Vec2{x / f, y / f}; }

const Vec2 Vec2::operator-() const { return Vec2{-x, -y}; }

Vec2& Vec2::operator+=(const Vec2& other)
{
    x += other.x;
    y += other.y;
    return *this;
}

Vec2& Vec2::operator-=(const Vec2& other)
{
    x -= other.x;
    y -= other.y;
    return *this;
}

Vec2& Vec2::operator*=(float f)
{
    x *= f;
    y *= f;
    return *this;
}

Vec2& Vec2::operator/=(float f)
{
    x /= f;
    y /= f;
    return *this;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

Size::Size() {}

Size::Size(const Size& other)
{
    width = other.width;
    height = other.height;
}

Size::Size(float width, float height)
{
    this->width = width;
    this->height = height;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

Rect::Rect() {}

Rect::Rect(const Rect& other)
{
    p0 = other.p0;
    width = other.width;
    height = other.height;
}

Rect::Rect(const Vec2& p0, float width, float height)
{
    this->p0 = p0;
    this->width = width;
    this->height = height;
}

Rect::Rect(float x, float y, float width, float height)
{
    p0 = Vec2(x, y);
    this->width = width;
    this->height = height;
}

Rect::Rect(const Vec2& p0, const Vec2& p1)
{
    this->p0 = p0;
    this->width = p1.x - p0.x;
    this->height = p1.y - p0.y;
}

bool Rect::isInRect(const Vec2& p)
{
    Vec2 p1 = p0 + Vec2(width, height);
    return (p.x >= p0.x && p.y >= p0.y && p.x <= p1.x && p.y <= p1.y);
}
