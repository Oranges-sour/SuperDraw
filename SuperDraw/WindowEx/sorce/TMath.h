//
//  TMath.h
//
//  Created by Oranges.
//  Copyright 2021 Oranges. All rights reserved.
//

#ifndef __MY_MATH_H__
#define __MY_MATH_H__

#include "Tools.h"
#include <cmath>


#define DEGREES_TO_RADIANS(__ANGLE__) ((__ANGLE__) * 0.01745329252f)
#define RADIANS_TO_DEGREES(__ANGLE__) ((__ANGLE__) * 57.29577951f)

/**
 *平方
 *@param t:要被平方的数
 *@return t的平方
 */
inline float POT(float t) { return t * t; }

constexpr float PI = 3.1415926f;

//三角函数,角度模式
class DEG {
public:
    static float tan(float d) { return tanf(DEGREES_TO_RADIANS(d)); }
    static float sin(float d) { return sinf(DEGREES_TO_RADIANS(d)); }
    static float cos(float d) { return cosf(DEGREES_TO_RADIANS(d)); }

    static float atan(float d) { return RADIANS_TO_DEGREES(atanf(d)); }
    static float asin(float d) { return RADIANS_TO_DEGREES(asinf(d)); }
    static float acos(float d) { return RADIANS_TO_DEGREES(acosf(d)); }
};

class TMath {
public:

    /**
     *两点间的距离
     *@param p1:第一个点
     *@param p2:第二个点
     *@return 距离
     */
    static float distance(const Vec2& p1, const Vec2& p2);

    /**
     *获得直线线段上,从起始点开始经过一段长度的坐标,以from到to为方向
     *@param from:起始点
     *@param to:方向
     *@return 坐标
     */
    static Vec2 getPosOnLine(const Vec2& from, const Vec2& to, float distance);

    /**
     *判断两个浮点数是否相等
     *@param num1:第一个数
     *@param num2:第二个数
     *@param delta:判断精度(如果两个数字相差大小不超过此值则认为是相等)
     *@return 是否相等
     */
    static bool float_equal(float num1, float num2, float delta = 0.000001f);

    /**
     *随机一个坐标,以position为中心点,x和y的偏移量在正负min到max之间
     *@param position:中心点
     *@param min:最小偏移量
     *@param max:最大偏移量
     *@return
     */
    static Vec2 randPos(const Vec2& position, float min, float max);

    /**
     *将float四舍五入一位到int
     *@param num:小数
     *@return 四舍五入后的整数
     */
    static int floatRoundInt(float num);
};

inline float TMath::distance(const Vec2& p1, const Vec2& p2)
{
    return sqrt(POT(p1.x - p2.x) + POT(p1.y - p2.y));
}

inline bool TMath::float_equal(float num1, float num2, float delta)
{
    return (abs(num1 - num2) <= delta);
}

inline int TMath::floatRoundInt(float num)
{
    return static_cast<int>(num + 0.5f);
}

#endif