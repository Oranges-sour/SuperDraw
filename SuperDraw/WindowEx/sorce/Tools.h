//
//  Tools.h
//
//  Created by Oranges.
//  Copyright 2021 Oranges. All rights reserved.
//

#ifndef __TOOLS_H__
#define __TOOLS_H__

class Vec2 {
public:
    Vec2();
    Vec2(const Vec2& other);
    Vec2(float x, float y);

    const Vec2 operator+(const Vec2& other) const;
    const Vec2 operator-(const Vec2& other) const;
    const Vec2 operator*(float f) const;
    const Vec2 operator/(float f) const;
    const Vec2 operator-() const;

    Vec2& operator+=(const Vec2& other);
    Vec2& operator-=(const Vec2& other);
    Vec2& operator*=(float f);
    Vec2& operator/=(float f);

    float x = 0;
    float y = 0;

    static Vec2 ZERO;
};

class Size {
public:
    Size();
    Size(const Size& other);
    Size(float width, float height);

    float width = 0;
    float height = 0;
};

class Rect {
public:
    Rect();
    Rect(const Rect& other);
    Rect(const Vec2& p0, float width, float height);
    Rect(float x, float y, float width, float height);
    Rect(const Vec2& p0, const Vec2& p1);

    //矩形是否包含参数点
    bool isInRect(const Vec2& p);
    //矩形是否包含参数矩形
    //bool isInRect(const Rect& otherRect);
    //矩形是否包含参数圆
    //bool isInRect(const Vec2& p, float radius);
    //矩形是否相交于参数矩形
    //bool isIntersect(const Rect& otherRect);
    //矩形是否相交于参数圆
    //bool isIntersect(const Vec2& p, float radius);

    Vec2 p0;
    float width = 0;
    float height = 0;
};

#endif
