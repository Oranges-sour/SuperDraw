//
//  Tools.h
//
//  Created by Oranges.
//  E-mail 873516725@qq.com
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
    const Size operator*(float f) const;
    const Size operator/(float f) const;

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
    // bool isInRect(const Rect& otherRect);
    //矩形是否包含参数圆
    // bool isInRect(const Vec2& p, float radius);
    //矩形是否相交于参数矩形
    // bool isIntersect(const Rect& otherRect);
    //矩形是否相交于参数圆
    // bool isIntersect(const Vec2& p, float radius);

    Vec2 p0;
    float width = 0;
    float height = 0;
};

enum class FontWeight  //字体的粗细
{
    light = 300,   //细--默认
    medium = 500,  //中
    black = 900    //粗
};

enum class FontStyle  //文字样式
{
    normal = 0,  //直体--默认
    oblique,     //"oblique"系斜体
    italic,      //"italic"系斜体
};

enum class LineStyle  //线的两端点的样式
{
    flat,      //平整--默认
    round,     //圆角
    triangle,  //三角
};

class Color4B;
class Color4F;

class Color4B {
public:
    Color4B(int r = 0, int g = 0, int b = 0, int a = 0);
    Color4B(const Color4B& other);
    Color4B(const Color4F& other);

    int red;
    int green;
    int blue;
    int alpha;

public:
    static const Color4B WHITE;
};

class Color4F {
public:
    Color4F(float r = 0, float g = 0, float b = 0, float a = 0);
    Color4F(const Color4F& other);
    Color4F(const Color4B& other);

    float red;
    float green;
    float blue;
    float alpha;

public:
    static const Color4F WHITE;
};

#endif
