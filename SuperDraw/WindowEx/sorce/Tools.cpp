//
//  Tools.cpp
//
//  Created by Oranges.
//  E-mail 873516725@qq.com
//  Copyright 2021 Oranges. All rights reserved.
//

#include "Tools.h"

Vec2 Vec2::ZERO{0, 0};

Vec2::Vec2() {
    x = 0;
    y = 0;
}

Vec2::Vec2(const Vec2& other) {
    x = other.x;
    y = other.y;
}

Vec2::Vec2(float x, float y) {
    this->x = x;
    this->y = y;
}

const Vec2 Vec2::operator+(const Vec2& other) const {
    return Vec2{x + other.x, y + other.y};
}

const Vec2 Vec2::operator-(const Vec2& other) const {
    return Vec2{x - other.x, y - other.y};
}

const Vec2 Vec2::operator*(float f) const { return Vec2{x * f, y * f}; }

const Vec2 Vec2::operator/(float f) const { return Vec2{x / f, y / f}; }

const Vec2 Vec2::operator-() const { return Vec2{-x, -y}; }

Vec2& Vec2::operator+=(const Vec2& other) {
    x += other.x;
    y += other.y;
    return *this;
}

Vec2& Vec2::operator-=(const Vec2& other) {
    x -= other.x;
    y -= other.y;
    return *this;
}

Vec2& Vec2::operator*=(float f) {
    x *= f;
    y *= f;
    return *this;
}

Vec2& Vec2::operator/=(float f) {
    x /= f;
    y /= f;
    return *this;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

Size::Size() {}

Size::Size(const Size& other) {
    width = other.width;
    height = other.height;
}

Size::Size(float width, float height) {
    this->width = width;
    this->height = height;
}

const Size Size::operator*(float f) const {
    return Size{width * f, height * f};
}

const Size Size::operator/(float f) const {
    return Size{width / f, height / f};
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

Rect::Rect() {}

Rect::Rect(const Rect& other) {
    p0 = other.p0;
    width = other.width;
    height = other.height;
}

Rect::Rect(const Vec2& p0, float width, float height) {
    this->p0 = p0;
    this->width = width;
    this->height = height;
}

Rect::Rect(float x, float y, float width, float height) {
    p0 = Vec2(x, y);
    this->width = width;
    this->height = height;
}

Rect::Rect(const Vec2& p0, const Vec2& p1) {
    this->p0 = p0;
    this->width = p1.x - p0.x;
    this->height = p1.y - p0.y;
}

bool Rect::isInRect(const Vec2& p) {
    Vec2 p1 = p0 + Vec2(width, height);
    return (p.x >= p0.x && p.y >= p0.y && p.x <= p1.x && p.y <= p1.y);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////

Color4B::Color4B(int r, int g, int b, int a)
    : red(r), green(g), blue(b), alpha(a) {}

Color4B::Color4B(const Color4B& other)
    : red(other.red),
      green(other.green),
      blue(other.blue),
      alpha(other.alpha) {}

Color4B::Color4B(const Color4F& other) {
    red = static_cast<int>(other.red * 255);
    blue = static_cast<int>(other.blue * 255);
    green = static_cast<int>(other.green * 255);
    alpha = static_cast<int>(other.alpha * 255);
}

const Color4B Color4B::WHITE = Color4B(255, 255, 255, 255);

////////////////////////////////////////////////////////////////////////////////////////////////////////

Color4F::Color4F(float r, float g, float b, float a)
    : red(r), green(g), blue(b), alpha(a) {}

Color4F::Color4F(const Color4F& other)
    : red(other.red),
      green(other.green),
      blue(other.blue),
      alpha(other.alpha) {}

Color4F::Color4F(const Color4B& other) {
    red = other.red / 255.0f;
    blue = other.blue / 255.0f;
    green = other.green / 255.0f;
    alpha = other.alpha / 255.0f;
}

const Color4F Color4F::WHITE = Color4F(1.0f, 1.0f, 1.0f, 1.0f);
